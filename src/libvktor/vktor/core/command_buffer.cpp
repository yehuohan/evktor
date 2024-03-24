#include "command_buffer.hpp"
#include "command_pool.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

CommandBuffer::CommandBuffer(const CommandPool& command_pool) : CoreResource(command_pool.device), command_pool(command_pool) {}

CommandBuffer::CommandBuffer(CommandBuffer&& rhs) : CoreResource(rhs.device), command_pool(rhs.command_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

CommandBuffer::~CommandBuffer() {
    if (!__borrowed && handle) {
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

void CommandBuffer::cmdBlitImage(const Image& src,
                                 const Image& dst,
                                 const Vector<VkImageBlit>& regions,
                                 VkImageLayout src_layout,
                                 VkImageLayout dst_layout,
                                 VkFilter filter) const {
    vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, u32(regions.size()), regions.data(), filter);
}

void CommandBuffer::cmdBlitImage(const Image& src,
                                 const Image& dst,
                                 VkImageLayout src_layout,
                                 VkImageLayout dst_layout,
                                 VkFilter filter) const {
    const VkOffset3D offset_min{0, 0, 0};
    VkOffset3D offset_max{};
    offset_max.x = std::min<uint32_t>(src.extent.width, dst.extent.width);
    offset_max.y = std::min<uint32_t>(src.extent.height, dst.extent.height);
    offset_max.z = std::min<uint32_t>(src.extent.depth, dst.extent.depth);
    const uint32_t layer_count = std::min<uint32_t>(src.array_layers, dst.array_layers);
    VkImageBlit blit{};
    blit.srcSubresource.aspectMask = isDepthStencilFormat(src.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    blit.srcSubresource.mipLevel = 0;
    blit.srcSubresource.baseArrayLayer = 0;
    blit.srcSubresource.layerCount = layer_count;
    blit.srcOffsets[0] = offset_min;
    blit.srcOffsets[1] = offset_max;
    blit.dstSubresource.aspectMask = isDepthStencilFormat(dst.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    blit.dstSubresource.mipLevel = 0;
    blit.dstSubresource.baseArrayLayer = 0;
    blit.dstSubresource.layerCount = layer_count;
    blit.dstOffsets[0] = offset_min;
    blit.dstOffsets[1] = offset_max;
    vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, 1, &blit, filter);
}

void CommandBuffer::cmdBlitImageMip(const Image& img, uint32_t mip, VkExtent2D extent, VkFilter filter) const {
    const auto aspect_mask = isDepthStencilFormat(img.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    const int32_t depth = img.extent.depth;
    int32_t mip_wid = extent.width;
    int32_t mip_hei = extent.height;
    VkImageBlit blit{};
    blit.srcOffsets[0] = VkOffset3D{0, 0, 0};
    blit.srcOffsets[1] = VkOffset3D{mip_wid, mip_hei, depth};
    blit.srcSubresource.aspectMask = aspect_mask;
    blit.srcSubresource.mipLevel = mip;
    blit.srcSubresource.baseArrayLayer = 0;
    blit.srcSubresource.layerCount = img.array_layers;
    if (mip_wid > 1) {
        mip_wid >>= 1;
    }
    if (mip_hei > 1) {
        mip_hei >>= 1;
    }
    blit.dstOffsets[0] = VkOffset3D{0, 0, 0};
    blit.dstOffsets[1] = VkOffset3D{mip_wid, mip_hei, depth};
    blit.dstSubresource.aspectMask = aspect_mask;
    blit.dstSubresource.mipLevel = mip + 1;
    blit.dstSubresource.baseArrayLayer = 0;
    blit.dstSubresource.layerCount = img.array_layers;
    vkCmdBlitImage(handle,
                   img,
                   VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                   img,
                   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   1,
                   &blit,
                   filter);
}

void CommandBuffer::cmdGenImageMips(const Image& img, VkFilter filter) const {
    uint32_t mip_wid = img.extent.width;
    uint32_t mip_hei = img.extent.height;
    Vector<VkImageMemoryBarrier> barriers{Itor::ImageMemoryBarrier()};
    auto& barrier = barriers[0];
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = img;
    barrier.subresourceRange.aspectMask = isDepthStencilFormat(img.format) ? VK_IMAGE_ASPECT_DEPTH_BIT
                                                                           : VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = img.array_layers;
    barrier.subresourceRange.levelCount = 1;
    for (uint32_t k = 1; k < img.mip_levels; k++) {
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
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.subresourceRange.baseMipLevel = img.mip_levels - 1;
    cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, barriers);
}

void CommandBuffer::cmdCopyImage(const Image& src,
                                 const Image& dst,
                                 const Vector<VkImageCopy>& regions,
                                 VkImageLayout src_layout,
                                 VkImageLayout dst_layout) const {
    vkCmdCopyImage(handle, src, src_layout, dst, dst_layout, u32(regions.size()), regions.data());
}

void CommandBuffer::cmdCopyImage(const Image& src, const Image& dst, VkImageLayout src_layout, VkImageLayout dst_layout) const {
    const uint32_t layer_count = std::min<uint32_t>(src.array_layers, dst.array_layers);
    VkImageCopy copy{};
    copy.srcSubresource.aspectMask = isDepthStencilFormat(src.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    copy.srcSubresource.mipLevel = 0;
    copy.srcSubresource.baseArrayLayer = 0;
    copy.srcSubresource.layerCount = layer_count;
    copy.srcOffset = VkOffset3D{0, 0, 0};
    copy.dstSubresource.aspectMask = isDepthStencilFormat(dst.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    copy.dstSubresource.mipLevel = 0;
    copy.dstSubresource.baseArrayLayer = 0;
    copy.dstSubresource.layerCount = layer_count;
    copy.dstOffset = VkOffset3D{0, 0, 0};
    copy.extent.width = std::min<uint32_t>(src.extent.width, dst.extent.width);
    copy.extent.height = std::min<uint32_t>(src.extent.height, dst.extent.height);
    copy.extent.depth = std::min<uint32_t>(src.extent.depth, dst.extent.depth);
    vkCmdCopyImage(handle, src, src_layout, dst, dst_layout, 1, &copy);
}

void CommandBuffer::cmdCopyBuffer(const Buffer& src, const Buffer& dst, const Vector<VkBufferCopy>& regions) const {
    vkCmdCopyBuffer(handle, src, dst, u32(regions.size()), regions.data());
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

void CommandBuffer::cmdCopyImageToBuffer(const Image& img,
                                         const Buffer& buf,
                                         const Vector<VkBufferImageCopy>& regions,
                                         VkImageLayout img_layout) const {
    vkCmdCopyImageToBuffer(handle, img, img_layout, buf, u32(regions.size()), regions.data());
}

void CommandBuffer::cmdCopyImageToBuffer(const Image& img, const Buffer& buf, VkImageLayout img_layout) const {
    VkBufferImageCopy copy{};
    copy.imageSubresource.aspectMask = isDepthStencilFormat(img.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    copy.imageSubresource.mipLevel = 0;
    copy.imageSubresource.baseArrayLayer = 0;
    copy.imageSubresource.layerCount = 1;
    copy.imageOffset = VkOffset3D{0, 0, 0};
    copy.imageExtent = img.extent;
    copy.bufferOffset = 0;
    copy.bufferRowLength = 0;
    copy.bufferImageHeight = 0;
    vkCmdCopyImageToBuffer(handle, img, img_layout, buf, 1, &copy);
};

void CommandBuffer::cmdCopyBufferToImage(const Buffer& buf,
                                         const Image& img,
                                         const Vector<VkBufferImageCopy>& regions,
                                         VkImageLayout img_layout) const {
    vkCmdCopyBufferToImage(handle, buf, img, img_layout, u32(regions.size()), regions.data());
}

void CommandBuffer::cmdCopyBufferToImage(const Buffer& buf, const Image& img, VkImageLayout img_layout) const {
    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferRowLength = 0;
    copy.bufferImageHeight = 0;
    copy.imageSubresource.aspectMask = isDepthStencilFormat(img.format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    copy.imageSubresource.mipLevel = 0;
    copy.imageSubresource.baseArrayLayer = 0;
    copy.imageSubresource.layerCount = 1;
    copy.imageOffset = VkOffset3D{0, 0, 0};
    copy.imageExtent = img.extent;
    vkCmdCopyBufferToImage(handle, buf, img, img_layout, 1, &copy);
}

void CommandBuffer::cmdMemoryBarrier(VkPipelineStageFlags src_stage,
                                     VkPipelineStageFlags dst_stage,
                                     const Vector<VkMemoryBarrier>& barriers,
                                     VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, u32(barriers.size()), barriers.data(), 0, nullptr, 0, nullptr);
}

void CommandBuffer::cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage,
                                           VkPipelineStageFlags dst_stage,
                                           const Vector<VkBufferMemoryBarrier>& barriers,
                                           VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 0, nullptr, u32(barriers.size()), barriers.data(), 0, nullptr);
}

void CommandBuffer::cmdImageMemoryBarrier(VkPipelineStageFlags src_stage,
                                          VkPipelineStageFlags dst_stage,
                                          const Vector<VkImageMemoryBarrier>& barriers,
                                          VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 0, nullptr, 0, nullptr, u32(barriers.size()), barriers.data());
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
