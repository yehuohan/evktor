#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<RenderContext> RenderContext::from(const BaseApi& api, uint32_t frame_count, size_t thread_count) {
    RenderContext render_context(api, thread_count);
    render_context.frame_index = 0;
    for (uint32_t k = 0; k < frame_count; k++) {
        render_context.frames.push_back(RenderFrame(api, thread_count));
    }
    return Ok(std::move(render_context));
}

Res<RenderContext> RenderContext::from(const BaseApi& api, const core::SwapchainState& info, size_t thread_count) {
    RenderContext render_context(api, thread_count);
    auto res = render_context.reinit(info);
    OnErr(res);
    return Ok(std::move(render_context));
}

RenderContext::RenderContext(RenderContext&& rhs) : api(rhs.api), thread_count(rhs.thread_count) {
    frame_index = rhs.frame_index;
    rhs.frame_index = 0;
    frames = std::move(rhs.frames);
    swapchain = std::move(rhs.swapchain);
}

Res<CRef<core::Swapchain>> RenderContext::reinit(const core::SwapchainState& info) {
    auto res = info.into(api);
    OnErr(res);
    // Re-initialize swapchain
    swapchain.reset();
    swapchain = newBox<Swapchain>(res.unwrap());
    // Re-initialize RenderFrame array
    frames.clear();
    for (uint32_t k = 0; k < swapchain->image_count; k++) {
        frames.push_back(RenderFrame(api, thread_count));
    }
    frame_index = 0;
    return Ok(newCRef(*swapchain));
}

void RenderContext::activateRenderFrame(uint32_t index) {
    frame_index = index;
}

Res<Ref<RenderFrame>> RenderContext::getFrame() {
    if (frame_index < frames.size()) {
        return Ok(newRef(frames[frame_index]));
    } else {
        return Er("The activated frame index is out of range");
    }
}

NAMESPACE_END(vkt)
