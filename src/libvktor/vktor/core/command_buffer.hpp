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

    enum class Level {
        Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
    };

    explicit CommandBuffer(const CommandPool& command_pool);
    CommandBuffer(CommandBuffer&&);
    ~CommandBuffer();

    VkResult begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) const;
    VkResult end() const;
    void beginRenderPass(const VkRenderPassBeginInfo& render_pass_bi,
                         VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE) const;
    void endRenderPass() const;

    void cmdBlitImage(const Image& src,
                      const Image& dst,
                      const Vector<VkImageBlit>& regions,
                      VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                      VkFilter filter = VK_FILTER_NEAREST) const;
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
    void cmdCopyImage(const Image& src,
                      const Image& dst,
                      const Vector<VkImageCopy>& regions,
                      VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;
    /**
     * @brief Copy image with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdCopyImage(const Arg<Image>& src,
                      const Arg<Image>& dst,
                      VkImageLayout src_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      VkImageLayout dst_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;
    void cmdCopyBuffer(const Buffer& src, const Buffer& dst, const Vector<VkBufferCopy>& regions) const;
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
    void cmdCopyImageToBuffer(const Image& img,
                              const Buffer& buf,
                              const Vector<VkBufferImageCopy>& regions,
                              VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) const;
    /**
     * @brief Copy image memory to buffer memory
     *
     * Make sure buffer memory size >= image memory size with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdCopyImageToBuffer(const Arg<Image>& img,
                              const Buffer& buf,
                              VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) const;
    void cmdCopyBufferToImage(const Buffer& buf,
                              const Image& img,
                              const Vector<VkBufferImageCopy>& regions,
                              VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;
    /**
     * @brief Copy buffer memory to image memory
     *
     * Make sure buffer memory size >= image memory size with Arg<Image>::VkImageSubresourceLayers
     */
    void cmdCopyBufferToImage(const Buffer& buf,
                              const Arg<Image>& img,
                              VkImageLayout img_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) const;

    void cmdMemoryBarrier(VkPipelineStageFlags src_stage,
                          VkPipelineStageFlags dst_stage,
                          const Vector<VkMemoryBarrier>& barriers,
                          VkDependencyFlags flags = 0) const;
    void cmdBufferMemoryBarrier(VkPipelineStageFlags src_stage,
                                VkPipelineStageFlags dst_stage,
                                const Vector<VkBufferMemoryBarrier>& barriers,
                                VkDependencyFlags flags = 0) const;
    void cmdImageMemoryBarrier(VkPipelineStageFlags src_stage,
                               VkPipelineStageFlags dst_stage,
                               const Vector<VkImageMemoryBarrier>& barriers,
                               VkDependencyFlags flags = 0) const;
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
