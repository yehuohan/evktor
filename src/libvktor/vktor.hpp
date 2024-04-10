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

    Box<RenderContext> createRctx(uint32_t frame_count = 3, size_t thread_count = 1) {
        return newBox<RenderContext>(RenderContext::from(api, frame_count, thread_count).unwrap());
    }
    Box<RenderContext> createRctx(core::SwapchainState&& info,
                                  RenderContext::FnSwapchainRTT fn = nullptr,
                                  size_t thread_count = 1) {
        return newBox<RenderContext>(RenderContext::from(api, std::move(info), fn, thread_count).unwrap());
    }
    // Box<RenderGraph> createRdg();
};

NAMESPACE_END(vkt)
