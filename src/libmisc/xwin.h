/*!
 * @file xwin.h
 * @brief Graphics window
 */
#pragma once
#include <GLFW/glfw3.h>
#include <camera.hpp>
#include <cstdint>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

class XWin {
public:
    XWin(int width, int height);
    virtual ~XWin() {}

    void setCameraType(vkt::ICamera::Type type);
    void setCameraPos(glm::vec3 pos);
    void setFPS(float fps) {
        fps = fps;
    }

    static void processKeys(GLFWwindow* window, float delta_time);
    static void processCursorPos(GLFWwindow* window, const uint32_t wid, const uint32_t hei);

    virtual void run() = 0;

protected:
    uint32_t wid;
    uint32_t hei;
    GLFWwindow* window;

    float fps = 0.0f;
    static std::shared_ptr<vkt::ICamera> camera; // 使用static类型，便于GLFWscrollfun的lambda函数捕获
    struct ViewMatrices {
        glm::mat4 view;
        glm::mat4 proj;
    };
    ViewMatrices view_matrices;
};
