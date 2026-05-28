#include "app_interface.hpp"
#include <generated/vk_string.hpp>

NAMESPACE_BEGIN(vktdev)

using namespace vkt;

IApp::IApp(uint32_t width, uint32_t height) : width(width), height(height) {
    if (!glfwInit()) {
        throw vktErr("Failed to init GLFW");
    };
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(width, height, "evktor", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw vktErr("Failed to create GLFW window");
    }
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeLimits(window, 1, 1, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，并Capture光标
}

IApp::~IApp() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

Vector<const char*> IApp::requiredInstanceExtensions() const {
    const char** glfw_exts;
    uint32_t glfw_exts_cnt = 0;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_exts_cnt);
    Vector<const char*> exts(glfw_exts, glfw_exts + glfw_exts_cnt);
    return exts;
}

VkSurfaceKHR IApp::createSurface(const core::Instance& instance) const {
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    auto res = glfwCreateWindowSurface(instance, window, instance, &surface);
    if (res != VK_SUCCESS) {
        throw vktErr("Failed to create window surface: {}", VkStr(VkResult, res));
    }
    return surface;
}

VkExtent2D IApp::getExtent() const {
    int wid, hei;
    glfwGetFramebufferSize(window, &wid, &hei);
    return VkExtent2D{u32(wid), u32(hei)};
}

void IApp::run() {
    float last_time = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        double timeout = -1.0;
        if (last_time > 0.0 && fps > 0.0) {
            timeout = 1.0 / fps - (glfwGetTime() - last_time);
        }
        if (timeout > 0.0) {
            glfwWaitEventsTimeout(timeout);
        } else {
            glfwPollEvents();
        }

        float cur_time = glfwGetTime();
        float delta_time = cur_time - last_time;
        last_time = cur_time;

        ImGuiIO& io = ImGui::GetIO();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
            if (!(io.WantCaptureMouse || io.WantCaptureKeyboard) &&
                glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
                io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
                io.ConfigFlags |= ImGuiConfigFlags_NoKeyboard;
                camera_active = true;
            }
        } else if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED &&
                   glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
            io.ConfigFlags &= ~ImGuiConfigFlags_NoKeyboard;
            camera_active = false;
        }

        tick(cur_time, delta_time);
    }
}

void IApp::setupGui(const core::Swapchain& swapchain) {
    gui_desc_pool = newBox<core::DescriptorPool>(core::DescriptorPoolState("GuiDescriptorPool")
                                                     .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                                                     .setMaxsets(16 * swapchain.image_count)
                                                     .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1 + 15)
                                                     .into(swapchain.api)
                                                     .unwrap());
    gui_render_pass = newBox<core::RenderPass>(
        core::RenderPassState{}
            .addAttachment(swapchain.image_format,
                           VK_SAMPLE_COUNT_1_BIT,
                           core::AttachmentOps::LoadStore,
                           core::AttachmentOps{},
                           core::AttachmentLayouts{VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR})
            .addAttachment(VK_FORMAT_D24_UNORM_S8_UINT,
                           VK_SAMPLE_COUNT_1_BIT,
                           core::AttachmentOps::LoadStore,
                           core::AttachmentOps::LoadStore,
                           core::AttachmentLayouts{VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
                                                   VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL})
            .addSubpass({0}, 1)
            .into(swapchain.api)
            .unwrap());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForVulkan(window, true);

    const auto& api = swapchain.api;
    ImGui_ImplVulkan_InitInfo info = {};
    info.Instance = api;
    info.PhysicalDevice = api;
    info.Device = api;
    info.QueueFamily = api.graphicsQueue().unwrap().get().family_index;
    info.Queue = api.graphicsQueue().unwrap().get();
    info.MinImageCount = swapchain.image_count;
    info.ImageCount = swapchain.image_count;
    info.DescriptorPool = *gui_desc_pool;
    info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    info.PipelineInfoMain.RenderPass = *gui_render_pass;
    info.PipelineInfoMain.Subpass = 0;
    ImGui_ImplVulkan_LoadFunctions(((const core::Instance&)api).getApiVersion(),
                                   [](const char* name, void* user_data) {
                                       return vkGetInstanceProcAddr(*(VkInstance*)user_data, name);
                                   },
                                   &info.Instance);
    ImGui_ImplVulkan_Init(&info);

    OnCheck(ImGui::GetCurrentContext(), "Failed to init ImGui context");
}

void IApp::shutdownGui() {
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    gui_desc_pool.reset();
    gui_render_pass.reset();
}

void IApp::tickCamera(vktscn::PerspCamera& camera, float delta_time) {
    glm::vec3 delta_rotation(0.0f, 0.0f, 0.0f);
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        glm::vec2 cur(2.0 * xpos / width - 1.0, 2.0 * ypos / height - 1.0);

        static glm::vec2 pre = cur;
        delta_rotation = glm::vec3(pre - cur, 0.0) * camera_sensitivity;
        pre = cur;
    }

    if (!camera_active) {
        return;
    }

    glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);
    {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            delta_translation.z -= camera_speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            delta_translation.z += camera_speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            delta_translation.x -= camera_speed;
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            delta_translation.x += camera_speed;
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            delta_translation.y += camera_speed;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            delta_translation.y -= camera_speed;
    }

    delta_translation *= delta_time;
    delta_rotation *= delta_time;

    auto& tr = camera.getNode()->getTransform();
    glm::quat qx = glm::angleAxis(delta_rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qy = glm::angleAxis(delta_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat rot = glm::normalize(qy * tr.getRotation() * qx);
    tr.setTranslation(tr.getTranslation() + delta_translation * glm::conjugate(rot));
    tr.setRotation(rot);
}

NAMESPACE_END(vktdev)
