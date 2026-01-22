#pragma once
#include "../component.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>

NAMESPACE_BEGIN(vktscn)

/**
 * @brief How the alpha value of the main factor and texture should be interpreted
 */
enum class AlphaMode {
    Opaque, /**< Alpha value is ignored */
    Mask,   /**< Either full opaque or fully transparent */
    Blend   /**< Output is combined with the background */
};

/**
 * @brief Basic material
 */
class Material : public Component {
private:
    HashMap<String, const Texture*> textures{};

public:
    glm::vec3 emissive_factor{0.0f, 0.0f, 0.0f}; /**< Emissive color (自发光) of the material */
    AlphaMode alpha_mode = AlphaMode::Opaque;    /**< Alpha rendering mode */
    float alpha_cutoff = 0.5f;                   /**< Cutoff threshold when in Mask mode */
    bool double_sided = false;                   /**< Whether the material is double sided */

    float normal_scale = 1.0;
    float occlusion_strength = 1.0;

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

/**
 * @brief PBR metallic-roughness model material
 */
class PBRMaterial : public Material {
public:
    glm::vec4 base_color_factor{1.0f, 1.0f, 1.0f, 1.0f};
    float metallic_factor = 1.0f;
    float roughness_factor = 1.0f;

public:
    PBRMaterial(const String& name = "") : Material(name) {}
    virtual ~PBRMaterial() = default;

    virtual std::type_index getType() const override {
        return typeid(PBRMaterial);
    }
};

NAMESPACE_END(vktscn)
