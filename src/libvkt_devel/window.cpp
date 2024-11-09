#include "window.hpp"
#include "generated/vk_string.hpp"

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
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，并Capture光标
    glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
        auto user = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        if (user && user->camera) {
            user->camera->processMouseScroll(yoffset);
        }
    });
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int wid, int hei) {
        auto user = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win));
        if (user) {
            user->framebuffer_resized = true;
        }
    });

    glfwMakeContextCurrent(window);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

std::vector<const char*> Window::requiredInstanceExtensions() const {
    const char** glfw_exts;
    uint32_t glfw_exts_cnt = 0;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_exts_cnt);
    std::vector<const char*> exts(glfw_exts, glfw_exts + glfw_exts_cnt);
    return std::move(exts);
}

VkSurfaceKHR Window::createSurface(VkInstance instance) const {
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    auto res = glfwCreateWindowSurface(instance, window, nullptr, &surface);
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

void Window::setCamera(ICamera::Type type, glm::vec3 eye_pos) {
    switch (type) {
    case ICamera::Arcball: camera.reset(new CameraArcball(eye_pos)); break;
    case ICamera::FirstPerson: camera.reset(new CameraFirstPerson(eye_pos)); break;
    }
}

void Window::run() {
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

        processKeys(delta_time);
        processCursorPos(width, height);

        tick(cur_time, delta_time);
    }
}

void Window::processKeys(float delta_time) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (!camera)
        return;

    int dir = -1;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        dir = ICamera::Movement::Forward;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        dir = ICamera::Movement::Backward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        dir = ICamera::Movement::Leftward;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        dir = ICamera::Movement::Rightward;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        dir = ICamera::Movement::Upward;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        dir = ICamera::Movement::Downward;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        dir = ICamera::Movement::Reset;

    if (dir >= 0)
        camera->processCameraMove((ICamera::Movement)dir, delta_time);
}

void Window::processCursorPos(const uint32_t wid, const uint32_t hei) {
    if (!camera)
        return;

    static bool first = true;
    static uint8_t last_btn = GLFW_RELEASE;
    static glm::vec2 pa;

    if (camera->type == ICamera::Arcball) {
        uint8_t btn = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
        if (btn == GLFW_RELEASE) {
            last_btn = btn;
            return;
        } else if (btn == GLFW_PRESS) {
            if (last_btn == GLFW_RELEASE)
                first = true;
        }
        last_btn = btn;
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (first) {
        pa.x = 2.0 * xpos / wid - 1.0;
        pa.y = 2.0 * ypos / hei - 1.0;
        first = false;
        return;
    }
    glm::vec2 pb(2.0 * xpos / wid - 1.0, 2.0 * ypos / hei - 1.0);
    camera->processMouseMove(pa, pb);

    pa = pb;
}

NAMESPACE_END(vktdev)
