#include "camera.hpp"

NAMESPACE_BEGIN(vkt)

void CameraArcball::processCameraMove(Movement dir, float delta_time) {
    float vel = delta_time * speed;
    switch (dir) {
    case Reset:
        {
            // 回复初始视角
            glm::vec3 d = eye - center;
            eye = glm::vec3(0.0f, 0.0f, glm::sqrt(glm::dot(d, d)));
            center = glm::vec3(0.0f, 0.0f, 0.0f);
            up = glm::vec3(0.0f, 1.0f, 0.0f);
            update();
            break;
        }
    case Forward: eye += glm::normalize(center - eye) * vel; break;
    case Backward: eye -= glm::normalize(center - eye) * vel; break;
    case Leftward: center -= right * vel; break;
    case Rightward: center += right * vel; break;
    case Upward: center += up * vel; break;
    case Downward: center -= up * vel; break;
    default: break;
    }
}

void CameraArcball::processMouseMove(const glm::vec2& pa, const glm::vec2& pb) {
#if 1
    float dx = (pa.x - pb.x) * sensitivity;
    float dy = (pa.y - pb.y) * sensitivity;
    glm::mat4 rotation;

    // 绕up旋转时，eye和right会变
    rotation = glm::rotate(glm::mat4(1.0f), dx, up);
    eye = glm::vec3(rotation * glm::vec4(eye - center, 1.0f)) + center;
    right = glm::cross(up, glm::normalize(eye - center));
    // 绕right旋转时，eye和up会变
    rotation = glm::rotate(glm::mat4(1.0f), dy, right);
    eye = glm::vec3(rotation * glm::vec4(eye - center, 1.0f)) + center;
    up = glm::cross(glm::normalize(eye - center), right);
#else
    // BUG: eye旋转有问题
    glm::vec3 p0 = arcball_coordinate(pa);
    glm::vec3 p1 = arcball_coordinate(pb);

    // da, dr均为eye0=(0, 0, 1)相对center0=(0, 0, 0)的旋转
    float da = glm::acos(glm::dot(p0, p1)) * sensitivity;
    if (da > 0.0f) {
        glm::vec3 dr = glm::cross(p0, p1);
        if (glm::dot(dr, dr) > 0.0f) {
            glm::mat4 dm = glm::rotate(glm::mat4(1.0f), da, dr);
            eye = center + glm::vec3(dm * glm::vec4(eye - center, 1.0f));
            up = center + glm::vec3(dm * glm::vec4(up - center, 1.0f));
        }
    }
#endif
}

glm::vec3 CameraArcball::arcball_coordinate(const glm::vec2& p) const {
    const float z = glm::dot(p, p);
    if (z <= 1.0f) {
        // 点p在球面上或者球内
        return glm::vec3(p.x, p.y, glm::sqrt(1.0f - z));
    } else {
        // 点p在半球外
        const glm::vec2 pn = glm::normalize(p);
        return glm::vec3(pn.x, pn.y, 0.0f);
    }
}

void CameraFirstPerson::processCameraMove(Movement dir, float delta_time) {
    float vel = delta_time * speed;
    switch (dir) {
    case Reset:
        // 回复初始视角
        center = glm::vec3(0.0f, 0.0f, -1.0f);
        pitch = 0.0f;
        yaw = -90.0f;
        update();
        break;
    case Forward: eye += (center - eye) * vel; break;
    case Backward: eye -= (center - eye) * vel; break;
    case Leftward: eye -= right * vel; break;
    case Rightward: eye += right * vel; break;
    case Upward: eye += up * vel; break;
    case Downward: eye -= up * vel; break;
    default: break;
    }
}

void CameraFirstPerson::processMouseMove(const glm::vec2& pa, const glm::vec2& pb) {
    glm::vec2 d = (pb - pa) * sensitivity;
    pitch += d.y;
    yaw += d.x;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    update();
}

void CameraFirstPerson::update() {
    glm::vec3 f;
    f.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    f.y = sin(-glm::radians(pitch));
    f.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    glm::vec3 dir = glm::normalize(f);

    right = glm::normalize(glm::cross(dir, world_up)); // center和world_up之间不一定是90度
    up = glm::normalize(glm::cross(right, dir));       // right, center, up是正交直角坐标系
    center = eye + dir;
}

NAMESPACE_END(vkt)
