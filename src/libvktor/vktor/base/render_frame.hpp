#pragma once
#include "api.hpp"
#include "vktor/core/buffer.hpp"
#include "vktor/core/command_pool.hpp"
#include "vktor/core/descriptor_pool.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"
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
    explicit RenderFrame(const BaseApi& base_api, size_t thread_count = 1);

    void reset();
    /**
     * @brief Free all descriptor pools and sets within thread index
     */
    void freeDescriptorSets(uint32_t thread_index = 0);
    /**
     * @brief Request one command buffer from this frame
     *
     * Reset command buffer via vkResetCommandBuffer or vkBeginCommandBuffer
     */
    Res<Ref<CommandBuffer>> requestCommandBuffer(const Queue& queue, uint32_t thread_index = 0);
    /**
     * @brief Request one descriptor set from an available descriptor pool that is got from pooler
     */
    Res<Ref<DescriptorSet>> requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                 const DescriptorInfo& desc_info,
                                                 uint32_t thread_index = 0);
};

NAMESPACE_END(vkt)
