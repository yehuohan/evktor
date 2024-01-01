#pragma once
#include "vktor/core/buffer.hpp"
#include "vktor/core/framebuffer.hpp"
#include "vktor/core/pipeline_compute.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/render_pass.hpp"
#include "vktor/core/sampler.hpp"
#include "vktor/core/shader_module.hpp"
#include <mutex>

NAMESPACE_BEGIN(vkt)

using namespace core;

#define RESOURCE_STATE_LOCKER(rs) std::lock_guard<std::mutex> guard((rs).mtx)

template <typename T>
struct ResourceState {
    HashMap<size_t, T> map{};
    std::mutex mtx;

    inline HashMap<size_t, T>::iterator find(size_t key) {
        return map.find(key);
    }
    inline bool found(const HashMap<size_t, T>::iterator& item) {
        return item != map.end();
    }
};

struct ResourceCache {
    ResourceState<ShaderModule> shader_modules{};
    ResourceState<DescriptorSetLayout> descriptor_setlayouts{};
    ResourceState<RenderPass> render_passes{};
    ResourceState<PipelineLayout> pipeline_layouts{};
    ResourceState<GraphicsPipeline> graphics_pipelines{};
    ResourceState<ComputePipeline> compute_pipelines{};
    ResourceState<Framebuffer> framebuffers{};
};

NAMESPACE_END(vkt)
