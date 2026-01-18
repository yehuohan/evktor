#pragma once
#include "../component.hpp"
#include <share/share.hpp>

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

public:
    Transform(Node& node);
    virtual ~Transform() = default;

    virtual std::type_index getType() const override {
        return typeid(Transform);
    }
    Node& getNode() {
        return node;
    }

public:
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
    inline void invalidateWorldMatrix() {
        valid = false;
    }

private:
    /** Update world transform */
    void update();
};

NAMESPACE_END(vktscn)
