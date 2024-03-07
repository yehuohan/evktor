/**
 * @file vktor.hpp
 * @brief Graphics builder framework based on Vulkan
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

using namespace core;

class Vktor {
public:
    BaseApi api{};
    Box<RenderContext> render_context = nullptr;

private:
    ResourceCache resource_cache{};

public:
    void addRenderContext();

    Res<Ref<ShaderModule>> requestShaderModule(const Shader& shader);
    Res<Ref<DescriptorSetLayout>> requestDescriptorSetLayout(const uint32_t set, const Vector<const Shader*>& shaders);
    Res<Ref<PipelineLayout>> requestPipelineLayout(const Vector<const Shader*>& shaders);
    Res<Ref<RenderPass>> requestRenderPass(const RenderTargetTable& render_target_table, const RenderPipeline& render_pipeline);
    Res<Ref<Framebuffer>> requestFramebuffer(const RenderTargetTable& render_target_table, const RenderPass& render_pass);
};

NAMESPACE_END(vkt)
