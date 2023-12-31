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
    VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
    VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
    VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;

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

    /**
     * @brief Build image with already allocated handle
     */
    static Image build(const Device& device,
                       const VkImage image,
                       VkFormat format,
                       VkExtent3D extent,
                       uint32_t mip_levels = 1,
                       uint32_t array_layers = 1,
                       VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                       VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL,
                       VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT,
                       Name&& name = "Image");
};

struct ImageInfo : public BuilderInfo {
    VkImageCreateInfo image_ci;
    VmaAllocationCreateFlags memory_flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    VmaMemoryUsage memory_usage = VMA_MEMORY_USAGE_AUTO;
};

class ImageBuilder : public Builder<ImageBuilder, Image, ImageInfo> {
private:
    const Device& device;

public:
    explicit ImageBuilder(const Device& device, Name&& name = "Image") : Builder(std::move(name)), device(device) {
        info.image_ci = Itor::ImageCreateInfo();
        info.image_ci.flags = 0;
        info.image_ci.imageType = VK_IMAGE_TYPE_2D;
        info.image_ci.format = VK_FORMAT_UNDEFINED;
        info.image_ci.extent = VkExtent3D{0, 0, 0};
        info.image_ci.mipLevels = 1;
        info.image_ci.arrayLayers = 1;
        info.image_ci.samples = VK_SAMPLE_COUNT_1_BIT;
        info.image_ci.tiling = VK_IMAGE_TILING_OPTIMAL;
        info.image_ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
        info.image_ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        // TODO: Support exclusive and concurrent mode
        info.image_ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.image_ci.queueFamilyIndexCount = 0;
        info.image_ci.pQueueFamilyIndices = nullptr;
    }
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
    Self setLayout(VkImageLayout layout);

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

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::Image> {
    size_t operator()(const vkt::core::Image& image) const {
        return hash<VkImage>{}(image);
    }
};

NAMESPACE_END(std)
