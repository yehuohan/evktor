#pragma once
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

NAMESPACE_BEGIN(vktscn)

class Transform : public vkt::NonCopyable {
private:
    glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
    glm::quat rotation = glm::quat(1.0, 0.0, 0.0, 0.0);
    glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
    glm::mat4 world_matrix = glm::mat4(1.0);

public:
    Transform();
};

NAMESPACE_END(vktscn)
