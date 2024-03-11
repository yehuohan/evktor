#include "render_subpass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderSubpass::RenderSubpass(RenderSubpass&& rhs) : vert(std::move(rhs.vert)), frag(std::move(rhs.frag)) {
    info = std::move(rhs.info);
};

NAMESPACE_END(vkt)
