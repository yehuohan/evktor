#include "camera.hpp"

NAMESPACE_BEGIN(vktscn)

glm::mat4 Camera::getView() {
    if (!node) {
        vktLogW("Camera component is not attached to a node");
        return glm::mat4(1.0);
    }
    return glm::inverse(node->getTransform().getWorldMatrix());
}

NAMESPACE_END(vktscn)
