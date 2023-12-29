#pragma once
#include "api.hpp"
#include "vktor/core/command_pool.hpp"
#include "vktor/core/descriptor_pool.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/queue.hpp"
#include <tuple>

NAMESPACE_BEGIN(vkt)

using namespace core;

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
