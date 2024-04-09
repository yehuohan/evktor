#pragma once
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"

NAMESPACE_BEGIN(vkt)

class Texture : private NonCopyable {
private:
    core::Image image;
    core::ImageView imageview;

public:
    explicit Texture(core::Image&& image, core::ImageView&& imageview);
    Texture(Texture&&);

    inline const core::Image& getImage() const {
        return image;
    }
    inline const core::ImageView& getImageView() const {
        return imageview;
    }
};

class Texture2D : public Texture {};

class Texture2DArray : public Texture2D {};

class Texture3D : public Texture {};

class TextureCube : public Texture {};

NAMESPACE_END(vkt)
