#include "vktor.hpp"
#include <set>

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<Ref<Shader>> Vktor::requestShader(const ShaderSource& shader_source) {
    size_t key = hash(shader_source);
    return resource_cache.shaders.request(key, [this, &shader_source]() {
        return Shader::from(shader_source);
    });
}

Res<Ref<DescriptorSetLayout>> Vktor::requestDescriptorSetLayout(const uint32_t set, const Vector<Shader>& shaders) {
    size_t key = hash(set, shaders);
    return resource_cache.descriptor_setlayouts.request(key, [this, set, &shaders]() -> Res<DescriptorSetLayout> {
        DescriptorSetLayoutState dso{};
        for (const auto& s : shaders) {
            switch (s.getStage()) {
            case VK_SHADER_STAGE_VERTEX_BIT:
            case VK_SHADER_STAGE_FRAGMENT_BIT:
            case VK_SHADER_STAGE_COMPUTE_BIT:
                {
                    const auto& desc_sets = s.getDescriptorSets();
                    auto item = desc_sets.find(set);
                    if (item != desc_sets.end()) {
                        for (const auto& d : item->second) {
                            dso.addBinding(d.binding, static_cast<VkDescriptorType>(d.type), d.count, s.getStage());
                        }
                    }
                }
                break;
            default:
                return Er("Request with unsupported shader ({}) stage: {}",
                          s.getFilename(),
                          VkStr(VkShaderStageFlags, s.getStage()));
            }
        }
        return dso.into(api);
    });
}

Res<Ref<PipelineLayout>> Vktor::requestPipelineLayout(const Vector<Shader>& shaders) {
    size_t key = hash(shaders);
    return resource_cache.pipeline_layouts.request(key, [this, &shaders]() -> Res<PipelineLayout> {
        // Collect all set index
        std::set<uint32_t> sets{};
        for (const auto& s : shaders) {
            const auto& desc_sets = s.getDescriptorSets();
            for (const auto& item : desc_sets) {
                sets.insert(item.first);
            }
        }
        // Collect all descriptor sets
        PipelineLayoutState pso{};
        for (const auto& s : sets) {
            auto res = requestDescriptorSetLayout(s, shaders);
            OnErr(res);
            pso.addDescriptorSetLayout(res.unwrap().get());
        }
        return pso.into(api);
    });
}

Res<Ref<GraphicsPipeline>> Vktor::requestGraphicsPipeline(const GraphicsPipelineState& pso) {
    size_t key = hash(pso);
    return resource_cache.graphics_pipelines.request(key, [this, &pso]() {
        return pso.into(api);
    });
}

Res<Ref<ComputePipeline>> Vktor::requestComputePipeline(const ComputePipelineState& pso) {
    size_t key = hash(pso);
    return resource_cache.compute_pipelines.request(key, [this, &pso]() {
        return pso.into(api);
    });
}

Res<Ref<RenderPass>> Vktor::requestRenderPass(const RenderTargetTable& render_target_table,
                                              const RenderPipeline& render_pipeline) {
    size_t key = hash(render_target_table.getTargets(), render_pipeline.getSubpasses());
    return resource_cache.render_passes.request(key, [&render_target_table, &render_pipeline]() {
        return render_pipeline.createRenderPass(render_target_table);
    });
}

Res<Ref<Framebuffer>> Vktor::requestFramebuffer(const RenderTargetTable& render_target_table, const RenderPass& render_pass) {
    size_t key = hash(render_target_table, render_pass);
    return resource_cache.framebuffers.request(key, [this, &render_target_table, &render_pass]() {
        FramebufferState fso{};
        fso.setRenderPass(render_pass);
        fso.addAttachments(render_target_table.getImageViews());
        fso.setExtent(render_target_table.getExtent());
        return fso.into(api);
    });
}

NAMESPACE_END(vkt)
