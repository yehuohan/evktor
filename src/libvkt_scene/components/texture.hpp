#pragma once
#include "component.hpp"
#include "image.hpp"
#include "sampler.hpp"

NAMESPACE_BEGIN(vktscn)

class Texture : public Component {
private:
    Image* image = nullptr;
    Sampler* sampler = nullptr;

public:
    Texture(const String& name) : Component(name) {}
    Texture(Texture&& other) = default;
    virtual ~Texture() = default;

    virtual operator std::type_index() override {
        return typeid(Texture);
    }

    inline void setImage(Image& _image) {
        image = &_image;
    }
    inline void setSampler(Sampler& _sampler) {
        sampler = &_sampler;
    }
    inline Image* getImage() {
        return image;
    }
    inline Sampler* getSample() const {
        return sampler;
    }
};

NAMESPACE_END(vktscn)
