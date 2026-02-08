#include "__helpers.hpp"
// #include "quad.slang.h"

void case_core_compute() {
    auto boxapi = createCoreApi();
    auto& api = *boxapi;
    const Quad quad{};

    // Create command buffer
    auto& queue = api.computeQueue().unwrap().get();
    auto cmdpool = CommandPoolState{}.setQueueFamilyIndex(queue.family_index).into(api).unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();
    tstOut("Command buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    auto shader_comp = Shader::fromComp(vktdev::Assets::loadShader(quad.comp_file), quad.comp_file).into(api).unwrap();
    // auto shader  = ShaderModuleState().setCode(quad_slang, quad_slang_size).into(api).unwrap();

    // Create pipeline
    auto desc_set_layout = DescriptorSetLayoutState{}
                               .addCompBinding(0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .addCompBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .into(api)
                               .unwrap();
    auto pipeline_layout = PipelineLayoutState{}
                               .addDescriptorSetLayout(desc_set_layout)
                               .addCompPushConstantRange(sizeof(Quad::PushArgs))
                               .into(api)
                               .unwrap();
    auto pipeline = ComputePipelineState{}
                        .setShader(shader_comp)
                        .setSpecializationData(&quad.spec_args, sizeof(Quad::SpecArgs))
                        .addSpecializationEntry(0, offsetof(Quad::SpecArgs, alpha), sizeof(int))
                        .setPipelineLayout(pipeline_layout)
                        .into(api)
                        .unwrap();
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
    desc_info.addImg().bind(inp_imgview).bind(VK_IMAGE_LAYOUT_GENERAL);
    desc_info.addImg().bind(out_imgview).bind(VK_IMAGE_LAYOUT_GENERAL);
    desc_set.update(desc_info);

    // Create staging buffer
    auto staging = BufferState{}
                       .setSize(quad.num * sizeof(float))
                       .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                       .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                       .into(api)
                       .unwrap();
    staging.copyFrom(quad.img.data());

    // Record command
    cmdbuf.begin();

    auto barrier = cmdbuf.cmdPipelineBarrier();
    barrier.from(VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_ACCESS_NONE, VK_IMAGE_LAYOUT_UNDEFINED)
        .into(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_WRITE_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        .img(Arg{inp_img});
    cmdbuf.cmdCopyBufferToImage(staging, Arg{inp_img});
    barrier.next(VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_ACCESS_SHADER_READ_BIT, VK_IMAGE_LAYOUT_GENERAL).img(Arg{inp_img});

    barrier.from(VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_ACCESS_NONE, VK_IMAGE_LAYOUT_UNDEFINED)
        .into(VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_ACCESS_SHADER_WRITE_BIT, VK_IMAGE_LAYOUT_GENERAL)
        .img(Arg{out_img});
    cmdbuf.cmdBindComputePipeline(pipeline)
        .cmdBindComputeDescriptorSets(pipeline_layout, 0, {desc_set})
        .cmdPushCompConstants(pipeline_layout, &quad.push_args, sizeof(Quad::PushArgs))
        .cmdDispatch(quad.group_count_x, quad.group_count_y, quad.group_count_z);
    barrier.next(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_READ_BIT, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
        .img(Arg{out_img});
    cmdbuf.cmdCopyImageToBuffer(Arg{out_img}, staging);

    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check staging buffer
    Vector<float> out(quad.num);
    staging.copyInto(out.data());
    quad.checkOutput(out);
}
