#pragma once
#include "share/helpers.hpp"
#include "share/share.hpp"
#include <camera.hpp>
#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

NAMESPACE_BEGIN(vktdev)

class Window {
protected:
    uint32_t width;
    uint32_t height;
    GLFWwindow* window = nullptr;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    float fps = 0.0f;

    /** Make static to be captured by GLFWscrollfun */
    static vkt::Box<ICamera> camera;

public:
    Window(uint32_t width, uint32_t height);
    virtual ~Window();

    std::vector<const char*> requiredInstanceExtensions() const;
    VkSurfaceKHR createSurface(VkInstance instance);
    void setCamera(ICamera::Type type, glm::vec3 eye_pos = glm::vec3(0.0f, 0.0f, 0.0f));

    virtual void run();
    virtual void tick(float cur_time, float delta_time) = 0;

protected:
    virtual void processKeys(float delta_time);
    virtual void processCursorPos(const uint32_t wid, const uint32_t hei);
};

NAMESPACE_END(vktdev)
