#include "pipeline_compute.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ComputePipelineState::Self;

Self ComputePipelineState::setFlags(VkPipelineCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self ComputePipelineState::setShader(ShaderModule&& _shader) {
    shader.emplace(std::move(_shader));
    return *this;
}

Self ComputePipelineState::setPipelineLayout(VkPipelineLayout _layout) {
    layout = _layout;
    return *this;
}

Res<ComputePipeline> ComputePipelineState::into(const Device& device) const {
    return ComputePipeline::from(device, *this);
}

ComputePipeline::ComputePipeline(ComputePipeline&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

ComputePipeline::~ComputePipeline() {
    if (handle) {
        vkDestroyPipeline(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<ComputePipeline> ComputePipeline::from(const Device& device, const ComputePipelineState& info) {
    ComputePipeline pipeline(device);
    auto pipeline_ci = Itor::ComputePipelineCreateInfo();
    pipeline_ci.flags = info.flags;
    pipeline_ci.stage = Itor::PipelineShaderStageCreateInfo();
    pipeline_ci.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    if (info.shader.has_value()) {
        const auto& s = info.shader.value();
        pipeline_ci.stage.module = s;
        pipeline_ci.stage.pName = s.entry.c_str();
    }
    pipeline_ci.layout = info.layout;
    pipeline_ci.basePipelineHandle = VK_NULL_HANDLE;
    pipeline_ci.basePipelineIndex = -1;

    OnRet(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &pipeline_ci, nullptr, pipeline),
          "Failed to create compute pipeline");
    OnName(pipeline, info.__name);

    return Ok(std::move(pipeline));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
