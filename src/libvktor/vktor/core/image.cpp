#include "image.hpp"
#include "utils.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ImageState::Self;

static VkImageType getType(const VkExtent3D& extent) {
    uint32_t dim = 0;
    if (extent.width >= 1) {
        dim++;
    }
    if (extent.height >= 1) {
        dim++;
    }
    if (extent.depth > 1) {
        dim++;
    }

    VkImageType type = VK_IMAGE_TYPE_2D;
    switch (dim) {
    case 1: type = VK_IMAGE_TYPE_1D; break;
    case 2: type = VK_IMAGE_TYPE_2D; break;
    case 3: type = VK_IMAGE_TYPE_3D; break;
    }
    return type;
}

Self ImageState::setFormat(VkFormat format) {
    image_ci.format = format;
    return *this;
}

Self ImageState::setExtent(const VkExtent3D& extent) {
    image_ci.extent = extent;
    image_ci.imageType = getType(extent);
    return *this;
}

Self ImageState::setMipLevels(uint32_t mip_levels) {
    image_ci.mipLevels = mip_levels;
    return *this;
}

Self ImageState::setArrayLayers(uint32_t array_layers) {
    image_ci.arrayLayers = array_layers;
    return *this;
}

Self ImageState::setSamples(VkSampleCountFlagBits samples) {
    image_ci.samples = samples;
    return *this;
}

Self ImageState::setTiling(VkImageTiling tiling) {
    image_ci.tiling = tiling;
    return *this;
}

Self ImageState::setUsage(VkImageUsageFlags usage) {
    image_ci.usage = usage;
    return *this;
}

Self ImageState::setLayout(VkImageLayout layout) {
    image_ci.initialLayout = layout;
    return *this;
}

Self ImageState::setMemoryFlags(VmaAllocationCreateFlags flags) {
    if ((flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT) ||
        (flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT)) {
        if (image_ci.tiling != VK_IMAGE_TILING_LINEAR) {
            vktLogW("Image should use linear tiling for host access");
        }
    }
    memory_flags = flags;
    return *this;
}

Self ImageState::setMemoryUsage(VmaMemoryUsage usage) {
    memory_usage = usage;
    return *this;
}

Res<Image> ImageState::into(const Device& device) const {
    return Image::from(device, *this);
}

Image::Image(Image&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    memory = rhs.memory;
    rhs.memory = VK_NULL_HANDLE;
    allocation = rhs.allocation;
    rhs.allocation = VK_NULL_HANDLE;

    type = rhs.type;
    format = rhs.format;
    extent = rhs.extent;
    mip_levels = rhs.mip_levels;
    array_layers = rhs.array_layers;
    samples = rhs.samples;
    tiling = rhs.tiling;
    usage = rhs.usage;
    layout = rhs.layout;
}

Image::~Image() {
    if (!__borrowed && handle) {
        if (allocation) {
            vmaDestroyImage(device, handle, allocation);
        } else {
            vkFreeMemory(device, memory, nullptr);
            vkDestroyImage(device, handle, nullptr);
        }
    }
    handle = VK_NULL_HANDLE;
    memory = VK_NULL_HANDLE;
    allocation = VK_NULL_HANDLE;
}

VkSubresourceLayout Image::getSubresourceLayout(uint32_t mip, uint32_t layer, VkImageAspectFlags aspect) const {
    VkImageSubresource subresource;
    subresource.aspectMask = aspect == 0 ? getAspectMask(format) : aspect;
    subresource.mipLevel = mip;
    subresource.arrayLayer = layer;
    VkSubresourceLayout subresource_layout;
    vkGetImageSubresourceLayout(device, handle, &subresource, &subresource_layout);
    return subresource_layout;
}

bool Image::copyFrom(const void* src, const VkDeviceSize src_size, uint32_t mip, uint32_t layer) const {
    VkSubresourceLayout subresource_layout = getSubresourceLayout(mip, layer);
    VkDeviceSize mem_size = std::min<VkDeviceSize>(src_size, subresource_layout.size);
    VkDeviceSize offset = subresource_layout.offset;

    void* data;
    auto ret = vmaMapMemory(device, allocation, &data);
    if (VK_SUCCESS != ret) {
        vktLogE("Failed to map image memory: {}", VkStr(VkResult, ret));
        return false;
    }
    std::memcpy((uint8_t*)data + offset, src, (size_t)mem_size);
    vmaUnmapMemory(device, allocation);
    return true;
}

bool Image::copyInto(void* dst, const VkDeviceSize dst_size = 0, uint32_t mip, uint32_t layer) const {
    VkSubresourceLayout subresource_layout = getSubresourceLayout(mip, layer);
    VkDeviceSize mem_size = std::min<VkDeviceSize>(dst_size, subresource_layout.size);
    VkDeviceSize offset = subresource_layout.offset;

    void* data;
    auto ret = vmaMapMemory(device, allocation, &data);
    if (VK_SUCCESS != ret) {
        vktLogE("Failed to map image memory: {}", VkStr(VkResult, ret));
        return false;
    }
    std::memcpy(dst, (uint8_t*)data + offset, (size_t)mem_size);
    vmaUnmapMemory(device, allocation);
    return true;
}

Res<void*> Image::map() const {
    void* data;
    OnRet(vmaMapMemory(device, allocation, &data), "Failed to map image memory");
    return Ok(data);
}
void Image::unmap() const {
    vmaUnmapMemory(device, allocation);
}

Res<Image> Image::from(const Device& device, const ImageState& info) {
    Image image(device);

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = info.memory_flags;
    allocation_ci.usage = info.memory_usage;
    VmaAllocationInfo allocation_info{};

    OnRet(vmaCreateImage(device, &info.image_ci, &allocation_ci, image, &image.allocation, &allocation_info),
          "Failed to create image");
    OnName(image, info.__name);
    image.type = info.image_ci.imageType;
    image.format = info.image_ci.format;
    image.extent = info.image_ci.extent;
    image.mip_levels = info.image_ci.mipLevels;
    image.array_layers = info.image_ci.arrayLayers;
    image.samples = info.image_ci.samples;
    image.tiling = info.image_ci.tiling;
    image.usage = info.image_ci.usage;
    image.layout = info.image_ci.initialLayout;
    image.memory = allocation_info.deviceMemory;

    return Ok(std::move(image));
}

Image Image::borrow(const Device& device,
                    const VkImage _image,
                    VkFormat _format,
                    VkExtent3D _extent,
                    uint32_t _mip_levels,
                    uint32_t _array_layers,
                    VkSampleCountFlagBits _samples,
                    VkImageTiling _tiling,
                    VkImageUsageFlags _usage) {
    if (VK_NULL_HANDLE == _image) {
        vktLogW("Create Image should from a existed & valid VkImage");
    }
    Image image(device);
    image.__borrowed = true;
    image.handle = _image;
    image.type = getType(_extent);
    image.format = _format;
    image.extent = _extent;
    image.mip_levels = _mip_levels;
    image.array_layers = _array_layers;
    image.samples = _samples;
    image.tiling = _tiling;
    image.usage = _usage;
    return std::move(image);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
