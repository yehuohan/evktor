#pragma once
#include "render_pipeline.hpp"
#include "render_target.hpp"
#include "share/resource_cache.hpp"
#include "vktor/base/shader.hpp"
#include "vktor/core/descriptor_pool.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/framebuffer.hpp"
#include "vktor/core/pipeline_compute.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/pipeline_layout.hpp"
#include "vktor/core/render_pass.hpp"
#include <functional>

NAMESPACE_BEGIN(vkt)

class RenderResource : private NonCopyable {
protected:
    const core::CoreApi& api;

    ResourceCache<core::ShaderModule> shader_modules{};
    ResourceCache<core::DescriptorSetLayout> descriptor_setlayouts{};
    ResourceCache<core::PipelineLayout> pipeline_layouts{};
    ResourceCache<core::GraphicsPipeline> graphics_pipelines{};
    ResourceCache<core::ComputePipeline> compute_pipelines{};
    ResourceCache<core::RenderPass> render_passes{};
    ResourceCache<core::Framebuffer> framebuffers{};

public:
    RenderResource(const core::CoreApi& api) : api(api) {}
    RenderResource(RenderResource&&);

    Res<CRef<core::ShaderModule>> requestShaderModule(const Shader& shader);
    Res<CRef<core::DescriptorSetLayout>> requestDescriptorSetLayout(const uint32_t set, const Vector<CRef<Shader>>& shaders);
    Res<CRef<core::PipelineLayout>> requestPipelineLayout(const Vector<CRef<Shader>>& shaders);
    Res<CRef<core::GraphicsPipeline>> requestGraphicsPipeline(const core::GraphicsPipelineState& pso);
    Res<CRef<core::ComputePipeline>> requestComputePipeline(const core::ComputePipelineState& pso);
    Res<CRef<core::RenderPass>> requestRenderPass(const RenderTargetTable& render_target_table,
                                                  const RenderPipeline& render_pipeline);
    Res<CRef<core::Framebuffer>> requestFramebuffer(const RenderTargetTable& render_target_table,
                                                    const core::RenderPass& render_pass);
};

NAMESPACE_END(vkt)
