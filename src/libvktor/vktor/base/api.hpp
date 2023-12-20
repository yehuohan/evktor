#pragma once
#include "vktor/core/device.hpp"
#include "vktor/core/instance.hpp"
#include "vktor/core/physical_device.hpp"
#include <cassert>

NAMESPACE_BEGIN(vkt)

using namespace core;

/**
 * @brief Basic Vulkan API for instance and device
 */
class BaseApi : private NonCopyable {
private:
    Box<Instance> instance = nullptr;
    Box<PhysicalDevice> phy_dev = nullptr;
    Box<Device> dev = nullptr;

public:
    explicit BaseApi() {}

    OnConstType(VkInstance, instance->handle);
    OnConstType(VkPhysicalDevice, phy_dev->handle);
    OnConstType(VkDevice, dev->handle);
    operator Instance&() const {
        assert(instance && "Instance device is invalid");
        return *instance;
    }
    operator PhysicalDevice&() const {
        assert(phy_dev && "Physical device is invalid");
        return *phy_dev;
    }
    operator Device&() const {
        assert(dev && "Device is invalid");
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

    uint32_t presentIndex() const {
        return phy_dev->indices.present.value();
    }
    uint32_t graphicsIndex() const {
        return phy_dev->indices.graphics.value();
    }
    uint32_t computeIndex() const {
        return phy_dev->indices.compute.value();
    }
    uint32_t transferIndex() const {
        return phy_dev->indices.transfer.value();
    }
    VkQueue presentQueue() const {
        return dev->queues.present;
    }
    VkQueue graphicsQueue() const {
        return dev->queues.graphics;
    }
    VkQueue computeQueue() const {
        return dev->queues.compute;
    }
    VkQueue transferQueue() const {
        return dev->queues.transfer;
    }
};

NAMESPACE_END(vkt)
