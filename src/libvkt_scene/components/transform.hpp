#pragma once
#include "component.hpp"
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

NAMESPACE_BEGIN(vktscn)

class Node;

class Transform : public Component {
private:
    Node& node;
    glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
    glm::quat rotation = glm::quat(1.0, 0.0, 0.0, 0.0);
    glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
    glm::mat4 world_matrix = glm::mat4(1.0);
    bool valid = true; /** The local transform and parent world transform is valid (not changed) */

private:
    /** Update world transform */
    void update();

public:
    Transform(Node& node);
    virtual ~Transform() = default;

    operator std::type_index() override {
        return typeid(Transform);
    }
    operator Node&() {
        return node;
    }

    void invalidateWorldMatrix() {
        valid = false;
    }

    void setTranslation(const glm::vec3& translation);
    void setRotation(const glm::quat& rotation);
    void setScale(const glm::vec3& scale);
    inline const glm::vec3& getTranslation() const {
        return translation;
    }
    inline const glm::quat& getRotation() const {
        return rotation;
    }
    inline const glm::vec3& getScale() const {
        return scale;
    }
    void setMatrix(const glm::mat4& matrix);
    glm::mat4 getMatrix() const;
    glm::mat4 getWorldMatrix();
};

NAMESPACE_END(vktscn)
