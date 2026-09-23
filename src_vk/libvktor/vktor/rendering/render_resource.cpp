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

Res<CRef<ShaderModule>> RenderResource::requestShaderModule(const Shader& shader, String&& name) {
    size_t key = hash(shader);
    return shader_modules.request(key, [this, &shader, &name]() -> Res<ShaderModule> {
        return shader.into(api, std::move(name));
    });
}

Res<Vector<CRef<core::DescriptorSetLayout>>> RenderResource::requestDescriptorSetLayouts(const Vector<CRef<Shader>>& shaders,
                                                                                         String&& name) {
    uint32_t count = 0;
    for (const auto& ref : shaders) {
        count = std::max<uint32_t>(count, ref.get().getDescriptorSets().size());
    }

    Vector<CRef<core::DescriptorSetLayout>> desc_setlayouts{};
    for (uint32_t set = 0; set < count; set++) {
        size_t key = hash(set, shaders); // Same set in different shaders (e.g. vert & frag) must has same layout
        OnErr(res, descriptor_setlayouts.request(key, [this, set, &shaders, &name]() -> Res<DescriptorSetLayout> {
            DescriptorSetLayoutState dslo{vktFmt("{}#{}", name, set)};

            for (const auto& ref : shaders) {
                const auto& s = ref.get();
                switch (s.getStage()) {
                case VK_SHADER_STAGE_VERTEX_BIT:
                case VK_SHADER_STAGE_FRAGMENT_BIT:
                case VK_SHADER_STAGE_COMPUTE_BIT:
                    {
                        for (const auto& [_, d] : s.getDescriptorSets()[set]) {
                            dslo.addBinding(d.binding, static_cast<VkDescriptorType>(d.type), d.count, s.getStage());
                        }
                    }
                    break;
                default:
                    return Er("Request with unsupported shader ({}) stage: {}",
                              s.getSourcePath(),
                              VkStr(VkShaderStageFlags, s.getStage()));
                }
            }

            return dslo.into(api);
        }));
        desc_setlayouts.push_back(res.unwrap());
    }

    return Ok(std::move(desc_setlayouts));
}

Res<CRef<PipelineLayout>> RenderResource::requestPipelineLayout(const Vector<CRef<Shader>>& shaders, String&& name) {
    size_t key = hash(shaders);
    return pipeline_layouts.request(key, [this, &shaders, &name]() -> Res<PipelineLayout> {
        PipelineLayoutState plso{std::move(name)};

        OnUnwrap(desc_setlayouts, requestDescriptorSetLayouts(shaders));
        for (const auto& item : desc_setlayouts) {
            plso.addDescriptorSetLayout(item.get());
        }
        for (const auto& ref : shaders) {
            auto& s = ref.get();
            const auto& push = s.getPushConstant();
            if (push.size > 0) {
                plso.addPushConstantRange(s.getStage(), push.size, push.offset);
            }
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
                                                        const Vector<CRef<core::RenderSubpassState>>& states,
                                                        String&& name) {
    size_t key = hash(rtt.getTargets(), states);
    return render_passes.request(key, [this, &rtt, &states, &name]() {
        RenderPassState rso{std::move(name)};
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

Res<CRef<Framebuffer>> RenderResource::requestFramebuffer(const RenderTargetTable& rtt,
                                                          const RenderPass& render_pass,
                                                          String&& name) {
    size_t key = hash(rtt, render_pass);
    return framebuffers.request(key, [this, &rtt, &render_pass, &name]() {
        FramebufferState fso{std::move(name)};
        fso.setRenderPass(render_pass);
        fso.addAttachments(rtt.getImageViews());
        fso.setExtent(rtt.getExtent());
        return fso.into(api);
    });
}

NAMESPACE_END(vkt)
