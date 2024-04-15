/**
 * @file vktor.hpp
 * @brief Graphics framework
 *
 * - Only support Vulkan
 * - Featured with state api: `auto xxx = XXXState().into().unwrap()` and
 *   static constructor api: `auto xxx = XXX::from().unwrap()`
 * - Avoid crash: wrap unexpected returns/results/errors with Res for custom processing
 *
 * @author yehuohan@qq.com
 */
#pragma once
#include "vktor/rendering/render_context.hpp"

NAMESPACE_BEGIN(vkt)

class Vktor {
public:
    Box<core::CoreApi> api = nullptr;

public:
    operator core::CoreApi&() {
        OnCheck(api, "CoreApi is invalid");
        return *api;
    }

    // Box<RenderGraph> newRdg();
    inline Box<RenderContext> newRctx(uint32_t frame_count = 3, size_t thread_count = 1) const {
        return newBox<RenderContext>(RenderContext::from(*api, frame_count, thread_count).unwrap());
    }
    inline Box<RenderContext> newRctx(core::SwapchainState&& info,
                                      RenderContext::FnSwapchainRTT fn = nullptr,
                                      size_t thread_count = 1) const {
        return newBox<RenderContext>(RenderContext::from(*api, std::move(info), fn, thread_count).unwrap());
    }

    inline Box<Texture2D> newTex(VkFormat format,
                                 const VkExtent2D& extent,
                                 Texture2D::Usage usage,
                                 uint32_t mip_levels = 1,
                                 Texture2D::Sample samples = Texture2D::S1) const {
        return newBox<Texture2D>(Texture2D::from(*api, format, extent, usage, mip_levels, samples).unwrap());
    }
};

NAMESPACE_END(vkt)
