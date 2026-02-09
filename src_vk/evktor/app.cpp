#include "app.h"
#include <cxxopts.hpp>

App::App(int argc, char* argv[]) : IApp(1920, 1080) {
    cxxopts::Options opts{"evktor"};
    auto adder = opts.add_options();
    adder("a,assets", "Setup asset path", cxxopts::value<std::string>()->default_value("./assets"));
    adder("s,shaders", "Setup shader path", cxxopts::value<std::string>()->default_value("./shaders"));

    auto res = opts.parse(argc, argv);
    Assets::setDirs(res["assets"].as<std::string>(), res["shaders"].as<std::string>());
}

App::~App() {
    base.reset();
    rctx.reset();
    vkt.api.reset();
    scene_camera = nullptr;
}

void App::run() {
    setup();
    setupBasePass();

    IApp::run();

    vkt.api->waitIdle();
}

void App::setup() {
    // Setup CoreApi
    auto inst_exts = requiredInstanceExtensions();
    inst_exts.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    auto& api = vkt.createApi(
        [&inst_exts](core::InstanceState& iso) {
            iso.addExtensions(inst_exts);
        },
        std::bind(&vktdev::IApp::createSurface, this, std::placeholders::_1));

    // Setup RenderContext with Swapchain
    core::SwapchainState sso{};
    sso.addDesiredFormat(VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
        .addDesiredPresentMode(VK_PRESENT_MODE_FIFO_KHR)
        .setDesiredExtent(getExtent());
    rctx = vkt.newRctx(std::move(sso));
}

void App::setupBasePass() {
    base = newBox<RenderPipeline>(*rctx, "Base");

    // Load scene
    auto scene = GLTFLoader(vkt).loadScene(Assets::scene("Sponza/glTF/Sponza.gltf"));
    scene_camera = dynamic_cast<PerspCamera*>(scene->findNode("default.camera")->getComponent<Camera>());
    scene_camera->aspect = (float)width / height;

    {
        auto vert_file = Assets::shader("pbr.vert");
        auto frag_file = Assets::shader("pbr.frag");
        auto vert = Shader::fromVert(Assets::loadShader(vert_file), vert_file);
        auto frag = Shader::fromFrag(Assets::loadShader(frag_file), frag_file);
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);

        // Subpass for base scene
        base->addSubpass<GeometrySubpass>(std::move(vert), std::move(frag), std::move(scene), *scene_camera)
            .setRTColors({0})
            .setRTDepthStencil(1);
    }
    {
        auto vert_file = Assets::shader("builtin.vert");
        auto frag_file = Assets::shader("builtin.frag");
        auto vert = Shader::fromVert(Assets::loadShader(vert_file), vert_file);
        auto frag = Shader::fromFrag(Assets::loadShader(frag_file), frag_file);
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);
        frag.setDefine("HAS_TEX");

        // Subpass for builtin mesh
        auto [pixels, w, h] = Assets::loadTexRGBA8(Assets::tex("box.png"));
        uint32_t mip_levels = static_cast<uint32_t>(std::floor(std::log2(std::max<int>(w, h)))) + 1;
        auto mesh_tex = newBox<Texture2D>(
            vkt.newTexture2D(VK_FORMAT_R8G8B8A8_SRGB, VkExtent2D(w, h), Texture2D::Transfer | Texture2D::Sampled, mip_levels));
        vkt.pushData(mesh_tex->getImage(), pixels);
        auto mesh = newBox<BuiltinMesh>(BuiltinMesh::from(vkt, BuiltinMeshData::Frustum, std::move(mesh_tex)).unwrap());
        base->addSubpass<BuiltinSubpass>(std::move(vert), std::move(frag), std::move(mesh), *scene_camera)
            .setRTColors({0})
            .setRTDepthStencil(1);
    }
}

void App::tick(float cur_time, float delta_time) {
    tick_camera(*scene_camera, delta_time);

    auto& cmdbuf = rctx->beginFrame().unwrap().get();

    auto& rtt = rctx->getFrame().get().getSwapchainRTT().unwrap().get();
    cmdbuf.begin();
    base->draw(cmdbuf, rtt);
    cmdbuf.end();
    auto& sem = rctx->submit(cmdbuf).unwrap().get();

    rctx->endFrame(sem).unwrap();

    // rctx->watchStatus();
}
