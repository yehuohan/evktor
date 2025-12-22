#pragma once
#include "__core.hpp"
#include "device_memory_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Image;

class ImageState : public CoreState<ImageState> {
    friend struct Image;
    friend struct DeviceMemoryPool;

private:
    mutable VkImageCreateInfo image_ci{};
    VmaAllocationCreateFlags memory_flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    VmaMemoryUsage memory_usage = VMA_MEMORY_USAGE_AUTO;
    const DeviceMemoryPool* memory_pool = nullptr;

public:
    explicit ImageState(String&& name = "Image") : CoreState(std::move(name)) {
        image_ci = Itor::ImageCreateInfo();
        image_ci.flags = 0;
        image_ci.imageType = VK_IMAGE_TYPE_2D;
        image_ci.format = VK_FORMAT_UNDEFINED;
        image_ci.extent = VkExtent3D{0, 0, 0};
        image_ci.mipLevels = 1;
        image_ci.arrayLayers = 1;
        image_ci.samples = VK_SAMPLE_COUNT_1_BIT;
        image_ci.tiling = VK_IMAGE_TILING_OPTIMAL;
        image_ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
        image_ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        // TODO: Support exclusive and concurrent mode
        image_ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        image_ci.queueFamilyIndexCount = 0;
        image_ci.pQueueFamilyIndices = nullptr;
    }

    Self setFormat(VkFormat format);
    Self setExtent(const VkExtent3D& extent);
    inline Self setExtent(const VkExtent2D& extent) {
        return setExtent(VkExtent3D{extent.width, extent.height, 1});
    }
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
    Self setMemoryPool(const DeviceMemoryPool* pool);

    Res<Image> into(const CoreApi& api) const;
};

/**
 * @brief Vulkan image
 *
 * Image memory layout with different depth, mip level and array layer:
 * ```
 *         Image3D     Image2DArray
 * level   0     1     0  1 0  1
 * layer   0     0     0    1
 * depth   0  1  0 1   0    0
 *         ## ## % %   ## % ## %
 *         ## ##       ##   ##
 * ```
 * Note that:
 *  - Image3D: array layers must be 1
 *  - Image2DArray: depth must be 1
 */
struct Image : public CoreResource<VkImage, VK_OBJECT_TYPE_IMAGE> {
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

protected:
    explicit Image(const CoreApi& api) : CoreResource(api) {}

public:
    Image(Image&&);
    ~Image();
    OnConstType(VkDeviceMemory, memory);

    /**
     * @brief Get image subresource layout
     *
     * @param aspect The 0 (VK_IMAGE_ASPECT_NONE) means auto select the image aspect
     */
    VkSubresourceLayout getSubresourceLayout(uint32_t mip = 0, uint32_t layer = 0, VkImageAspectFlags aspect = 0) const;
    /**
     * @brief Copy data from cpu memory `src` into gpu image memory
     *
     * Compute image pixel size according to VkFormat. Note that 3-channel format takes 4-channel memory.
     * Examples:
     *  - R8_UNORM          : w * h * 1 * sizeof(uint8)
     *  - R16G16_SINT       : w * h * 2 * sizeof(uint16)
     *  - R32G32B32_SFLOAT  : w * h * 4 * sizeof(uint32)
     *  - R32G32B32A32_UINT : w * h * 4 * sizeof(uint32)
     *
     * @param src_size The `src` size in bytes
     * @param mip The image mip level to copy into
     * @param layer The image array layer to copy into
     */
    bool copyFrom(const void* src, const VkDeviceSize src_size, uint32_t mip = 0, uint32_t layer = 0) const;
    /**
     * @brief Copy data from gpu image memory to cpu memory `dst`
     *
     * @param dst_size The `dst` size in bytes
     * @param mip The image mip level to copy from
     * @param layer The image array layer to copy from
     */
    bool copyInto(void* dst, const VkDeviceSize dst_size, uint32_t mip = 0, uint32_t layer = 0) const;
    Res<void*> map() const;
    void unmap() const;
    VkResult getFd(int& fd, VkExternalMemoryHandleTypeFlagBits hdl_type = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT);
    VkResult getWin32Handle(HANDLE& hdl,
                            VkExternalMemoryHandleTypeFlagBits hdl_type = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT);

    static Res<Image> from(const CoreApi& api, const ImageState& info);
    /**
     * @brief Borrow image with already allocated handle (e.g. for swapchain images)
     */
    static Image borrow(const CoreApi& api,
                        const VkImage image,
                        VkFormat format,
                        VkExtent3D extent,
                        uint32_t mip_levels = 1,
                        uint32_t array_layers = 1,
                        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                        VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL,
                        VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT);
};

/**
 * @brief Check format is depth only
 */
bool isDepthOnlyFormat(VkFormat format);

/**
 * @brief Check format is stencil only
 */
bool isStencilOnlyFormat(VkFormat format);

/**
 * @brief Check format is depth or stencil
 */
bool isDepthStencilFormat(VkFormat format);

/**
 * @brief Get image aspect from format
 */
VkImageAspectFlags getAspectMask(VkFormat format);

template <>
class Arg<Image> : private NonCopyable {
public:
    VkImageAspectFlags aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    uint32_t mip = 0; /**< Base mip level or the mip level index */
    uint32_t mip_count = 1;
    uint32_t layer = 0; /**< Base layer or the layer index */
    uint32_t layer_count = 1;

public:
    const Image& a;

public:
    explicit Arg(const Image& a) : a(a) {
        aspect = getAspectMask(a.format);
        mip = 0;
        mip_count = a.mip_levels;
        layer = 0;
        layer_count = a.array_layers;
    }
    OnConstType(VkImage, a.handle);
    operator VkImageSubresourceRange() const {
        return VkImageSubresourceRange{aspect, mip, mip_count, layer, layer_count};
    }
    operator VkImageSubresourceLayers() const {
        return VkImageSubresourceLayers{aspect, mip, layer, layer_count};
    }
    operator VkImageSubresource() const {
        return VkImageSubresource{aspect, mip, layer};
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::Image> {
    inline size_t operator()(const vkt::core::Image& image) const {
        return hash<VkImage>{}(image);
    }
};

NAMESPACE_END(std)
