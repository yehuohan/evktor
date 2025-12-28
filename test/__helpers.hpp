#pragma once
#include <assets.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vktor.hpp>

#define tstOut(f, ...) vkt::print(vktFmt("[tst] " f "\n", ##__VA_ARGS__))

using namespace vkt;
using namespace vkt::core;

typedef void (*FnCaseVoid)(void);

struct Quad {
    uint32_t wid;
    uint32_t hei;
    uint32_t cha;
    uint32_t num;

    String comp_file;
    uint32_t group_count_x;
    uint32_t group_count_y;
    uint32_t group_count_z;
    struct PushArgs {
        int scaler;
    } push_args;
    struct SpecArgs {
        int alpha;
    } spec_args;
    Vector<float> img;

    Quad();
    void checkOutput(const Vector<float>& out) const;
};

struct Triangle {
    struct UBO {
        glm::mat4 view;
        glm::mat4 proj;
    };

    uint32_t wid;
    uint32_t hei;
    uint32_t cha;
    uint32_t num;

    String vert_file;
    String frag_file;
    struct PushArgs {
        int flipy;
        int scaler;
    } push_args;
    struct SpecArgs {
        int alpha;
    } spec_args;
    UBO ubo;
    Vector<float> tex;
    static float vertices[24];
    static uint32_t indices[3];
    static const char* out_color[9];

    Triangle();
    void checkOutput(const Vector<float>& out) const;
};

Box<vkt::core::CoreApi> createCoreApi(const Vector<const char*> inst_exts = {}, const Vector<const char*> dev_exts = {});
