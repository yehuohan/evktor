#pragma once
#include "share/libglm.hpp"
#include "share/share.hpp"
#include "share/traits.hpp"

NAMESPACE_BEGIN(vktscn)

class Node;

class Transform : private NonCopyable {
private:
    Node& node;
    glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);   /**< Local transform translation */
    glm::quat rotation = glm::quat(1.0, 0.0, 0.0, 0.0); /**< Local transform rotation */
    glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);         /**< Local transform scale */
    glm::mat4 world_matrix = glm::mat4(1.0);            /**< Global world transform matrix */
    bool world_matrix_valid = true;                     /** Global world transform is valid and does't need update */

public:
    Transform(Node& node);
    virtual ~Transform() = default;

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

    void setLocalMatrix(const glm::mat4& matrix);
    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix();
    inline void invalidateWorldMatrix() {
        world_matrix_valid = false;
    }

private:
    void updateWorldMatrix();
};

NAMESPACE_END(vktscn)
