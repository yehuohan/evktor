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

Res<ComputePipeline> ComputePipelineState::into(const CoreApi& api) const {
    return ComputePipeline::from(api, *this);
}

ComputePipeline::ComputePipeline(ComputePipeline&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

ComputePipeline::~ComputePipeline() {
    if (!__borrowed && handle) {
        vkDestroyPipeline(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<ComputePipeline> ComputePipeline::from(const CoreApi& api, const ComputePipelineState& info) {
    ComputePipeline pipeline(api);
    auto pipeline_ci = Itor::ComputePipelineCreateInfo(info.__next);
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

    OnRet(vkCreateComputePipelines(api, VK_NULL_HANDLE, 1, &pipeline_ci, api, pipeline), "Failed to create compute pipeline");
    OnName(pipeline, info.__name);

    return Ok(std::move(pipeline));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
