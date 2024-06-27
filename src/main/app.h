#pragma once
#include "vktor.hpp"
#include "window.hpp"

using namespace vkt;
using namespace vkt::core;
using namespace vktdev;

class App : public Window {
private:
    Vktor vkt;
    Box<RenderContext> rctx = nullptr;
    Box<RenderGraph> rdg = nullptr;

    Box<RenderPipeline> base = nullptr;
    // Box<RenderPipeline> skybox = nullptr;
    // Box<RenderPipeline> ui = nullptr;

    // Box<vktdev::Scene> sponza = nullptr;

    Vector<Buffer> buffer_uniform;

    Box<Buffer> buffer_index;
    Box<Buffer> buffer_vertex;
    Box<Texture2D> mesh;
    Box<Sampler> mesh_spl;

public:
    App(int argc, char* argv[]);
    virtual ~App() {}

    void run() override;
    void tick(float cur_time, float delta_time) override;

private:
    void setup();
    void setupBasePass();

    void recordCommandBuffers(CommandBuffer& cmdbuf, uint32_t frm_idx);
    void createIndexBuffer();
    void createVertexBuffer();
};
