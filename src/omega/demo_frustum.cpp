/*!
 * @brief draw frustum with opengl
 */

#include <iostream>
#include "demos.h"


DemoFrustum::DemoFrustum(int width, int height)
    : LnGL(width, height)
    , text_renderer(width, height)
{
    this->setCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));

    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glEnable(GL_CULL_FACE); // 启用面剃除
    glCullFace(GL_BACK); // 只剃除背向面
    glFrontFace(GL_CCW); // 设置逆时针方向为正向面

    // load verteices
    mesh_data = loadMeshData(MESH_DATA_Frustum);

    // load shader
    shader.load(GLSL_VERT_MESH_DATA, GLSL_FRAG_MESH_DATA);
    shader.use();
    shader.setInt("meshType", 0);

    // load font
    text_renderer.load(Assets::getFont("FantasqueSansNFM.ttf"), 18);

    initSubWin();
}

void DemoFrustum::initSubWin() {
    sub_win = glfwCreateWindow(wid / 2, hei / 2, "demo sub", NULL, window);
    glfwMakeContextCurrent(sub_win);
    glfwSetFramebufferSizeCallback(sub_win, [](GLFWwindow*, int wid, int hei) { glViewport(0, 0, wid, hei); });

    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &sub_vao);
    glBindVertexArray(sub_vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_data.vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)(9 * sizeof(float)));

    glBindVertexArray(0);
}

void DemoFrustum::tick(float cur_time, float delta_time) {
    drawSubWin(cur_time);
    drawMainWin(cur_time);
}

void DemoFrustum::drawSubWin(float cur_time) {
    glfwMakeContextCurrent(sub_win);
    glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glm::mat4 mmodel(1.0f);
    mmodel = glm::rotate(glm::mat4(1.0f), (float)cur_time, glm::vec3(0.0, 1.0, 0.0));
    shader.setMat4("model", mmodel);
    shader.setMat4("view", view_matrices.view);
    shader.setMat4("proj", view_matrices.proj);

    glBindVertexArray(sub_vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh_data.indices_num);

    glfwSwapBuffers(sub_win);
}

void DemoFrustum::drawMainWin(float cur_time) {
    glfwMakeContextCurrent(window);
    glClearColor(0.5f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glm::mat4 mmodel(1.0f);
    mmodel = glm::rotate(glm::mat4(1.0f), -(float)cur_time, glm::vec3(0.0, 1.0, 0.0));
    shader.setMat4("model", mmodel);
    shader.setMat4("view", view_matrices.view);
    shader.setMat4("proj", view_matrices.proj);

    glBindVertexArray(mesh_data.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh_data.indices_num);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 显示字形时，需要去除透明的部分
    text_renderer.renderText("Square Frustum", 5.0, 5.0, 1.0, glm::vec3(1.0, 0.0, 0.0));
    glDisable(GL_BLEND);
}
