#pragma once
#include "__core.hpp"
#include "buffer.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct CommandPool;

/**
 * @brief Command buffer
 *
 * CommandBuffer must be allocated with CommandPool::allocate().
 */
struct CommandBuffer : public CoreResource<VkCommandBuffer, VK_OBJECT_TYPE_COMMAND_BUFFER> {
    const CommandPool& command_pool;

public:
    using Self = const CommandBuffer&;

    explicit CommandBuffer(const CommandPool& command_pool);
    CommandBuffer(CommandBuffer&&);
    ~CommandBuffer();

public:
    VkResult begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) const;
    inline VkResult end() const;

public:
#if VK_KHR_dynamic_rendering // As a block region
    inline Self cmdBeginRendering(const VkRenderingInfo& rendering_bi) const;
    /**
     * @brief Begin dynamic rendering
     *
     * ```
     * attms: | all attachments                     |
     *        | colors    | depth     | stencil     |
     *         ----------- =========== -------------
     *         color_count depth_index stencil_index
     * ```
     *
     * @param attms All required rendering attachments for color, depth and stencil
     * @param color_count The number of color attachments from the start of `attms` (color_count > 0)
     * @param depth_index The index of depth attachment from `attms` (VK_ATTACHMENT_UNUSED means no depth attachment)
     * @param stencil_index The index of stencil attachment from `attms` (VK_ATTACHMENT_UNUSED means no stencil attachment)
     */
    Self cmdBeginRendering(const VkOffset2D offset,
                           const VkExtent2D extent,
                           const Vector<VkRenderingAttachmentInfo>& attms,
                           const uint32_t color_count = 0,
                           const uint32_t depth_index = VK_ATTACHMENT_UNUSED,
                           const uint32_t stencil_index = VK_ATTACHMENT_UNUSED) const;
    inline Self cmdBeginRendering(const VkExtent2D extent,
                                  const Vector<VkRenderingAttachmentInfo>& attms,
                                  const uint32_t color_count = 0,
                                  const uint32_t depth_index = VK_ATTACHMENT_UNUSED,
                                  const uint32_t stencil_index = VK_ATTACHMENT_UNUSED) const;
    inline Self cmdEndRendering() const;
#endif

public:
    inline Self beginRenderPass(const VkRenderPassBeginInfo& render_pass_bi,
                                VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE) const;
    Self beginRenderPass(const VkOffset2D offset,
                         const VkExtent2D extent,
                         const VkRenderPass render_pass,
                         const VkFramebuffer framebuffer,
                         const Vector<VkClearValue>& clear_values,
                         VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE) const;
    inline Self beginRenderPass(const VkExtent2D extent,
                                const VkRenderPass render_pass,
                                const VkFramebuffer framebuffer,
                                const Vector<VkClearValue>& clear_values,
                                VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE) const;
    inline Self endRenderPass() const;
    inline Self cmdBindPipeline(VkPipelineBindPoint bind_point, VkPipeline pipeline) const;
    inline Self cmdBindGraphicsPipeline(VkPipeline pipeline) const;
    inline Self cmdBindComputePipeline(VkPipeline pipeline) const;
    inline Self cmdBindDescriptorSets(VkPipelineBindPoint bind_point,
                                      VkPipelineLayout pipeline_layout,
                                      uint32_t first_set = 0,
                                      const Vector<VkDescriptorSet>& descriptors = {},
                                      const Vector<uint32_t>& dynamics = {}) const;
    inline Self cmdBindGraphicsDescriptorSets(VkPipelineLayout pipeline_layout,
                                              uint32_t first_set = 0,
                                              const Vector<VkDescriptorSet>& descriptors = {},
                                              const Vector<uint32_t>& dynamics = {}) const;
    inline Self cmdBindComputeDescriptorSets(VkPipelineLayout pipeline_layout,
                                             uint32_t first_set = 0,
                                             const Vector<VkDescriptorSet>& descriptors = {},
                                             const Vector<uint32_t>& dynamics = {}) const;
    inline Self cmdPushConstants(VkPipelineLayout layout,
                                 VkShaderStageFlags stage,
                                 const void* data,
                                 uint32_t size,
                                 uint32_t offset = 0) const;
    inline Self cmdPushGraphicsConstants(VkPipelineLayout layout, const void* data, uint32_t size, uint32_t offset = 0) const;
    inline Self cmdPushVertConstants(VkPipelineLayout layout, const void* data, uint32_t size, uint32_t offset = 0) const;
    inline Self cmdPushFragConstants(VkPipelineLayout layout, const void* data, uint32_t size, uint32_t offset = 0) const;
    inline Self cmdPushCompConstants(VkPipelineLayout layout, const void* data, uint32_t size, uint32_t offset = 0) const;
    inline Self cmdBindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType index_type) const;
    inline Self cmdBindIndexBufferU32(VkBuffer buffer, VkDeviceSize offset = 0) const;
    inline Self cmdBindIndexBufferU16(VkBuffer buffer, VkDeviceSize offset = 0) const;
    inline Self cmdBindVertexBuffers(uint32_t first_binding,
                                     const Vector<VkBuffer>& buffers,
                                     const Vector<VkDeviceSize>& offsets) const;
    inline Self cmdDrawIndexed(uint32_t index_count,
                               uint32_t instance_count = 1,
                               uint32_t first_index = 0,
                               int32_t vertex_offset = 0,
                               uint32_t first_instance = 0) const;
    inline Self cmdDispatch(uint32_t group_count_x, uint32_t group_count_y, uint32_t group_count_z) const;

public:
    inline void cmdBlitImage(const Image& src,
                             const Image& dst,
                             const Vector<VkImageBlit>& regions,
                             VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                             VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                             VkFilter filter = VK_FILTER_NEAREST) const;
    inline void cmdCopyImage(const Image& src,
                             const Image& dst,
                             const Vector<VkImageCopy>& regions,
                             VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                             VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;
    inline void cmdCopyBuffer(const Buffer& src, const Buffer& dst, const Vector<VkBufferCopy>& regions) const;
    inline void cmdCopyImageToBuffer(const Image& img,
                                     const Buffer& buf,
                                     const Vector<VkBufferImageCopy>& regions,
                                     VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) const;
    inline void cmdCopyBufferToImage(const Buffer& buf,
                                     const Image& img,
                                     const Vector<VkBufferImageCopy>& regions,
                                     VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;
    /**
     * @brief Blit image with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdBlitImage(const Arg<Image>& src,
                      const Arg<Image>& dst,
                      VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                      VkFilter filter = VK_FILTER_NEAREST) const;
    /**
     * @brief Blit image's mip for Arg<Image>::{aspect, layer, layer_count}
     *
     * Blit image `mip` level to `mip + 1` level.
     * Make sure:
     *  - `mip` layout is VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL.
     *  - `mip + 1` layout is VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.
     *
     * @param mip The image mip level to copy from
     * @param extent The extent of image `mip` level
     */
    void cmdBlitImageMip(const Arg<Image>& img, uint32_t mip, VkExtent2D extent, VkFilter filter = VK_FILTER_NEAREST) const;
    /**
     * @brief Generate image's mipmaps for Arg<Image>::{aspect, layer, layer_count}
     *
     * Make sure `img` all mip levels are VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.
     * After generate mipmaps, `img` transit to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL.
     */
    void cmdGenImageMips(const Arg<Image>& img, VkFilter filter = VK_FILTER_NEAREST) const;
    /**
     * @brief Copy image with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdCopyImage(const Arg<Image>& src,
                      const Arg<Image>& dst,
                      VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;
    /**
     * @brief Copy buffer
     *
     * If `copy_size` is 0, then use `min(src.size, dst.size)`.
     */
    void cmdCopyBuffer(const Buffer& src,
                       const Buffer& dst,
                       VkDeviceSize src_offset = 0,
                       VkDeviceSize dst_offset = 0,
                       VkDeviceSize copy_size = 0) const;
    /**
     * @brief Copy image memory to buffer memory
     *
     * Make sure buffer memory size >= image memory size with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdCopyImageToBuffer(const Arg<Image>& img,
                              const Buffer& buf,
                              VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) const;
    /**
     * @brief Copy buffer memory to image memory
     *
     * Make sure buffer memory size >= image memory size with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdCopyBufferToImage(const Buffer& buf,
                              const Arg<Image>& img,
                              VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;

public:
    inline void cmdMemoryBarrier(VkPipelineStageFlags src_stage,
                                 VkPipelineStageFlags dst_stage,
                                 const Vector<VkMemoryBarrier>& barriers,
                                 VkDependencyFlags flags = 0) const;
    void cmdMemoryBarrier(VkPipelineStageFlags src_stage,
                          VkPipelineStageFlags dst_stage,
                          VkAccessFlags src_access,
                          VkAccessFlags dst_access,
                          VkDependencyFlags flags = 0) const;
    void cmdMemoryBarrier2(const Vector<VkMemoryBarrier2>& barriers, VkDependencyFlags flags = 0) const;
    void cmdMemoryBarrier2(VkPipelineStageFlags2 src_stage,
                           VkPipelineStageFlags2 dst_stage,
                           VkAccessFlags2 src_access,
                           VkAccessFlags2 dst_access,
                           VkDependencyFlags flags = 0) const;
    inline void cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage,
                                       VkPipelineStageFlags dst_stage,
                                       const Vector<VkBufferMemoryBarrier>& barriers,
                                       VkDependencyFlags flags = 0) const;
    /**
     * @brief Buffer memory barrier
     *
     * If `size` is 0, then use `buf.size`.
     */
    void cmdBufferMemoryBarrier(const Buffer& buf,
                                VkPipelineStageFlags src_stage,
                                VkPipelineStageFlags dst_stage,
                                VkAccessFlags src_access,
                                VkAccessFlags dst_access,
                                VkDeviceSize offset = 0,
                                VkDeviceSize size = 0,
                                VkDependencyFlags flags = 0) const;
    void cmdBufferMemoryBarrier2(const Vector<VkBufferMemoryBarrier2>& barriers, VkDependencyFlags flags = 0) const;
    /**
     * @brief Buffer memory barrier
     *
     * If `size` is 0, then use `buf.size`.
     */
    void cmdBufferMemoryBarrier2(const Buffer& buf,
                                 VkPipelineStageFlags2 src_stage,
                                 VkPipelineStageFlags2 dst_stage,
                                 VkAccessFlags2 src_access,
                                 VkAccessFlags2 dst_access,
                                 VkDeviceSize offset = 0,
                                 VkDeviceSize size = 0,
                                 VkDependencyFlags flags = 0) const;
    inline void cmdImageMemoryBarrier(VkPipelineStageFlags src_stage,
                                      VkPipelineStageFlags dst_stage,
                                      const Vector<VkImageMemoryBarrier>& barriers,
                                      VkDependencyFlags flags = 0) const;
    void cmdImageMemoryBarrier(const Arg<Image>& img,
                               VkPipelineStageFlags src_stage,
                               VkPipelineStageFlags dst_stage,
                               VkAccessFlags src_access,
                               VkAccessFlags dst_access,
                               VkImageLayout old_layout,
                               VkImageLayout new_layout,
                               VkDependencyFlags flags = 0) const;
    void cmdImageMemoryBarrier2(const Vector<VkImageMemoryBarrier2>& barriers, VkDependencyFlags flags = 0) const;
    void cmdImageMemoryBarrier2(const Arg<Image>& img,
                                VkPipelineStageFlags2 src_stage,
                                VkPipelineStageFlags2 dst_stage,
                                VkAccessFlags2 src_access,
                                VkAccessFlags2 dst_access,
                                VkImageLayout old_layout,
                                VkImageLayout new_layout,
                                VkDependencyFlags flags = 0) const;
};

inline VkResult CommandBuffer::end() const {
    return vkEndCommandBuffer(handle);
}

#if VK_KHR_dynamic_rendering
inline CommandBuffer::Self CommandBuffer::cmdBeginRendering(const VkRenderingInfo& rendering_bi) const {
    vkCmdBeginRendering(handle, &rendering_bi);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBeginRendering(const VkExtent2D extent,
                                                            const Vector<VkRenderingAttachmentInfo>& attms,
                                                            const uint32_t color_count,
                                                            const uint32_t depth_index,
                                                            const uint32_t stencil_index) const {
    return cmdBeginRendering({0, 0}, extent, attms, color_count, depth_index, stencil_index);
}

inline CommandBuffer::Self CommandBuffer::cmdEndRendering() const {
    vkCmdEndRendering(handle);
    return *this;
}
#endif

inline CommandBuffer::Self CommandBuffer::beginRenderPass(const VkRenderPassBeginInfo& render_pass_bi,
                                                          VkSubpassContents contents) const {
    vkCmdBeginRenderPass(handle, &render_pass_bi, contents);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::beginRenderPass(const VkExtent2D extent,
                                                          const VkRenderPass render_pass,
                                                          const VkFramebuffer framebuffer,
                                                          const Vector<VkClearValue>& clear_values,
                                                          VkSubpassContents contents) const {
    return beginRenderPass({0, 0}, extent, render_pass, framebuffer, clear_values, contents);
}

inline CommandBuffer::Self CommandBuffer::endRenderPass() const {
    vkCmdEndRenderPass(handle);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindPipeline(VkPipelineBindPoint bind_point, VkPipeline pipeline) const {
    vkCmdBindPipeline(handle, bind_point, pipeline);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindGraphicsPipeline(VkPipeline pipeline) const {
    vkCmdBindPipeline(handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindComputePipeline(VkPipeline pipeline) const {
    vkCmdBindPipeline(handle, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindDescriptorSets(VkPipelineBindPoint bind_point,
                                                                VkPipelineLayout pipeline_layout,
                                                                uint32_t first_set,
                                                                const Vector<VkDescriptorSet>& descriptors,
                                                                const Vector<uint32_t>& dynamics) const {
    vkCmdBindDescriptorSets(handle,
                            bind_point,
                            pipeline_layout,
                            first_set,
                            u32(descriptors.size()),
                            descriptors.data(),
                            u32(dynamics.size()),
                            dynamics.data());
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindGraphicsDescriptorSets(VkPipelineLayout pipeline_layout,
                                                                        uint32_t first_set,
                                                                        const Vector<VkDescriptorSet>& descriptors,
                                                                        const Vector<uint32_t>& dynamics) const {
    vkCmdBindDescriptorSets(handle,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipeline_layout,
                            first_set,
                            u32(descriptors.size()),
                            descriptors.data(),
                            u32(dynamics.size()),
                            dynamics.data());
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindComputeDescriptorSets(VkPipelineLayout pipeline_layout,
                                                                       uint32_t first_set,
                                                                       const Vector<VkDescriptorSet>& descriptors,
                                                                       const Vector<uint32_t>& dynamics) const {
    vkCmdBindDescriptorSets(handle,
                            VK_PIPELINE_BIND_POINT_COMPUTE,
                            pipeline_layout,
                            first_set,
                            u32(descriptors.size()),
                            descriptors.data(),
                            u32(dynamics.size()),
                            dynamics.data());
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdPushConstants(VkPipelineLayout layout,
                                                           VkShaderStageFlags stage,
                                                           const void* data,
                                                           uint32_t size,
                                                           uint32_t offset) const {
    vkCmdPushConstants(handle, layout, stage, offset, size, data);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdPushGraphicsConstants(VkPipelineLayout layout,
                                                                   const void* data,
                                                                   uint32_t size,
                                                                   uint32_t offset) const {
    vkCmdPushConstants(handle, layout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, offset, size, data);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdPushVertConstants(VkPipelineLayout layout,
                                                               const void* data,
                                                               uint32_t size,
                                                               uint32_t offset) const {
    vkCmdPushConstants(handle, layout, VK_SHADER_STAGE_VERTEX_BIT, offset, size, data);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdPushFragConstants(VkPipelineLayout layout,
                                                               const void* data,
                                                               uint32_t size,
                                                               uint32_t offset) const {
    vkCmdPushConstants(handle, layout, VK_SHADER_STAGE_FRAGMENT_BIT, offset, size, data);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdPushCompConstants(VkPipelineLayout layout,
                                                               const void* data,
                                                               uint32_t size,
                                                               uint32_t offset) const {
    vkCmdPushConstants(handle, layout, VK_SHADER_STAGE_COMPUTE_BIT, offset, size, data);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindIndexBuffer(VkBuffer buffer,
                                                             VkDeviceSize offset,
                                                             VkIndexType index_type) const {
    vkCmdBindIndexBuffer(handle, buffer, offset, index_type);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindIndexBufferU32(VkBuffer buffer, VkDeviceSize offset) const {
    vkCmdBindIndexBuffer(handle, buffer, offset, VK_INDEX_TYPE_UINT32);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindIndexBufferU16(VkBuffer buffer, VkDeviceSize offset) const {
    vkCmdBindIndexBuffer(handle, buffer, offset, VK_INDEX_TYPE_UINT16);
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdBindVertexBuffers(uint32_t first_binding,
                                                               const Vector<VkBuffer>& buffers,
                                                               const Vector<VkDeviceSize>& offsets) const {
    vkCmdBindVertexBuffers(handle, first_binding, u32(buffers.size()), buffers.data(), offsets.data());
    return *this;
}

inline CommandBuffer::Self CommandBuffer::cmdDrawIndexed(uint32_t index_count,
                                                         uint32_t instance_count,
                                                         uint32_t first_index,
                                                         int32_t vertex_offset,
                                                         uint32_t first_instance) const {
    vkCmdDrawIndexed(handle, index_count, instance_count, first_index, vertex_offset, first_instance);
    return *this;
};

inline CommandBuffer::Self CommandBuffer::cmdDispatch(uint32_t group_count_x,
                                                      uint32_t group_count_y,
                                                      uint32_t group_count_z) const {
    vkCmdDispatch(handle, group_count_x, group_count_y, group_count_z);
    return *this;
}

inline void CommandBuffer::cmdBlitImage(const Image& src,
                                        const Image& dst,
                                        const Vector<VkImageBlit>& regions,
                                        VkImageLayout src_layout,
                                        VkImageLayout dst_layout,
                                        VkFilter filter) const {

    vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, u32(regions.size()), regions.data(), filter);
}

inline void CommandBuffer::cmdCopyImage(const Image& src,
                                        const Image& dst,
                                        const Vector<VkImageCopy>& regions,
                                        VkImageLayout src_layout,
                                        VkImageLayout dst_layout) const {
    vkCmdCopyImage(handle, src, src_layout, dst, dst_layout, u32(regions.size()), regions.data());
}

inline void CommandBuffer::cmdCopyBuffer(const Buffer& src, const Buffer& dst, const Vector<VkBufferCopy>& regions) const {
    vkCmdCopyBuffer(handle, src, dst, u32(regions.size()), regions.data());
}

inline void CommandBuffer::cmdCopyImageToBuffer(const Image& img,
                                                const Buffer& buf,
                                                const Vector<VkBufferImageCopy>& regions,
                                                VkImageLayout img_layout) const {
    vkCmdCopyImageToBuffer(handle, img, img_layout, buf, u32(regions.size()), regions.data());
}

inline void CommandBuffer::cmdCopyBufferToImage(const Buffer& buf,
                                                const Image& img,
                                                const Vector<VkBufferImageCopy>& regions,
                                                VkImageLayout img_layout) const {
    vkCmdCopyBufferToImage(handle, buf, img, img_layout, u32(regions.size()), regions.data());
}

inline void CommandBuffer::cmdMemoryBarrier(VkPipelineStageFlags src_stage,
                                            VkPipelineStageFlags dst_stage,
                                            const Vector<VkMemoryBarrier>& barriers,
                                            VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, u32(barriers.size()), barriers.data(), 0, nullptr, 0, nullptr);
}

inline void CommandBuffer::cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage,
                                                  VkPipelineStageFlags dst_stage,
                                                  const Vector<VkBufferMemoryBarrier>& barriers,
                                                  VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 0, nullptr, u32(barriers.size()), barriers.data(), 0, nullptr);
}

inline void CommandBuffer::cmdImageMemoryBarrier(VkPipelineStageFlags src_stage,
                                                 VkPipelineStageFlags dst_stage,
                                                 const Vector<VkImageMemoryBarrier>& barriers,
                                                 VkDependencyFlags flags) const {
    vkCmdPipelineBarrier(handle, src_stage, dst_stage, flags, 0, nullptr, 0, nullptr, u32(barriers.size()), barriers.data());
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
