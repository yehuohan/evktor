#pragma once
#include "__builder.hpp"
#include "command_buffer.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Image : public BuiltResource<VkImage, VK_OBJECT_TYPE_IMAGE, Device> {
    VkImageType type = VK_IMAGE_TYPE_2D;
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkExtent3D extent{};
    uint32_t mip_levels = 1;
    uint32_t array_layers = 1;

    VkDeviceMemory memory = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;

    Image(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    Image(Image&&);
    ~Image();
    OnConstType(VkDeviceMemory, memory);

    /** Copy data `src` from cpu to image memory at `src_size` */
    void copyFrom(VkDeviceSize dst_offset, const void* src, const VkDeviceSize src_size) const;
    inline void copyFrom(const void* src, const VkDeviceSize src_size = 0) const {
        copyFrom(0, src, src_size);
    }
    void genMipmaps(const CommandBuffer& cmdbuf) const;
};

struct ImageInfo : public BuilderInfo {
    VkImageCreateFlags flags = 0;
    VkImageType type = VK_IMAGE_TYPE_2D;
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkExtent3D extent{};
    uint32_t mip_levels = 1;
    uint32_t array_layers = 1;
    VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
    VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
    VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    // TODO: Support exclusive and concurrent mode
    // VkSharingMode sharing_mode = VK_SHARING_MODE_EXCLUSIVE;
    // uint32_t queue_family_index_count = 0;
    // const uint32_t* queue_family_indices = nullptr;
    VkImageLayout initial_layout = VK_IMAGE_LAYOUT_UNDEFINED;

    VmaAllocationCreateFlags memory_flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    VmaMemoryUsage memory_usage = VMA_MEMORY_USAGE_AUTO;
};

class ImageBuilder : public Builder<ImageBuilder, Image, ImageInfo> {
private:
    const Device& device;

public:
    explicit ImageBuilder(const Device& device, Name&& name = "Image") : Builder(std::move(name)), device(device) {}
    virtual Built build() override;

    Self setFormat(VkFormat format);
    Self setExtent(const VkExtent3D& extent);
    inline Self setExtent(uint32_t width, uint32_t height, uint32_t depth = 1) {
        return setExtent(VkExtent3D{width, height, depth});
    }
    Self setMipLevels(uint32_t mip_levels);
    Self setArrayLayers(uint32_t array_layers);
    Self setSamples(VkSampleCountFlagBits samples);
    Self setTiling(VkImageTiling tiling);
    Self setUsage(VkImageUsageFlags usage);

    Self setMemoryFlags(VmaAllocationCreateFlags flags);
    Self setMemoryUsage(VmaMemoryUsage usage);
};

/**
 * @brief Check format is depth only
 */
bool isDepthOnlyFormat(VkFormat format);

/**
 * @brief Check format is depth or stencil
 */
bool isDepthStencilFormat(VkFormat format);

NAMESPACE_END(core)
NAMESPACE_END(vkt)
