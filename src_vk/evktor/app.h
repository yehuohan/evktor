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
    PerspCamera* scene_camera = nullptr;

public:
    App(int argc, char* argv[]);
    virtual ~App();

    void run() override;
    void tick(float cur_time, float delta_time) override;

private:
    void setup();
    void setupBasePass();
};
