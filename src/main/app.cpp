#include "app.h"
#include "assets.hpp"
#include "simple_mesh.hpp"
#include <fstream>
#include <stb_image.h>

App::App(int argc, char* argv[]) : Window(1280, 720) {
    if (argc >= 2) {
        Assets::setDirs(argv[1], "./glsl");
    }
    if (argc >= 3) {
        Assets::setDirs(argv[1], argv[2]);
    }
    setCamera(ICamera::Arcball, glm::vec3(0.0f, 0.0f, 5.0f));
}

void App::run() {
    setup();
    setupBasePass();
    Window::run();
    vkt.api->waitIdle();
}

void App::setup() {
    CoreApiState aso{};
    DebugState dso{};

    // Create instance
    auto& inst = aso.init(InstanceState()
                              .setNext(dso)
                              .setAppName("evktor")
                              .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                              .setEngineName("vktor")
                              .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                              .setApiVerion(VK_API_VERSION_1_2)
                              .addExtensions(requiredInstanceExtensions())
                              .enableLayerValidation()
                              .enableExtensionDebugUtils()
                              .setVerbose(false))
                     .unwrap()
                     .get();

    // Create debug
    aso.init(dso).unwrap();

    // Create surface
    auto surface = createSurface(inst);

    // Select physical device
    auto& phy_dev = aso.init(PhysicalDeviceState()
                                 .preferDiscreteGPU()
                                 // .preferIntegratedGPU()
                                 .requirePresentQueue(surface)
                                 .requireGraphicsQueue()
                                 .requireComputeQueue()
                                 .requireTransferQueue()
                                 .addRequiredExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME)
                                 .addRequiredExtension(VK_KHR_MAINTENANCE1_EXTENSION_NAME)
                                 .addChecker([](VkInstance, VkPhysicalDevice pd) {
                                     auto indexing_features = Itor::PhysicalDeviceDescriptorIndexingFeatures();
                                     auto physical_device_features = Itor::PhysicalDeviceFeatures2(&indexing_features);
                                     vkGetPhysicalDeviceFeatures2(pd, &physical_device_features);
                                     return indexing_features.descriptorBindingPartiallyBound &&
                                            indexing_features.runtimeDescriptorArray;
                                 })
                                 .setVerbose(false))
                        .unwrap()
                        .get();

    auto physical_device_features = Itor::PhysicalDeviceFeatures2();
    vkGetPhysicalDeviceFeatures2(phy_dev, &physical_device_features);
    auto indexing_features = Itor::PhysicalDeviceDescriptorIndexingFeatures();
    indexing_features.descriptorBindingPartiallyBound = VK_TRUE;
    indexing_features.runtimeDescriptorArray = VK_TRUE;
    physical_device_features.pNext = &indexing_features;

    // Create device
    aso.init(DeviceState().setNext(&physical_device_features).setMaxQueueCount(1).setVerbose(false)).unwrap();

    // Create core api
    vkt.api = aso.into().unwrap();
    CoreApi& api = vkt;

    // Create swapchain
    SwapchainState sso(api.newSurface(surface).unwrap());
    sso.addDesiredFormat(VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
        .addDesiredPresentMode(VK_PRESENT_MODE_FIFO_KHR)
        .setDesiredExtent(getExtent());
    rctx = vkt.newRctx(std::move(sso));
}

void App::tick(float cur_time, float delta_time) {
    const auto& extent = rctx->getSurfaceExtent();
    glm::mat4 view = camera.get()->getView();
    glm::mat4 proj = camera.get()->getProj(extent.width, extent.height);

    auto& cmdbuf = rctx->beginFrame().unwrap().get();

    // base->bindImage();
    // ...
    // base->draw(cmdbuf);

    uint32_t frm_idx = rctx->getFrameIndex();

    {
        SimpleMesh::UBO ubo;
        ubo.model = glm::mat4(1.0);
        ubo.view = view;
        ubo.proj = proj;
        buffer_uniform[frm_idx].copyFrom(&ubo);
    }
    recordCommandBuffers(cmdbuf, frm_idx);

    auto& sem = rctx->submit(cmdbuf).unwrap().get();
    rctx->endFrame(sem).unwrap();
}

const auto& MESH = MESH_Frustum;

static void uploadPixels(const Image& image, Vector<uint8_t> pixels) {
    auto& api = image.api;
    auto& queue = api.transferQueue().unwrap().get();
    auto cmdpool = CommandPoolState()
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueFamilyIndex(queue.family_index)
                       .into(api)
                       .unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();

    auto buf = BufferState("StageBuffer")
                   .setSize(u64(pixels.size()))
                   .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                   .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                   .into(image.api)
                   .unwrap();
    buf.copyFrom(pixels.data());

    Arg arg(image);
    cmdbuf.begin();
    cmdbuf.cmdImageMemoryBarrier(arg,
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 0,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    cmdbuf.cmdCopyBufferToImage(buf, arg);
    cmdbuf.cmdGenImageMips(arg, VK_FILTER_LINEAR);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
}

void App::recordCommandBuffers(CommandBuffer& cmdbuf, uint32_t frm_idx) {
    const auto& extent = rctx->getSurfaceExtent();
    auto& frm = rctx->getFrame().get();
    auto& rtt = frm.getSwapchainRTT().unwrap().get();

    auto& subpass = base->getSubpasses()[0];
    const auto& shaders = subpass.Shaders();
    const auto& vert = subpass.vertShader();
    const auto& frag = subpass.fragShader();
    auto shader_vert = vert.into(vkt).unwrap();
    auto shader_frag = frag.into(vkt).unwrap();

    {
        const auto& buffer = buffer_uniform[frm_idx];
        auto& buf = desc_info[0].bufs[0];
        buf.buffer = buffer;
        buf.offset = 0;
        buf.range = buffer.size;
    }

    auto& desc_setlayout = rctx->requestDescriptorSetLayout(0, shaders).unwrap().get();
    auto& desc_set = frm.requestDescriptorSet(desc_setlayout, desc_info[0]).unwrap().get();
    auto& pipeline_layout = rctx->requestPipelineLayout(shaders).unwrap().get();
    auto& render_pass = rctx->requestRenderPass(rtt, *base).unwrap().get();
    GraphicsPipelineState pso{};
    pso.addShader(std::move(shader_vert))
        .addShader(std::move(shader_frag))
        .setRenderPass(render_pass)
        .setPipelineLayout(pipeline_layout)
        .addVertexInputBinding(MESH.vertexBindings())
        .addVertexInputAttributes(MESH.vertexAttributes())
        .addViewport(0.0, extent.height, extent.width, -float(extent.height))
        .addScissor(0, 0, extent.width, extent.height)
        .setDepthTest(VK_TRUE, VK_TRUE)
        // .addDynamic(VK_DYNAMIC_STATE_VIEWPORT)
        // .addDynamic(VK_DYNAMIC_STATE_SCISSOR)
        .addColorBlendAttachment(
            VkPipelineColorBlendAttachmentState{.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                                  VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT});
    auto& pipeline = rctx->requestGraphicsPipeline(pso).unwrap().get();
    auto& framebuffer = rctx->requestFramebuffer(rtt, render_pass).unwrap().get();

    VkResult res = cmdbuf.begin();
    if (res != VK_SUCCESS) {
        throw vktErr("failed to begin recording command buffer[{}]: {}", frm_idx, (int)res);
    }
    cmdbuf.beginRenderPass(render_pass, framebuffer, {0, 0}, rtt.getExtent(), rtt.getClearValues())
        .cmdBindPipeline(VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline)
        .cmdBindDescriptorSets(VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout, 0, {desc_set})
        .cmdBindIndexBuffer(*buffer_index, 0, VK_INDEX_TYPE_UINT16)
        .cmdBindVertexBuffers(0, 1, {*buffer_vertex}, {0})
        .cmdDrawIndexed(u32(MESH.indices.size()), 1, 0, 0, 0)
        .endRenderPass();
    res = cmdbuf.end();
    if (res != VK_SUCCESS) {
        throw vktErr("failed to end recording command buffer[{}]: {}", frm_idx, (int)res);
    }
}

void App::setupBasePass() {
    SceneLoader loader(vkt);
    scene = loader.load(Assets::scene("triangle.gltf"));

    base = newBox<RenderPipeline>(vkt);
    {
        auto filename = Assets::shaderFile("simple_mesh.vert");
        auto stage = Assets::shaderStage(filename);
        auto code = Assets::shaderSource(filename);
        auto vert_source = ShaderSource::from(stage, std::move(code)).unwrap();
        filename = Assets::shaderFile("simple_mesh.frag");
        stage = Assets::shaderStage(filename);
        code = Assets::shaderSource(filename);
        auto frag_source = ShaderSource::from(stage, std::move(code)).unwrap();
        auto& vert = rctx->requestShader(vert_source).unwrap().get();
        auto& frag = rctx->requestShader(frag_source).unwrap().get();
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);

        RenderSubpass subpass{std::move(vert), std::move(frag)};
        subpass.setRTColors({0});
        subpass.setRTDepthStencil(1);
        base->addSubpass(std::move(subpass));
    }

    {
        std::vector<uint8_t> pixels{};
        int w, h, c;
        {
            stbi_uc* raw = stbi_load(Assets::tex("box.png").c_str(), &w, &h, &c, STBI_rgb_alpha);
            pixels = {raw, raw + w * h * c};
            stbi_image_free(raw);
        }
        uint32_t mip_levels = static_cast<uint32_t>(std::floor(std::log2(std::max(w, h)))) + 1;

        mesh = vkt.newTex(VK_FORMAT_R8G8B8A8_SRGB, VkExtent2D(w, h), Texture2D::Transfer | Texture2D::Sampled, mip_levels);
        uploadPixels(mesh->getImage(), pixels);

        mesh_spl = newBox<Sampler>(SamplerState().setNearest().into(vkt).unwrap());
    }

    {
        const core::ImageView& imageview = mesh->getImageView();
        const core::Sampler& sampler = *mesh_spl;
        auto& img = desc_info[0].imgs[1];
        img.sampler = sampler;
        img.imageView = imageview;
        img.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    for (uint32_t k = 0; k < rctx->getFrameCount(); k++) {
        buffer_uniform.push_back(BufferState()
                                     .setSize(sizeof(SimpleMesh::UBO))
                                     .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                     // .native_from(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT).unwrap()));
                                     .into(vkt)
                                     .unwrap());
    }

    // Create index buffer
    {
        VkDeviceSize buffer_size = MESH.indices_size();
        Buffer buffer_staging = BufferState()
                                    .setSize(buffer_size)
                                    .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                    .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                    .into(vkt)
                                    .unwrap();
        buffer_index = newBox<Buffer>(BufferState()
                                          .setSize(buffer_size)
                                          .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                                          .into(vkt)
                                          .unwrap());

        CoreApi& api = vkt;
        auto& render_frame = rctx->getFrame().get();
        auto& queue = api.transferQueue().unwrap().get();
        auto& cmdbuf = render_frame.requestCommandBuffer(queue).unwrap().get();
        buffer_staging.copyFrom(MESH.indices.data());
        cmdbuf.begin();
        cmdbuf.cmdCopyBuffer(buffer_staging, *buffer_index);
        cmdbuf.end();
        queue.submit(cmdbuf);
        queue.waitIdle();
    }

    // Create vertex buffer
    {
        VkDeviceSize buffer_size = MESH.vertices_size();
        Buffer buffer_staging = BufferState()
                                    .setSize(buffer_size)
                                    .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                    .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                    .into(vkt)
                                    .unwrap();
        buffer_vertex = newBox<Buffer>(BufferState()
                                           .setSize(buffer_size)
                                           .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
                                           .into(vkt)
                                           .unwrap());

        CoreApi& api = vkt;
        auto& render_frame = rctx->getFrame().get();
        auto& queue = api.transferQueue().unwrap().get();
        auto& cmdbuf = render_frame.requestCommandBuffer(queue).unwrap().get();
        buffer_staging.copyFrom(MESH.vertices.data());
        cmdbuf.begin();
        cmdbuf.cmdCopyBuffer(buffer_staging, *buffer_vertex);
        cmdbuf.end();
        queue.submit(cmdbuf);
        queue.waitIdle();
    }
}
