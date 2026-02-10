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
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int wid, int hei) {
        auto user = reinterpret_cast<IApp*>(glfwGetWindowUserPointer(win));
        if (user) {
            user->framebuffer_resized = true;
        }
    });

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
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

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

        tick(cur_time, delta_time);
    }
}

void IApp::setupGui(const core::Swapchain& swapchain) {
    VkDescriptorPoolSize poolsizes[] = {
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1 + 15}
    };
    auto descpool_ci = Itor::DescriptorPoolCreateInfo();
    descpool_ci.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    descpool_ci.maxSets = 16 * swapchain.image_count;
    descpool_ci.poolSizeCount = 1;
    descpool_ci.pPoolSizes = poolsizes;
    auto res = vkCreateDescriptorPool(swapchain.api, &descpool_ci, swapchain.api, &gui_desc_pool);
    if (res != VK_SUCCESS) {
        throw vktErr("Failed to create gui descriptor pool: {}", VkStr(VkResult, res));
    }

    gui_render_pass = newBox<core::RenderPass>(
        core::RenderPassState{}
            .addAttachment(
                swapchain.image_format,
                VK_SAMPLE_COUNT_1_BIT,
                core::AttachmentOps{VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE},
                core::AttachmentOps{},
                core::AttachmentLayouts{VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL})
            .addSubpass({0})
            .into(swapchain.api)
            .unwrap());

    // gui_window->Surface = swapchain.api;
    // gui_window->SurfaceFormat = swaImGui_ImplVulkanH_SelectSurfaceFormat(swapchain.api, gui_window->Surface,
    // requestSurfaceImageFormat, (size_t)IM_COUNTOF(requestSurfaceImageFormat), requestSurfaceColorSpace);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    const auto& api = swapchain.api;
    ImGui_ImplGlfw_InitForVulkan(window, true);
    ImGui_ImplVulkan_InitInfo info = {};
    info.Instance = api;
    info.PhysicalDevice = api;
    info.Device = api;
    info.QueueFamily = api.graphicsQueue().unwrap().get().family_index;
    info.Queue = api.graphicsQueue().unwrap().get();
    info.MinImageCount = swapchain.image_count;
    info.ImageCount = swapchain.image_count;
    info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    info.DescriptorPool = gui_desc_pool;
    info.RenderPass = *gui_render_pass;
    info.Subpass = 0;
    ImGui_ImplVulkan_Init(&info);

    OnCheck(ImGui::GetCurrentContext(), "Failed to init ImGui context");
}

void IApp::tickCamera(vktscn::PerspCamera& camera, float delta_time) {
    const float speed = 5.5f;       /**< 摄像机移动速度 */
    const float sensitivity = 50.0; /**< 鼠标移动灵敏度 */

    glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);
    glm::vec3 delta_rotation(0.0f, 0.0f, 0.0f);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        glm::vec2 cur(2.0 * xpos / width - 1.0, 2.0 * ypos / height - 1.0);

        static glm::vec2 pre = cur;
        delta_rotation = glm::vec3(pre - cur, 0.0) * sensitivity;
        pre = cur;
    }
    {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            delta_translation.z -= speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            delta_translation.z += speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            delta_translation.x -= speed;
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            delta_translation.x += speed;
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            delta_translation.y += speed;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            delta_translation.y -= speed;
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
