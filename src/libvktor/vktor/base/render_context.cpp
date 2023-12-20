#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

void RenderContext::addRenderFrames(uint32_t count) {
    if (count > frames.size()) {
        frames.clear();
        for (uint32_t k = 0; k < count; k++) {
            frames.push_back(newBox<RenderFrame>(api));
        }
    }
}

vkt::RenderFrame& RenderContext::getRenderFrame() {
    assert(frame_index < frames.size() && "The activated frame index is out of range");
    return *frames[frame_index];
}

void RenderContext::activateRenderFrame(uint32_t index) {
    assert(frame_index < frames.size() && "The frame index to activate is out of range");
    frame_index = index;
}

NAMESPACE_END(vkt)
