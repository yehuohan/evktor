#include "app.h"
#include "assets.hpp"
#include "gltf_loader.hpp"
#include "simple_mesh.hpp"
#include <fstream>
#include <tuple>

#define SIMPLE_MESH 0

App::App(int argc, char* argv[]) : Window(1280, 720) {
    if (argc >= 2) {
        Assets::setDirs(argv[1], "./glsl");
    }
    if (argc >= 3) {
        Assets::setDirs(argv[1], argv[2]);
    }
#if SIMPLE_MESH
    setCamera(ICamera::Arcball, glm::vec3(0.0f, 0.0f, 5.0f));
#else
    setCamera(ICamera::FirstPerson, glm::vec3(0.0f, 0.0f, 5.0f));
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，并Capture光标
#endif
}

App::~App() {
    scene.reset();

    buffer_uniform.clear();
    buffer_index.reset();
    buffer_vertex.reset();
    mesh.reset();
    mesh_spl.reset();

    base.reset();

    rctx.reset();
    vkt.api.reset();
}

void App::run() {
    setup();
    setupBasePass();
    Window::run();
    vkt.api->waitIdle();
}

void App::setup() {
    auto inst_exts = requiredInstanceExtensions();
    inst_exts.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    auto& api = vkt.createApi(
        [&inst_exts](InstanceState& iso) {
            iso.addExtensions(inst_exts);
        },
        std::bind(&vktdev::Window::createSurface, this, std::placeholders::_1));

    SwapchainState sso{};
    sso.addDesiredFormat(VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
        .addDesiredPresentMode(VK_PRESENT_MODE_FIFO_KHR)
        .setDesiredExtent(getExtent());
    rctx = vkt.newRctx(std::move(sso));
}

struct GlobalUBO {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view_proj;
};

void App::tick(float cur_time, float delta_time) {
    const auto& extent = rctx->getSurfaceExtent();
    glm::mat4 view = camera.get()->getView();
    glm::mat4 proj = camera.get()->getProj(extent.width, extent.height);

    auto& cmdbuf = rctx->beginFrame().unwrap().get();
    cmdbuf.setDebugName("Recorder");

    // base->bindImage();
    // ...
    // base->draw(cmdbuf);

    uint32_t frm_idx = rctx->getFrameIndex();

    {
#if SIMPLE_MESH
        SimpleMesh::UBO ubo;
        ubo.model = glm::mat4(1.0);
        ubo.view = view;
        ubo.proj = proj;
#else
        GlobalUBO ubo;
        ubo.model = glm::mat4(1.0);
        ubo.view_proj = proj * view;
#endif
        buffer_uniform[frm_idx].copyFrom(&ubo);
    }
    recordCommandBuffers(cmdbuf, frm_idx);

    auto& sem = rctx->submit(cmdbuf).unwrap().get();
    rctx->endFrame(sem).unwrap();
}

const auto& MESH = MESH_Frustum;

static void uploadPixels(const Image& image, const Vector<uint8_t>& pixels) {
    auto& api = image.api;
    auto& queue = api.graphicsQueue().unwrap().get();
    auto cmdpool = CommandPoolState("CommandPool.Upload")
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueFamilyIndex(queue.family_index)
                       .into(api)
                       .unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary, "CommandBuffer.Upload").unwrap().get();

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

    auto& desc_setlayout = rctx->requestDescriptorSetLayout(0, shaders).unwrap().get();
    auto& pipeline_layout = rctx->requestPipelineLayout(shaders).unwrap().get();
    auto& render_pass = rctx->requestRenderPass(rtt, *base).unwrap().get();

#if SIMPLE_MESH
    auto vertex_input_bindings = Vector<VkVertexInputBindingDescription>({MESH.vertexBindings()});
    auto vertex_input_attrs = MESH.vertexAttributes();
#else
    auto vertex_input_bindings = Vector<VkVertexInputBindingDescription>({
        // layout(location = 0) in vec3 inp_position;
        VkVertexInputBindingDescription{
                                        0, sizeof(glm::vec3),
                                        VK_VERTEX_INPUT_RATE_VERTEX, },
        // layout(location = 1) in vec2 inp_texcoord;
        VkVertexInputBindingDescription{
                                        1, sizeof(glm::vec2),
                                        VK_VERTEX_INPUT_RATE_VERTEX, },
        // layout(location = 2) in vec3 inp_normal;
        VkVertexInputBindingDescription{
                                        2, sizeof(glm::vec3),
                                        VK_VERTEX_INPUT_RATE_VERTEX, },
    });
    auto vertex_input_attrs = Vector<VkVertexInputAttributeDescription>{
        VkVertexInputAttributeDescription{0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0},
        VkVertexInputAttributeDescription{1, 1,    VK_FORMAT_R32G32_SFLOAT, 0},
        VkVertexInputAttributeDescription{2, 2, VK_FORMAT_R32G32B32_SFLOAT, 0},
    };
#endif

    GraphicsPipelineState pso{};
    pso.addVertShader(rctx->requestShaderModule(vert).unwrap().get(), vert.getEntry())
        .addFragShader(rctx->requestShaderModule(frag).unwrap().get(), frag.getEntry())
        .setRenderPass(render_pass)
        .setPipelineLayout(pipeline_layout)
        .addVertexInputBindings(vertex_input_bindings)
        .addVertexInputAttributes(vertex_input_attrs)
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

    vkt.api->cmdBeginLabel(cmdbuf, "OpaquePass");
    cmdbuf.beginRenderPass(rtt.getExtent(), render_pass, framebuffer, rtt.getClearValues()).cmdBindGraphicsPipeline(pipeline);

    desc_info[0].setBuf(0, buffer_uniform[frm_idx]);
#if SIMPLE_MESH
    // Draw sample mesh
    auto& desc_set = frm.requestDescriptorSet(desc_setlayout, desc_info[0]).unwrap().get();
    cmdbuf.cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set})
        .cmdBindIndexBufferU16(*buffer_index)
        .cmdBindVertexBuffers(0, {*buffer_vertex}, {0})
        .cmdDrawIndexed(u32(MESH.indices.size()), 1, 0, 0, 0);
#else
    // Draw scene
    glm::mat4 view = camera.get()->getView();
    glm::mat4 proj = camera.get()->getProj(extent.width, extent.height);

    auto& desc_set = frm.requestDescriptorSet(desc_setlayout, desc_info[0]).unwrap().get();
    for (size_t k = 0; k < scene->meshes.size(); k++) {
        auto& mesh = scene->meshes[k];

        GlobalUBO ubo;
        ubo.model = mesh.model;
        ubo.view_proj = proj * view;
        buffer_uniform[frm_idx].copyFrom(&ubo);

        cmdbuf.cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set});
        if (mesh.tex_idx > -1) {
            auto& tex = scene->textures[mesh.tex_idx];
            desc_info[0].imgs[1].imageView = tex.getImageView();
            auto& desc_set = frm.requestDescriptorSet(desc_setlayout, desc_info[0]).unwrap().get();

            cmdbuf.cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set});
        }

        cmdbuf.cmdBindIndexBuffer(mesh.index, mesh.index_offset, mesh.index_type);
        cmdbuf.cmdBindVertexBuffers(0,
                                    {
                                        mesh.position,
                                        mesh.texcoord,
                                        mesh.normal,
                                        // mesh.tangent
                                    },
                                    {
                                        mesh.position_offset,
                                        mesh.texcoord_offset,
                                        mesh.normal_offset,
                                        // mesh.tangent_offset
                                    });
        // cmdbuf.cmdBindVertexBuffers(0, {mesh.position}, {mesh.position_offset});
        // cmdbuf.cmdBindVertexBuffers(1, {mesh.texcoord}, {mesh.texcoord_offset});
        // cmdbuf.cmdBindVertexBuffers(2, {mesh.normal}, {mesh.normal_offset});

        cmdbuf.cmdDrawIndexed(u32(mesh.index_count), 1, 0, 0, 0);
    }
#endif

    cmdbuf.endRenderPass();
    vkt.api->cmdEndLabel(cmdbuf);

    res = cmdbuf.end();
    if (res != VK_SUCCESS) {
        throw vktErr("failed to end recording command buffer[{}]: {}", frm_idx, (int)res);
    }
}

void App::setupBasePass() {
    vktscn::GLTFLoader loader(vkt);
#if !SIMPLE_MESH
    // scene = loader.loadScene(Assets::scene("triangle.gltf"));
    scene = loader.loadScene(Assets::scene("Sponza/glTF/Sponza.gltf"));
#endif

    base = newBox<RenderPipeline>(vkt);
    {
#if SIMPLE_MESH
        auto vert_file = Assets::shader("simple_mesh.vert");
        auto frag_file = Assets::shader("simple_mesh.frag");
#else
        auto vert_file = Assets::shader("pbr.vert");
        auto frag_file = Assets::shader("pbr.frag");
#endif
        auto vert = Shader::fromVert(Assets::loadShader(vert_file), vert_file);
        auto frag = Shader::fromFrag(Assets::loadShader(frag_file), frag_file);
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);

        RenderSubpass subpass{std::move(vert), std::move(frag)};
        subpass.setRTColors({0});
        subpass.setRTDepthStencil(1);
        base->addSubpass(std::move(subpass));
    }

    {
        auto [pixels, w, h] = Assets::loadTexRGBA8(Assets::tex("box.png"));
        uint32_t mip_levels = static_cast<uint32_t>(std::floor(std::log2(std::max<int>(w, h)))) + 1;
        mesh = newBox<Texture2D>(
            vkt.newTexture2D(VK_FORMAT_R8G8B8A8_SRGB, VkExtent2D(w, h), Texture2D::Transfer | Texture2D::Sampled, mip_levels));
        uploadPixels(mesh->getImage(), pixels);
        mesh_spl = newBox<Sampler>(SamplerState().setNearest().into(vkt).unwrap());

        desc_info[0].setImg(1, mesh->getImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, *mesh_spl);
    }

    for (uint32_t k = 0; k < rctx->getFrameCount(); k++) {
        buffer_uniform.push_back(BufferState()
                                     .setSize(sizeof(SimpleMesh::UBO))
                                     // .setSize(sizeof(GlobalUBO))
                                     .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
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
