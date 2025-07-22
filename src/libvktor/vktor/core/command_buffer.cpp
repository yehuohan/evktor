#include "command_buffer.hpp"
#include "command_pool.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = CommandBuffer::Self;

CommandBuffer::CommandBuffer(const CommandPool& command_pool) : CoreResource(command_pool.api), command_pool(command_pool) {}

CommandBuffer::CommandBuffer(CommandBuffer&& rhs) : CoreResource(rhs.api), command_pool(rhs.command_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

CommandBuffer::~CommandBuffer() {
    if (!__borrowed && handle) {
        vkFreeCommandBuffers(command_pool.api, command_pool, 1, &handle);
    }
    handle = VK_NULL_HANDLE;
}

VkResult CommandBuffer::begin(VkCommandBufferUsageFlags flags) const {
    auto cmdbuf_bi = Itor::CommandBufferBeginInfo();
    cmdbuf_bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    return vkBeginCommandBuffer(handle, &cmdbuf_bi);
}

CommandBuffer::Self CommandBuffer::beginRenderPass(const VkRenderPass render_pass,
                                                   const VkFramebuffer framebuffer,
                                                   const VkOffset2D offset,
                                                   const VkExtent2D extent,
                                                   const Vector<VkClearValue>& clear_values,
                                                   VkSubpassContents contents) const {
    auto render_pass_bi = Itor::RenderPassBeginInfo();
    render_pass_bi.renderPass = render_pass;
    render_pass_bi.framebuffer = framebuffer;
    render_pass_bi.renderArea = VkRect2D{offset, extent};
    render_pass_bi.clearValueCount = u32(clear_values.size());
    render_pass_bi.pClearValues = clear_values.data();
    vkCmdBeginRenderPass(handle, &render_pass_bi, contents);
    return *this;
}

void CommandBuffer::cmdBlitImage(const Arg<Image>& src,
                                 const Arg<Image>& dst,
                                 VkImageLayout src_layout,
                                 VkImageLayout dst_layout,
                                 VkFilter filter) const {
    const VkOffset3D offset_min{0, 0, 0};
    VkOffset3D offset_max{};
    offset_max.x = std::min<uint32_t>(src.a.extent.width, dst.a.extent.width);
    offset_max.y = std::min<uint32_t>(src.a.extent.height, dst.a.extent.height);
    offset_max.z = std::min<uint32_t>(src.a.extent.depth, dst.a.extent.depth);
    VkImageBlit blit{};
    blit.srcSubresource = src;
    blit.srcOffsets[0] = offset_min;
    blit.srcOffsets[1] = offset_max;
    blit.dstSubresource = dst;
    blit.dstOffsets[0] = offset_min;
    blit.dstOffsets[1] = offset_max;
    vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, 1, &blit, filter);
}

void CommandBuffer::cmdBlitImageMip(const Arg<Image>& img, uint32_t mip, VkExtent2D extent, VkFilter filter) const {
    const int32_t depth = img.a.extent.depth;
    int32_t mip_wid = extent.width;
    int32_t mip_hei = extent.height;
    VkImageBlit blit{};
    blit.srcOffsets[0] = VkOffset3D{0, 0, 0};
    blit.srcOffsets[1] = VkOffset3D{mip_wid, mip_hei, depth};
    blit.srcSubresource.aspectMask = img.aspect;
    blit.srcSubresource.mipLevel = mip;
    blit.srcSubresource.baseArrayLayer = img.layer;
    blit.srcSubresource.layerCount = img.layer_count;
    if (mip_wid > 1) {
        mip_wid >>= 1;
    }
    if (mip_hei > 1) {
        mip_hei >>= 1;
    }
    blit.dstOffsets[0] = VkOffset3D{0, 0, 0};
    blit.dstOffsets[1] = VkOffset3D{mip_wid, mip_hei, depth};
    blit.dstSubresource.aspectMask = img.aspect;
    blit.dstSubresource.mipLevel = mip + 1;
    blit.dstSubresource.baseArrayLayer = img.layer;
    blit.dstSubresource.layerCount = img.layer_count;
    vkCmdBlitImage(handle,
                   img,
                   VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                   img,
                   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   1,
                   &blit,
                   filter);
}

void CommandBuffer::cmdGenImageMips(const Arg<Image>& img, VkFilter filter) const {
    uint32_t mip_wid = img.a.extent.width;
    uint32_t mip_hei = img.a.extent.height;
    Vector<VkImageMemoryBarrier> barriers{Itor::ImageMemoryBarrier()};
    auto& barrier = barriers[0];
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = img;
    barrier.subresourceRange.aspectMask = img.aspect;
    barrier.subresourceRange.baseArrayLayer = img.layer;
    barrier.subresourceRange.layerCount = img.layer_count;
    barrier.subresourceRange.levelCount = 1;
    for (uint32_t k = 1; k < img.a.mip_levels; k++) {
        uint32_t mip = k - 1;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.subresourceRange.baseMipLevel = mip;
        cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, barriers);
        cmdBlitImageMip(img, mip, VkExtent2D{mip_wid, mip_hei}, filter);
        if (mip_wid > 1) {
            mip_wid >>= 1;
        }
        if (mip_hei > 1) {
            mip_hei >>= 1;
        }
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, barriers);
    }
    if (img.a.mip_levels >= 1) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.subresourceRange.baseMipLevel = img.a.mip_levels - 1;
        cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, barriers);
    }
}

void CommandBuffer::cmdCopyImage(const Arg<Image>& src,
                                 const Arg<Image>& dst,
                                 VkImageLayout src_layout,
                                 VkImageLayout dst_layout) const {
    VkImageCopy copy{};
    copy.srcSubresource = src;
    copy.srcOffset = VkOffset3D{0, 0, 0};
    copy.dstSubresource = dst;
    copy.dstOffset = VkOffset3D{0, 0, 0};
    copy.extent.width = std::min<uint32_t>(src.a.extent.width, dst.a.extent.width);
    copy.extent.height = std::min<uint32_t>(src.a.extent.height, dst.a.extent.height);
    copy.extent.depth = std::min<uint32_t>(src.a.extent.depth, dst.a.extent.depth);
    vkCmdCopyImage(handle, src, src_layout, dst, dst_layout, 1, &copy);
}

void CommandBuffer::cmdCopyBuffer(const Buffer& src,
                                  const Buffer& dst,
                                  VkDeviceSize src_offset,
                                  VkDeviceSize dst_offset,
                                  VkDeviceSize copy_size) const {
    VkDeviceSize size = copy_size > 0 ? copy_size : std::min<VkDeviceSize>(src.size, dst.size);
    VkBufferCopy copy{};
    copy.srcOffset = src_offset;
    copy.dstOffset = dst_offset;
    copy.size = size;
    vkCmdCopyBuffer(handle, src, dst, 1, &copy);
}

void CommandBuffer::cmdCopyImageToBuffer(const Arg<Image>& img, const Buffer& buf, VkImageLayout img_layout) const {
    VkBufferImageCopy copy{};
    copy.imageSubresource = img;
    copy.imageOffset = VkOffset3D{0, 0, 0};
    copy.imageExtent = img.a.extent;
    copy.bufferOffset = 0;
    copy.bufferRowLength = 0;
    copy.bufferImageHeight = 0;
    vkCmdCopyImageToBuffer(handle, img, img_layout, buf, 1, &copy);
};

void CommandBuffer::cmdCopyBufferToImage(const Buffer& buf, const Arg<Image>& img, VkImageLayout img_layout) const {
    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferRowLength = 0;
    copy.bufferImageHeight = 0;
    copy.imageSubresource = img;
    copy.imageOffset = VkOffset3D{0, 0, 0};
    copy.imageExtent = img.a.extent;
    vkCmdCopyBufferToImage(handle, buf, img, img_layout, 1, &copy);
}

void CommandBuffer::cmdMemoryBarrier(VkPipelineStageFlags src_stage,
                                     VkPipelineStageFlags dst_stage,
                                     VkAccessFlags src_access,
                                     VkAccessFlags dst_access,
                                     VkDependencyFlags flags) const {
    auto barrier = Itor::MemoryBarrier();
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 1, &barrier, 0, nullptr, 0, nullptr);
}

void CommandBuffer::cmdMemoryBarrier2(const Vector<VkMemoryBarrier2>& barriers, VkDependencyFlags flags) const {
    auto info = Itor::DependencyInfo();
    info.dependencyFlags = flags;
    info.memoryBarrierCount = u32(barriers.size());
    info.pMemoryBarriers = barriers.data();
    vkCmdPipelineBarrier2(handle, &info);
}

void CommandBuffer::cmdMemoryBarrier2(VkPipelineStageFlags2 src_stage,
                                      VkPipelineStageFlags2 dst_stage,
                                      VkAccessFlags2 src_access,
                                      VkAccessFlags2 dst_access,
                                      VkDependencyFlags flags) const {
    auto barrier = Itor::MemoryBarrier2();
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    auto info = Itor::DependencyInfo();
    info.dependencyFlags = flags;
    info.memoryBarrierCount = 1;
    info.pMemoryBarriers = &barrier;
    vkCmdPipelineBarrier2(handle, &info);
}

void CommandBuffer::cmdBufferMemoryBarrier(const Buffer& buf,
                                           VkPipelineStageFlags src_stage,
                                           VkPipelineStageFlags dst_stage,
                                           VkAccessFlags src_access,
                                           VkAccessFlags dst_access,
                                           VkDeviceSize offset,
                                           VkDeviceSize size,
                                           VkDependencyFlags flags) const {
    auto barrier = Itor::BufferMemoryBarrier();
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.buffer = buf;
    barrier.offset = offset;
    barrier.size = size == 0 ? buf.size : size;
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 0, nullptr, 1, &barrier, 0, nullptr);
}

void CommandBuffer::cmdBufferMemoryBarrier2(const Vector<VkBufferMemoryBarrier2>& barriers, VkDependencyFlags flags) const {
    auto info = Itor::DependencyInfo();
    info.dependencyFlags = flags;
    info.bufferMemoryBarrierCount = u32(barriers.size());
    info.pBufferMemoryBarriers = barriers.data();
    vkCmdPipelineBarrier2(handle, &info);
}

void CommandBuffer::cmdBufferMemoryBarrier2(const Buffer& buf,
                                            VkPipelineStageFlags2 src_stage,
                                            VkPipelineStageFlags2 dst_stage,
                                            VkAccessFlags2 src_access,
                                            VkAccessFlags2 dst_access,
                                            VkDeviceSize offset,
                                            VkDeviceSize size,
                                            VkDependencyFlags flags) const {
    auto barrier = Itor::BufferMemoryBarrier2();
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.buffer = buf;
    barrier.offset = offset;
    barrier.size = size == 0 ? buf.size : size;
    auto info = Itor::DependencyInfo();
    info.dependencyFlags = flags;
    info.bufferMemoryBarrierCount = 1;
    info.pBufferMemoryBarriers = &barrier;
    vkCmdPipelineBarrier2(handle, &info);
}

void CommandBuffer::cmdImageMemoryBarrier(const Arg<Image>& img,
                                          VkPipelineStageFlags src_stage,
                                          VkPipelineStageFlags dst_stage,
                                          VkAccessFlags src_access,
                                          VkAccessFlags dst_access,
                                          VkImageLayout old_layout,
                                          VkImageLayout new_layout,
                                          VkDependencyFlags flags) const {
    auto barrier = Itor::ImageMemoryBarrier();
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = img;
    barrier.subresourceRange = img;
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 0, nullptr, 0, nullptr, 1, &barrier);
}

void CommandBuffer::cmdImageMemoryBarrier2(const Vector<VkImageMemoryBarrier2>& barriers, VkDependencyFlags flags) const {
    auto info = Itor::DependencyInfo();
    info.dependencyFlags = flags;
    info.imageMemoryBarrierCount = u32(barriers.size());
    info.pImageMemoryBarriers = barriers.data();
    vkCmdPipelineBarrier2(handle, &info);
}

void CommandBuffer::cmdImageMemoryBarrier2(const Arg<Image>& img,
                                           VkPipelineStageFlags2 src_stage,
                                           VkPipelineStageFlags2 dst_stage,
                                           VkAccessFlags2 src_access,
                                           VkAccessFlags2 dst_access,
                                           VkImageLayout old_layout,
                                           VkImageLayout new_layout,
                                           VkDependencyFlags flags) const {
    auto barrier = Itor::ImageMemoryBarrier2();
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = img;
    barrier.subresourceRange = img;
    auto info = Itor::DependencyInfo();
    info.dependencyFlags = flags;
    info.imageMemoryBarrierCount = 1;
    info.pImageMemoryBarriers = &barrier;
    vkCmdPipelineBarrier2(handle, &info);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
