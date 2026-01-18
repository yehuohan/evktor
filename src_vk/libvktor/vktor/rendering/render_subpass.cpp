#include "render_subpass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderSubpass::RenderSubpass(RenderSubpass&& rhs)
    : vert_shader(std::move(rhs.vert_shader))
    , frag_shader(std::move(rhs.frag_shader)) {
    state = std::move(rhs.state);
};

NAMESPACE_END(vkt)
