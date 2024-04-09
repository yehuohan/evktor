/**
 * @file vktor.hpp
 * @brief Vulkan graphics framework
 *
 * @author yehuohan@qq.com
 */
#pragma once
#include "vktor/base/api.hpp"
#include "vktor/rendering/render_context.hpp"

NAMESPACE_BEGIN(vkt)

class Vktor {
public:
    BaseApi api{};
    // Res<RenderContext> createRctx();
    // Res<RenderGraph> createRdg();
};

NAMESPACE_END(vkt)
