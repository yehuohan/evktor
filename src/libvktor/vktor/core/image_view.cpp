#include "image_view.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ImageViewState::Self;

ImageViewState::ImageViewState(const Image& image, Name&& name) : CoreStater(std::move(name)), image(image) {
    imageview_ci = Itor::ImageViewCreateInfo();
    imageview_ci.flags = 0;
    imageview_ci.image = image;
    imageview_ci.components = VkComponentMapping{
        VK_COMPONENT_SWIZZLE_R,
        VK_COMPONENT_SWIZZLE_G,
        VK_COMPONENT_SWIZZLE_B,
        VK_COMPONENT_SWIZZLE_A,
    };
    bool is_array = image.array_layers > 1;
    switch (image.type) {
    case VK_IMAGE_TYPE_1D: imageview_ci.viewType = is_array ? VK_IMAGE_VIEW_TYPE_1D_ARRAY : VK_IMAGE_VIEW_TYPE_1D; break;
    case VK_IMAGE_TYPE_2D: imageview_ci.viewType = is_array ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_2D; break;
    case VK_IMAGE_TYPE_3D: imageview_ci.viewType = VK_IMAGE_VIEW_TYPE_3D; break;
    default: break;
    };
    imageview_ci.format = image.format;
    if (isDepthStencilFormat(image.format)) {
        imageview_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    } else {
        imageview_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }
    imageview_ci.subresourceRange.baseMipLevel = 0;
    imageview_ci.subresourceRange.levelCount = image.mip_levels;
    imageview_ci.subresourceRange.baseArrayLayer = 0;
    imageview_ci.subresourceRange.layerCount = image.array_layers;
}

Self ImageViewState::setType(VkImageViewType type) {
    imageview_ci.viewType = type;
    return *this;
}

Self ImageViewState::setFormat(VkFormat format) {
    imageview_ci.format = format;
    return *this;
}

Self ImageViewState::setSwizzleRGBA(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a) {
    imageview_ci.components.r = r;
    imageview_ci.components.g = g;
    imageview_ci.components.b = b;
    imageview_ci.components.a = a;
    return *this;
}

Self ImageViewState::setAspect(VkImageAspectFlags aspect) {
    imageview_ci.subresourceRange.aspectMask = aspect;
    return *this;
}

Self ImageViewState::setMipRange(uint32_t base, uint32_t count) {
    imageview_ci.subresourceRange.baseMipLevel = base;
    imageview_ci.subresourceRange.levelCount = count;
    return *this;
}

Self ImageViewState::setArrayRange(uint32_t base, uint32_t count) {
    imageview_ci.subresourceRange.baseArrayLayer = base;
    imageview_ci.subresourceRange.layerCount = count;
    return *this;
}

Res<ImageView> ImageViewState::into() const {
    return ImageView::from(*this);
}

ImageView::ImageView(ImageView&& rhs) : CoreResource(rhs.device), image(rhs.image) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

ImageView::~ImageView() {
    if (!__borrowed && handle) {
        vkDestroyImageView(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<ImageView> ImageView::from(const ImageViewState& info) {
    ImageView imageview(info.image);

    OnRet(vkCreateImageView(info.image.device, &info.imageview_ci, nullptr, imageview), "Failed to create image view");
    OnName(imageview, info.__name);
    imageview.subresource_range = info.imageview_ci.subresourceRange;

    return Ok(std::move(imageview));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
