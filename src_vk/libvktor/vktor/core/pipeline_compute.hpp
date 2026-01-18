#pragma once
#include "__core.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ComputePipeline;

class ComputePipelineState : public CoreState<ComputePipelineState> {
    friend struct ComputePipeline;
    friend struct std::hash<ComputePipelineState>;

private:
    VkPipelineCreateFlags flags = 0;
    PipelineShader shader{};
    VkPipelineLayout layout = VK_NULL_HANDLE;

public:
    explicit ComputePipelineState(String&& name = "ComputePipeline") : CoreState(std::move(name)) {}

    Self setFlags(VkPipelineCreateFlags flags);
    Self setShader(VkShaderModule shader, const String& entry = "main", const ShaderSpecialization& spec = {nullptr, 0, {}});
    Self setSpecializationData(const void* data, size_t data_size);
    Self addSpecializationEntry(uint32_t id, uint32_t offset, size_t size);
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
        hashCombine(res, pso.shader.shader);
        hashCombine(res, pso.shader.entry);
        if (pso.shader.spec.data) {
            for (const auto& e : pso.shader.spec.entries) {
                hashCombine(res, e.constantID);
                for (uint32_t k = 0; k < e.size; k++) {
                    hashCombine(res, ((uint8_t*)pso.shader.spec.data)[e.offset + k]);
                }
            }
        }
        hashCombine(res, pso.layout);
        return res;
    }
};

NAMESPACE_END(std)
