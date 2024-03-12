#include "vktor.hpp"
#include <set>

NAMESPACE_BEGIN(vkt)

using namespace core;

void Vktor::addRenderContext() {
    render_context = newBox<RenderContext>(api);
}

Res<Ref<ShaderModule>> Vktor::requestShaderModule(const Shader& shader) {
    size_t key = hash(shader);
    return resource_cache.shader_modules.request(key, [this, &shader]() {
        ShaderModuleBuilder builder(api);
        builder.setFilename(shader.getFilename());
        builder.setCode(std::string(shader.getCode()), shader.getStage());
        builder.setEntry("main");
        return builder();
    });
}

Res<Ref<DescriptorSetLayout>> Vktor::requestDescriptorSetLayout(const uint32_t set, const Vector<const Shader*>& shaders) {
    size_t key = hash(set, shaders);
    return resource_cache.descriptor_setlayouts.request(key, [this, set, &shaders]() -> Res<DescriptorSetLayout> {
        DescriptorSetLayoutBuilder builder(api);
        for (const auto s : shaders) {
            if (!s) {
                continue;
            }
            switch (s->getStage()) {
            case VK_SHADER_STAGE_VERTEX_BIT:
            case VK_SHADER_STAGE_FRAGMENT_BIT:
            case VK_SHADER_STAGE_COMPUTE_BIT:
                {
                    const auto& desc_sets = s->getDescriptorSets();
                    auto item = desc_sets.find(set);
                    if (item != desc_sets.end()) {
                        for (const auto& d : item->second) {
                            builder.addBinding(d.binding, static_cast<VkDescriptorType>(d.type), d.count, s->getStage());
                        }
                    }
                }
                break;
            default:
                return Er("Request with unsupported shader ({}) stage: {}",
                          s->getFilename(),
                          VkStr(VkShaderStageFlags, s->getStage()));
            }
        }
        return builder();
    });
}

Res<Ref<PipelineLayout>> Vktor::requestPipelineLayout(const Vector<const Shader*>& shaders) {
    size_t key = hash(shaders);
    return resource_cache.pipeline_layouts.request(key, [this, &shaders]() -> Res<PipelineLayout> {
        // Collect all set index
        std::set<uint32_t> sets{};
        for (const auto& s : shaders) {
            const auto& desc_sets = s->getDescriptorSets();
            for (const auto& item : desc_sets) {
                sets.insert(item.first);
            }
        }
        // Collect all descriptor sets
        PipelineLayoutBuilder builder(api);
        for (const auto& s : sets) {
            auto res = requestDescriptorSetLayout(s, shaders);
            OnErr(res);
            builder.addDescriptorSetLayout(res.unwrap().get());
        }
        return builder();
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
    return resource_cache.framebuffers.request(key, [&render_target_table, &render_pass]() {
        FramebufferBuilder builder(render_pass);
        builder.addAttachments(render_target_table.getImageViews());
        builder.setExtent(render_target_table.getExtent());
        return builder();
    });
}

NAMESPACE_END(vkt)
