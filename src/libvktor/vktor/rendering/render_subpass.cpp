#include "render_subpass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderSubpass::RenderSubpass(RenderSubpass&& rhs) {
    shaders = std::move(rhs.shaders);
    state = std::move(rhs.state);
};

NAMESPACE_END(vkt)
