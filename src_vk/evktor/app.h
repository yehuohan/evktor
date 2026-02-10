#pragma once
#include <vkt_devel.hpp>
#include <vkt_scene/vkt_scene.hpp>
#include <vktor/vktor.hpp>

using namespace vkt;
using namespace vktdev;
using namespace vktscn;

class App : public IApp {
private:
    Vktor vkt;
    Box<RenderContext> rctx = nullptr;
    Box<RenderPipeline> base = nullptr;
    Box<RenderPipeline> skybox = nullptr;
    PerspCamera* scene_camera = nullptr;

    Box<TextureCube> tex_cube = nullptr;

public:
    App(int argc, char* argv[]);
    virtual ~App();

    void run() override;
    void tick(float cur_time, float delta_time) override;
    void drawGui(const core::CommandBuffer& cmdbuf, float delta_time);

private:
    void setup();
    void setupBasePass();
};
