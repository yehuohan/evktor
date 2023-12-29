#include "pipeline_compute.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ComputePipelineBuilder::Self;

ComputePipeline::ComputePipeline(ComputePipeline&& rhs)
    : BuiltResource(rhs.device, std::move(rhs.__name))
    , pipeline_layout(rhs.pipeline_layout) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

ComputePipeline::~ComputePipeline() {
    if (handle) {
        vkDestroyPipeline(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Self ComputePipelineBuilder::setFlags(VkPipelineCreateFlags flags) {
    info.flags = flags;
    return *this;
}

Self ComputePipelineBuilder::setShader(ShaderModule&& shader) {
    info.shader.emplace(std::move(shader));
    return *this;
}

ComputePipelineBuilder::Built ComputePipelineBuilder::build() {
    ComputePipeline pipeline(pipeline_layout, std::move(info.__name));
    auto pipeline_ci = Itor::ComputePipelineCreateInfo();
    pipeline_ci.flags = info.flags;
    pipeline_ci.stage = Itor::PipelineShaderStageCreateInfo();
    pipeline_ci.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    if (info.shader.has_value()) {
        const auto& s = info.shader.value();
        pipeline_ci.stage.module = s;
        pipeline_ci.stage.pName = s.entry.c_str();
    }
    pipeline_ci.layout = pipeline_layout;
    pipeline_ci.basePipelineHandle = VK_NULL_HANDLE;
    pipeline_ci.basePipelineIndex = -1;

    OnRet(vkCreateComputePipelines(pipeline_layout.device, VK_NULL_HANDLE, 1, &pipeline_ci, nullptr, pipeline),
          "Failed to create compute pipeline");
    OnName(pipeline);

    return Ok(std::move(pipeline));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
