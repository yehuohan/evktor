#pragma once
#include "__core.hpp"
#include "device.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ComputePipeline;

class ComputePipelineState : public CoreStater<ComputePipelineState> {
    friend struct ComputePipeline;

private:
    VkPipelineCreateFlags flags = 0;
    Opt<ShaderModule> shader{};
    VkPipelineLayout layout = VK_NULL_HANDLE;

public:
    explicit ComputePipelineState(Name&& name = "GraphicsPipeline") : CoreStater(std::move(name)) {}

    Self setFlags(VkPipelineCreateFlags flags);
    Self setShader(ShaderModule&& shader);
    Self setPipelineLayout(VkPipelineLayout layout);

    Res<ComputePipeline> into(const Device& device) const;
};

struct ComputePipeline : public CoreResource<VkPipeline, VK_OBJECT_TYPE_PIPELINE, Device> {
    ComputePipeline(const Device& device) : CoreResource(device) {}
    ComputePipeline(ComputePipeline&&);
    ~ComputePipeline();

    static Res<ComputePipeline> from(const Device& device, const ComputePipelineState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::ComputePipelineState> {
    size_t operator()(const vkt::core::ComputePipelineState& pso) const {
        size_t res = 0;
        // TODO
        // vkt::hashCombine(res, )
        return res;
    }
};

NAMESPACE_END(std)
