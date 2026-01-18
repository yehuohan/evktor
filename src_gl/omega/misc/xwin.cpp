#include "xwin.h"

std::shared_ptr<ICamera> XWin::camera = nullptr;

XWin::XWin(int width, int height)
    : wid(static_cast<uint32_t>(width))
    , hei(static_cast<uint32_t>(height))
    , window(nullptr)
{
    camera.reset(new CameraFirstPerson(glm::vec3(0.0f, 0.0f, 0.0f)));
}

void XWin::setCameraType(ICamera::Type type) {
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    if (camera.get()) {
        pos = camera.get()->eye;
    }
    switch (type) {
        case ICamera::Arcball:
            camera.reset(new CameraArcball(pos));
            break;
        case ICamera::FirstPerson:
            camera.reset(new CameraFirstPerson(pos));
            break;
    }
}

void XWin::setCameraPos(glm::vec3 pos) {
    if (camera.get()) {
        camera.get()->eye = pos;
        camera.get()->update();
    }
}

void XWin::processKeys(GLFWwindow* window, float delta_time) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (!camera.get())
        return;

    int dir = -1;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) dir = ICamera::Movement::Forward;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dir = ICamera::Movement::Backward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dir = ICamera::Movement::Leftward;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) dir = ICamera::Movement::Rightward;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dir = ICamera::Movement::Upward;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) dir = ICamera::Movement::Downward;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) dir = ICamera::Movement::Reset;

    if (dir >= 0)
        camera->processCameraMove((ICamera::Movement)dir, delta_time);
}

void XWin::processCursorPos(GLFWwindow* window, const uint32_t wid, const uint32_t hei) {
    if (!camera.get())
        return;

    static bool first = true;
    static uint8_t last_btn = GLFW_RELEASE;
    static glm::vec2 pa;

    if (camera.get()->type == ICamera::Arcball) {
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
    glm::vec2 pb(
        2.0 * xpos / wid - 1.0,
        2.0 * ypos / hei - 1.0);
    camera->processMouseMove(pa, pb);

    pa = pb;
}
