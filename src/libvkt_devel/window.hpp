#pragma once
#include <camera.hpp>
#include <cstdint>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <vktor/core/api/instance.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

NAMESPACE_BEGIN(vktdev)

class Window {
protected:
    uint32_t width;
    uint32_t height;
    GLFWwindow* window = nullptr;
    vkt::Box<ICamera> camera = nullptr;
    bool framebuffer_resized = false;
    float fps = 0.0f;

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
    VkSurfaceKHR createSurface(const vkt::core::Instance& instance) const;
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
