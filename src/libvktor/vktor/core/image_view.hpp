#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ImageView : public BuiltResource<VkImageView, VK_OBJECT_TYPE_IMAGE_VIEW, Device> {
    const VkImage image;

    ImageView(const Device& device, VkImage image, Name&& name) : BuiltResource(device, std::move(name)), image(image) {}
    ImageView(ImageView&&);
    ~ImageView();
};

struct ImageViewInfo : public BuilderInfo {
    VkImageViewCreateFlags flags = 0;
    VkImageViewType type = VK_IMAGE_VIEW_TYPE_2D;
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkComponentMapping components{};
    VkImageSubresourceRange subresource_range{};
};

class ImageViewBuilder : public Builder<ImageViewBuilder, ImageView, ImageViewInfo> {
private:
    const Device& device;
    const VkImage image;

public:
    explicit ImageViewBuilder(const Device& device, VkImage image, Name&& name = "ImageView")
        : Builder(std::move(name))
        , device(device)
        , image(image) {}
    virtual Built build() override;

    Self setFromImage(const Image& image);
    Self setType(VkImageViewType type);
    Self setFormat(VkFormat format);
    Self setSwizzleRGBA(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a);
    Self setAspect(VkImageAspectFlags aspect);
    Self setMipRange(uint32_t base, uint32_t count);
    Self setArrayRange(uint32_t base, uint32_t count);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
