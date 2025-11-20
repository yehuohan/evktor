#pragma once
#include "component.hpp"
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

class Material : public Component {
public:
    HashMap<String, Texture*> textures;
    glm::vec3 emissive{0.0f, 0.0f, 0.0f};     /**< Emissive color of the material */
    bool double_sided = false;                /**< Whether the material is double sided */
    float alpha_cutoff = 0.5f;                /**< Cutoff threshold when in Mask mode */
    AlphaMode alpha_mode = AlphaMode::Opaque; /**< Alpha rendering mode */

public:
    Material(const std::string& name);

    Material(Material&& other) = default;

    virtual ~Material() = default;

    virtual operator std::type_index() override {
        return typeid(Material);
    }
};

NAMESPACE_END(vktscn)
