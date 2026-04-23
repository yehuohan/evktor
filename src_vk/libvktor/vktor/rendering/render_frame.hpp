#pragma once
#include "render_target.hpp"
#include "vktor/core/command_buffer.hpp"
#include "vktor/core/command_pool.hpp"
#include "vktor/core/descriptor_pool.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/event.hpp"
#include "vktor/core/fence.hpp"
#include "vktor/core/semaphore.hpp"

NAMESPACE_BEGIN(vkt)

/**
 * @brief Render frame
 *
 * One render frame hold descriptors, command buffers for each thread.
 */
class RenderFrame : private NonCopyable {
private:
    const core::CoreApi& api;

    const size_t thread_count = 1;
    /** Map queue family index to command pool */
    Vector<HashMap<uint32_t, core::CommandPool>> cmd_pools{};
    /** Map DescriptorSetLayout to DescriptorPooler */
    Vector<HashMap<size_t, core::DescriptorPooler>> desc_poolers{};
    /** Map DescriptorSetLayout + DescriptorPool + DescriptorInfo to DescriptorSet */
    Vector<HashMap<size_t, Box<core::DescriptorSet>>> desc_sets{};
    core::FencePool fence_pool;
    core::SemaphorePool semaphore_pool;
    core::EventPool event_pool;

public:
    explicit RenderFrame(const core::CoreApi& api, size_t thread_count);
    RenderFrame(RenderFrame&&);

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
    Res<CRef<core::CommandBuffer>> requestCommandBuffer(const core::Queue& queue,
                                                        const String& cmd_name = "Command",
                                                        size_t thread_index = 0);
    /**
     * @brief Request one descriptor set from an available descriptor pool that is got from pooler
     *
     * To return the referrence of the DescriptorSet, store DescriptorSet inside Box.
     */
    Res<CRef<core::DescriptorSet>> requestDescriptorSet(const core::DescriptorSetLayout& desc_setlayout,
                                                        const core::DescriptorInfo& desc_info,
                                                        const String& desc_name = "Descriptor",
                                                        size_t thread_index = 0);

private:
    /**
     * @brief Request one descriptor pool
     *
     * DescriptorPool will only be referrenced inside RenderFrame, so can store DescriptorPool without Box.
     */
    Res<Ref<core::DescriptorPool>> requestDescriptorPool(const core::DescriptorSetLayout& desc_setlayout,
                                                         String&& name = "Descriptor#Pool",
                                                         size_t thread_index = 0);

public:
    inline Res<CRef<core::Fence>> requestFence(String&& name = "Fence") {
        return fence_pool.request(std::move(name));
    }
    inline Res<core::Fence> acquireFence(String&& name = "Fence") {
        return fence_pool.acquire(std::move(name));
    }
    inline void rebackFence(core::Fence&& fence) {
        return fence_pool.reback(std::move(fence));
    }
    inline Res<CRef<core::Semaphore>> requestSemaphore(String&& name = "Semaphore") {
        return semaphore_pool.request(std::move(name));
    }
    inline Res<core::Semaphore> acquireSemaphore(String&& name = "Semaphore") {
        return semaphore_pool.acquire(std::move(name));
    }
    inline void rebackSemaphore(core::Semaphore&& semaphore) {
        return semaphore_pool.reback(std::move(semaphore));
    }
    inline Res<CRef<core::Event>> requestEvent(String&& name = "Event") {
        return event_pool.request(std::move(name));
    }
    inline Res<core::Event> acquireEvent(String&& name = "Event") {
        return event_pool.acquire(std::move(name));
    }
    inline void rebackEvent(core::Event&& event) {
        return event_pool.reback(std::move(event));
    }

public:
    void watchStatus() const;
};

NAMESPACE_END(vkt)
