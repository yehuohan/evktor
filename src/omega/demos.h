#ifndef DEMOS_H
#define DEMOS_H

#include "assets.hpp"
#include "model.h"
#include "mesh_data.h"
#include "glbase.h"
#include "shader.h"
#include "font.h"
#include "utils.h"

#define DWID 800
#define DHEI 600

#define GLSL_VERT_MESH_DATA         Assets::getShader("omega/mesh_data.vert")
#define GLSL_FRAG_MESH_DATA         Assets::getShader("omega/mesh_data.frag")
#define GLSL_COMP_FILTER            Assets::getShader("omega/filter.comp")
#define GLSL_VERT_BASE              Assets::getShader("omega/base.vert")
#define GLSL_FRAG_BASE              Assets::getShader("omega/base.frag")
#define GLSL_VERT_LIGHTING          Assets::getShader("omega/lighting.vert")
#define GLSL_FRAG_LIGHTING          Assets::getShader("omega/lighting.frag")


class DemoFrustum : public LnGL {
public:
    DemoFrustum(int width = DWID, int height = DHEI);
    ~DemoFrustum() { };

    virtual void tick(float cur_time, float delta_time) override;

private:
    void initSubWin();
    void drawSubWin(float cur_time);
    void drawMainWin(float cur_time);

private:
    RMeshData mesh_data;
    Shader shader;
    TextRenderer text_renderer;

    GLFWwindow* sub_win;
    GLuint sub_vao;
};

class DemoFilter : public LnGL {
public:
    DemoFilter(int width = DWID, int height = DHEI);
    ~DemoFilter() { };

    virtual void tick(float cur_time, float delta_time) override;

private:
    void queryWorkGroup();
    void drawFilter(float time);
    void drawRect(float time);

private:
    RMeshData rect;
    Shader shader;
    Shader shader_filter;
    GLuint img;
    GLuint tex;
    uint32_t tex_wid;
    uint32_t tex_hei;
};

class DemoDeferred : public LnGL {
public:
    DemoDeferred(int width = DWID, int height = DHEI);

    virtual void tick(float cur_time, float delta_time) override;

private:
    void initBasePass();
    void initGBuffer();
    void initLightingPass();
    void initLightBoxes();
    void initSkyBox();

    void drawBasePass();
    void drawLightingPass();
    void drawLightBoxes();
    void drawSkyBox();

private:
    // Base pass
    struct GBuffer {
        GLuint A; // Position
        GLuint B; // Normal
        GLuint C; // Diffuse + Specular
    };
    GBuffer GBuf;
    GLuint GBuf_fbo; // Framebuffer as GBuffer
    GLuint GBuf_rbo; // Depth render buffer object for GBuffer
    RModel model;
    std::vector<glm::vec3> positions;
    Shader shader_basepass;

    // Lighting pass
    struct Light {
        glm::vec3 pos;
        glm::vec3 color;
    };
    const int LightNum = 32;
    std::vector<Light> lights;
    RMeshData quad;
    Shader shader_lightingpass;

    // Light boxes
    RMeshData box;
    Shader shader_lightbox;

    // Sky box
    RMeshData cube;
    GLuint cubemap;
    Shader shader_skybox;
};

#endif /* end of include guard: DEMOS_H */
