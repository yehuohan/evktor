#include "command_buffer.hpp"
#include "command_pool.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

PipelineBarrier::PipelineBarrier(const VkCommandBuffer cmdbuf, VkDependencyFlags flags)
    : IPipelineBarrier<PipelineBarrier, VkPipelineStageFlags, VkAccessFlags>(cmdbuf, flags) {}

PipelineBarrier& PipelineBarrier::mem(const void* next) {
    auto barrier = Itor::MemoryBarrier(next);
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    vkCmdPipelineBarrier(cmdbuf, src_stage, dst_stage, flags, 1, &barrier, 0, nullptr, 0, nullptr);
    return *this;
}

PipelineBarrier& PipelineBarrier::buf(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const void* next) {
    auto barrier = Itor::BufferMemoryBarrier(next);
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.buffer = buffer;
    barrier.offset = offset;
    barrier.size = size;
    vkCmdPipelineBarrier(cmdbuf, src_stage, dst_stage, flags, 0, nullptr, 1, &barrier, 0, nullptr);
    return *this;
}

PipelineBarrier& PipelineBarrier::buf(const Buffer& buffer, const void* next) {
    auto barrier = Itor::BufferMemoryBarrier(next);
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.buffer = buffer;
    barrier.offset = 0;
    barrier.size = buffer.getSize();
    vkCmdPipelineBarrier(cmdbuf, src_stage, dst_stage, flags, 0, nullptr, 1, &barrier, 0, nullptr);
    return *this;
}

PipelineBarrier& PipelineBarrier::img(VkImage image, const VkImageSubresourceRange& subresource_range, const void* next) {
    auto barrier = Itor::ImageMemoryBarrier(next);
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.image = image;
    barrier.subresourceRange = subresource_range;
    vkCmdPipelineBarrier(cmdbuf, src_stage, dst_stage, flags, 0, nullptr, 0, nullptr, 1, &barrier);
    return *this;
}

PipelineBarrier& PipelineBarrier::img(const Arg<Image>& image, const void* next) {
    auto barrier = Itor::ImageMemoryBarrier(next);
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.image = image;
    barrier.subresourceRange = image;
    vkCmdPipelineBarrier(cmdbuf, src_stage, dst_stage, flags, 0, nullptr, 0, nullptr, 1, &barrier);
    return *this;
}

PipelineBarrier2::PipelineBarrier2(const VkCommandBuffer cmdbuf, VkDependencyFlags flags)
    : IPipelineBarrier<PipelineBarrier2, VkPipelineStageFlags2, VkAccessFlags2>(cmdbuf, flags) {}

PipelineBarrier2& PipelineBarrier2::mem(const void* next) {
    auto barrier = Itor::MemoryBarrier2();
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    auto info = Itor::DependencyInfo(next);
    info.dependencyFlags = flags;
    info.pMemoryBarriers = &barrier;
    info.memoryBarrierCount = 1;
    vkCmdPipelineBarrier2(cmdbuf, &info);
    return *this;
}

PipelineBarrier2& PipelineBarrier2::buf(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const void* next) {
    auto barrier = Itor::BufferMemoryBarrier2(next);
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.buffer = buffer;
    barrier.offset = offset;
    barrier.size = size;
    auto info = Itor::DependencyInfo(next);
    info.dependencyFlags = flags;
    info.pBufferMemoryBarriers = &barrier;
    info.bufferMemoryBarrierCount = 1;
    vkCmdPipelineBarrier2(cmdbuf, &info);
    return *this;
}

PipelineBarrier2& PipelineBarrier2::buf(const Buffer& buffer, const void* next) {
    auto barrier = Itor::BufferMemoryBarrier2(next);
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.buffer = buffer;
    barrier.offset = 0;
    barrier.size = buffer.getSize();
    auto info = Itor::DependencyInfo(next);
    info.dependencyFlags = flags;
    info.pBufferMemoryBarriers = &barrier;
    info.bufferMemoryBarrierCount = 1;
    vkCmdPipelineBarrier2(cmdbuf, &info);
    return *this;
}

PipelineBarrier2& PipelineBarrier2::img(VkImage image, const VkImageSubresourceRange& subresource_range, const void* next) {
    auto barrier = Itor::ImageMemoryBarrier2(next);
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.image = image;
    barrier.subresourceRange = subresource_range;
    auto info = Itor::DependencyInfo(next);
    info.dependencyFlags = flags;
    info.pImageMemoryBarriers = &barrier;
    info.imageMemoryBarrierCount = 1;
    vkCmdPipelineBarrier2(cmdbuf, &info);
    return *this;
}

PipelineBarrier2& PipelineBarrier2::img(const Arg<Image>& image, const void* next) {
    auto barrier = Itor::ImageMemoryBarrier2(next);
    barrier.srcStageMask = src_stage;
    barrier.dstStageMask = dst_stage;
    barrier.srcAccessMask = src_access;
    barrier.dstAccessMask = dst_access;
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = src_qfi;
    barrier.dstQueueFamilyIndex = dst_qfi;
    barrier.image = image;
    barrier.subresourceRange = image;
    auto info = Itor::DependencyInfo(next);
    info.dependencyFlags = flags;
    info.pImageMemoryBarriers = &barrier;
    info.imageMemoryBarrierCount = 1;
    vkCmdPipelineBarrier2(cmdbuf, &info);
    return *this;
}

using Self = CommandBuffer::Self;

CommandBuffer::CommandBuffer(const CommandPool& command_pool) : CoreResource(command_pool.api), command_pool(command_pool) {}

CommandBuffer::CommandBuffer(CommandBuffer&& rhs) : CoreResource(rhs.api), command_pool(rhs.command_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

CommandBuffer::~CommandBuffer() {
    if (!__borrowed && handle) {
        vkFreeCommandBuffers(api, command_pool, 1, &handle);
    }
    handle = VK_NULL_HANDLE;
}

VkResult CommandBuffer::begin(VkCommandBufferUsageFlags flags) const {
    auto cmdbuf_bi = Itor::CommandBufferBeginInfo();
    cmdbuf_bi.flags = flags;
    return vkBeginCommandBuffer(handle, &cmdbuf_bi);
}

#if VK_KHR_dynamic_rendering
Self CommandBuffer::cmdBeginRendering(const VkOffset2D offset,
                                      const VkExtent2D extent,
                                      const Vector<VkRenderingAttachmentInfo>& attms,
                                      const uint32_t color_count,
                                      const uint32_t depth_index,
                                      const uint32_t stencil_index) const {
    auto info = Itor::RenderingInfo();
    info.renderArea = VkRect2D{offset, extent};
    info.layerCount = 1;
    info.colorAttachmentCount = color_count;
    info.pColorAttachments = attms.data();
    if (depth_index < attms.size()) {
        info.pDepthAttachment = &attms[depth_index];
    }
    if (stencil_index < attms.size()) {
        info.pStencilAttachment = &attms[stencil_index];
    }
    vkCmdBeginRendering(handle, &info);
    return *this;
}
#endif

Self CommandBuffer::beginRenderPass(const VkOffset2D offset,
                                    const VkExtent2D extent,
                                    const VkRenderPass render_pass,
                                    const VkFramebuffer framebuffer,
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

CommandBuffer::Self CommandBuffer::cmdBlitImage(const Arg<Image>& src,
                                                const Arg<Image>& dst,
                                                VkOffset3D src_offsets[2],
                                                VkOffset3D dst_offsets[2],
                                                VkImageLayout src_layout,
                                                VkImageLayout dst_layout,
                                                VkFilter filter) const {
    VkImageBlit blit{};
    blit.srcSubresource = src;
    blit.srcOffsets[0] = src_offsets[0];
    blit.srcOffsets[1] = src_offsets[1];
    blit.dstSubresource = dst;
    blit.dstOffsets[0] = dst_offsets[0];
    blit.dstOffsets[1] = dst_offsets[1];
    vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, 1, &blit, filter);
    return *this;
}

CommandBuffer::Self CommandBuffer::cmdBlitImage(const Arg<Image>& src,
                                                const Arg<Image>& dst,
                                                VkImageLayout src_layout,
                                                VkImageLayout dst_layout,
                                                VkFilter filter) const {
    VkImageBlit blit{};
    blit.srcSubresource = src;
    blit.srcOffsets[0] = src.copy_offset;
    blit.srcOffsets[1] = VkOffset3D{src.copy_offset.x + (int32_t)src.copy_extent.width,
                                    src.copy_offset.y + (int32_t)src.copy_extent.height,
                                    src.copy_offset.z + (int32_t)src.copy_extent.depth};
    blit.dstSubresource = dst;
    blit.dstOffsets[0] = dst.copy_offset;
    blit.dstOffsets[1] = VkOffset3D{dst.copy_offset.x + (int32_t)dst.copy_extent.width,
                                    dst.copy_offset.y + (int32_t)dst.copy_extent.height,
                                    dst.copy_offset.z + (int32_t)dst.copy_extent.depth};
    vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, 1, &blit, filter);
    return *this;
}

CommandBuffer::Self CommandBuffer::cmdBlitImageMip(const Arg<Image>& img,
                                                   uint32_t mip,
                                                   VkExtent2D extent,
                                                   VkFilter filter) const {
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
    return *this;
}

CommandBuffer::Self CommandBuffer::cmdGenImageMips(const Arg<Image>& img, VkFilter filter) const {
    uint32_t mip_wid = img.a.extent.width;
    uint32_t mip_hei = img.a.extent.height;
    VkImageSubresourceRange sub = img;
    sub.levelCount = 1;
    auto bar = cmdPipelineBarrier();
    for (uint32_t k = 1; k < img.a.mip_levels; k++) {
        uint32_t mip = k - 1;
        sub.baseMipLevel = mip;
        bar.from(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_WRITE_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
            .into(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_READ_BIT, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
            .img(img.a, sub);
        cmdBlitImageMip(img, mip, VkExtent2D{mip_wid, mip_hei}, filter);
        if (mip_wid > 1) {
            mip_wid >>= 1;
        }
        if (mip_hei > 1) {
            mip_hei >>= 1;
        }
        bar.next(VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VK_ACCESS_SHADER_READ_BIT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
            .img(img.a, sub);
    }
    if (img.a.mip_levels >= 1) {
        sub.baseMipLevel = img.a.mip_levels - 1;
        bar.from(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_WRITE_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
            .into(VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VK_ACCESS_SHADER_READ_BIT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
            .img(img.a, sub);
    }
    return *this;
}

CommandBuffer::Self CommandBuffer::cmdCopyImage(const Arg<Image>& src,
                                                const Arg<Image>& dst,
                                                VkImageLayout src_layout,
                                                VkImageLayout dst_layout) const {
    VkImageCopy copy{};
    copy.srcSubresource = src;
    copy.srcOffset = src.copy_offset;
    copy.dstSubresource = dst;
    copy.dstOffset = dst.copy_offset;
    copy.extent = minExtent3D(src.copy_extent, dst.copy_extent);
    vkCmdCopyImage(handle, src, src_layout, dst, dst_layout, 1, &copy);
    return *this;
}

CommandBuffer::Self CommandBuffer::cmdCopyBuffer(const Buffer& src,
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
    return *this;
}

CommandBuffer::Self CommandBuffer::cmdCopyImageToBuffer(const Arg<Image>& img,
                                                        const Buffer& buf,
                                                        VkDeviceSize buf_offset,
                                                        uint32_t buf_row_len,
                                                        uint32_t buf_img_hei,
                                                        VkImageLayout img_layout) const {
    VkBufferImageCopy copy{};
    copy.imageSubresource = img;
    copy.imageOffset = img.copy_offset;
    copy.imageExtent = img.copy_extent;
    copy.bufferOffset = buf_offset;
    copy.bufferRowLength = buf_row_len;
    copy.bufferImageHeight = buf_img_hei;
    vkCmdCopyImageToBuffer(handle, img, img_layout, buf, 1, &copy);
    return *this;
};

CommandBuffer::Self CommandBuffer::cmdCopyBufferToImage(const Buffer& buf,
                                                        const Arg<Image>& img,
                                                        VkDeviceSize buf_offset,
                                                        uint32_t buf_row_len,
                                                        uint32_t buf_img_hei,
                                                        VkImageLayout img_layout) const {
    VkBufferImageCopy copy{};
    copy.bufferOffset = buf_offset;
    copy.bufferRowLength = buf_row_len;
    copy.bufferImageHeight = buf_img_hei;
    copy.imageSubresource = img;
    copy.imageOffset = img.copy_offset;
    copy.imageExtent = img.copy_extent;
    vkCmdCopyBufferToImage(handle, buf, img, img_layout, 1, &copy);
    return *this;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
