#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

void RenderContext::add(Swapchain&& _swapchain) {
    swapchain.reset();
    swapchain = newBox<Swapchain>(std::move(_swapchain));
    for (uint32_t k = 0; k < swapchain->image_count; k++) {
        frames.push_back(RenderFrame(api, thread_count));
    }
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
