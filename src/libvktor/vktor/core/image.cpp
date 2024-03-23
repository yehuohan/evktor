#include "image.hpp"

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
            LogW("Image should use linear tiling for host access");
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

bool Image::copyFrom(const void* src, const VkDeviceSize src_size) const {
    VkDeviceSize copy_size = src_size;
    void* data;
    auto ret = vmaMapMemory(device, allocation, &data);
    if (VK_SUCCESS != ret) {
        LogE("Failed to map image memory: {}", VkStr(VkResult, ret));
        return false;
    }
    std::memcpy((uint8_t*)data, src, (size_t)copy_size);
    vmaUnmapMemory(device, allocation);
    return true;
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
        LogW("Create Image should from a existed & valid VkImage");
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

bool isDepthOnlyFormat(VkFormat format) {
    return format == VK_FORMAT_D16_UNORM || format == VK_FORMAT_D32_SFLOAT;
}

bool isDepthStencilFormat(VkFormat format) {
    return format == VK_FORMAT_D16_UNORM_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT ||
           format == VK_FORMAT_D32_SFLOAT_S8_UINT || isDepthOnlyFormat(format);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
