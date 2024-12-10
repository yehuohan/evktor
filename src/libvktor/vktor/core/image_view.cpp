#include "image_view.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ImageViewState::Self;

Self ImageViewState::setFromImage(const Image& image) {
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
    imageview_ci.subresourceRange.aspectMask = getAspectMask(image.format);
    imageview_ci.subresourceRange.baseMipLevel = 0;
    imageview_ci.subresourceRange.levelCount = image.mip_levels;
    imageview_ci.subresourceRange.baseArrayLayer = 0;
    imageview_ci.subresourceRange.layerCount = image.array_layers;
    return *this;
}

Self ImageViewState::setImage(VkImage image) {
    imageview_ci.image = image;
    return *this;
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

Res<ImageView> ImageViewState::into(const CoreApi& api) const {
    return ImageView::from(api, *this);
}

ImageView::ImageView(ImageView&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    image = rhs.image;
    rhs.image = VK_NULL_HANDLE;
    subresource_range = rhs.subresource_range;
}

ImageView::~ImageView() {
    if (!__borrowed && handle) {
        vkDestroyImageView(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
    image = VK_NULL_HANDLE;
}

Res<ImageView> ImageView::from(const CoreApi& api, const ImageViewState& info) {
    ImageView imageview(api);

    OnRet(vkCreateImageView(api, &info.imageview_ci, api, imageview), "Failed to create image view");
    OnName(imageview, info.__name);
    imageview.image = info.imageview_ci.image;
    imageview.subresource_range = info.imageview_ci.subresourceRange;

    return Ok(std::move(imageview));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
