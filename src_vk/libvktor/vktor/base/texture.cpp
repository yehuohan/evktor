#include "texture.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Texture::Texture(core::Image&& image, ImageView&& imageview) : image(std::move(image)), imageview(std::move(imageview)) {}

Texture::Texture(Texture&& rhs) : image(std::move(rhs.image)), imageview(std::move(rhs.imageview)) {}

Texture2D::Texture2D(core::Image&& image, ImageView&& imageview) : Texture(std::move(image), std::move(imageview)) {}

Res<Texture2D> Texture2D::from(const CoreApi& api,
                               VkFormat format,
                               const VkExtent2D& extent,
                               Usage usage,
                               uint32_t mip_levels,
                               Sample samples) {
    auto res_image = ImageState()
                         .setFormat(format)
                         .setExtent(extent)
                         .setUsage(static_cast<VkImageUsageFlags>(usage))
                         .setMipLevels(mip_levels)
                         .setSamples(static_cast<VkSampleCountFlagBits>(samples))
                         .into(api);
    OnErr(res_image);
    auto image = res_image.unwrap();

    auto res_view = ImageViewState().setFromImage(image).into(api);
    OnErr(res_view);

    return Ok(Texture2D(std::move(image), res_view.unwrap()));
}

TextureCube::TextureCube(core::Image&& image, core::ImageView&& imageview) : Texture(std::move(image), std::move(imageview)) {}

Res<TextureCube> TextureCube::from(const core::CoreApi& api,
                                   VkFormat format,
                                   const VkExtent2D& extent,
                                   Usage usage,
                                   uint32_t mip_levels,
                                   Sample samples) {
    auto res_image = ImageState()
                         .setFlags(VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT)
                         .setFormat(format)
                         .setExtent(extent)
                         .setUsage(static_cast<VkImageUsageFlags>(usage))
                         .setMipLevels(mip_levels)
                         .setArrayLayers(6)
                         .setSamples(static_cast<VkSampleCountFlagBits>(samples))
                         .into(api);
    OnErr(res_image);
    auto image = res_image.unwrap();

    auto res_view = ImageViewState().setFromImage(image).setType(VK_IMAGE_VIEW_TYPE_CUBE).into(api);
    OnErr(res_view);

    return Ok(TextureCube(std::move(image), res_view.unwrap()));
}

NAMESPACE_END(vkt)
