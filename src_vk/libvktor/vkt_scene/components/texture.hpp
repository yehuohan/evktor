#pragma once
#include "../component.hpp"
#include "image.hpp"
#include "sampler.hpp"

NAMESPACE_BEGIN(vktscn)

class Texture : public Component {
private:
    const Image* image = nullptr;
    const Sampler* sampler = nullptr;

public:
    Texture(const String& name = "") : Component(name) {}
    virtual ~Texture() = default;

    virtual std::type_index getType() const override {
        return typeid(Texture);
    }

public:
    inline void setImage(const Image& _image) {
        image = &_image;
    }
    const Image* getImage() const {
        return image;
    }
    inline void setSampler(const Sampler& _sampler) {
        sampler = &_sampler;
    }
    const Sampler* getSampler() const {
        return sampler;
    }
};

NAMESPACE_END(vktscn)
