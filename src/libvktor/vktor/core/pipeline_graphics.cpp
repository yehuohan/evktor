#include "pipeline_graphics.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = GraphicsPipelineState::Self;

GraphicsPipelineState::GraphicsPipelineState(Name&& name) : CoreStater(std::move(name)) {
    input_assembly = Itor::PipelineInputAssemblyStateCreateInfo();
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly.primitiveRestartEnable = VK_FALSE;
    tessellation = Itor::PipelineTessellationStateCreateInfo();
    rasterization = Itor::PipelineRasterizationStateCreateInfo();
    rasterization.depthClampEnable = VK_FALSE;
    rasterization.rasterizerDiscardEnable = VK_FALSE;
    rasterization.polygonMode = VK_POLYGON_MODE_FILL;
    rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterization.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterization.depthBiasEnable = VK_FALSE;
    rasterization.lineWidth = 1.0f;
    multisample = Itor::PipelineMultisampleStateCreateInfo();
    multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisample.sampleShadingEnable = VK_FALSE;
    multisample.minSampleShading = 1.0f;
    multisample.pSampleMask = nullptr;
    multisample.alphaToCoverageEnable = VK_FALSE;
    multisample.alphaToOneEnable = VK_FALSE;
    depth_stencil = Itor::PipelineDepthStencilStateCreateInfo();
    depth_stencil.depthTestEnable = VK_FALSE;
    depth_stencil.depthWriteEnable = VK_FALSE;
    depth_stencil.depthBoundsTestEnable = VK_FALSE;
    depth_stencil.stencilTestEnable = VK_FALSE;
}

Self GraphicsPipelineState::setFlags(VkPipelineCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self GraphicsPipelineState::addShader(ShaderModule&& shader) {
    shaders.push_back(std::move(shader));
    return *this;
}

Self GraphicsPipelineState::addVertexInputBinding(const VkVertexInputBindingDescription& binding) {
    vertex_input.bindings.push_back(binding);
    return *this;
}

Self GraphicsPipelineState::addVertexInputBindings(const Vector<VkVertexInputBindingDescription>& bindings) {
    vertex_input.bindings.insert(vertex_input.bindings.end(), bindings.begin(), bindings.end());
    return *this;
}

Self GraphicsPipelineState::addVertexInputAttribute(const VkVertexInputAttributeDescription& attribute) {
    vertex_input.attributes.push_back(attribute);
    return *this;
}

Self GraphicsPipelineState::addVertexInputAttributes(const Vector<VkVertexInputAttributeDescription>& attributes) {
    vertex_input.attributes.insert(vertex_input.attributes.end(), attributes.begin(), attributes.end());
    return *this;
}

Self GraphicsPipelineState::setInputAssembly(VkPrimitiveTopology topology, VkBool32 enable_primitive_restart) {
    input_assembly.topology = topology;
    input_assembly.primitiveRestartEnable = enable_primitive_restart;
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

Self GraphicsPipelineState::setRasterizationDepthClamp(VkBool32 enable_depth_clamp) {
    rasterization.depthClampEnable = enable_depth_clamp;
    return *this;
}

Self GraphicsPipelineState::setRasterizationDiscard(VkBool32 enable_rasterizer_discard) {
    rasterization.rasterizerDiscardEnable = enable_rasterizer_discard;
    return *this;
}

Self GraphicsPipelineState::setRasterizationPolygonMode(VkPolygonMode polygon_mode) {
    rasterization.polygonMode = polygon_mode;
    return *this;
}

Self GraphicsPipelineState::setRasterizationCullFace(VkCullModeFlags cull_mode, VkFrontFace front_face) {
    rasterization.cullMode = cull_mode;
    rasterization.frontFace = front_face;
    return *this;
}

Self GraphicsPipelineState::setRasterizationDepthBias(VkBool32 enable, float constant, float clamp, float slope) {
    rasterization.depthBiasEnable = enable;
    rasterization.depthBiasConstantFactor = constant;
    rasterization.depthBiasClamp = clamp;
    rasterization.depthBiasSlopeFactor = clamp;
    return *this;
}

Self GraphicsPipelineState::setRasterizationLineWith(float line_width) {
    rasterization.lineWidth = line_width;
    return *this;
}

Self GraphicsPipelineState::setMultisampleCount(VkSampleCountFlagBits sample_count) {
    multisample.rasterizationSamples = sample_count;
    return *this;
}

Self GraphicsPipelineState::setMultisampleShading(VkBool32 enable, float min_sample_shading) {
    multisample.sampleShadingEnable = enable;
    multisample.minSampleShading = min_sample_shading;
    return *this;
}

Self GraphicsPipelineState::setDepthTest(VkBool32 enable_test, VkBool32 enable_write, VkCompareOp op) {
    depth_stencil.depthTestEnable = enable_test;
    depth_stencil.depthWriteEnable = enable_write;
    depth_stencil.depthCompareOp = op;
    return *this;
}

Self GraphicsPipelineState::setDepthBoundsTest(VkBool32 enable, float min_depth, float max_depth) {
    depth_stencil.depthBoundsTestEnable = enable;
    depth_stencil.minDepthBounds = min_depth;
    depth_stencil.maxDepthBounds = max_depth;
    return *this;
}

Self GraphicsPipelineState::setStencilTest(VkBool32 enable, const VkStencilOpState& front, const VkStencilOpState& back) {
    depth_stencil.stencilTestEnable = enable;
    depth_stencil.front = front;
    depth_stencil.back = back;
    return *this;
}

Self GraphicsPipelineState::setColorBlendLogicOp(VkBool32 enable, VkLogicOp op) {
    color_blend.enable_logic_op = enable;
    color_blend.logic_op = op;
    return *this;
}

Self GraphicsPipelineState::addColorBlendAttachment(const VkPipelineColorBlendAttachmentState& attachment) {
    color_blend.attachments.push_back(attachment);
    return *this;
}

Self GraphicsPipelineState::addColorBlendAttachments(const Vector<VkPipelineColorBlendAttachmentState>& attachments) {
    color_blend.attachments.insert(color_blend.attachments.begin(), attachments.begin(), attachments.end());
    return *this;
}

Self GraphicsPipelineState::setColorBlendConstants(float c0, float c1, float c2, float c3) {
    color_blend.constants[0] = c0;
    color_blend.constants[1] = c1;
    color_blend.constants[2] = c2;
    color_blend.constants[3] = c3;
    return *this;
}

Self GraphicsPipelineState::addDynamic(VkDynamicState dynamic) {
    dynamics.push_back(dynamic);
    return *this;
}

Self GraphicsPipelineState::addDynamics(const Vector<VkDynamicState>& _dynamics) {
    dynamics.insert(dynamics.end(), _dynamics.begin(), _dynamics.end());
    return *this;
}

Self GraphicsPipelineState::setPipelineLayout(VkPipelineLayout _layout) {
    layout = _layout;
    return *this;
}

Self GraphicsPipelineState::setRenderPass(VkRenderPass _render_pass, uint32_t subpass_index) {
    render_pass = _render_pass;
    subpass = subpass_index;
    return *this;
}

Res<GraphicsPipeline> GraphicsPipelineState::into(const CoreApi& api) const {
    return GraphicsPipeline::from(api, *this);
}

GraphicsPipeline::GraphicsPipeline(GraphicsPipeline&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

GraphicsPipeline::~GraphicsPipeline() {
    if (!__borrowed && handle) {
        vkDestroyPipeline(api, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<GraphicsPipeline> GraphicsPipeline::from(const CoreApi& api, const GraphicsPipelineState& info) {
    // Shader stages
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
    vertex_input_sci.vertexBindingDescriptionCount = u32(info.vertex_input.bindings.size());
    vertex_input_sci.pVertexBindingDescriptions = info.vertex_input.bindings.data();
    vertex_input_sci.vertexAttributeDescriptionCount = u32(info.vertex_input.attributes.size());
    vertex_input_sci.pVertexAttributeDescriptions = info.vertex_input.attributes.data();

    // State: input assembly
    const auto& input_assembly_sci = info.input_assembly;

    // State: tessellation state
    const auto& tessellation_sci = info.tessellation;

    // State: viewport and scissor
    auto viewport_sci = Itor::PipelineViewportStateCreateInfo();
    viewport_sci.viewportCount = u32(info.viewports.size());
    viewport_sci.pViewports = info.viewports.data();
    viewport_sci.scissorCount = u32(info.scissors.size());
    viewport_sci.pScissors = info.scissors.data();

    // State: rasterization
    const auto& rasterization_sci = info.rasterization;

    // State: multisample
    const auto& multisample_sci = info.multisample;

    // State: depth stencil
    const auto& depth_stencil_sci = info.depth_stencil;

    // State: color blend
    auto color_blend_sci = Itor::PipelineColorBlendStateCreateInfo();
    color_blend_sci.logicOpEnable = info.color_blend.enable_logic_op;
    color_blend_sci.logicOp = info.color_blend.logic_op;
    color_blend_sci.attachmentCount = u32(info.color_blend.attachments.size());
    color_blend_sci.pAttachments = info.color_blend.attachments.data();
    color_blend_sci.blendConstants[0] = info.color_blend.constants[0];
    color_blend_sci.blendConstants[1] = info.color_blend.constants[1];
    color_blend_sci.blendConstants[2] = info.color_blend.constants[2];
    color_blend_sci.blendConstants[3] = info.color_blend.constants[3];

    // State: dynamic
    auto dynamic_sci = Itor::PipelineDynamicStateCreateInfo();
    dynamic_sci.dynamicStateCount = u32(info.dynamics.size());
    dynamic_sci.pDynamicStates = info.dynamics.data();

    // Create graphics pipeline
    GraphicsPipeline pipeline(api);
    auto pipeline_ci = Itor::GraphicsPipelineCreateInfo();
    pipeline_ci.flags = info.flags;
    pipeline_ci.stageCount = u32(shader_stages.size());
    pipeline_ci.pStages = shader_stages.data();
    pipeline_ci.pVertexInputState = &vertex_input_sci;
    pipeline_ci.pInputAssemblyState = &input_assembly_sci;
    pipeline_ci.pTessellationState = &tessellation_sci;
    pipeline_ci.pViewportState = &viewport_sci;
    pipeline_ci.pRasterizationState = &rasterization_sci;
    pipeline_ci.pMultisampleState = &multisample_sci;
    pipeline_ci.pDepthStencilState = &depth_stencil_sci;
    pipeline_ci.pColorBlendState = &color_blend_sci;
    pipeline_ci.pDynamicState = &dynamic_sci;
    pipeline_ci.layout = info.layout;
    pipeline_ci.renderPass = info.render_pass;
    pipeline_ci.subpass = info.subpass;
    pipeline_ci.basePipelineHandle = VK_NULL_HANDLE;
    pipeline_ci.basePipelineIndex = -1;

    OnRet(vkCreateGraphicsPipelines(api, VK_NULL_HANDLE, 1, &pipeline_ci, nullptr, pipeline),
          "Failed to create graphics pipeline");
    OnName(pipeline, info.__name);

    return Ok(std::move(pipeline));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
