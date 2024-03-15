#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<Ref<Swapchain>> RenderContext::add(SwapchainState& info) {
    auto res = info.into(api);
    OnErr(res);
    swapchain.reset();
    swapchain = newBox<Swapchain>(res.unwrap());
    for (uint32_t k = 0; k < swapchain->image_count; k++) {
        frames.push_back(RenderFrame(api, thread_count));
    }
    return Ok(newRef(*swapchain));
}

void RenderContext::activateRenderFrame(uint32_t index) {
    frame_index = index;
}

Res<Ref<RenderFrame>> RenderContext::getRenderFrame() {
    if (frame_index < frames.size()) {
        return Ok(newRef(frames[frame_index]));
    } else {
        return Er("The activated frame index is out of range");
    }
}

NAMESPACE_END(vkt)
