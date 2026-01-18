#include "transform.hpp"
#include "../node.hpp"
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

void Transform::setMatrix(const glm::mat4& matrix) {
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(matrix, scale, rotation, translation, skew, perspective);
    invalidateWorldMatrix();
}

glm::mat4 Transform::getMatrix() const {
    return glm::translate(glm::mat4(1.0), translation) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0), scale);
}

glm::mat4 Transform::getWorldMatrix() {
    update();
    return world_matrix;
}

void Transform::update() {
    if (valid) {
        return;
    }

    world_matrix = getMatrix();
    auto parent = node.getParent();
    if (parent) {
        auto& transform = parent->getComponent<Transform>();
        world_matrix = transform.getWorldMatrix() * world_matrix;
    }

    valid = true;
}

NAMESPACE_END(vktscn)
