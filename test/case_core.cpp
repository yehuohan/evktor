#include "__helpers.hpp"
#include <iostream>
#include <vktor.hpp>

using namespace vkt;
using namespace vkt::core;

Box<CoreApi> setupCoreApi() {
    CoreApiState aso{};

    // Create instance
    DebugState dso{};
    aso.init(InstanceState()
                 .setAppName("tst_core")
                 .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                 .setEngineName("vktor")
                 .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                 .setApiVerion(VK_API_VERSION_1_2)
                 .enableLayerValidation()
                 .enableExtensionDebugUtils(&dso)
                 .setVerbose(true))
        .unwrap();

    // Select physical device
    aso.init(PhysicalDeviceState()
                 .preferDiscreteGPU()
                 // .preferIntegratedGPU()
                 .requireGraphicsQueue()
                 .requireComputeQueue()
                 .setVerbose(true))
        .unwrap();

    // Create device
    aso.init(DeviceState().setMaxQueueCount(1).setVerbose(true)).unwrap();

    // Create core api
    Box<CoreApi> api = newBox<CoreApi>(aso.into().unwrap());

    vktOut("Instance: {}, Physical Device: {}, Device: {}",
           fmt::ptr((VkInstance)*api),
           fmt::ptr((VkPhysicalDevice)*api),
           fmt::ptr((VkDevice)*api));

    return std::move(api);
}

void setupComputePass(const CoreApi& api) {
    const std::string shader_file = "./glsl/test/quad.comp";
    const uint32_t wid = 32;
    const uint32_t hei = 18;
    const uint32_t cha = 4;
    static float buf[wid * hei * cha];

    auto& queue = api.computeQueue().unwrap().get();

    // Create shader module
    auto shader_source = ShaderSource::from(ShaderSource::Comp, read_shader(shader_file)).unwrap();
    auto shader = Shader::from(shader_source).unwrap().into(api).unwrap();

    // Create pipeline
    auto desc_set_layout = DescriptorSetLayoutState{}
                               .addCompBinding(0, VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .addCompBinding(1, VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                               .into(api)
                               .unwrap();
    auto pipeline_layout = PipelineLayoutState{}.addDescriptorSetLayout(desc_set_layout).into(api).unwrap();
    auto pipeline = ComputePipelineState{}.setShader(std::move(shader)).setPipelineLayout(pipeline_layout).into(api).unwrap();
    vktOut("Pipeline: {}", fmt::ptr((VkPipeline)pipeline));

    // Create descriptors
    auto desc_pool = DescriptorPoolState{}
                         .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                         .into(desc_set_layout)
                         .unwrap();
    auto desc_set = desc_pool.allocate().unwrap();
    auto inp_img = ImageState{}
                       .setFormat(VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(wid, hei)
                       .setUsage(VkImageUsageFlagBits::VK_IMAGE_USAGE_STORAGE_BIT |
                                 VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                                 VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto inp_imgview = ImageViewState{}.setFromImage(inp_img).into(api).unwrap();
    auto out_img = ImageState{}
                       .setFormat(VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT)
                       .setExtent(wid, hei)
                       .setUsage(VkImageUsageFlagBits::VK_IMAGE_USAGE_STORAGE_BIT |
                                 VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                                 VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
                       .into(api)
                       .unwrap();
    auto out_imgview = ImageViewState{}.setFromImage(out_img).into(api).unwrap();
    auto desc_info = DescriptorInfo{};
    desc_info.imgs[0] = VkDescriptorImageInfo{VK_NULL_HANDLE, inp_imgview, VK_IMAGE_LAYOUT_GENERAL};
    desc_info.imgs[1] = VkDescriptorImageInfo{VK_NULL_HANDLE, out_imgview, VK_IMAGE_LAYOUT_GENERAL};
    desc_set.update(desc_info);

    // Create stage buffer
    auto stage = BufferState{}
                     .setSize(wid * hei * cha * sizeof(float))
                     .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                     .setMemoryFlags(VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                     .into(api)
                     .unwrap();
    for (int k = 0; k < 10; k++) {
        buf[k] = (k + 1) * 10;
    }
    stage.copyFrom(buf);

    // Create command buffer
    auto cmdpool = CommandPoolState{}.setQueueFamilyIndex(queue.family_index).into(api).unwrap();
    auto& cmdbuf = cmdpool.allocate(CommandPool::Level::Primary).unwrap().get();
    vktOut("Comamnd buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Record command
    auto inp_barrier = Itor::ImageMemoryBarrier();
    auto out_barrier = Itor::ImageMemoryBarrier();
    inp_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    inp_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    inp_barrier.image = inp_img;
    inp_barrier.subresourceRange = Arg{inp_img};
    out_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    out_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    out_barrier.image = out_img;
    out_barrier.subresourceRange = Arg{out_img};
    cmdbuf.begin();
    inp_barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    inp_barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    cmdbuf.cmdImageMemoryBarrier(VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 {inp_barrier});
    cmdbuf.cmdCopyBufferToImage(stage, Arg{inp_img});
    inp_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    inp_barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    out_barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    out_barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    cmdbuf.cmdImageMemoryBarrier(VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                 {inp_barrier, out_barrier});
    cmdbuf.cmdBindPipeline(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_COMPUTE, pipeline)
        .cmdBindDescriptorSets(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_COMPUTE, pipeline_layout, 0, {desc_set})
        .cmdDispatch((wid + 7) / 8, (hei + 7) / 8, 1);
    out_barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
    out_barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    cmdbuf.cmdImageMemoryBarrier(VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 {out_barrier});
    cmdbuf.cmdCopyImageToBuffer(Arg{out_img}, stage);
    cmdbuf.end();

    // Submit command
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check stage buffer
    stage.copyInto(buf);
    vktOut("out_img: {}", vec2str(vkt::Vector<float>{buf, buf + 10}));
}

void case_core() {
    auto api = setupCoreApi();
    setupComputePass(*api);
}
