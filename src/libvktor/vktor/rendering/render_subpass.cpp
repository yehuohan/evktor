#include "render_subpass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderSubpass::RenderSubpass(RenderSubpass&& rhs) {
    shaders = std::move(rhs.shaders);
    info = std::move(rhs.info);
};

NAMESPACE_END(vkt)
