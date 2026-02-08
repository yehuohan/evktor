#include "window.hpp"
#include <generated/vk_string.hpp>

NAMESPACE_BEGIN(vktdev)

using namespace vkt;

Window::Window(uint32_t width, uint32_t height) : width(width), height(height) {
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
        auto user = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        if (user) {
            user->framebuffer_resized = true;
        }
    });

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，并Capture光标
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

Vector<const char*> Window::requiredInstanceExtensions() const {
    const char** glfw_exts;
    uint32_t glfw_exts_cnt = 0;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_exts_cnt);
    Vector<const char*> exts(glfw_exts, glfw_exts + glfw_exts_cnt);
    return exts;
}

VkSurfaceKHR Window::createSurface(const vkt::core::Instance& instance) const {
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    auto res = glfwCreateWindowSurface(instance, window, instance, &surface);
    if (res != VK_SUCCESS) {
        throw vktErr("Failed to create window surface: {}", VkStr(VkResult, res));
    }
    return surface;
}

VkExtent2D Window::getExtent() const {
    int wid, hei;
    glfwGetFramebufferSize(window, &wid, &hei);
    return VkExtent2D{u32(wid), u32(hei)};
}

void Window::run() {
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

void Window::tick_camera(vktscn::PerspCamera& camera, float delta_time) {
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
