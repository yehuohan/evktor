#pragma once
#include "../node.hpp"

NAMESPACE_BEGIN(vktscn)

class Camera : public Component {
protected:
    Node* node = nullptr;

public:
    Camera(const String& name = "") : Component(name) {}
    virtual ~Camera() = default;

    /**
     * @brief PerspCamera and OrthoCamera don't override `getType()`, then share the same type with Camera
     */
    virtual std::type_index getType() const override {
        return typeid(Camera);
    }

public:
    virtual glm::mat4 getProj() = 0;
    virtual glm::mat4 getView();
    inline void setNode(Node& _node) {
        node = &_node;
    }
    inline Node* getNode() {
        return node;
    }
};

class PerspCamera : public Camera {
public:
    float aspect = 1920.0 / 1080.0f;  /**< Screen size aspect ratio from width/height */
    float fovy = glm::radians(45.0f); /**< Y direction field of view in radians */
    float znear = 0.1f;
    float zfar = 1000.0;

public:
    PerspCamera(const String& name = "") : Camera(name) {}
    virtual ~PerspCamera() = default;

public:
    virtual glm::mat4 getProj() override {
        return glm::reversedInfinitePerspective(fovy, aspect, znear);
    }
};

class OrthoCamera : public Camera {
public:
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float top = 1.0f;
    float znear = 0.0f;
    float zfar = 100.0f;

public:
    OrthoCamera(const String& name = "") : Camera(name) {}
    virtual ~OrthoCamera() = default;

public:
    virtual glm::mat4 getProj() override {
        // Swap znear and zfar for reversed-z
        return glm::ortho(left, right, bottom, top, zfar, znear);
    }
};

NAMESPACE_END(vktscn)
