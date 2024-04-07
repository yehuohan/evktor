#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

const RenderContext::FnSwapchainRTT RenderContext::defaultFnSwapchainRTT =
    [](const Arg<Swapchain>& swapchain) -> Res<RenderTargetTable> {
    Vector<RenderTarget> rts;
    // RT-0: Color
    auto res_color = RenderTarget::from(swapchain);
    OnErr(res_color);
    rts.push_back(res_color.unwrap());
    // RT-1: depth
    auto res_depth = RenderTarget::from(swapchain.a.device, swapchain.a.image_extent, VK_FORMAT_D32_SFLOAT);
    OnErr(res_depth);
    rts.push_back(res_depth.unwrap());
    return RenderTargetTable::from(std::move(rts));
};

Res<RenderContext> RenderContext::from(const BaseApi& api, uint32_t frame_count, size_t thread_count) {
    RenderContext render_context(api, thread_count);
    render_context.frame_index = 0;
    for (uint32_t k = 0; k < frame_count; k++) {
        render_context.frames.push_back(RenderFrame(api, thread_count));
    }
    return Ok(std::move(render_context));
}

Res<RenderContext> RenderContext::from(const BaseApi& api,
                                       const core::SwapchainState& info,
                                       FnSwapchainRTT fn,
                                       size_t thread_count) {
    RenderContext render_context(api, thread_count);
    if (fn) {
        render_context.createSwapchainRTT = fn;
    } else {
        vktLogW("RenderContext can't be from a null FnSwapchainRTT. Use defaultFnSwapchainRTT.");
    }
    auto res = render_context.reinit(info);
    OnErr(res);
    return Ok(std::move(render_context));
}

RenderContext::RenderContext(RenderContext&& rhs) : api(rhs.api), thread_count(rhs.thread_count) {
    frame_index = rhs.frame_index;
    frame_actived = rhs.frame_actived;
    frames = std::move(rhs.frames);
    swapchain = std::move(rhs.swapchain);
    acquisition = std::move(rhs.acquisition);
}

Res<CRef<core::Swapchain>> RenderContext::reinit(const core::SwapchainState& info) {
    auto res = info.into(api);
    OnErr(res);
    // Re-initialize swapchain
    swapchain.reset();
    swapchain = newBox<Swapchain>(res.unwrap());
    // Re-initialize render frames
    frames.clear();
    for (uint32_t k = 0; k < swapchain->image_count; k++) {
        frames.push_back(RenderFrame(api, thread_count));
        // Set swapchain render target table for render frames
        Arg arg(*swapchain);
        arg.image_index = k;
        auto res_rtt = createSwapchainRTT(arg);
        OnErr(res_rtt);
        frames.back().setSwapchainRTT(newBox<RenderTargetTable>(res_rtt.unwrap()));
    }
    frame_index = 0;
    return Ok(newCRef(*swapchain));
}

Res<Ref<core::CommandBuffer>> RenderContext::beginFrame() {
    auto& prev_frame = frames[frame_index];

    OnCheck(!frame_actived, "Please call endFrame to inactivate the frame");
    if (hasSwapchain()) {
        // Use previous frame's semaphore from in current frame need ownership
        auto res = prev_frame.acquireSemaphore();
        OnErr(res);
        acquisition = newBox<Semaphore>(res.unwrap());
        // Acquire next swapchain image
        auto ret = swapchain->acquireNextImage(frame_index, *acquisition);
        if (ret == VK_SUBOPTIMAL_KHR || ret == VK_ERROR_OUT_OF_DATE_KHR) {
            return Er("Need to reinit swapchain");
        }
        OnRet(ret, "Failed to acquire the next swapchain image to begin frame");
    } else {
        // Advance to next frame
        frame_index = (frame_index + 1) % frames.size();
    }
    OnCheck(frame_index < frames.size(), "The activated frame index {} is out of frames count {}", frame_index, frames.size());

    // Reset the frame to begin
    auto& frame = frames[frame_index];
    {
        auto res = frame.resetFrame();
        OnErr(res);
    }
    frame_actived = true;

    auto res = api.graphicsQueue();
    OnErr(res);
    auto& queue = res.unwrap().get();
    return frame.requestCommandBuffer(queue);
}

Res<Void> RenderContext::endFrame(VkSemaphore wait_semaphore) {
    auto& frame = frames[frame_index];

    OnCheck(frame_actived, "Please call beginFrame to activate the frame");
    if (hasSwapchain()) {
        auto res = api.presentQueue();
        OnErr(res);
        auto& queue = res.unwrap().get();
        auto ret = queue.present(*swapchain, frame_index, wait_semaphore);
        if (ret == VK_SUBOPTIMAL_KHR || ret == VK_ERROR_OUT_OF_DATE_KHR) {
            return Er("Need to reinit swapchain");
        }
        OnRet(ret, "Failed to present the activated swapchain image");
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
    auto res = api.graphicsQueue();
    OnErr(res);
    auto& queue = res.unwrap().get();
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
