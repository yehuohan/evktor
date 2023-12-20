#include "command_buffer.hpp"
#include "command_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

CommandBuffer::CommandBuffer(const CommandPool& command_pool, Name&& name)
    : BuiltResource(command_pool.device, std::move(name))
    , command_pool(command_pool) {}

CommandBuffer::CommandBuffer(CommandBuffer&& rhs)
    : BuiltResource(rhs.device, std::move(rhs.__name))
    , command_pool(rhs.command_pool) {
    __name = std::move(rhs.__name);
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

CommandBuffer::~CommandBuffer() {
    if (handle) {
        vkFreeCommandBuffers(command_pool.device, command_pool, 1, &handle);
    }
    handle = VK_NULL_HANDLE;
}

VkResult CommandBuffer::begin(VkCommandBufferUsageFlags flags) const {
    auto cmdbuf_bi = Itor::CommandBufferBeginInfo();
    cmdbuf_bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    return vkBeginCommandBuffer(handle, &cmdbuf_bi);
}

VkResult CommandBuffer::end() const {
    return vkEndCommandBuffer(handle);
}

void CommandBuffer::cmdMemoryBarrier(VkPipelineStageFlags src_stage_mask,
                                     VkPipelineStageFlags dst_stage_mask,
                                     uint32_t barrier_count,
                                     const VkMemoryBarrier* barriers,
                                     VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage_mask, dst_stage_mask, flags, barrier_count, barriers, 0, nullptr, 0, nullptr);
}

void CommandBuffer::cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage_mask,
                                           VkPipelineStageFlags dst_stage_mask,
                                           uint32_t barrier_count,
                                           const VkBufferMemoryBarrier* barriers,
                                           VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage_mask, dst_stage_mask, flags, 0, nullptr, barrier_count, barriers, 0, nullptr);
}

void CommandBuffer::cmdImageMemoryBarrier(VkPipelineStageFlags src_stage_mask,
                                          VkPipelineStageFlags dst_stage_mask,
                                          uint32_t barrier_count,
                                          const VkImageMemoryBarrier* barriers,
                                          VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage_mask, dst_stage_mask, flags, 0, nullptr, 0, nullptr, barrier_count, barriers);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
