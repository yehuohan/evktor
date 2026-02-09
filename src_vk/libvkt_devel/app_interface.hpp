#pragma once
#include <cstdint>
#include <share/share.hpp>
#include <vkt_scene/components/camera.hpp>
#include <vktor/core/api/instance.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

NAMESPACE_BEGIN(vktdev)

class IApp {
protected:
    uint32_t width;
    uint32_t height;
    GLFWwindow* window = nullptr;
    bool framebuffer_resized = false;
    float fps = 0.0f;

public:
    IApp(uint32_t width, uint32_t height);
    virtual ~IApp();

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

    virtual void run();
    virtual void tick(float cur_time, float delta_time) = 0;

protected:
    virtual void tick_camera(vktscn::PerspCamera& camera, float delta_time);
};

NAMESPACE_END(vktdev)
