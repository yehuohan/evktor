#include "render_resource.hpp"
#include <functional>
#include <set>

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderResource::RenderResource(RenderResource&& rhs) : api(rhs.api) {
    shader_modules = std::move(rhs.shader_modules);
    descriptor_setlayouts = std::move(rhs.descriptor_setlayouts);
    pipeline_layouts = std::move(rhs.pipeline_layouts);
    graphics_pipelines = std::move(rhs.graphics_pipelines);
    compute_pipelines = std::move(rhs.compute_pipelines);
    render_passes = std::move(rhs.render_passes);
    framebuffers = std::move(rhs.framebuffers);
}

Res<CRef<ShaderModule>> RenderResource::requestShaderModule(const Shader& shader) {
    size_t key = hash(shader);
    return shader_modules.request(key, [this, &shader]() -> Res<ShaderModule> {
        return shader.into(api);
    });
}

Res<CRef<DescriptorSetLayout>> RenderResource::requestDescriptorSetLayout(const uint32_t set,
                                                                          const Vector<CRef<Shader>>& shaders) {
    size_t key = hash(set, shaders);
    return descriptor_setlayouts.request(key, [this, set, &shaders]() -> Res<DescriptorSetLayout> {
        DescriptorSetLayoutState dso{};
        for (const auto& ref : shaders) {
            auto& s = ref.get();
            switch (s.getStage()) {
            case VK_SHADER_STAGE_VERTEX_BIT:
            case VK_SHADER_STAGE_FRAGMENT_BIT:
            case VK_SHADER_STAGE_COMPUTE_BIT:
                {
                    const auto& desc_sets = s.getDescriptorSets();
                    if (auto it = desc_sets.find(set); it != desc_sets.end()) {
                        for (const auto& d : it->second) {
                            dso.addBinding(d.binding, static_cast<VkDescriptorType>(d.type), d.count, s.getStage());
                        }
                    }
                }
                break;
            default:
                return Er("Request with unsupported shader ({}) stage: {}",
                          s.getSourcePath(),
                          VkStr(VkShaderStageFlags, s.getStage()));
            }
        }
        return dso.into(api);
    });
}

Res<CRef<PipelineLayout>> RenderResource::requestPipelineLayout(const Vector<CRef<Shader>>& shaders) {
    size_t key = hash(shaders);
    return pipeline_layouts.request(key, [this, &shaders]() -> Res<PipelineLayout> {
        PipelineLayoutState plso{};
        std::set<uint32_t> sets{};
        for (const auto& ref : shaders) {
            // Collect all set index
            auto& s = ref.get();
            const auto& desc_sets = s.getDescriptorSets();
            for (const auto& item : desc_sets) {
                sets.insert(item.first);
            }
            // Collect all push constants
            const auto& push = s.getPushConstant();
            if (push.size > 0) {
                plso.addPushConstantRange(s.getStage(), push.size, push.offset);
            }
        }
        // Collect all descriptor sets
        for (const auto& s : sets) {
            auto res = requestDescriptorSetLayout(s, shaders);
            OnErr(res);
            plso.addDescriptorSetLayout(res.unwrap().get());
        }
        return plso.into(api);
    });
}

Res<CRef<GraphicsPipeline>> RenderResource::requestGraphicsPipeline(const GraphicsPipelineState& pso) {
    size_t key = hash(pso);
    return graphics_pipelines.request(key, [this, &pso]() {
        return pso.into(api);
    });
}

Res<CRef<ComputePipeline>> RenderResource::requestComputePipeline(const ComputePipelineState& pso) {
    size_t key = hash(pso);
    return compute_pipelines.request(key, [this, &pso]() {
        return pso.into(api);
    });
}

Res<CRef<RenderPass>> RenderResource::requestRenderPass(const RenderTargetTable& rtt,
                                                        const Vector<CRef<core::RenderSubpassState>>& states) {
    size_t key = hash(rtt.getTargets(), states);
    return render_passes.request(key, [this, &rtt, &states]() {
        RenderPassState rso{};
        for (const auto& rt : rtt.getTargets()) {
            auto& image = rt.getImage();
            rso.addAttachment(image.getFormat(), image.getSamples(), rt.ops, rt.stencil_ops, rt.layouts);
        }
        for (const auto& state : states) {
            rso.addSubpass(state.get());
        }
        return rso.into(api);
    });
}

Res<CRef<Framebuffer>> RenderResource::requestFramebuffer(const RenderTargetTable& rtt, const RenderPass& render_pass) {
    size_t key = hash(rtt, render_pass);
    return framebuffers.request(key, [this, &rtt, &render_pass]() {
        FramebufferState fso{};
        fso.setRenderPass(render_pass);
        fso.addAttachments(rtt.getImageViews());
        fso.setExtent(rtt.getExtent());
        return fso.into(api);
    });
}

NAMESPACE_END(vkt)
