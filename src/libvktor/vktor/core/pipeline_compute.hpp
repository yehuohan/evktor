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
    String shader_entry = "main";
    VkShaderModule shader = VK_NULL_HANDLE;
    VkPipelineLayout layout = VK_NULL_HANDLE;

public:
    explicit ComputePipelineState(String&& name = "ComputePipeline") : CoreStater(std::move(name)) {}

    Self setFlags(VkPipelineCreateFlags flags);
    Self setShader(VkShaderModule shader, const char* entry = "main");
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
        hashCombine(res, pso.flags);
        hashCombine(res, pso.shader);
        hashCombine(res, pso.shader_entry);
        hashCombine(res, pso.layout);
        return res;
    }
};

NAMESPACE_END(std)
