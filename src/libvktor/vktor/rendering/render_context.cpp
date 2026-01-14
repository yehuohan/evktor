#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

const RenderContext::FnSwapchainRTT RenderContext::defaultFnSwapchainRTT =
    [](const Arg<Swapchain>& swapchain) -> Res<RenderTargetTable> {
    RenderTargetTable rtt{};
    // RT-0: Color
    auto res_color = rtt.addTarget(swapchain);
    OnErr(res_color);
    // RT-1: depth
    auto res_depth = rtt.addTarget(swapchain.a.api, swapchain.a.image_extent, VK_FORMAT_D32_SFLOAT);
    OnErr(res_depth);
    return Ok(std::move(rtt));
};

Res<RenderContext> RenderContext::from(const CoreApi& api, uint32_t frame_count, size_t thread_count) {
    RenderContext render_context(api, thread_count);
    render_context.frame_index = 0;
    for (uint32_t k = 0; k < frame_count; k++) {
        render_context.frames.push_back(RenderFrame(api, thread_count));
    }
    return Ok(std::move(render_context));
}

Res<RenderContext> RenderContext::from(const CoreApi& api,
                                       core::SwapchainState&& info,
                                       FnSwapchainRTT fn,
                                       size_t thread_count) {
    RenderContext render_context(api, thread_count);
    if (fn) {
        render_context.newSwapchainRTT = fn;
    } else {
        vktLogW("RenderContext can't be from a null FnSwapchainRTT. Use defaultFnSwapchainRTT.");
    }
    render_context.frame_index = 0;
    render_context.swapchain_state = newBox<SwapchainState>(std::move(info));
    auto res = render_context.reinitSwapchain();
    OnErr(res);
    return Ok(std::move(render_context));
}

RenderContext::RenderContext(RenderContext&& rhs) : RenderResource(rhs.api), api(rhs.api), thread_count(rhs.thread_count) {
    frame_index = rhs.frame_index;
    frame_actived = rhs.frame_actived;
    frames = std::move(rhs.frames);
    surface_extent = rhs.surface_extent;
    swapchain = std::move(rhs.swapchain);
    swapchain_state = std::move(rhs.swapchain_state);
    acquisition = std::move(rhs.acquisition);
}

Res<CRef<core::Swapchain>> RenderContext::reinitSwapchain() {
    // Re-initialize swapchain, must reset swapchain before info.into().
    swapchain.reset();
    auto res_swc = swapchain_state->into(api);
    OnErr(res_swc);
    swapchain = newBox<Swapchain>(res_swc.unwrap());
    surface_extent = swapchain->image_extent;
    // Re-initialize render frames
    for (uint32_t k = 0; k < swapchain->image_count; k++) {
        if (k >= frames.size()) {
            frames.push_back(RenderFrame(api, thread_count));
        }
        // Set swapchain render target table for render frames
        auto res_rtt = newSwapchainRTT(Arg<Swapchain>(*swapchain, k));
        OnErr(res_rtt);
        frames[k].setSwapchainRTT(newBox<RenderTargetTable>(res_rtt.unwrap()));
    }
    return Ok(newCRef(*swapchain));
}

bool RenderContext::updateSwapchain(bool force) {
    if (!swapchain || !swapchain_state) {
        return false;
    }
    VkSurfaceCapabilitiesKHR capalibities;
    if (VK_SUCCESS != vkGetPhysicalDeviceSurfaceCapabilitiesKHR(api, api, &capalibities)) {
        vktLogE("Failed to get surface capalibities to update swapchain");
        return false;
    }

    auto extent = capalibities.currentExtent;
    if (force || extent.width != swapchain->image_extent.width || extent.height != swapchain->image_extent.height) {
        api.waitIdle();
        framebuffers.clear();
        // Update swapchain info then reinit swapchain
        swapchain_state->setDesiredExtent(extent);
        swapchain_state->setOld(swapchain->take());
        reinitSwapchain();
        return true;
    }
    return false;
}

Res<Ref<core::CommandBuffer>> RenderContext::beginFrame() {
    auto& prev_frame = frames[frame_index];

    OnCheck(!frame_actived, "Please call endFrame to inactivate the frame");
    if (hasSwapchain()) {
        // Use previous frame's semaphore in current frame need ownership
        auto res_sem = prev_frame.acquireSemaphore();
        OnErr(res_sem);
        acquisition = newBox<Semaphore>(res_sem.unwrap());

        // Acquire next swapchain image
        auto res = swapchain->acquireNextImage(frame_index, *acquisition);
        if (res == VK_SUBOPTIMAL_KHR || res == VK_ERROR_OUT_OF_DATE_KHR) {
            if (updateSwapchain(res == VK_ERROR_OUT_OF_DATE_KHR)) {
                res = swapchain->acquireNextImage(frame_index, *acquisition);
            }
        }
        // After update swapchain and acquire image again, `res` should be success.
        if (res != VK_SUCCESS) {
            prev_frame.resetFrame();
        }
        OnRet(res, "Failed to acquire the next swapchain image to begin frame");
    } else {
        // Advance to next frame
        frame_index = (frame_index + 1) % frames.size();
    }
    OnCheck(frame_index < frames.size(), "The activated frame index {} is out of frames count {}", frame_index, frames.size());

    // Reset the frame to begin
    auto& frame = frames[frame_index];
    auto res_void = frame.resetFrame();
    OnErr(res_void);
    frame_actived = true;

    auto res_queue = api.graphicsQueue();
    OnErr(res_queue);
    return frame.requestCommandBuffer(res_queue.unwrap().get());
}

Res<Void> RenderContext::endFrame(VkSemaphore wait_semaphore) {
    auto& frame = frames[frame_index];

    OnCheck(frame_actived, "Please call beginFrame to activate the frame");
    if (hasSwapchain()) {
        auto res_queue = api.presentQueue();
        OnErr(res_queue);
        auto& queue = res_queue.unwrap().get();

        // Present swapchain image
        auto res = queue.present(*swapchain, frame_index, wait_semaphore);
        if (res == VK_SUBOPTIMAL_KHR || res == VK_ERROR_OUT_OF_DATE_KHR) {
            updateSwapchain();
        } else {
            OnRet(res, "Failed to present the activated swapchain image");
        }

        // Reback previous frame's semaphore to current frame with ownership
        if (acquisition) {
            frame.rebackSemaphore(std::move(*acquisition));
            acquisition.reset();
        }
    }
    frame_actived = false;
    return Ok(Void{});
}

Res<CRef<core::Semaphore>> RenderContext::submit(const core::CommandBuffer& cmdbuf) {
    auto& frame = frames[frame_index];
    auto res_queue = api.graphicsQueue();
    OnErr(res_queue);
    auto& queue = res_queue.unwrap().get();

    auto res_fence = frame.requestFence();
    OnErr(res_fence);
    auto& fence = res_fence.unwrap().get();
    auto res_semaphore = frame.requestSemaphore();
    OnErr(res_semaphore);
    auto& signal_semaphore = res_semaphore.unwrap().get();

    auto submit_info = Itor::SubmitInfo();
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = cmdbuf;
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = signal_semaphore;
    if (hasSwapchain()) {
        // Must render into swapchain image with graphics pipeline
        VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submit_info.waitSemaphoreCount = 1;
        submit_info.pWaitSemaphores = *acquisition;
        submit_info.pWaitDstStageMask = wait_stages;
    }
    queue.submit({submit_info}, fence);

    return Ok(newCRef(signal_semaphore));
}

Ref<RenderFrame> RenderContext::getFrame() {
    OnCheck(frame_index < frames.size(), "The activated frame index {} is out of frames count {}", frame_index, frames.size());
    return newRef(frames[frame_index]);
}

NAMESPACE_END(vkt)
