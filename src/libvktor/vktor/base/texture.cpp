#include "texture.hpp"

NAMESPACE_BEGIN(vkt)

Texture::Texture(core::Image&& image, core::ImageView&& imageview) : image(std::move(image)), imageview(std::move(imageview)) {}

Texture::Texture(Texture&& rhs) : image(std::move(rhs.image)), imageview(std::move(rhs.imageview)) {}

NAMESPACE_END(vkt)
