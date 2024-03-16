#pragma once
#include "vktor/base/api.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

/**
 * @brief Render frame
 *
 * One render frame hold descriptors, command buffers for each thread.
 */
class RenderFrame : private NonCopyable {
private:
    const BaseApi& api;

    const size_t thread_count = 1;
    /** Map queue family index to command pool */
    Vector<HashMap<uint32_t, CommandPool>> cmd_pools{};
    /** Map DescriptorSetLayout to DescriptorPooler */
    Vector<HashMap<size_t, DescriptorPooler>> desc_poolers{};
    /** Map DescriptorSetLayout + DescriptorPool + DescriptorInfo to DescriptorSet */
    Vector<HashMap<size_t, DescriptorSet>> desc_sets{};
    FencePool fence_pool;
    SemaphorePool semaphore_pool;
    EventPool event_pool;

public:
    explicit RenderFrame(const BaseApi& api, size_t thread_count);
    RenderFrame(RenderFrame&&);

    void reset();
    /**
     * @brief Free all descriptor pools and sets within thread index
     */
    void freeDescriptorSets(size_t thread_index = 0);
    /**
     * @brief Request one command buffer from this frame
     *
     * Reset command buffer via vkResetCommandBuffer or vkBeginCommandBuffer
     */
    Res<Ref<CommandBuffer>> requestCommandBuffer(const Queue& queue, size_t thread_index = 0);
    /**
     * @brief Request one descriptor set from an available descriptor pool that is got from pooler
     */
    Res<Ref<DescriptorSet>> requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                 const DescriptorInfo& desc_info,
                                                 size_t thread_index = 0);
    /**
     * @brief Request one descriptor set from an available descriptor pool that is got from pooler
     */
    Res<Ref<DescriptorSet>> requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                 const DescriptorArrayInfo& desc_info,
                                                 size_t thread_index = 0);

    inline Res<Ref<Fence>> requestFence() {
        return fence_pool.request();
    }
    inline Res<Ref<Semaphore>> requestSemaphore() {
        return semaphore_pool.request();
    }
    inline Res<Ref<Event>> requestEvent() {
        return event_pool.request();
    }

private:
    Res<Ref<DescriptorPool>> requestDescriptorPool(const DescriptorSetLayout& desc_setlayout, size_t thread_index);
    /** T should be DescriptorInfo or DescriptorArrayInfo */
    template <typename T>
    Res<Ref<DescriptorSet>> requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                 const T& desc_info,
                                                 DescriptorPool& desc_pool,
                                                 size_t thread_index);
};

NAMESPACE_END(vkt)
