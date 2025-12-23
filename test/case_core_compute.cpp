#include "__helpers.hpp"

void case_core_compute() {
    auto boxapi = createCoreApi();
    auto& api = *boxapi;
    const Quad quad{};

    // Create command buffer
    auto& queue = api.computeQueue().unwrap().get();
    auto cmdpool = CommandPoolState{}.setQueueFamilyIndex(queue.family_index).into(api).unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();
    tstOut("Comamnd buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    ShaderState shader_state;
    shader_state.setStage(VK_SHADER_STAGE_COMPUTE_BIT).setEntry("main");
    auto comp_source = ShaderSource(quad.comp_file, vktdev::Assets::loadShader(quad.comp_file));
    auto shader = Shader::from(comp_source, shader_state).unwrap().into(api).unwrap();

    // Create pipeline
    auto desc_set_layout = DescriptorSetLayoutState{}
                               .addCompBinding(0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .addCompBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .into(api)
                               .unwrap();
    auto pipeline_layout = PipelineLayoutState{}.addDescriptorSetLayout(desc_set_layout).into(api).unwrap();
    auto pipeline = ComputePipelineState{}.setShader(shader).setPipelineLayout(pipeline_layout).into(api).unwrap();
    tstOut("Compute pipeline: {}", fmt::ptr((VkPipeline)pipeline));

    // Create descriptors
    auto desc_pool = DescriptorPoolState{}
                         .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                         .into(desc_set_layout)
                         .unwrap();
    auto desc_set = desc_pool.allocate().unwrap();
    auto inp_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(quad.wid, quad.hei)
                       .setUsage(VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto inp_imgview = ImageViewState{}.setFromImage(inp_img).into(api).unwrap();
    auto out_img = ImageState{}
                       .setFormat(VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(quad.wid, quad.hei)
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
                     .setSize(quad.num * sizeof(float))
                     .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                     .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                     .into(api)
                     .unwrap();
    stage.copyFrom(quad.img.data());

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
        .cmdDispatch(quad.group_count_x, quad.group_count_y, quad.group_count_z);
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
    Vector<float> out(quad.num);
    stage.copyInto(out.data());
    quad.checkOutput(out);
}
