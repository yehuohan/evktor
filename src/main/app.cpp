#include "app.h"
#include "assets.hpp"
#include "simple_mesh.hpp"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static void uploadPixels(const Image& image, Vector<uint8_t> pixels) {
    auto& api = image.api;
    auto& queue = api.transferQueue().unwrap().get();
    auto cmdpool = CommandPoolState()
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueIndex(queue.family_index)
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
    cmdbuf.cmdTransitImageLayout(arg, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    cmdbuf.cmdCopyBufferToImage(buf, arg);
    cmdbuf.cmdGenImageMips(arg, VK_FILTER_LINEAR);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
}

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

void App::tick(float cur_time, float delta_time) {
    const auto& extent = rctx->getSurfaceExtent();
    glm::mat4 view = camera.get()->getView();
    glm::mat4 proj = camera.get()->getProj(extent.width, extent.height);
    // Vulkan use top-left as original (0, 0), so invert the Y axis of projection.
    proj[1][1] *= -1;

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

void App::setup() {
    CoreApiState aso{};

    // Create instance
    DebugState dso{};
    auto& inst = aso.init(InstanceState()
                              .setAppName("evktor")
                              .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                              .setEngineName("vktor")
                              .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                              .setApiVerion(VK_API_VERSION_1_2)
                              .addExtensions(requiredInstanceExtensions())
                              .enableLayerValidation()
                              .enableExtensionDebugUtils(&dso)
                              .setVerbose(false))
                     .unwrap()
                     .get();

    // Create surface
    auto surface = createSurface(inst);

    // Select physical device
    aso.init(PhysicalDeviceState()
                 .preferDiscreteGPU()
                 // .preferIntegratedGPU()
                 .requirePresentQueue(surface)
                 .requireGraphicsQueue()
                 .requireComputeQueue()
                 .requireTransferQueue()
                 .addRequiredExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME)
                 .setVerbose(false))
        .unwrap();

    // Create device
    aso.init(DeviceState().setMaxQueueCount(1).setVerbose(true)).unwrap();

    // Create core api
    vkt.api = newBox<CoreApi>(aso.into().unwrap());
    CoreApi& api = vkt;

    // Create swapchain
    SwapchainState sso(api.newSurface(surface).unwrap());
    sso.addDesiredFormat(VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
        .addDesiredPresentMode(VK_PRESENT_MODE_FIFO_KHR)
        .setDesiredExtent(getExtent());
    rctx = vkt.newRctx(std::move(sso));
    rdg = vkt.newRdg();
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

    base->bindBuffer(buffer_uniform[frm_idx], 0);
    auto& desc_setlayout = rctx->requestDescriptorSetLayout(0, shaders).unwrap().get();
    auto& desc_set = frm.requestDescriptorSet(desc_setlayout, base->desc_info[0]).unwrap().get();
    auto& pipeline_layout = rctx->requestPipelineLayout(shaders).unwrap().get();
    auto& render_pass = rctx->requestRenderPass(rtt, *base).unwrap().get();
    GraphicsPipelineState pso{};
    VkPipelineColorBlendAttachmentState color_blend_attm{};
    color_blend_attm.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                                      VK_COLOR_COMPONENT_A_BIT;
    pso.addShader(std::move(shader_vert))
        .addShader(std::move(shader_frag))
        .setRenderPass(render_pass)
        .setPipelineLayout(pipeline_layout)
        .addVertexInputBinding(MESH_Frustum.vertexBindings())
        .addVertexInputAttributes(MESH_Frustum.vertexAttributes())
        .addViewport(0.0, 0.0, extent.width, extent.height)
        .addScissor(0, 0, extent.width, extent.height)
        .setDepthTest(VK_TRUE, VK_TRUE)
        .addColorBlendAttachment(color_blend_attm);
    // .addDynamic(VK_DYNAMIC_STATE_VIEWPORT)
    // .addDynamic(VK_DYNAMIC_STATE_SCISSOR)
    auto& pipeline = rctx->requestGraphicsPipeline(pso).unwrap().get();
    auto& framebuffer = rctx->requestFramebuffer(rtt, render_pass).unwrap().get();

    auto clears = rtt.getClearValues();
    auto render_pass_bi = Itor::RenderPassBeginInfo();
    render_pass_bi.renderPass = render_pass;
    render_pass_bi.framebuffer = framebuffer;
    render_pass_bi.renderArea = VkRect2D{
        .offset = {0, 0},
        .extent = rtt.getExtent(),
    };
    render_pass_bi.clearValueCount = u32(clears.size());
    render_pass_bi.pClearValues = clears.data();

    VkResult ret = cmdbuf.begin();
    if (ret != VK_SUCCESS) {
        throw vktErr("failed to begin recording command buffer[{}]: {}", frm_idx, (int)ret);
    }
    cmdbuf.beginRenderPass(render_pass_bi)
        .cmdBindPipeline(VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline)
        .cmdBindDescriptorSets(VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout, 0, {desc_set})
        .cmdBindIndexBuffer(*buffer_index, 0, VK_INDEX_TYPE_UINT16)
        .cmdBindVertexBuffers(0, 1, {*buffer_vertex}, {0})
        .cmdDrawIndexed(u32(MESH_Frustum.indices.size()), 1, 0, 0, 0)
        .endRenderPass();
    ret = cmdbuf.end();
    if (ret != VK_SUCCESS) {
        throw vktErr("failed to end recording command buffer[{}]: {}", frm_idx, (int)ret);
    }
}

void App::setupBasePass() {
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
    base->bindImage(mesh->getImageView(), *mesh_spl, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 1);

    for (uint32_t k = 0; k < rctx->getFrameCount(); k++) {
        buffer_uniform.push_back(BufferState()
                                     .setSize(sizeof(SimpleMesh::UBO))
                                     .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                     // .native_from(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT).unwrap()));
                                     .into(vkt)
                                     .unwrap());
    }

    createIndexBuffer();
    createVertexBuffer();
}

void App::createIndexBuffer() {
    VkDeviceSize buffer_size = MESH_Frustum.indices_size();
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
    buffer_staging.copyFrom(MESH_Frustum.indices.data());
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(buffer_staging, *buffer_index);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
}

void App::createVertexBuffer() {
    VkDeviceSize buffer_size = MESH_Frustum.vertices_size();
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
    buffer_staging.copyFrom(MESH_Frustum.vertices.data());
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(buffer_staging, *buffer_vertex);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
}
