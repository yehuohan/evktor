#include "render_subpass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderSubpass::RenderSubpass(RenderSubpass&& rhs)
    : name(rhs.name)
    , vert_shader(std::move(rhs.vert_shader))
    , frag_shader(std::move(rhs.frag_shader)) {
    state = std::move(rhs.state);
};

RenderSubpass& RenderSubpass::setRTInputs(const Vector<uint32_t>& inputs) {
    state.inputs = inputs;
    return *this;
}

RenderSubpass& RenderSubpass::setRTColors(const Vector<uint32_t>& colors) {
    state.colors = colors;
    return *this;
}

RenderSubpass& RenderSubpass::setRTDepthStencil(uint32_t depthstencil) {
    state.depthstencil = depthstencil;
    return *this;
}

NAMESPACE_END(vkt)
