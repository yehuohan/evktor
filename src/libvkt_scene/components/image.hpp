#pragma once
#include "component.hpp"
#include <vktor/core/image.hpp>
#include <vktor/core/image_view.hpp>

NAMESPACE_BEGIN(vktscn)

/**
 * @brief Mipmap information
 */
struct Mipmap {
    uint32_t level = 0;            /**< Mipmap level */
    uint32_t offset = 0;           /**< Byte offset used for uploading */
    VkExtent3D extent = {0, 0, 0}; /**< Width depth and height of the mipmap */
};

class Image : public Component {
private:
    Box<vkt::core::Image> image;
    Box<vkt::core::ImageView> imageview;

public:
    Image(const String& name) : Component(name) {}
    virtual ~Image() = default;

    virtual operator std::type_index() override {
        return typeid(Image);
    }

    inline const vkt::core::Image& getImage() const {
        return *image;
    }
    inline const vkt::core::ImageView& getImageView() const {
        return *imageview;
    }
};

NAMESPACE_END(vktscn)
