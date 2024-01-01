#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ImageView : public BuiltResource<VkImageView, VK_OBJECT_TYPE_IMAGE_VIEW, Device> {
    const Image& image;

    VkImageSubresourceRange subresource_range{VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

    ImageView(const Image& image, Name&& name) : BuiltResource(image.device, std::move(name)), image(image) {}
    ImageView(ImageView&&);
    ~ImageView();
};

struct ImageViewInfo : public BuilderInfo {
    VkImageViewCreateFlags flags = 0;
    VkImageViewType type = VK_IMAGE_VIEW_TYPE_2D;
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkComponentMapping components{
        VK_COMPONENT_SWIZZLE_R,
        VK_COMPONENT_SWIZZLE_G,
        VK_COMPONENT_SWIZZLE_B,
        VK_COMPONENT_SWIZZLE_A,
    };
    VkImageSubresourceRange subresource_range{VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
};

class ImageViewBuilder : public Builder<ImageViewBuilder, ImageView, ImageViewInfo> {
private:
    const Image& image;

public:
    explicit ImageViewBuilder(const Image& image, Name&& name = "ImageView");
    virtual Built build() override;

    Self setType(VkImageViewType type);
    Self setFormat(VkFormat format);
    Self setSwizzleRGBA(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a);
    Self setAspect(VkImageAspectFlags aspect);
    Self setMipRange(uint32_t base, uint32_t count);
    Self setArrayRange(uint32_t base, uint32_t count);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::ImageView> {
    size_t operator()(const vkt::core::ImageView& imageview) const {
        return hash<VkImageView>{}(imageview);
    }
};

NAMESPACE_END(std)
