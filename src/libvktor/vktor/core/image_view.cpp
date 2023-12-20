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
    switch (image.type) {
    case VK_IMAGE_TYPE_1D: info.type = image.array_layers > 1 ? VK_IMAGE_VIEW_TYPE_1D_ARRAY : VK_IMAGE_VIEW_TYPE_1D; break;
    case VK_IMAGE_TYPE_2D: info.type = image.array_layers > 1 ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_2D; break;
    case VK_IMAGE_TYPE_3D: info.type = VK_IMAGE_VIEW_TYPE_3D; break;
    default: break;
    };
    info.format = image.format;
    if (isDepthStencilFormat(image.format)) {
        info.subresource_range.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    } else {
        info.subresource_range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }
    info.subresource_range.baseMipLevel = 0;
    info.subresource_range.levelCount = image.mip_levels;
    info.subresource_range.baseArrayLayer = 0;
    info.subresource_range.layerCount = image.array_layers;
}

Self ImageViewBuilder::setType(VkImageViewType type) {
    info.type = type;
    return *this;
}

Self ImageViewBuilder::setFormat(VkFormat format) {
    info.format = format;
    return *this;
}

Self ImageViewBuilder::setSwizzleRGBA(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a) {
    info.components.r = r;
    info.components.g = g;
    info.components.b = b;
    info.components.a = a;
    return *this;
}

Self ImageViewBuilder::setAspect(VkImageAspectFlags aspect) {
    info.subresource_range.aspectMask = aspect;
    return *this;
}

Self ImageViewBuilder::setMipRange(uint32_t base, uint32_t count) {
    info.subresource_range.baseMipLevel = base;
    info.subresource_range.levelCount = count;
    return *this;
}

Self ImageViewBuilder::setArrayRange(uint32_t base, uint32_t count) {
    info.subresource_range.baseArrayLayer = base;
    info.subresource_range.layerCount = count;
    return *this;
}

ImageViewBuilder::Built ImageViewBuilder::build() {
    ImageView imageview(image, std::move(info.__name));

    auto imageview_ci = Itor::ImageViewCreateInfo();
    imageview_ci.image = image;
    imageview_ci.viewType = info.type;
    imageview_ci.format = info.format;
    imageview_ci.components = info.components;
    imageview_ci.subresourceRange = info.subresource_range;

    OnRet(vkCreateImageView(image.device, &imageview_ci, nullptr, imageview), "Failed to create image view");
    OnName(imageview);

    return Ok(std::move(imageview));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
