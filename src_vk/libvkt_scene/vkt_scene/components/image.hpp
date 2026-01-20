#pragma once
#include "../component.hpp"
#include <vktor/core/image.hpp>
#include <vktor/core/image_view.hpp>

NAMESPACE_BEGIN(vktscn)

class Image : public Component {
private:
    vkt::core::Image image;
    vkt::core::ImageView imageview;

public:
    Image(vkt::core::Image&& image, vkt::core::ImageView&& imageview, const String& name)
        : Component(name)
        , image(std::move(image))
        , imageview(std::move(imageview)) {}
    virtual ~Image() = default;

    OnConstType(VkImage, image.getHandle());
    OnConstType(VkImageView, imageview.getHandle());

    virtual std::type_index getType() const override {
        return typeid(Image);
    }
};

NAMESPACE_END(vktscn)
