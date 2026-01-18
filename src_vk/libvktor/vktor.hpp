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
    core::CoreApi& createApi(std::function<void(core::InstanceState&)> update_inst = nullptr,
                             std::function<VkSurfaceKHR(const core::Instance& instance)> create_surface = nullptr,
                             std::function<void(const core::Instance&, core::PhysicalDeviceState&)> update_phy_dev = nullptr,
                             std::function<void(const core::PhysicalDevice&, core::DeviceState&)> update_dev = nullptr);

public:
    // Box<RenderGraph> newRdg();
    inline Box<RenderContext> newRctx(uint32_t frame_count = 3, size_t thread_count = 1) const;
    inline Box<RenderContext> newRctx(core::SwapchainState&& info,
                                      RenderContext::FnSwapchainRTT fn = nullptr,
                                      size_t thread_count = 1) const;

public:
    inline Texture2D newTexture2D(VkFormat format,
                                  const VkExtent2D& extent,
                                  Texture2D::Usage usage,
                                  uint32_t mip_levels = 1,
                                  Texture2D::Sample samples = Texture2D::S1) const;
    inline core::Buffer newStorageBuffer(VkDeviceSize size) const;
    inline core::Buffer newUniformBuffer(VkDeviceSize size) const;
    inline core::Buffer newVertexBuffer(VkDeviceSize size) const;
    inline core::Buffer newIndexBuffer(VkDeviceSize size) const;
    inline core::Buffer newStagingBuffer(VkDeviceSize size) const;
};

inline Box<RenderContext> Vktor::newRctx(uint32_t frame_count, size_t thread_count) const {
    return newBox<RenderContext>(RenderContext::from(*api, frame_count, thread_count).unwrap());
}

inline Box<RenderContext> Vktor::newRctx(core::SwapchainState&& info,
                                         RenderContext::FnSwapchainRTT fn,
                                         size_t thread_count) const {
    return newBox<RenderContext>(RenderContext::from(*api, std::move(info), fn, thread_count).unwrap());
}

inline Texture2D Vktor::newTexture2D(VkFormat format,
                                     const VkExtent2D& extent,
                                     Texture2D::Usage usage,
                                     uint32_t mip_levels,
                                     Texture2D::Sample samples) const {
    return Texture2D::from(*api, format, extent, usage, mip_levels, samples).unwrap();
}

inline core::Buffer Vktor::newStorageBuffer(VkDeviceSize size) const {
    return core::BufferState{}
        .setSize(size)
        .setUsage(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
        .into(*api)
        .unwrap();
}

inline core::Buffer Vktor::newUniformBuffer(VkDeviceSize size) const {
    return core::BufferState{}
        .setSize(size)
        .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
        .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
        .into(*api)
        .unwrap();
}

inline core::Buffer Vktor::newVertexBuffer(VkDeviceSize size) const {
    return core::BufferState{}
        .setSize(size)
        .setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
        .into(*api)
        .unwrap();
}

inline core::Buffer Vktor::newIndexBuffer(VkDeviceSize size) const {
    return core::BufferState{}
        .setSize(size)
        .setUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
        .into(*api)
        .unwrap();
}

inline core::Buffer Vktor::newStagingBuffer(VkDeviceSize size) const {
    return core::BufferState{}
        .setSize(size)
        .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
        .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
        .into(*api)
        .unwrap();
}

NAMESPACE_END(vkt)
