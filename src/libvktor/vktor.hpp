/**
 * @file vktor.hpp
 * @brief Vulkan graphics framework
 *
 * @author yehuohan@qq.com
 */
#pragma once
#include "vktor/base/api.hpp"
#include "vktor/base/resource_cache.hpp"
#include "vktor/base/shader.hpp"
#include "vktor/rendering/render_context.hpp"
#include "vktor/rendering/render_frame.hpp"
#include "vktor/rendering/render_pipeline.hpp"
#include "vktor/rendering/render_subpass.hpp"
#include "vktor/rendering/render_target.hpp"

NAMESPACE_BEGIN(vkt)

class Vktor {
public:
    BaseApi api{};
    Box<RenderContext> render_context = nullptr;

private:
    ResourceCache resource_cache{};

public:
    void addRenderContext();

    Res<Ref<Shader>> requestShader(const ShaderSource& shader_source);
    Res<Ref<core::DescriptorSetLayout>> requestDescriptorSetLayout(const uint32_t set, const Vector<Shader>& shaders);
    Res<Ref<core::PipelineLayout>> requestPipelineLayout(const Vector<Shader>& shaders);
    Res<Ref<core::GraphicsPipeline>> requestGraphicsPipeline(const core::GraphicsPipelineState& pso);
    Res<Ref<core::ComputePipeline>> requestComputePipeline(const core::ComputePipelineState& pso);
    Res<Ref<core::RenderPass>> requestRenderPass(const RenderTargetTable& render_target_table,
                                                 const RenderPipeline& render_pipeline);
    Res<Ref<core::Framebuffer>> requestFramebuffer(const RenderTargetTable& render_target_table,
                                                   const core::RenderPass& render_pass);
};

NAMESPACE_END(vkt)
