#include "pipeline_compute.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ComputePipelineState::Self;

Self ComputePipelineState::setFlags(VkPipelineCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self ComputePipelineState::setShader(VkShaderModule _shader, const char* entry) {
    shader = _shader;
    shader_entry = String(entry);
    return *this;
}

Self ComputePipelineState::setSpecializationData(const void* data, size_t data_size) {
    spec_data = data;
    spec_data_size = data_size;
    return *this;
}

Self ComputePipelineState::addSpecializationEntry(uint32_t id, uint32_t offset, size_t size) {
    spec_entries.push_back(VkSpecializationMapEntry{id, offset, size});
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
    VkSpecializationInfo spec_info{u32(info.spec_entries.size()),
                                   info.spec_entries.data(),
                                   info.spec_data_size,
                                   info.spec_data};
    pipeline_ci.flags = info.flags;
    pipeline_ci.stage = Itor::PipelineShaderStageCreateInfo();
    pipeline_ci.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    pipeline_ci.stage.module = info.shader;
    pipeline_ci.stage.pName = info.shader_entry.c_str();
    if (info.spec_data && !info.spec_entries.empty()) {
        pipeline_ci.stage.pSpecializationInfo = &spec_info;
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
