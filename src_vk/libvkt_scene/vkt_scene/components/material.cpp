#include "material.hpp"

NAMESPACE_BEGIN(vktscn)

const Texture* Material::getTexture(const String& attr_name) const {
    if (auto it = textures.find(attr_name); it != textures.end()) {
        return it->second;
    }
    return nullptr;
}

NAMESPACE_END(vktscn)
