#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "pipeline_layout.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ComputePipeline : public BuiltResource<VkPipeline, VK_OBJECT_TYPE_PIPELINE, Device> {
    const PipelineLayout& pipeline_layout;

    ComputePipeline(const PipelineLayout& layout, Name&& name)
        : BuiltResource(layout.device, std::move(name))
        , pipeline_layout(layout) {}
    ComputePipeline(ComputePipeline&&);
    ~ComputePipeline();
    OnConstType(VkPipelineLayout, pipeline_layout.handle);
};

struct ComputePipelineInfo : public BuilderInfo {
    VkPipelineCreateFlags flags = 0;
    Opt<ShaderModule> shader{};
};

class ComputePipelineBuilder : public Builder<ComputePipelineBuilder, ComputePipeline, ComputePipelineInfo> {
private:
    const PipelineLayout& pipeline_layout;

public:
    explicit ComputePipelineBuilder(const PipelineLayout& layout, Name&& name = "GraphicsPipeline")
        : Builder(std::move(name))
        , pipeline_layout(layout) {}
    virtual Built build() override;

    Self setFlags(VkPipelineCreateFlags flags);
    Self setShader(ShaderModule&& shader);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
