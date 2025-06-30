#include "__helpers.hpp"
#include <assets.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vktor.hpp>

using namespace vkt;
using namespace vkt::core;

Box<CoreApi> setupCoreApi() {
    CoreApiState aso{};
    DebugState dso{};

    // Create instance
    aso.init(InstanceState()
                 .setNext(dso)
                 .setAppName("tst_core")
                 .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                 .setEngineName("vktor")
                 .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                 .setApiVerion(VK_API_VERSION_1_2)
                 .enableLayerValidation()
                 .enableExtensionDebugUtils()
                 .setVerbose(true))
        .unwrap();

    aso.init(dso).unwrap();

    // Select physical device
    aso.init(PhysicalDeviceState()
                 .preferDiscreteGPU()
                 // .preferIntegratedGPU()
                 .requireGraphicsQueue()
                 .requireComputeQueue()
                 .addRequiredExtension(VK_KHR_MAINTENANCE1_EXTENSION_NAME)
                 .setVerbose(true))
        .unwrap();

    // Create device
    aso.init(DeviceState().setMaxQueueCount(1).setVerbose(true)).unwrap();

    // Create core api
    Box<CoreApi> api = aso.into().unwrap();

    tstOut("Instance: {}, Physical Device: {}, Device: {}",
           fmt::ptr((VkInstance)*api),
           fmt::ptr((VkPhysicalDevice)*api),
           fmt::ptr((VkDevice)*api));

    return std::move(api);
}

void computePass(const CoreApi& api) {
    const vkt::String shader_file = vktdev::Assets::shaderFile("test/quad.comp");
    const uint32_t wid = 9;
    const uint32_t hei = 9;
    const uint32_t cha = 4;
    const uint32_t num = wid * hei * cha;
    static float buf[num];

    // Create command buffer
    auto& queue = api.computeQueue().unwrap().get();
    auto cmdpool = CommandPoolState{}.setQueueFamilyIndex(queue.family_index).into(api).unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();
    tstOut("Comamnd buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    auto shader_source = ShaderSource::from(ShaderSource::Comp, read_shader(shader_file)).unwrap();
    auto shader = Shader::from(shader_source).unwrap().into(api).unwrap();

    // Create pipeline
    auto desc_set_layout = DescriptorSetLayoutState{}
                               .addCompBinding(0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .addCompBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .into(api)
                               .unwrap();
    auto pipeline_layout = PipelineLayoutState{}.addDescriptorSetLayout(desc_set_layout).into(api).unwrap();
    auto pipeline = ComputePipelineState{}.setShader(std::move(shader)).setPipelineLayout(pipeline_layout).into(api).unwrap();
    tstOut("Compute pipeline: {}", fmt::ptr((VkPipeline)pipeline));

    // Create descriptors
    auto desc_pool = DescriptorPoolState{}
                         .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                         .into(desc_set_layout)
                         .unwrap();
    auto desc_set = desc_pool.allocate().unwrap();
    auto inp_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(wid, hei)
                       .setUsage(VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto inp_imgview = ImageViewState{}.setFromImage(inp_img).into(api).unwrap();
    auto out_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(wid, hei)
                       .setUsage(VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto out_imgview = ImageViewState{}.setFromImage(out_img).into(api).unwrap();
    auto desc_info = DescriptorInfo{};
    desc_info.imgs[0] = VkDescriptorImageInfo{VK_NULL_HANDLE, inp_imgview, VK_IMAGE_LAYOUT_GENERAL};
    desc_info.imgs[1] = VkDescriptorImageInfo{VK_NULL_HANDLE, out_imgview, VK_IMAGE_LAYOUT_GENERAL};
    desc_set.update(desc_info);

    // Create stage buffer
    auto stage = BufferState{}
                     .setSize(num * sizeof(float))
                     .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                     .into(api)
                     .unwrap();
    for (int k = 0; k < 12; k++) {
        buf[k] = k + 1;
    }
    stage.copyFrom(buf);

    // Record command
    cmdbuf.begin();
    cmdbuf.cmdImageMemoryBarrier(Arg{inp_img},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 0,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    cmdbuf.cmdCopyBufferToImage(stage, Arg{inp_img});
    cmdbuf.cmdImageMemoryBarrier(Arg{inp_img},
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                                 VK_ACCESS_TRANSFER_READ_BIT,
                                 VK_ACCESS_SHADER_READ_BIT,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                 VK_IMAGE_LAYOUT_GENERAL);
    cmdbuf.cmdImageMemoryBarrier(Arg{out_img},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                                 0,
                                 VK_ACCESS_SHADER_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_GENERAL);
    cmdbuf.cmdBindPipeline(VK_PIPELINE_BIND_POINT_COMPUTE, pipeline)
        .cmdBindDescriptorSets(VK_PIPELINE_BIND_POINT_COMPUTE, pipeline_layout, 0, {desc_set})
        .cmdDispatch((wid + 7) / 8, (hei + 7) / 8, 1);
    cmdbuf.cmdImageMemoryBarrier(Arg{out_img},
                                 VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_ACCESS_SHADER_WRITE_BIT,
                                 VK_ACCESS_TRANSFER_READ_BIT,
                                 VK_IMAGE_LAYOUT_GENERAL,
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    cmdbuf.cmdCopyImageToBuffer(Arg{out_img}, stage);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check stage buffer
    stage.copyInto(buf);
    tstOut("out_img: {}", vec2str(vkt::Vector<float>{buf, buf + 12}));
}

void graphicsPass(const CoreApi& api) {
    const vkt::String shader_vert_file = vktdev::Assets::shaderFile("test/triangle.vert");
    const vkt::String shader_frag_file = vktdev::Assets::shaderFile("test/triangle.frag");
    const uint32_t wid = 9;
    const uint32_t hei = 9;
    const uint32_t cha = 4;
    const uint32_t num = wid * hei * cha;
    const float vertex_data[] = {
        // pos,             color,            uv
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 左下角
        1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 右下角
        0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, // 上中
    };
    const uint32_t index_data[] = {0, 1, 2};
    struct Ubo {
        glm::mat4 view;
        glm::mat4 proj;
    } ubo;
    ubo.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f) /* eye */,
                           glm::vec3(0.0f, 0.0f, 0.0f) /* center */,
                           glm::vec3(0.0f, 1.0f, 0.0f) /* up */);
    ubo.proj = glm::perspective(glm::radians(45.0f), (float)wid / hei, 0.1f, 100.0f);
    static float buf[num];

    // Create command buffer
    auto& queue = api.computeQueue().unwrap().get();
    auto cmdpool = CommandPoolState{}.setQueueFamilyIndex(queue.family_index).into(api).unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();
    tstOut("Comamnd buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    auto shader_vert_source = vkt::ShaderSource::from(ShaderSource::Vert, read_shader(shader_vert_file)).unwrap();
    auto shader_vert = vkt::Shader::from(shader_vert_source).unwrap().into(api).unwrap();
    auto shader_frag_source = vkt::ShaderSource::from(ShaderSource::Frag, read_shader(shader_frag_file)).unwrap();
    auto shader_frag = vkt::Shader::from(shader_frag_source).unwrap().into(api).unwrap();

    // Create pipeline
    auto render_pass = RenderPassState{}
                           .addColorAttachment(VK_FORMAT_R32G32B32A32_SFLOAT, VK_SAMPLE_COUNT_1_BIT)
                           .addSubpass({}, {0})
                           .into(api)
                           .unwrap();
    auto desc_set_layout = DescriptorSetLayoutState{}
                               .addVertBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
                               .addFragBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                               .into(api)
                               .unwrap();
    auto pipeline_layout = PipelineLayoutState{}.addDescriptorSetLayout(desc_set_layout).into(api).unwrap();

    auto pipeline = GraphicsPipelineState{}
                        .addShader(std::move(shader_vert))
                        .addShader(std::move(shader_frag))
                        .addVertexInputBinding({0, 8 * sizeof(float), VK_VERTEX_INPUT_RATE_VERTEX})
                        .addVertexInputAttribute({0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0})
                        .addVertexInputAttribute({1, 0, VK_FORMAT_R32G32B32_SFLOAT, 3 * sizeof(float)})
                        .addVertexInputAttribute({2, 0, VK_FORMAT_R32G32_SFLOAT, 6 * sizeof(float)})
                        // Vulkan use top-left as original (0, 0), flip the Y axis with negative viewport height
                        .addViewport(0, hei, wid, -float(hei))
                        .addScissor(0, 0, wid, hei)
                        .setRasterizationCullFace(VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_COUNTER_CLOCKWISE)
                        .addColorBlendAttachment(VkPipelineColorBlendAttachmentState{
                            .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                                              VK_COLOR_COMPONENT_A_BIT})
                        .setPipelineLayout(pipeline_layout)
                        .setRenderPass(render_pass)
                        .into(api)
                        .unwrap();
    tstOut("Graphics pipeline: {}", fmt::ptr((VkPipeline)pipeline));

    // Create framebuffer
    auto out_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(wid, hei)
                       .setUsage(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto out_imgview = ImageViewState{}.setFromImage(out_img).into(api).unwrap();
    auto framebuffer =
        FramebufferState{}.setRenderPass(render_pass).setExtent(wid, hei).addAttachment(out_imgview).into(api).unwrap();

    // Create descriptors
    auto desc_pool = DescriptorPoolState{}
                         .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                         .into(desc_set_layout)
                         .unwrap();
    auto desc_set = desc_pool.allocate().unwrap();
    auto ubo_buf = BufferState{}
                       .setSize(sizeof(Ubo))
                       .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                       .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                       .into(api)
                       .unwrap();
    ubo_buf.copyFrom(&ubo);
    auto tex_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(wid, hei)
                       .setUsage(VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT)
                       .into(api)
                       .unwrap();
    auto tex_imgview = ImageViewState{}.setFromImage(tex_img).into(api).unwrap();
    auto spl = SamplerState{}.setLinear().into(api).unwrap();
    auto desc_info = DescriptorInfo{};
    desc_info.bufs[0] = VkDescriptorBufferInfo{ubo_buf, 0, sizeof(Ubo)};
    desc_info.imgs[1] = VkDescriptorImageInfo{spl, tex_imgview, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
    desc_set.update(desc_info);

    // Create stage buffer
    auto stage = BufferState{}
                     .setSize(num * sizeof(float))
                     .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                     .into(api)
                     .unwrap();

    // Create vertex and index buffer
    auto vertex_buf = BufferState{}
                          .setSize(sizeof(vertex_data))
                          .setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                          .into(api)
                          .unwrap();
    auto index_buf = BufferState{}
                         .setSize(sizeof(index_data))
                         .setUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                         .into(api)
                         .unwrap();
    stage.copyFrom(vertex_data, sizeof(vertex_data));
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(stage, vertex_buf, 0, 0, sizeof(vertex_data));
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
    stage.copyFrom(index_data, sizeof(index_data));
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(stage, index_buf, 0, 0, sizeof(index_data));
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Record command
    for (int k = 0; k < num; k++) {
        buf[k] = 1.0;
    }
    stage.copyFrom(buf);
    cmdbuf.begin();
    cmdbuf.cmdImageMemoryBarrier(Arg{tex_img},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 0,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    cmdbuf.cmdCopyBufferToImage(stage, Arg{tex_img});
    cmdbuf.cmdImageMemoryBarrier(Arg{tex_img},
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_ACCESS_SHADER_READ_BIT,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                 VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    cmdbuf.cmdImageMemoryBarrier(Arg{out_img},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 0,
                                 VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    cmdbuf.beginRenderPass(render_pass, framebuffer, {0, 0}, {wid, hei}, {VkClearValue{}})
        .cmdBindPipeline(VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline)
        .cmdBindDescriptorSets(VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout, 0, {desc_set})
        .cmdBindVertexBuffers(0, {vertex_buf}, {0})
        .cmdBindIndexBuffer(index_buf, 0, VK_INDEX_TYPE_UINT32)
        .cmdDrawIndexed(3, 1, 0, 0, 0)
        .endRenderPass();
    cmdbuf.cmdImageMemoryBarrier(Arg{out_img},
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    cmdbuf.cmdCopyImageToBuffer(Arg{out_img}, stage);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check stage buffer
    stage.copyInto(buf);
    tstOut("out_img:");
    for (size_t r = 0; r < hei; r++) {
        char line[wid + 1];
        for (size_t c = 0; c < wid; c++) {
            size_t idx = (r * wid + c) * cha;
            float gray = (buf[idx + 0] + buf[idx + 1] + buf[idx + 2]) / 3.0;
            line[c] = gray > 0.5 ? '*' : '#';
        }
        line[wid] = '\0';
        tstOut("{}", line);
    }
}

void case_core() {
    auto api = setupCoreApi();
    computePass(*api);
    graphicsPass(*api);
}
