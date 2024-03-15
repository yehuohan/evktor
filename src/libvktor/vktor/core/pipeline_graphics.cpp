#include "pipeline_graphics.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = GraphicsPipelineState::Self;

Self GraphicsPipelineState::setFlags(VkPipelineCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self GraphicsPipelineState::addShader(ShaderModule&& shader) {
    shaders.push_back(std::move(shader));
    return *this;
}

Self GraphicsPipelineState::addVertexInputBinding(const VkVertexInputBindingDescription& binding) {
    vert_input_bindings.push_back(binding);
    return *this;
}

Self GraphicsPipelineState::addVertexInputBindings(const Vector<VkVertexInputBindingDescription>& bindings) {
    vert_input_bindings.insert(vert_input_bindings.end(), bindings.begin(), bindings.end());
    return *this;
}

Self GraphicsPipelineState::addVertexInputAttribute(const VkVertexInputAttributeDescription& attribute) {
    vert_input_attributes.push_back(attribute);
    return *this;
}

Self GraphicsPipelineState::addVertexInputAttributes(const Vector<VkVertexInputAttributeDescription>& attributes) {
    vert_input_attributes.insert(vert_input_attributes.end(), attributes.begin(), attributes.end());
    return *this;
}

Self GraphicsPipelineState::addViewport(const VkViewport& viewport) {
    viewports.push_back(viewport);
    return *this;
}

Self GraphicsPipelineState::addViewport(float x, float y, float width, float height, float min_depth, float max_depth) {
    viewports.push_back(VkViewport{x, y, width, height, min_depth, max_depth});
    return *this;
}

Self GraphicsPipelineState::addScissor(const VkRect2D& rect) {
    scissors.push_back(rect);
    return *this;
}

Self GraphicsPipelineState::addScissor(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    scissors.push_back(VkRect2D{x, y, width, height});
    return *this;
}

Self GraphicsPipelineState::setRenderPass(VkRenderPass _render_pass, uint32_t subpass_index) {
    render_pass = _render_pass;
    subpass = subpass_index;
    return *this;
}

Self GraphicsPipelineState::setPipelineLayout(VkPipelineLayout _layout) {
    layout = _layout;
    return *this;
}

Res<GraphicsPipeline> GraphicsPipelineState::into(const Device& device) const {
    return GraphicsPipeline::from(device, *this);
}

GraphicsPipeline::GraphicsPipeline(GraphicsPipeline&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

GraphicsPipeline::~GraphicsPipeline() {
    if (handle) {
        vkDestroyPipeline(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<GraphicsPipeline> GraphicsPipeline::from(const Device& device, const GraphicsPipelineState& info) {
    // Setup shader stages
    Vector<VkPipelineShaderStageCreateInfo> shader_stages{};
    for (auto& s : info.shaders) {
        auto stage = Itor::PipelineShaderStageCreateInfo();
        stage.stage = s.stage;
        stage.module = s;
        stage.pName = s.entry.c_str();
        shader_stages.push_back(stage);
    }

    // State: vertex input
    auto vertex_input_sci = Itor::PipelineVertexInputStateCreateInfo();
    vertex_input_sci.vertexBindingDescriptionCount = u32(info.vert_input_bindings.size());
    vertex_input_sci.pVertexBindingDescriptions = info.vert_input_bindings.data();
    vertex_input_sci.vertexAttributeDescriptionCount = u32(info.vert_input_attributes.size());
    vertex_input_sci.pVertexAttributeDescriptions = info.vert_input_attributes.data();

    // State: input assembly
    auto input_assembly_sci = Itor::PipelineInputAssemblyStateCreateInfo();
    input_assembly_sci.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly_sci.primitiveRestartEnable = VK_FALSE;

    // State: tessellation state
    auto tessellation_sci = Itor::PipelineTessellationStateCreateInfo();

    // State: viewport and scissor
    auto viewport_sci = Itor::PipelineViewportStateCreateInfo();
    viewport_sci.viewportCount = u32(info.viewports.size());
    viewport_sci.pViewports = info.viewports.data();
    viewport_sci.scissorCount = u32(info.scissors.size());
    viewport_sci.pScissors = info.scissors.data();

    // State: rasterization
    auto rasterization_sci = Itor::PipelineRasterizationStateCreateInfo();
    // Specify if clamp fragments that are beyond the near and far planes to the planes
    rasterization_sci.depthClampEnable = VK_FALSE;
    rasterization_sci.rasterizerDiscardEnable = VK_FALSE;
    // Specify how fragments are generated for geometry
    rasterization_sci.polygonMode = VK_POLYGON_MODE_FILL;
    rasterization_sci.cullMode = VK_CULL_MODE_NONE; // VK_CULL_MODE_BACK_BIT,
    rasterization_sci.frontFace = VK_FRONT_FACE_CLOCKWISE;
    // Specify how to alter(修正，映射) depth values
    rasterization_sci.depthBiasEnable = VK_FALSE;
    rasterization_sci.depthBiasConstantFactor = 0.0f;
    rasterization_sci.depthBiasClamp = 0.0f;
    rasterization_sci.depthBiasSlopeFactor = 0.0f;
    rasterization_sci.lineWidth = 1.0f;

    // State: multisample
    auto multisample_sci = Itor::PipelineMultisampleStateCreateInfo();
    multisample_sci.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisample_sci.sampleShadingEnable = VK_FALSE;
    multisample_sci.minSampleShading = 1.0f;
    multisample_sci.pSampleMask = nullptr;
    multisample_sci.alphaToCoverageEnable = VK_FALSE;
    multisample_sci.alphaToOneEnable = VK_FALSE;

    // State: depth stencil
    auto depth_stencil_sci = Itor::PipelineDepthStencilStateCreateInfo();

    // State: color blend
    VkPipelineColorBlendAttachmentState color_blend_attm{};
    color_blend_attm.blendEnable = VK_FALSE;
    color_blend_attm.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    color_blend_attm.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_blend_attm.colorBlendOp = VK_BLEND_OP_ADD;
    color_blend_attm.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    color_blend_attm.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_blend_attm.alphaBlendOp = VK_BLEND_OP_ADD;
    color_blend_attm.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                                      VK_COLOR_COMPONENT_A_BIT;
    auto color_blend_sci = Itor::PipelineColorBlendStateCreateInfo();
    color_blend_sci.logicOpEnable = VK_FALSE;
    color_blend_sci.logicOp = VK_LOGIC_OP_COPY;
    color_blend_sci.attachmentCount = 1;
    color_blend_sci.pAttachments = &color_blend_attm;
    color_blend_sci.blendConstants[0] = 0.0f;
    color_blend_sci.blendConstants[1] = 0.0f;
    color_blend_sci.blendConstants[2] = 0.0f;
    color_blend_sci.blendConstants[3] = 0.0f;

    // State: dynamic
    Vector<VkDynamicState> dynamics{VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    auto dynamic_sci = Itor::PipelineDynamicStateCreateInfo();
    dynamic_sci.dynamicStateCount = u32(dynamics.size());
    dynamic_sci.pDynamicStates = dynamics.data();

    // Create graphics pipeline
    GraphicsPipeline pipeline(device);
    auto pipeline_ci = Itor::GraphicsPipelineCreateInfo();
    pipeline_ci.flags = info.flags;
    pipeline_ci.stageCount = u32(shader_stages.size());
    pipeline_ci.pStages = shader_stages.data();
    pipeline_ci.pVertexInputState = &vertex_input_sci;
    pipeline_ci.pInputAssemblyState = &input_assembly_sci;
    pipeline_ci.pTessellationState = nullptr; //&tessellation_sci;
    pipeline_ci.pViewportState = &viewport_sci;
    pipeline_ci.pRasterizationState = &rasterization_sci;
    pipeline_ci.pMultisampleState = &multisample_sci;
    pipeline_ci.pDepthStencilState = nullptr; //&depth_stencil_sci;
    pipeline_ci.pColorBlendState = &color_blend_sci;
    pipeline_ci.pDynamicState = nullptr; //&dynamic_sci;
    pipeline_ci.layout = info.layout;
    pipeline_ci.renderPass = info.render_pass;
    pipeline_ci.subpass = info.subpass;
    pipeline_ci.basePipelineHandle = VK_NULL_HANDLE;
    pipeline_ci.basePipelineIndex = -1;

    OnRet(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipeline_ci, nullptr, pipeline),
          "Failed to create graphics pipeline");
    OnName(pipeline, info.__name);

    return Ok(std::move(pipeline));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
