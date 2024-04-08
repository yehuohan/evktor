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
    float fps = 0.0f;

    /** Make static to be captured by GLFWscrollfun */
    static vkt::Box<ICamera> camera;

public:
    Window(uint32_t width, uint32_t height);
    virtual ~Window();

    /**
     * @brief Get required instance extensions from GLFW
     */
    std::vector<const char*> requiredInstanceExtensions() const;
    /**
     * @brief Create surface from GLFW
     *
     * This function should be invoked only once
     */
    VkSurfaceKHR createSurface(VkInstance instance) const;
    /**
     * @brief Get surface extent
     */
    VkExtent2D getExtent() const;
    void setCamera(ICamera::Type type, glm::vec3 eye_pos = glm::vec3(0.0f, 0.0f, 0.0f));

    virtual void run();
    virtual void tick(float cur_time, float delta_time) = 0;

protected:
    virtual void processKeys(float delta_time);
    virtual void processCursorPos(const uint32_t wid, const uint32_t hei);
};

NAMESPACE_END(vktdev)
