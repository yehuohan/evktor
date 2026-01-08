#include "__helpers.hpp"

struct Conv2DParams {
    uint32_t IH = 1080;
    uint32_t IW = 1920;
    uint32_t IC = 3;
    uint32_t OH = 0;
    uint32_t OW = 0;
    uint32_t OC = 16;
    uint32_t KH = 3;
    uint32_t KW = 3;
    uint32_t stride_H = 2;
    uint32_t stride_W = 2;
    uint32_t padding_H = 1;
    uint32_t padding_W = 1;
    uint32_t dilation_H = 1;
    uint32_t dilation_W = 1;
    uint32_t activation = 1;

    Conv2DParams() {
        OH = (IH + 2 * padding_H - dilation_H * (KH - 1) - 1) / stride_H + 1;
        OW = (IW + 2 * padding_W - dilation_W * (KW - 1) - 1) / stride_W + 1;
    }
};

struct Conv2DTiles {
    uint32_t TILE_W = 8;
    uint32_t TILE_H = 8;
    uint32_t TILE_M = 64; // TILE_M == TILE_W * TILE_H
    uint32_t TILE_N = 64;
    uint32_t TILE_K = 16;
};

void case_rctx_cooperative_matrix() {
    // Create RenderContext
    Vktor vkt;
    CoreApi& api = vkt.createApi(nullptr, nullptr, nullptr, [](const PhysicalDevice& phydev, DeviceState& dso) {
        static auto cm_feats = Itor::PhysicalDeviceCooperativeMatrixFeaturesKHR();
        cm_feats.cooperativeMatrix = VK_TRUE;
        dso.setNext(&cm_feats)
            .tryAddExtension(VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME)
            .setFeatures<VkPhysicalDeviceVulkan12Features>([](VkPhysicalDeviceVulkan12Features& feats) {
                feats.shaderFloat16 = VK_TRUE;
                feats.vulkanMemoryModel = VK_TRUE;
                feats.vulkanMemoryModelDeviceScope = VK_TRUE;
            });
    });
    auto rctx = vkt.newRctx(1);
    auto& rfrm = rctx->getFrame().get();

    // Initialize params and tiles
    Conv2DParams params{};
    Conv2DTiles tiles{};
    uint32_t sub_group_size;
    bool use_coopmat = true;
    if (use_coopmat) {
        Vector<VkCooperativeMatrixPropertiesKHR> cm_props;
        enumerate(cm_props,
                  Itor::CooperativeMatrixPropertiesKHR(),
                  vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR,
                  (VkPhysicalDevice)api);
        for (size_t k = 0; k < cm_props.size(); k++) {
            const auto& prop = cm_props[k];
            String str = vktFmt("Cooperative Matrix Prop {} {{\n"
                                "\tM, N, K: {}, {}, {}\n"
                                "\tA, B, C, Result: {}, {}, {}, {}\n"
                                "\tsaturatingAccumulation: {}\n"
                                "\tScope: {}\n"
                                "}}",
                                k,
                                prop.MSize,
                                prop.NSize,
                                prop.KSize,
                                VkStr(VkComponentTypeKHR, prop.AType),
                                VkStr(VkComponentTypeKHR, prop.BType),
                                VkStr(VkComponentTypeKHR, prop.CType),
                                VkStr(VkComponentTypeKHR, prop.ResultType),
                                prop.saturatingAccumulation,
                                VkStr(VkScopeKHR, prop.scope));
            tstOut("{}", str);
            if (prop.AType == VK_COMPONENT_TYPE_FLOAT16_KHR && prop.BType == VK_COMPONENT_TYPE_FLOAT16_KHR &&
                prop.CType == VK_COMPONENT_TYPE_FLOAT16_KHR && prop.ResultType == VK_COMPONENT_TYPE_FLOAT16_KHR) {
                tiles.TILE_M = prop.MSize;
                tiles.TILE_N = prop.NSize;
                tiles.TILE_K = prop.KSize;
                uint32_t a = sqrt(prop.MSize);
                assert(a * a == prop.MSize);
                tiles.TILE_W = a;
                tiles.TILE_H = a;
                break;
            }
        }

        NextState<VkPhysicalDeviceProperties2, VkPhysicalDeviceSubgroupProperties> sg_props{
            Itor::PhysicalDeviceProperties2(),
            Itor::PhysicalDeviceSubgroupProperties()};
        vkGetPhysicalDeviceProperties2(api, sg_props.into());
        tstOut("subgroupSize: {}", sg_props.get<1>().subgroupSize);
        tstOut("supportedStages: {}", VkStr(VkShaderStageFlags, sg_props.get<1>().supportedStages));
        sub_group_size = sg_props.get<1>().subgroupSize;
    }

    // Create command buffer
    auto& queue = api.graphicsQueue().unwrap().get();
    auto& cmdbuf = rctx->beginFrame().unwrap().get();
    tstOut("Command buffer: {}", fmt::ptr((VkCommandBuffer)cmdbuf));

    // Create shader module
    const String comp_file = vktdev::Assets::shader("test/conv2d.comp");
    auto shader_comp = Shader::fromComp(vktdev::Assets::loadShader(comp_file), comp_file);
    if (use_coopmat) {
        shader_comp.setDefine("USE_NHWC")
            .setDefine("USE_COOPMAT")
            .setDefine("SUB_GROUP_SIZE", std::to_string(sub_group_size))
            .setDefine("DType", "float16_t");
    }
    shader_comp.addDescriptor(ShaderDescriptor::Type::BufferStorage, 0)
        .addDescriptor(ShaderDescriptor::Type::BufferStorage, 1)
        .addDescriptor(ShaderDescriptor::Type::BufferStorage, 2)
        .addDescriptor(ShaderDescriptor::Type::BufferStorage, 3)
        .setPushConstant(sizeof(Conv2DParams))
        .addSpecConstant(0, (const uint8_t*)&tiles.TILE_W, sizeof(uint32_t))
        .addSpecConstant(1, (const uint8_t*)&tiles.TILE_H, sizeof(uint32_t))
        .addSpecConstant(2, (const uint8_t*)&tiles.TILE_M, sizeof(uint32_t))
        .addSpecConstant(3, (const uint8_t*)&tiles.TILE_N, sizeof(uint32_t))
        .addSpecConstant(4, (const uint8_t*)&tiles.TILE_K, sizeof(uint32_t));
    auto shaders = Vector<CRef<Shader>>{newCRef(shader_comp)};

    // Create descriptors
    auto yout = vkt.newStorageBuffer(params.OH * params.OW * params.OC * sizeof(float));
    auto xinp = vkt.newStorageBuffer(params.IH * params.IW * params.IC * sizeof(float));
    auto kern = vkt.newStorageBuffer(params.KH * params.KW * params.IC * params.OC * sizeof(float));
    auto bias = vkt.newStorageBuffer(params.OC * sizeof(float));
    auto desc_info = DescriptorInfo{};
    desc_info.nextBuf(yout, yout.size);
    desc_info.nextBuf(xinp, xinp.size);
    desc_info.nextBuf(kern, kern.size);
    desc_info.nextBuf(bias, bias.size);

    // Create pipeline
    auto& desc_setlayout = rctx->requestDescriptorSetLayout(0, shaders).unwrap().get();
    auto& desc_set = rfrm.requestDescriptorSet(desc_setlayout, desc_info).unwrap().get();
    auto& pipeline_layout = rctx->requestPipelineLayout(shaders).unwrap().get();
    auto& pipeline = rctx->requestComputePipeline(ComputePipelineState()
                                                      .setShader(rctx->requestShaderModule(shader_comp).unwrap().get(),
                                                                 "main",
                                                                 shader_comp.getSpecialization())
                                                      .setPipelineLayout(pipeline_layout))
                         .unwrap()
                         .get();
    tstOut("Compute pipeline: {}", fmt::ptr((VkPipeline)pipeline));

    // Create stage buffer
    auto stage = vkt.newStageBuffer(std::max<VkDeviceSize>(yout.size, xinp.size));
    Vector<float> buf(stage.size / sizeof(float));
    for (size_t k = 0; k < buf.size(); k++) {
        buf[k] = float(k % 255) / 255.0;
    }
    stage.copyFrom(buf.data());
    cmdbuf.begin();
    cmdbuf.cmdCopyBuffer(stage, xinp);
    cmdbuf.cmdCopyBuffer(stage, kern);
    cmdbuf.cmdCopyBuffer(stage, bias);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Record command
    auto gcx = (params.OW + tiles.TILE_W - 1) / tiles.TILE_W;
    auto gcy = (params.OH + tiles.TILE_H - 1) / tiles.TILE_H;
    auto gcz = (params.OC + tiles.TILE_N - 1) / tiles.TILE_N;
    cmdbuf.begin();
    cmdbuf.cmdBindComputePipeline(pipeline)
        .cmdBindComputeDescriptorSets(pipeline_layout, 0, {desc_set})
        .cmdPushCompConstants(pipeline_layout, &params, sizeof(Conv2DParams))
        .cmdDispatch(gcx, gcy, gcz);
    cmdbuf.cmdCopyBuffer(yout, stage);
    cmdbuf.end();
    queue.submit(cmdbuf);
    queue.waitIdle();

    // Check stage buffer
    Vector<float> out(yout.size / sizeof(float));
    stage.copyInto(out.data(), yout.size);
    Vector<float> disp{};
    for (size_t k = 0; k < out.size(); k += out.size() / 11) {
        disp.push_back(out[k]);
    }
    tstOut("yout: {}", vec2str(disp));
}
