#include "glbase.h"


LnGL::LnGL(int width, int height)
    : XWin(width, height)
{
    // Initialize glfw
    if (!glfwInit()) {
        throw eformat("Failed to init GLFW");
    };
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLAD_CTX_VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLAD_CTX_VER_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, "Omega", NULL, NULL);
    if (NULL == this->window) {
        glfwTerminate();
        throw eformat("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(this->window); // 设置当前上下文为win，有了win才能加载glad

    int glad_version = gladLoadGL(glfwGetProcAddress);
    std::printf("GL version from glad: %d.%d\n", GLAD_VERSION_MAJOR(glad_version), GLAD_VERSION_MINOR(glad_version));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，并Capture光标
    glfwSetScrollCallback(window, [](GLFWwindow*, double xoffset, double yoffset) { camera.get()->processMouseScroll(yoffset); });
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int wid, int hei) { glViewport(0, 0, wid, hei); });

    // Init imgui
    const char* glsl_version = "#version 450";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Print GPU info
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::printf(
        "GPU info:\n"
        "\t* Vender: %s\n"
        "\t* Renderer: %s\n"
        "\t* Version: %s\n",
        vendor, renderer, version);
}

void LnGL::run() {
    float last_time = 0.0f;
    while (!glfwWindowShouldClose(this->window)) {
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

        static ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) { processKeys(window, delta_time); }
        if (!io.WantCaptureMouse) { processCursorPos(window, wid, hei); }
        view_matrices.view = camera.get()->getView();
        view_matrices.proj = camera.get()->getProj(wid, hei);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        tick(cur_time, delta_time);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
