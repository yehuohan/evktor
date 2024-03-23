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
    auto barrier = Itor::ImageMemoryBarrier();
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = img;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
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
        cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 1, &barrier);
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
        cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 1, &barrier);
    }
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.subresourceRange.baseMipLevel = img.mip_levels - 1;
    cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 1, &barrier);
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
