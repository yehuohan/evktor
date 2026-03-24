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
    vkt.api->waitIdle();

    skybox.reset();
    base.reset();
    rctx.reset();
    scene.reset();
    scene_camera = nullptr;

    vkt.api.reset();
}

void App::run() {
    setup();
    setupBasePass();
    setupSkyboxPass();

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

    // Load scene
    scene = newBox<Scene>();
    GLTFLoader(vkt).loadScene(*scene, Assets::scene("Sponza/glTF/Sponza.gltf"));
    scene_camera = dynamic_cast<PerspCamera*>(scene->findNode("default.camera")->getComponent<Camera>());
    scene_camera->aspect = (float)width / height;
}

void App::setupBasePass() {
    base = newBox<RenderPipeline>(*rctx, "Base");
    {
        auto vert = Shader::fromVert(Assets::getShader("pbr.vert")).unwrap();
        auto frag = Shader::fromFrag(Assets::getShader("pbr.frag")).unwrap();
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);

        // Subpass for base scene
        base->addSubpass<GeometrySubpass>(std::move(vert), std::move(frag), *scene, *scene_camera)
            .setRTColors({0})
            .setRTDepthStencil(1);
    }
    {
        auto vert = Shader::fromVert(Assets::getShader("builtin.vert")).unwrap();
        auto frag = Shader::fromFrag(Assets::getShader("builtin.frag")).unwrap();
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);
        frag.setDefine("HAS_TEX");

        // Subpass for builtin mesh
        auto [pixels, w, h] = Assets::loadTexRGBA8("box.png");
        auto mesh_tex = newBox<Texture2D>(
            vkt.newTexture2D(VK_FORMAT_R8G8B8A8_SRGB, VkExtent2D(w, h), Texture2D::Transfer | Texture2D::Sampled, 0));
        vkt.pushData(mesh_tex->getImage(), pixels);
        base->addSubpass<BuiltinSubpass>(
                std::move(vert),
                std::move(frag),
                newBox<BuiltinMesh>(BuiltinMesh::from(vkt, BuiltinMeshData::Frustum, std::move(mesh_tex)).unwrap()),
                *scene_camera)
            .setRTColors({0})
            .setRTDepthStencil(1);
    }
}

void App::setupSkyboxPass() {
    skybox = newBox<RenderPipeline>(*rctx, "Skybox");

    {
        auto vert = Shader::fromVert(Assets::getShader("builtin.vert")).unwrap();
        auto frag = Shader::fromFrag(Assets::getShader("builtin.frag")).unwrap();
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);
        vert.setDefine("HAS_SKYBOX");
        frag.setDefine("HAS_SKYBOX");

        auto [pixels, w, h] = Assets::loadCubeRGBA8("spacebox1/right.png",
                                                    "spacebox1/left.png",
                                                    "spacebox1/top.png",
                                                    "spacebox1/bottom.png",
                                                    "spacebox1/front.png",
                                                    "spacebox1/back.png"

        );
        Box<TextureCube> tex_cube = newBox<TextureCube>(
            TextureCube::from(vkt, VK_FORMAT_R8G8B8A8_SRGB, VkExtent2D(w, h), Texture2D::Transfer | Texture2D::Sampled, 0)
                .unwrap());
        vkt.pushData(tex_cube->getImage(), pixels);
        skybox
            ->addSubpass<BuiltinSubpass>(
                std::move(vert),
                std::move(frag),
                newBox<BuiltinMesh>(BuiltinMesh::from(vkt, BuiltinMeshData::Cube, std::move(tex_cube)).unwrap()),
                *scene_camera)
            .setRTColors({0})
            .setRTDepthStencil(1);
    }
}

void App::tick(float cur_time, float delta_time) {
    tickCamera(*scene_camera, delta_time);

    auto& cmdbuf = rctx->beginFrame().unwrap().get();
    auto& rtt = rctx->getFrameRTT().unwrap().get();
    cmdbuf.begin();

    auto& rts = rtt.getTargets();
    rts[0].setOps(core::AttachmentOps::ClearStore);
    rts[0].setLayouts(core::AttachmentLayouts::Color);
    rts[1].setOps(core::AttachmentOps::ClearStore);
    base->draw(cmdbuf, rtt).unwrap();
    rts[0].setOps(core::AttachmentOps::LoadStore);
    rts[0].nextLayout(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    rts[1].setOps(core::AttachmentOps::LoadStore);
    rts[1].nextLayout(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
    skybox->draw(cmdbuf, rtt).unwrap();

    cmdbuf.end();
    auto& sem = rctx->submit(cmdbuf).unwrap().get();

    rctx->endFrame(sem).unwrap();

    // rctx->watchStatus();
}
