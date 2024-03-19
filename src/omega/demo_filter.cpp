/*!
 * @brief filter with compute shader
 */

#include <iostream>
#include <cstdio>
#include "demos.h"


DemoFilter::DemoFilter(int width, int height)
    : LnGL(width, height)
{
    this->setCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));

    glEnable(GL_DEPTH_TEST);

    // load verteices
    rect = loadMeshData(MESH_DATA_Rectangle);

    // load texture
    tex_wid = 512;
    tex_hei = 512;
    img = loadTexture(Assets::getTex("lena.jpg"));
    tex = createTexture(tex_wid, tex_hei);

    // load shader
    shader.load(GLSL_VERT_MESH_DATA, GLSL_FRAG_MESH_DATA);
    shader.use();
    shader.setInt("meshType", 2);
    shader.setInt("meshTexture", 0); // meshTexture use TEXTURE0 for render shader

    shader_filter.load(GLSL_COMP_FILTER);
    shader_filter.use();
    shader_filter.setInt("imgIn", 0); // imgIn use TEXTURE0 for compute shader
    shader_filter.setInt("imgOut", 1); // imgOut use TEXTURE1 for compute shader

    queryWorkGroup();
}

void DemoFilter::queryWorkGroup() {
    int cnt[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &cnt[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &cnt[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &cnt[2]);
    printf("max global work group size: %d, %d, %d\n", cnt[0], cnt[1], cnt[2]); // glDispatchCompute(x, y, z) <= cnt[0, 1, 2]
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &cnt[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &cnt[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &cnt[2]);
    printf("max local work group size: %d, %d, %d\n", cnt[0], cnt[1], cnt[2]); // local_size_[x, y, z] <= cnt[0, 1, 2]
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &cnt[0]);
    printf("max local work group invocations: %d\n", cnt[0]); // local_size_x * local_size_y * local_size_z <= cnt[0]

}

void DemoFilter::tick(float cur_time, float delta_time) {
    drawFilter(cur_time);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    drawRect(cur_time);
}

void DemoFilter::drawFilter(float time) {
    glBindImageTexture(0, img, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8); // bind img to binding = 0
    glBindImageTexture(1, tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8); // bind tex to binding = 1
    shader_filter.use();
    shader_filter.setInt("imgWidth", tex_wid);
    shader_filter.setInt("imgHeight", tex_hei);
    shader_filter.setFloat("coef", glm::sin(time));
    glDispatchCompute(tex_wid / 8, tex_hei / 8, 1); // split image to 8x8 blocks
}

void DemoFilter::drawRect(float time) {
    // launch render shader
    glfwMakeContextCurrent(window);
    glClearColor(0.5f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glm::mat4 mmodel(1.0f);
    mmodel = glm::rotate(mmodel, (float)-time, glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("model", mmodel);
    shader.setMat4("view", view_matrices.view);
    shader.setMat4("proj", view_matrices.proj);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex); // bind tex to TEXTURE0 for render shader

    glBindVertexArray(rect.vao);

    // glDrawElements使用vao中的GL_ELEMENT_ARRAY_BUFFER索引顶点数据，来绘制图元
    glDrawElements(
            GL_TRIANGLES,
            rect.indices_num, // 绘制6个顶点，2个三角形
            GL_UNSIGNED_SHORT, // 索引类型
            0); // 偏移量或索引数组
}
