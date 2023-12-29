#pragma once
#include "vktor/core/buffer.hpp"
#include "vktor/core/framebuffer.hpp"
#include "vktor/core/pipeline_compute.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/render_pass.hpp"
#include "vktor/core/sampler.hpp"
#include "vktor/core/shader_module.hpp"

NAMESPACE_BEGIN(vkt)

struct ResourceCache {
    HashMap<size_t, core::ShaderModule> shader_modules{};
    HashMap<size_t, core::DescriptorSetLayout> descriptor_setlayouts{};
    HashMap<size_t, core::RenderPass> render_passes{};
    HashMap<size_t, core::PipelineLayout> pipeline_layouts{};
    HashMap<size_t, core::GraphicsPipeline> graphics_pipelines{};
    HashMap<size_t, core::ComputePipeline> compute_pipelines{};
    HashMap<size_t, core::Framebuffer> framebuffers{};
};

NAMESPACE_END(vkt)
