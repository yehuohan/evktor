#include "__helpers.hpp"

void case_rctx_dynamic_rendering() {
    // Create RenderContext
    Vktor vkt;
    CoreApi& api = vkt.createApi();
    auto rctx = vkt.newRctx(1);
    auto& rfrm = rctx->getFrame().get();
    const Triangle tri{};

    // Create command buffer
    auto& queue = api.graphicsQueue().unwrap().get();
    auto& cmdbuf = rctx->beginFrame().unwrap().get();
    tstOut("Command buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    auto shader_vert = Shader::fromVert(vktdev::Assets::loadShader(tri.vert_file), tri.vert_file);
    auto shader_frag = Shader::fromFrag(vktdev::Assets::loadShader(tri.frag_file), tri.frag_file);
    shader_vert.addDescriptor(ShaderDescriptor::Type::BufferUniform, 0).setPushConstant(sizeof(int));
    shader_frag.addDescriptor(ShaderDescriptor::Type::ImageSampler, 1)
        .setPushConstant(sizeof(int), 20)
        .addSpecConstant(0, reinterpret_cast<const uint8_t*>(&tri.spec_args.alpha), sizeof(int));
    auto shaders = Vector<CRef<Shader>>{newCRef(shader_vert), newCRef(shader_frag)};

    // Create descriptors
    auto ubo_buf = vkt.newUniformBuffer(sizeof(Triangle::UBO));
    ubo_buf.copyFrom(&tri.ubo);
    auto tex = vkt.newTexture2D(VK_FORMAT_R32G32B32A32_SFLOAT,
                                {tri.wid, tri.hei},
                                Texture2D::UsageBits::Sampled | Texture2D::UsageBits::TransferDst);
    auto spl = SamplerState{}.setLinear().into(api).unwrap();
    auto desc_info = DescriptorInfo{};
    desc_info.addBuf().bind(ubo_buf);
    desc_info.addImg().bind(tex).bind(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL).bind(spl);

    // Create pipeline
    auto& desc_setlayout = rctx->requestDescriptorSetLayout(0, shaders).unwrap().get();
    auto& desc_set = rfrm.requestDescriptorSet(desc_setlayout, desc_info).unwrap().get();
    auto& pipeline_layout = rctx->requestPipelineLayout(shaders).unwrap().get();
    auto& pipeline = rctx->requestGraphicsPipeline(
                             GraphicsPipelineState()
                                 .addVertShader(rctx->requestShaderModule(shader_vert).unwrap().get(),
                                                "main",
                                                shader_vert.getSpecialization())
                                 .addFragShader(rctx->requestShaderModule(shader_frag).unwrap().get(),
                                                "main",
                                                shader_frag.getSpecialization())
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
                                     .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                       VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT})
                                 .setPipelineLayout(pipeline_layout)
                                 .chainRendering({VK_FORMAT_R32G32B32A32_SFLOAT}, VK_FORMAT_D32_SFLOAT))
                         .unwrap()
                         .get();
    tstOut("Graphics pipeline: {}", fmt::ptr((VkPipeline)pipeline));

    // Create vertex and index buffer
    auto staging = vkt.newStagingBuffer(tri.num * sizeof(float));
    auto vertex_buf = vkt.newVertexBuffer(sizeof(tri.vertices));
    auto index_buf = vkt.newIndexBuffer(sizeof(tri.indices));
    staging.copyFrom(tri.vertices, sizeof(tri.vertices));
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(staging, vertex_buf, 0, 0, sizeof(tri.vertices));
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();
    staging.copyFrom(tri.indices, sizeof(tri.indices));
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(staging, index_buf, 0, 0, sizeof(tri.indices));
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Create render targets
    RenderTargetTable rtt{};
    rtt.addTarget(Texture2D::from(api,
                                  VK_FORMAT_R32G32B32A32_SFLOAT,
                                  VkExtent2D{tri.wid, tri.hei},
                                  Texture::UsageBits::Color | Texture::UsageBits::Transfer)
                      .unwrap())
        .unwrap()
        .get()
        .set(VkClearColorValue{});
    rtt.addTarget(api, VkExtent2D{tri.wid, tri.hei}, VK_FORMAT_D32_SFLOAT).unwrap();
    auto& out_color = rtt[0].unwrap().get().getImage();
    auto& out_depth = rtt[1].unwrap().get().getImage();

    // Record command
    staging.copyFrom(tri.tex.data());
    cmdbuf.begin();
    cmdbuf.cmdImageMemoryBarrier(Arg{tex.getImage()},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_ACCESS_NONE,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    cmdbuf.cmdCopyBufferToImage(staging, Arg{tex.getImage()});
    cmdbuf.cmdImageMemoryBarrier(Arg{tex.getImage()},
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                                 VK_ACCESS_TRANSFER_WRITE_BIT,
                                 VK_ACCESS_SHADER_READ_BIT,
                                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                 VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    cmdbuf.cmdImageMemoryBarrier(Arg{out_color},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 VK_ACCESS_NONE,
                                 VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    cmdbuf.cmdImageMemoryBarrier(Arg{out_depth},
                                 VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
                                 VK_ACCESS_NONE,
                                 VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
                                 VK_IMAGE_LAYOUT_UNDEFINED,
                                 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL);
    cmdbuf.cmdBeginRendering(rtt.getExtent(), rtt.getAttachmentInfos(), 1, 1)
        .cmdBindGraphicsPipeline(pipeline)
        .cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set})
        .cmdPushVertConstants(pipeline_layout, &tri.push_args.flipy, sizeof(int), 0)
        .cmdPushFragConstants(pipeline_layout, &tri.push_args.scaler, sizeof(int), 20)
        .cmdBindVertexBuffers({vertex_buf})
        .cmdBindIndexBuffer(index_buf, 0, VK_INDEX_TYPE_UINT32)
        .cmdDrawIndexed(3, 1, 0, 0, 0)
        .cmdEndRendering();
    cmdbuf.cmdImageMemoryBarrier(Arg{out_color},
                                 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                                 VK_ACCESS_TRANSFER_READ_BIT,
                                 VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    cmdbuf.cmdCopyImageToBuffer(Arg{out_color}, staging);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check staging buffer
    Vector<float> out(tri.num);
    staging.copyInto(out.data());
    tri.checkOutput(out);
}
