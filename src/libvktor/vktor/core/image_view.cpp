#include "image_view.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ImageViewBuilder::Self;

ImageView::ImageView(ImageView&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)), image(rhs.image) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

ImageView::~ImageView() {
    if (handle) {
        vkDestroyImageView(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

ImageViewBuilder::ImageViewBuilder(const Image& image, Name&& name) : Builder(std::move(name)), image(image) {
    info.imageview_ci = Itor::ImageViewCreateInfo();
    info.imageview_ci.flags = 0;
    info.imageview_ci.image = image;
    info.imageview_ci.components = VkComponentMapping{
        VK_COMPONENT_SWIZZLE_R,
        VK_COMPONENT_SWIZZLE_G,
        VK_COMPONENT_SWIZZLE_B,
        VK_COMPONENT_SWIZZLE_A,
    };
    bool is_array = image.array_layers > 1;
    switch (image.type) {
    case VK_IMAGE_TYPE_1D: info.imageview_ci.viewType = is_array ? VK_IMAGE_VIEW_TYPE_1D_ARRAY : VK_IMAGE_VIEW_TYPE_1D; break;
    case VK_IMAGE_TYPE_2D: info.imageview_ci.viewType = is_array ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_2D; break;
    case VK_IMAGE_TYPE_3D: info.imageview_ci.viewType = VK_IMAGE_VIEW_TYPE_3D; break;
    default: break;
    };
    info.imageview_ci.format = image.format;
    if (isDepthStencilFormat(image.format)) {
        info.imageview_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    } else {
        info.imageview_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }
    info.imageview_ci.subresourceRange.baseMipLevel = 0;
    info.imageview_ci.subresourceRange.levelCount = image.mip_levels;
    info.imageview_ci.subresourceRange.baseArrayLayer = 0;
    info.imageview_ci.subresourceRange.layerCount = image.array_layers;
}

Self ImageViewBuilder::setType(VkImageViewType type) {
    info.imageview_ci.viewType = type;
    return *this;
}

Self ImageViewBuilder::setFormat(VkFormat format) {
    info.imageview_ci.format = format;
    return *this;
}

Self ImageViewBuilder::setSwizzleRGBA(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a) {
    info.imageview_ci.components.r = r;
    info.imageview_ci.components.g = g;
    info.imageview_ci.components.b = b;
    info.imageview_ci.components.a = a;
    return *this;
}

Self ImageViewBuilder::setAspect(VkImageAspectFlags aspect) {
    info.imageview_ci.subresourceRange.aspectMask = aspect;
    return *this;
}

Self ImageViewBuilder::setMipRange(uint32_t base, uint32_t count) {
    info.imageview_ci.subresourceRange.baseMipLevel = base;
    info.imageview_ci.subresourceRange.levelCount = count;
    return *this;
}

Self ImageViewBuilder::setArrayRange(uint32_t base, uint32_t count) {
    info.imageview_ci.subresourceRange.baseArrayLayer = base;
    info.imageview_ci.subresourceRange.layerCount = count;
    return *this;
}

ImageViewBuilder::Built ImageViewBuilder::build() {
    ImageView imageview(image, std::move(info.__name));

    OnRet(vkCreateImageView(image.device, &info.imageview_ci, nullptr, imageview), "Failed to create image view");
    OnName(imageview);
    imageview.subresource_range = info.imageview_ci.subresourceRange;

    return Ok(std::move(imageview));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
