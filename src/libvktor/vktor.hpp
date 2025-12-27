/**
 * @file vktor.hpp
 * @brief Vulkan based graphics framework
 *
 * Features:
 * - Requires: Vulkan >= v1.3
 * - No crash: wrap unexpected returns/results/errors with `Res`
 * - Module `core`: wrap Vulkan handles inside core handles with RAII
 *      * `CoreApi`: `auto xxx = XXXState().into(CoreApi).unwrap()` and `auto xxx = XXX::from(CoreApi, XXXState).unwrap()`
 * - Module `base`: advanced wrap core handles with more functionalities for Vulkan handles
 * - Module `rendering`: graphics rendering with `core` and `base`
 *
 * @author yehuohan@qq.com
 */
#pragma once
#include "vktor/rendering/render_context.hpp"

NAMESPACE_BEGIN(vkt)

class Vktor : private NonCopyable, private NonMoveable {
public:
    Box<core::CoreApi> api = nullptr;

public:
    operator core::CoreApi&() {
        OnCheck(api, "CoreApi is invalid");
        return *api;
    }

    /**
     * @brief Create a default CoreApi
     */
    core::CoreApi& createApi(const Vector<const char*>& inst_exts = {},
                             const Vector<const char*>& dev_exts = {},
                             std::function<VkSurfaceKHR(const core::Instance& instance)> create_surface = nullptr);

public:
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
