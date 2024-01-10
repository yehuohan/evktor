#pragma once
#include "vktor/core/buffer.hpp"
#include "vktor/core/framebuffer.hpp"
#include "vktor/core/pipeline_compute.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/render_pass.hpp"
#include "vktor/core/sampler.hpp"
#include "vktor/core/shader_module.hpp"
#include <functional>
#include <mutex>

NAMESPACE_BEGIN(vkt)

using namespace core;

#define LOCK_RESOURCE_STATE(rs) std::lock_guard<std::mutex> guard((rs).mtx)

template <typename T>
class ResourceState {
private:
    HashMap<size_t, T> map{};
    std::mutex mtx;

public:
    inline HashMap<size_t, T>::iterator find(size_t key) {
        return map.find(key);
    }

    inline bool found(const HashMap<size_t, T>::iterator& item) {
        return item != map.end();
    }

    /**
     * @brief Add resource
     *
     * This returns the iterator returned from HashMap::insert() directly.
     * So you should make sure the insertion is going to success or fail.
     */
    inline HashMap<size_t, T>::iterator add(size_t key, T&& value) {
        return map.insert({key, std::move(value)}).first;
    }

    /**
     * @brief Request resource that stored in `map`
     */
    inline Res<Ref<T>> request(size_t key, std::function<Res<T>()> fn) {
        LOCK_RESOURCE_STATE(*this);

        T* ptr;
        {
            auto item = this->find(key);
            if (this->found(item)) {
                ptr = &item->second;
            } else {
                auto res = fn();
                OnErr(res);
                auto iter = this->add(key, res.unwrap());
                ptr = &iter->second;
            }
        }

        return Ok(newRef(*ptr));
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
