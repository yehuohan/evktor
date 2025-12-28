#include "__helpers.hpp"

void case_core_graphics() {
    auto boxapi = createCoreApi();
    auto& api = *boxapi;
    const Triangle tri{};

    // Create command buffer
    auto& queue = api.graphicsQueue().unwrap().get();
    auto cmdpool = CommandPoolState{}.setQueueFamilyIndex(queue.family_index).into(api).unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();
    tstOut("Comamnd buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    ShaderState shader_state;
    auto vert_source = ShaderSource(tri.vert_file, vktdev::Assets::loadShader(tri.vert_file));
    auto frag_source = ShaderSource(tri.frag_file, vktdev::Assets::loadShader(tri.frag_file));
    shader_state.setStage(VK_SHADER_STAGE_VERTEX_BIT).setEntry("main");
    auto shader_vert = Shader::from(vert_source, shader_state).unwrap().into(api).unwrap();
    shader_state.setStage(VK_SHADER_STAGE_FRAGMENT_BIT);
    auto shader_frag = Shader::from(frag_source, shader_state).unwrap().into(api).unwrap();

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
    auto pipeline_layout = PipelineLayoutState{}
                               .addDescriptorSetLayout(desc_set_layout)
                               .addGraphicsPushConstant(sizeof(Triangle::PushArgs))
                               .into(api)
                               .unwrap();
    auto pipeline = GraphicsPipelineState{}
                        .addVertShader(shader_vert)
                        .addFragShader(shader_frag,
                                       "main",
                                       {&tri.spec_args,
                                        sizeof(Triangle::SpecArgs),
                                        {{0, offsetof(Triangle::SpecArgs, alpha), sizeof(int)}}})
                        .addVertexInputBinding({0, 8 * sizeof(float), VK_VERTEX_INPUT_RATE_VERTEX})
                        .addVertexInputAttribute({0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0})
                        .addVertexInputAttribute({1, 0, VK_FORMAT_R32G32B32_SFLOAT, 3 * sizeof(float)})
                        .addVertexInputAttribute({2, 0, VK_FORMAT_R32G32_SFLOAT, 6 * sizeof(float)})
                        // Vulkan use top-left as original (0, 0), flip the Y axis with negative viewport height
                        .addViewport(0, tri.hei, tri.wid, -float(tri.hei))
                        .addScissor(0, 0, tri.wid, tri.hei)
                        // Disable culling face to display flipped y axis
                        .setRasterizationCullFace(VK_CULL_MODE_NONE)
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
                       .setExtent(tri.wid, tri.hei)
                       .setUsage(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto out_imgview = ImageViewState{}.setFromImage(out_img).into(api).unwrap();
    auto framebuffer =
        FramebufferState{}.setRenderPass(render_pass).setExtent(tri.wid, tri.hei).addAttachment(out_imgview).into(api).unwrap();

    // Create descriptors
    auto desc_pool = DescriptorPoolState{}
                         .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                         .into(desc_set_layout)
                         .unwrap();
    auto desc_set = desc_pool.allocate().unwrap();
    auto ubo_buf = BufferState{}
                       .setSize(sizeof(Triangle::UBO))
                       .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                       .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                       .into(api)
                       .unwrap();
    ubo_buf.copyFrom(&tri.ubo);
    auto tex_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(tri.wid, tri.hei)
                       .setUsage(VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT)
                       .into(api)
                       .unwrap();
    auto tex_imgview = ImageViewState{}.setFromImage(tex_img).into(api).unwrap();
    auto spl = SamplerState{}.setLinear().into(api).unwrap();
    auto desc_info = DescriptorInfo{};
    desc_info.bufs[0] = VkDescriptorBufferInfo{ubo_buf, 0, sizeof(Triangle::UBO)};
    desc_info.imgs[1] = VkDescriptorImageInfo{spl, tex_imgview, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
    desc_set.update(desc_info);

    // Create stage buffer
    auto stage = BufferState{}
                     .setSize(tri.num * sizeof(float))
                     .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                     .into(api)
                     .unwrap();

    // Create vertex and index buffer
    auto vertex_buf = BufferState{}
                          .setSize(sizeof(tri.vertices))
                          .setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                          .into(api)
                          .unwrap();
    auto index_buf = BufferState{}
                         .setSize(sizeof(tri.indices))
                         .setUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                         .into(api)
                         .unwrap();
    stage.copyFrom(tri.vertices, sizeof(tri.vertices));
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(stage, vertex_buf, 0, 0, sizeof(tri.vertices));
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
    stage.copyFrom(tri.indices, sizeof(tri.indices));
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(stage, index_buf, 0, 0, sizeof(tri.indices));
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Record command
    stage.copyFrom(tri.tex.data());
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
    cmdbuf.beginRenderPass({tri.wid, tri.hei}, render_pass, framebuffer, {VkClearValue{}})
        .cmdBindGraphicsPipeline(pipeline)
        .cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set})
        .cmdPushGraphicsConstants(pipeline_layout, &tri.push_args, sizeof(Triangle::PushArgs))
        .cmdBindVertexBuffers(0, {vertex_buf}, {0})
        .cmdBindIndexBuffer(index_buf, 0, VK_INDEX_TYPE_UINT32)
        .cmdDrawIndexed(3, 1, 0, 0, 0)
        .endRenderPass();
    cmdbuf.cmdImageMemoryBarrier(Arg{out_img},
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                                 VK_ACCESS_TRANSFER_READ_BIT,
                                 VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    cmdbuf.cmdCopyImageToBuffer(Arg{out_img}, stage);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check stage buffer
    Vector<float> out(tri.num);
    stage.copyInto(out.data());
    tri.checkOutput(out);
}
