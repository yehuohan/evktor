#pragma once
#include "render_target.hpp"
#include "vktor/base/shader.hpp"
#include "vktor/base/texture.hpp"
#include "vktor/core/buffer.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/device_memory.hpp"
#include "vktor/core/framebuffer.hpp"
#include "vktor/core/pipeline_compute.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/pipeline_layout.hpp"
#include "vktor/core/query_pool.hpp"
#include "vktor/core/render_pass.hpp"

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
    Res<CRef<core::RenderPass>> requestRenderPass(const RenderTargetTable& rtt,
                                                  const Vector<CRef<core::RenderSubpassState>>& states);
    Res<CRef<core::Framebuffer>> requestFramebuffer(const RenderTargetTable& rtt, const core::RenderPass& render_pass);
};

NAMESPACE_END(vkt)
