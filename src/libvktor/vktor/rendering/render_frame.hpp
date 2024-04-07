#pragma once
#include "render_target.hpp"
#include "vktor/base/api.hpp"

NAMESPACE_BEGIN(vkt)

/**
 * @brief Render frame
 *
 * One render frame hold descriptors, command buffers for each thread.
 */
class RenderFrame : private NonCopyable {
private:
    const BaseApi& api;

    const size_t thread_count = 1;
    /** Render target table for swapchain */
    Box<RenderTargetTable> swapchain_rtt = nullptr;
    /** Map queue family index to command pool */
    Vector<HashMap<uint32_t, core::CommandPool>> cmd_pools{};
    /** Map DescriptorSetLayout to DescriptorPooler */
    Vector<HashMap<size_t, core::DescriptorPooler>> desc_poolers{};
    /** Map DescriptorSetLayout + DescriptorPool + DescriptorInfo to DescriptorSet */
    Vector<HashMap<size_t, core::DescriptorSet>> desc_sets{};
    core::FencePool fence_pool;
    core::SemaphorePool semaphore_pool;
    core::EventPool event_pool;

public:
    explicit RenderFrame(const BaseApi& api, size_t thread_count);
    RenderFrame(RenderFrame&&);

    void setSwapchainRTT(Box<RenderTargetTable>&& rtt = nullptr);
    Res<CRef<RenderTargetTable>> getSwapchainRTT() const;
    Res<Void> resetFrame();
    /**
     * @brief Reset all descriptor pools and sets within thread index
     */
    void resetDescriptorSets(size_t thread_index = 0);
    /**
     * @brief Request one command buffer from this frame
     *
     * Reset command buffer via vkResetCommandBuffer or vkBeginCommandBuffer
     */
    Res<Ref<core::CommandBuffer>> requestCommandBuffer(const core::Queue& queue, size_t thread_index = 0);
    /**
     * @brief Request one descriptor set from an available descriptor pool that is got from pooler
     */
    Res<Ref<core::DescriptorSet>> requestDescriptorSet(const core::DescriptorSetLayout& desc_setlayout,
                                                       const core::DescriptorInfo& desc_info,
                                                       size_t thread_index = 0);
    /**
     * @brief Request one descriptor set from an available descriptor pool that is got from pooler
     */
    Res<Ref<core::DescriptorSet>> requestDescriptorSet(const core::DescriptorSetLayout& desc_setlayout,
                                                       const core::DescriptorArrayInfo& desc_info,
                                                       size_t thread_index = 0);

    inline Res<CRef<core::Fence>> requestFence() {
        return fence_pool.request();
    }
    inline Res<core::Fence> acquireFence() {
        return fence_pool.acquire();
    }
    inline void rebackFence(core::Fence&& fence) {
        return fence_pool.reback(std::move(fence));
    }
    inline Res<CRef<core::Semaphore>> requestSemaphore() {
        return semaphore_pool.request();
    }
    inline Res<core::Semaphore> acquireSemaphore() {
        return semaphore_pool.acquire();
    }
    inline void rebackSemaphore(core::Semaphore&& semaphore) {
        return semaphore_pool.reback(std::move(semaphore));
    }
    inline Res<CRef<core::Event>> requestEvent() {
        return event_pool.request();
    }
    inline Res<core::Event> acquireEvent() {
        return event_pool.acquire();
    }
    inline void rebackEvent(core::Event&& event) {
        return event_pool.reback(std::move(event));
    }

private:
    Res<Ref<core::DescriptorPool>> requestDescriptorPool(const core::DescriptorSetLayout& desc_setlayout, size_t thread_index);
    /** T should be DescriptorInfo or DescriptorArrayInfo */
    template <typename T>
    Res<Ref<core::DescriptorSet>> requestDescriptorSet(const core::DescriptorSetLayout& desc_setlayout,
                                                       core::DescriptorPool& desc_pool,
                                                       const T& desc_info,
                                                       size_t thread_index);
};

NAMESPACE_END(vkt)
