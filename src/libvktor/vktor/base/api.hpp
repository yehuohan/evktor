#pragma once
#include "resource_cache.hpp"
#include "vktor/core/device.hpp"
#include "vktor/core/instance.hpp"
#include "vktor/core/physical_device.hpp"
#include "vktor/core/queue.hpp"
#include "vktor/rendering/render_target.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

class RenderPipeline;

/**
 * @brief Basic Vulkan API for instance and device
 */
class BaseApi : private NonCopyable {
private:
    Box<Instance> instance = nullptr;
    Box<PhysicalDevice> phy_dev = nullptr;
    Box<Device> dev = nullptr;
    ResourceCache resource_cache{};

public:
    explicit BaseApi() {}

    OnConstType(VkInstance, instance->handle);
    OnConstType(VkPhysicalDevice, phy_dev->handle);
    OnConstType(VkDevice, dev->handle);
    operator Instance&() const {
        Check(instance, "Instance device is invalid");
        return *instance;
    }
    operator PhysicalDevice&() const {
        Check(phy_dev, "Physical device is invalid");
        return *phy_dev;
    }
    operator Device&() const {
        Check(dev, "Device is invalid");
        return *dev;
    }

    inline void add(Instance&& _instance) {
        instance.reset();
        instance = newBox<Instance>(std::move(_instance));
    }
    inline void add(PhysicalDevice&& _phy_dev) {
        phy_dev.reset();
        phy_dev = newBox<PhysicalDevice>(std::move(_phy_dev));
    }
    inline void add(Device&& _dev) {
        dev.reset();
        dev = newBox<Device>(std::move(_dev));
    }

    Res<Ref<Queue>> presentQueue() const;
    Res<Ref<Queue>> graphicsQueue() const;
    Res<Ref<Queue>> computeQueue() const;
    Res<Ref<Queue>> transferQueue() const;

    /* Resource cache */
    Res<Ref<RenderPass>> requestRenderPass(const RenderTargetTable& render_target_table, const RenderPipeline& render_pipeline);
    Res<Ref<Framebuffer>> requestFramebuffer(const RenderTargetTable& render_target_table, const RenderPass& render_pass);
};

NAMESPACE_END(vkt)
