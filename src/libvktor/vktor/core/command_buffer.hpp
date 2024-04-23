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
    inline VkResult begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) const {
        auto cmdbuf_bi = Itor::CommandBufferBeginInfo();
        cmdbuf_bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        return vkBeginCommandBuffer(handle, &cmdbuf_bi);
    }
    inline VkResult end() const {
        return vkEndCommandBuffer(handle);
    }

public:
    inline Self beginRenderPass(const VkRenderPassBeginInfo& render_pass_bi,
                                VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE) const {
        vkCmdBeginRenderPass(handle, &render_pass_bi, contents);
        return *this;
    }
    inline Self endRenderPass() const {
        vkCmdEndRenderPass(handle);
        return *this;
    }
    inline Self cmdBindPipeline(VkPipelineBindPoint bind_point, VkPipeline pipeline) const {
        vkCmdBindPipeline(handle, bind_point, pipeline);
        return *this;
    }
    inline Self cmdBindDescriptorSets(VkPipelineBindPoint bind_point,
                                      VkPipelineLayout pipeline_layout,
                                      uint32_t first_set = 0,
                                      const Vector<VkDescriptorSet>& descriptors = {},
                                      const Vector<uint32_t>& dynamics = {}) const {
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
    inline Self cmdBindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType index_type) const {
        vkCmdBindIndexBuffer(handle, buffer, offset, index_type);
        return *this;
    }
    inline Self cmdBindVertexBuffers(uint32_t first_binding,
                                     uint32_t binding_count,
                                     const Vector<VkBuffer>& buffers,
                                     const Vector<VkDeviceSize>& offsets) const {
        vkCmdBindVertexBuffers(handle, first_binding, binding_count, buffers.data(), offsets.data());
        return *this;
    }
    inline Self cmdDrawIndexed(uint32_t index_count,
                               uint32_t instance_count,
                               uint32_t first_index,
                               int32_t vertex_offset,
                               uint32_t first_instance) const {
        vkCmdDrawIndexed(handle, index_count, instance_count, first_index, vertex_offset, first_instance);
        return *this;
    };
    inline Self cmdDispatch(uint32_t group_count_x, uint32_t group_count_y, uint32_t group_count_z) const {
        vkCmdDispatch(handle, group_count_x, group_count_y, group_count_z);
        return *this;
    }

public:
    inline void cmdBlitImage(const Image& src,
                             const Image& dst,
                             const Vector<VkImageBlit>& regions,
                             VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                             VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                             VkFilter filter = VK_FILTER_NEAREST) const {
        vkCmdBlitImage(handle, src, src_layout, dst, dst_layout, u32(regions.size()), regions.data(), filter);
    }
    inline void cmdCopyImage(const Image& src,
                             const Image& dst,
                             const Vector<VkImageCopy>& regions,
                             VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                             VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const {
        vkCmdCopyImage(handle, src, src_layout, dst, dst_layout, u32(regions.size()), regions.data());
    }
    inline void cmdCopyBuffer(const Buffer& src, const Buffer& dst, const Vector<VkBufferCopy>& regions) const {
        vkCmdCopyBuffer(handle, src, dst, u32(regions.size()), regions.data());
    }
    inline void cmdCopyImageToBuffer(const Image& img,
                                     const Buffer& buf,
                                     const Vector<VkBufferImageCopy>& regions,
                                     VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) const {
        vkCmdCopyImageToBuffer(handle, img, img_layout, buf, u32(regions.size()), regions.data());
    }
    inline void cmdCopyBufferToImage(const Buffer& buf,
                                     const Image& img,
                                     const Vector<VkBufferImageCopy>& regions,
                                     VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const {
        vkCmdCopyBufferToImage(handle, buf, img, img_layout, u32(regions.size()), regions.data());
    }
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
                                 VkDependencyFlags flags = 0) const {
        vkCmdPipelineBarrier(handle,
                             src_stage,
                             dst_stage,
                             flags,
                             u32(barriers.size()),
                             barriers.data(),
                             0,
                             nullptr,
                             0,
                             nullptr);
    }
    inline void cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage,
                                       VkPipelineStageFlags dst_stage,
                                       const Vector<VkBufferMemoryBarrier>& barriers,
                                       VkDependencyFlags flags = 0) const {
        vkCmdPipelineBarrier(handle,
                             src_stage,
                             dst_stage,
                             flags,
                             0,
                             nullptr,
                             u32(barriers.size()),
                             barriers.data(),
                             0,
                             nullptr);
    }
    inline void cmdImageMemoryBarrier(VkPipelineStageFlags src_stage,
                                      VkPipelineStageFlags dst_stage,
                                      const Vector<VkImageMemoryBarrier>& barriers,
                                      VkDependencyFlags flags = 0) const {
        vkCmdPipelineBarrier(handle,
                             src_stage,
                             dst_stage,
                             flags,
                             0,
                             nullptr,
                             0,
                             nullptr,
                             u32(barriers.size()),
                             barriers.data());
    }
    /**
     * @brief Transit image layout with Arg<Image>::VkImageSubresourceRange
     */
    bool cmdTransitImageLayout(const Arg<Image>& img,
                               VkImageLayout old_layout,
                               VkImageLayout new_layout,
                               VkDependencyFlags flags = 0) const;
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
