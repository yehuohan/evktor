/*!
 * @brief deferred shading
 */

#include <iostream>
#include <cstdio>
#include <glm/gtc/random.hpp>
#include "demos.h"


DemoDeferred::DemoDeferred(int width, int height)
    : LnGL(width, height)
{
    this->setCameraType(ICamera::Arcball);
    this->setCameraPos(glm::vec3(0.0f, 0.0f, 20.0f));
    this->setFPS(60.0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glEnable(GL_DEPTH_TEST);

    initBasePass();
    initLightingPass();
    initLightBoxes();
    initSkyBox();
}

void DemoDeferred::initBasePass() {
    Model mod(Assets::getObj("backpack/backpack.obj"));
    model = loadModel(mod);
    for (int x = -1; x <= 1; x ++) {
        for (int z = -1; z <= 1; z ++) {
            positions.push_back(glm::vec3(5.0f * x, -0.5, 5.0f * z));
        }
    }

    shader_basepass.load(GLSL_VERT_BASE, GLSL_FRAG_BASE);

    initGBuffer();
}

void DemoDeferred::initGBuffer() {
    // Framebuffer object
    glGenFramebuffers(1, &GBuf_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, GBuf_fbo);

    // GBuffer.A
    glGenTextures(1, &GBuf.A);
    glBindTexture(GL_TEXTURE_2D, GBuf.A);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, wid, hei, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GBuf.A, 0);
    // GBuffer.B
    glGenTextures(1, &GBuf.B);
    glBindTexture(GL_TEXTURE_2D, GBuf.B);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, wid, hei, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, GBuf.B, 0);
    // GBuffer.C
    glGenTextures(1, &GBuf.C);
    glBindTexture(GL_TEXTURE_2D, GBuf.C);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wid, hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, GBuf.C, 0);

    // Multi-RenderTarget with attachment0~2 (Means there multi-output in fragment shader)
    GLenum attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    // Render buffer object with depth buffer established
    // (For depth/stencil test, render buffer object is faster)
    glGenRenderbuffers(1, &GBuf_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, GBuf_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, wid, hei);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Attach GBufRBO on GBufFBO
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GBuf_rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw eformat("Framebuffer 'GBufFBO' is not complete");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DemoDeferred::initLightingPass() {
    quad = loadMeshData(MESH_DATA_Rectangle);

    for (int k = 0; k < LightNum; k ++) {
        lights.push_back(
            Light {
                .pos = glm::vec3(glm::ballRand(12.0)) * glm::vec3(1.0f, 0.5f, 1.0f),
                .color = 0.5f + (glm::vec3(glm::ballRand(1.0)) * 0.5f)
            });
    }

    shader_lightingpass.load(GLSL_VERT_LIGHTING, GLSL_FRAG_LIGHTING);
    shader_lightingpass.use();
    // Use TEXTURE0~2 for GBuf
    shader_lightingpass.setInt("GBuf.pos", 0);
    shader_lightingpass.setInt("GBuf.normal", 1);
    shader_lightingpass.setInt("GBuf.diffspec", 2);
}

void DemoDeferred::initLightBoxes() {
    box = loadMeshData(MESH_DATA_Cube);

    shader_lightbox.load(GLSL_VERT_MESH_DATA, GLSL_FRAG_MESH_DATA);
    shader_lightbox.use();
    shader_lightbox.setInt("meshType", 1);
}

void DemoDeferred::initSkyBox() {
    cube = loadMeshData(MESH_DATA_Cube);
    cubemap = loadCubemap(std::vector<std::string> {
        Assets::getTex("spacebox1/right.png"),
        Assets::getTex("spacebox1/left.png"),
        Assets::getTex("spacebox1/top.png"),
        Assets::getTex("spacebox1/bottom.png"),
        Assets::getTex("spacebox1/front.png"),
        Assets::getTex("spacebox1/back.png"),
    });

    shader_skybox.load(GLSL_VERT_MESH_DATA, GLSL_FRAG_MESH_DATA);
    shader_skybox.use();
    shader_skybox.setInt("meshType", 3);
    shader_skybox.setInt("meshCubemap", 0);
}

void DemoDeferred::tick(float cur_time, float delta_time) {
    static bool show_light_boxes = true;
    static bool show_sky_box = true;

    ImGui::Begin("Deferred Shading");
    ImGui::Checkbox("Show light boxes", &show_light_boxes);
    ImGui::Checkbox("Show sky box", &show_sky_box);
    ImGui::End();

    drawBasePass();
    drawLightingPass();
    if (show_light_boxes) {
        drawLightBoxes();
    }
    if (show_sky_box) {
        drawSkyBox();
    }
}

void DemoDeferred::drawBasePass() {
    // Render scene's geometry information into GBuffer
    glBindFramebuffer(GL_FRAMEBUFFER, GBuf_fbo);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_basepass.use();
    shader_basepass.setMat4("view", view_matrices.view);
    shader_basepass.setMat4("proj", view_matrices.proj);
    for (const auto& pos : positions) {
        glm::mat4 mat_model = glm::translate(glm::mat4(1.0f), pos);
        shader_basepass.setMat4("model", mat_model);
        drawModel(model, shader_basepass);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DemoDeferred::drawLightingPass() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Lighting with GBuffer
    shader_lightingpass.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GBuf.A);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, GBuf.B);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, GBuf.C);

    for (int k = 0; k < lights.size(); k ++) {
        shader_lightingpass.setVec3("lights[" + std::to_string(k) + "].pos", lights[k].pos);
        shader_lightingpass.setVec3("lights[" + std::to_string(k) + "].color", lights[k].color);
    }
    shader_lightingpass.setVec3("viewPos", camera.get()->eye);

    glBindVertexArray(quad.vao);
    glDrawElements(GL_TRIANGLES, quad.indices_num, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    // Lighting pass本质就是一个Quad并着色，所有的depth是相同的，
    // 所以需要将base pass的depth copy过来，便于后续与depth有关的处理
    // Copy GBufFBO's depth to default framebuffer's depth buffer
    glBindFramebuffer(GL_READ_FRAMEBUFFER, GBuf_fbo); // Read from GBufFBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Write to default framebuffer
    glBlitFramebuffer(
        0, 0, wid, hei, // Read viewrect of src framebuffer
        0, 0, wid, hei, // Write viewrect of dst framebuffer
        GL_DEPTH_BUFFER_BIT, // Copy depth
        GL_NEAREST); // With nearst filter
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DemoDeferred::drawLightBoxes() {
    shader_lightbox.use();
    shader_lightbox.setMat4("view", view_matrices.view);
    shader_lightbox.setMat4("proj", view_matrices.proj);

    for (const auto& light : lights) {
        glm::mat4 mat_model(1.0f);
        mat_model = glm::translate(mat_model, light.pos);
        mat_model = glm::scale(mat_model, glm::vec3(0.1));
        shader_lightbox.setMat4("model", mat_model);
        shader_lightbox.setVec3("meshColor", light.color);

        glBindVertexArray(box.vao);
        glDrawElements(GL_TRIANGLES, box.indices_num, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }
}

void DemoDeferred::drawSkyBox() {
    // Sky box的z为最大深度1.0，使用LEQUAL，在没有任何其它片段的地方绘制sky box
    glDepthFunc(GL_LEQUAL);

    shader_skybox.use();
    // 移除view矩阵中的translation部分，这样eye就不会移动到sky box处
    glm::mat4 mat_view = glm::mat4(glm::mat3(view_matrices.view));
    shader_skybox.setMat4("view", mat_view);
    shader_skybox.setMat4("proj", view_matrices.proj);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

    glBindVertexArray(cube.vao);
    glDrawElements(GL_TRIANGLES, cube.indices_num, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}
