#pragma once
#include "__core.hpp"
#include "device.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ImageView;

class ImageViewState : public CoreStater<ImageViewState> {
    friend struct ImageView;

private:
    VkImageViewCreateInfo imageview_ci{};

public:
    explicit ImageViewState(Name&& name = "ImageView") : CoreStater(std::move(name)) {}

    Self setFromImage(const Image& image);
    Self setImage(VkImage image);
    Self setType(VkImageViewType type);
    Self setFormat(VkFormat format);
    Self setSwizzleRGBA(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a);
    Self setAspect(VkImageAspectFlags aspect);
    Self setMipRange(uint32_t base, uint32_t count);
    Self setArrayRange(uint32_t base, uint32_t count);

    Res<ImageView> into(const Device& device) const;
};

struct ImageView : public CoreResource<VkImageView, VK_OBJECT_TYPE_IMAGE_VIEW, Device> {
    VkImage image = VK_NULL_HANDLE; /**< Store the image that this image view created for */
    VkImageSubresourceRange subresource_range{VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

    ImageView(const Device& device) : CoreResource(device) {}
    ImageView(ImageView&&);
    ~ImageView();

    static Res<ImageView> from(const Device& device, const ImageViewState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::ImageView> {
    inline size_t operator()(const vkt::core::ImageView& imageview) const {
        return hash<VkImageView>{}(imageview);
    }
};

NAMESPACE_END(std)
