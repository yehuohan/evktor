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

    Cache<core::ShaderModule> shader_modules{};
    Cache<core::DescriptorSetLayout> descriptor_setlayouts{};
    Cache<core::PipelineLayout> pipeline_layouts{};
    Cache<core::GraphicsPipeline> graphics_pipelines{};
    Cache<core::ComputePipeline> compute_pipelines{};
    Cache<core::RenderPass> render_passes{};
    Cache<core::Framebuffer> framebuffers{};

public:
    RenderResource(const core::CoreApi& api) : api(api) {}
    RenderResource(RenderResource&&);

    Res<CRef<core::ShaderModule>> requestShaderModule(const Shader& shader, String&& name = "ShaderModule");
    Res<Vector<CRef<core::DescriptorSetLayout>>> requestDescriptorSetLayouts(const Vector<CRef<Shader>>& shaders,
                                                                             String&& name = "DescriptorSetLayout");
    Res<CRef<core::PipelineLayout>> requestPipelineLayout(const Vector<CRef<Shader>>& shaders,
                                                          String&& name = "PipelineLayout");
    Res<CRef<core::GraphicsPipeline>> requestGraphicsPipeline(const core::GraphicsPipelineState& pso);
    Res<CRef<core::ComputePipeline>> requestComputePipeline(const core::ComputePipelineState& pso);
    Res<CRef<core::RenderPass>> requestRenderPass(const RenderTargetTable& rtt,
                                                  const Vector<CRef<core::RenderSubpassState>>& states,
                                                  String&& name = "RenderPass");
    Res<CRef<core::Framebuffer>> requestFramebuffer(const RenderTargetTable& rtt,
                                                    const core::RenderPass& render_pass,
                                                    String&& name = "Framebuffer");
};

NAMESPACE_END(vkt)
