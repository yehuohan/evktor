#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ImageBuilder::Self;

Image::Image(Image&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    type = rhs.type;
    format = rhs.format;
    extent = rhs.extent;
    mip_levels = rhs.mip_levels;
    array_layers = rhs.array_layers;
    memory = rhs.memory;
    rhs.memory = VK_NULL_HANDLE;
    allocation = rhs.allocation;
    rhs.allocation = VK_NULL_HANDLE;
}

Image::~Image() {
    if (handle) {
        if (allocation) {
            vmaDestroyImage(device, handle, allocation);
        } else {
            vkFreeMemory(device, memory, nullptr);
            vkDestroyImage(device, handle, nullptr);
        }
    }
    handle = VK_NULL_HANDLE;
    memory = VK_NULL_HANDLE;
}

void Image::copyFrom(const void* src, const VkDeviceSize src_size) const {
    VkDeviceSize copy_size = src_size;
    void* data;
    vmaMapMemory(device, allocation, &data);
    std::memcpy(data, src, (size_t)copy_size);
    vmaUnmapMemory(device, allocation);
}

void Image::genMipmaps(const CommandBuffer& cmdbuf) const {
    int32_t mip_wid = extent.width;
    int32_t mip_hei = extent.height;

    cmdbuf.begin();
    auto barrier = Itor::ImageMemoryBarrier();
    barrier.image = handle;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.subresourceRange.levelCount = 1;
    for (uint32_t k = 1; k < mip_levels; k++) {
        barrier.subresourceRange.baseMipLevel = k - 1;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        cmdbuf.cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 1, &barrier);

        VkImageBlit blit{};
        blit.srcOffsets[0] = VkOffset3D{0, 0, 0};
        blit.srcOffsets[1] = VkOffset3D{mip_wid, mip_hei, 1};
        blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        blit.srcSubresource.mipLevel = k - 1;
        blit.srcSubresource.baseArrayLayer = 0;
        blit.srcSubresource.layerCount = 1;

        // Copy from image.mipLevel[k - 1] to image.mipLevel[k] with linear
        if (mip_wid > 1) {
            mip_wid >>= 1;
        }
        if (mip_hei > 1) {
            mip_hei >>= 1;
        }

        blit.dstOffsets[0] = VkOffset3D{0, 0, 0};
        blit.dstOffsets[1] = VkOffset3D{mip_wid, mip_hei, 1};
        blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        blit.dstSubresource.mipLevel = k;
        blit.dstSubresource.baseArrayLayer = 0;
        blit.dstSubresource.layerCount = 1;
        vkCmdBlitImage(cmdbuf,
                       handle,
                       VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                       handle,
                       VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       1,
                       &blit,
                       VK_FILTER_LINEAR);

        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        cmdbuf.cmdImageMemoryBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 1, &barrier);
    }
    cmdbuf.end();

    device.queues.transfer->submit(cmdbuf);
    device.queues.transfer->waitIdle();
}

Self ImageBuilder::setFormat(VkFormat format) {
    info.format = format;
    return *this;
}

Self ImageBuilder::setExtent(const VkExtent3D& extent) {
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

    info.extent = extent;
    info.type = type;
    return *this;
}

Self ImageBuilder::setMipLevels(uint32_t mip_levels) {
    info.mip_levels = mip_levels;
    return *this;
}

Self ImageBuilder::setArrayLayers(uint32_t array_layers) {
    info.array_layers = array_layers;
    return *this;
}

Self ImageBuilder::setSamples(VkSampleCountFlagBits samples) {
    info.samples = samples;
    return *this;
}

Self ImageBuilder::setTiling(VkImageTiling tiling) {
    info.tiling = tiling;
    return *this;
}

Self ImageBuilder::setUsage(VkImageUsageFlags usage) {
    info.usage = usage;
    return *this;
}

Self ImageBuilder::setMemoryFlags(VmaAllocationCreateFlags flags) {
    if ((flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT) ||
        (flags & VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT)) {
        if (info.tiling != VK_IMAGE_TILING_LINEAR) {
            LogW("Image should use linear tiling for host access");
        }
    }
    info.memory_flags = flags;
    return *this;
}

Self ImageBuilder::setMemoryUsage(VmaMemoryUsage usage) {
    info.memory_usage = usage;
    return *this;
}

ImageBuilder::Built ImageBuilder::build() {
    Image image(device, std::move(info.__name));

    auto image_ci = Itor::ImageCreateInfo();
    image_ci.flags = info.flags;
    image_ci.imageType = info.type;
    image_ci.format = info.format;
    image_ci.extent = info.extent;
    image_ci.mipLevels = info.mip_levels;
    image_ci.arrayLayers = info.array_layers;
    image_ci.samples = info.samples;
    image_ci.tiling = info.tiling;
    image_ci.usage = info.usage;
    image_ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_ci.queueFamilyIndexCount = 0;
    image_ci.pQueueFamilyIndices = nullptr;
    image_ci.initialLayout = info.initial_layout;

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = info.memory_flags;
    allocation_ci.usage = info.memory_usage;
    VmaAllocationInfo allocation_info{};

    OnRet(vmaCreateImage(device, &image_ci, &allocation_ci, image, &image.allocation, &allocation_info),
          "Failed to create image");
    OnName(image);
    image.type = info.type;
    image.format = info.format;
    image.extent = info.extent;
    image.mip_levels = info.mip_levels;
    image.array_layers = info.array_layers;
    image.memory = allocation_info.deviceMemory;

    return Ok(std::move(image));
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
