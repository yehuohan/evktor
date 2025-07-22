#pragma once
#include "__core.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ComputePipeline;

class ComputePipelineState : public CoreStater<ComputePipelineState> {
    friend struct ComputePipeline;
    friend struct std::hash<ComputePipelineState>;

private:
    VkPipelineCreateFlags flags = 0;
    Opt<ShaderModule> shader{};
    VkPipelineLayout layout = VK_NULL_HANDLE;

public:
    explicit ComputePipelineState(String&& name = "GraphicsPipeline") : CoreStater(std::move(name)) {}

    Self setFlags(VkPipelineCreateFlags flags);
    Self setShader(ShaderModule&& shader);
    Self setPipelineLayout(VkPipelineLayout layout);

    Res<ComputePipeline> into(const CoreApi& api) const;
};

struct ComputePipeline : public CoreResource<VkPipeline, VK_OBJECT_TYPE_PIPELINE> {
protected:
    explicit ComputePipeline(const CoreApi& api) : CoreResource(api) {}

public:
    ComputePipeline(ComputePipeline&&);
    ~ComputePipeline();

    static Res<ComputePipeline> from(const CoreApi& api, const ComputePipelineState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::ComputePipelineState> {
    size_t operator()(const vkt::core::ComputePipelineState& pso) const {
        size_t res = 0;
        if (pso.shader.has_value()) {
            hashCombine(res, pso.shader.value());
        }
        hashCombine(res, pso.layout);
        return res;
    }
};

NAMESPACE_END(std)
