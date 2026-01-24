#include "transform.hpp"
#include "node.hpp"
#include <glm/gtx/matrix_decompose.hpp>

NAMESPACE_BEGIN(vktscn)

Transform::Transform(Node& node) : node{node} {}

void Transform::setTranslation(const glm::vec3& new_translation) {
    translation = new_translation;
    invalidateWorldMatrix();
}

void Transform::setRotation(const glm::quat& new_rotation) {
    rotation = new_rotation;
    invalidateWorldMatrix();
}

void Transform::setScale(const glm::vec3& new_scale) {
    scale = new_scale;
    invalidateWorldMatrix();
}

void Transform::setLocalMatrix(const glm::mat4& matrix) {
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(matrix, scale, rotation, translation, skew, perspective);
    invalidateWorldMatrix();
}

glm::mat4 Transform::getLocalMatrix() const {
    return glm::translate(glm::mat4(1.0), translation) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0), scale);
}

glm::mat4 Transform::getWorldMatrix() {
    updateWorldMatrix();
    return world_matrix;
}

void Transform::updateWorldMatrix() {
    if (world_matrix_valid) {
        return;
    }

    world_matrix = getLocalMatrix();
    auto parent = node.getParent();
    if (parent) {
        world_matrix = parent->getTransform().getWorldMatrix() * world_matrix;
    }

    world_matrix_valid = true;
}

NAMESPACE_END(vktscn)
