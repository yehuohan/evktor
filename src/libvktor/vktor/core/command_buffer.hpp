#pragma once
#include "__builder.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct CommandPool;

/**
 * @brief Command buffer
 *
 * `CommandBuffer` must be allocated with `CommandPool::requestCommandBuffer()`.
 */
struct CommandBuffer : public BuiltResource<VkCommandBuffer, VK_OBJECT_TYPE_COMMAND_BUFFER, Device> {
    const CommandPool& command_pool;

    enum class Level {
        Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
    };

    CommandBuffer(const CommandPool& command_pool, Name&& name = "CommandBuffer");
    CommandBuffer(CommandBuffer&&);
    ~CommandBuffer();

    VkResult begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) const;
    VkResult end() const;

    void cmdMemoryBarrier(VkPipelineStageFlags src_stage_mask,
                          VkPipelineStageFlags dst_stage_mask,
                          uint32_t barrier_count,
                          const VkMemoryBarrier* barriers,
                          VkDependencyFlags flags = 0) const;
    void cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage_mask,
                                VkPipelineStageFlags dst_stage_mask,
                                uint32_t barrier_count,
                                const VkBufferMemoryBarrier* barriers,
                                VkDependencyFlags flags = 0) const;
    void cmdImageMemoryBarrier(VkPipelineStageFlags src_stage_mask,
                               VkPipelineStageFlags dst_stage_mask,
                               uint32_t barrier_count,
                               const VkImageMemoryBarrier* barriers,
                               VkDependencyFlags flags = 0) const;
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
