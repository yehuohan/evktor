#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdint>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#include <share/share.hpp>
#include <vkt_scene/components/camera.hpp>
#include <vktor/core/api/instance.hpp>
#include <vktor/core/descriptor_pool.hpp>
#include <vktor/core/exts/swapchain.hpp>
#include <vktor/core/render_pass.hpp>

NAMESPACE_BEGIN(vktdev)

class IApp {
protected:
    uint32_t width;
    uint32_t height;
    GLFWwindow* window = nullptr;
    bool framebuffer_resized = false;
    float fps = 0.0f;

protected:
    ImGui_ImplVulkanH_Window* gui_window = nullptr;
    VkDescriptorPool gui_desc_pool = VK_NULL_HANDLE;
    Box<vkt::core::RenderPass> gui_render_pass = nullptr;

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
    void setupGui(const vkt::core::Swapchain& swapchain);
    void tickCamera(vktscn::PerspCamera& camera, float delta_time);
};

NAMESPACE_END(vktdev)
