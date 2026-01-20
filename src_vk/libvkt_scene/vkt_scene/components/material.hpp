#pragma once
#include "../component.hpp"
#include "texture.hpp"

NAMESPACE_BEGIN(vktscn)

class Material : public Component {
private:
    HashMap<String, const Texture*> textures{};

public:
    Material(const std::string& name = "") : Component(name) {}
    virtual ~Material() = default;

    virtual std::type_index getType() const override {
        return typeid(Material);
    }

public:
    inline void setTexture(const String& attr_name, const Texture& texture) {
        textures[attr_name] = &texture;
    }
    const Texture* getTexture(const String& attr_name) const;
};

NAMESPACE_END(vktscn)
