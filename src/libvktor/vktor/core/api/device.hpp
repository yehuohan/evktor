#pragma once
#include "__api.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "queue.hpp"
#include <vk_mem_alloc.h>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Device;

class DeviceState : public CoreStater<DeviceState> {
    friend struct Device;

private:
    uint32_t max_queue_count = 1; /**< The max count of queues for each queue family, must >= 1. */

private:
    VkResult createMemAllocator(Device& device) const;

public:
    explicit DeviceState(Name&& name = "Device") : CoreStater(std::move(name)) {}

    Self setMaxQueueCount(uint32_t count);

    Res<Device> into(const Instance& instance, const PhysicalDevice& phy_dev);
};

struct Device : public CoreHandle<VkDevice> {
    const Instance& instance;
    const PhysicalDevice& physical_device;

    Queues queues{};                                  /**< Corresponding queues for PhysicalDevice::queue_families */
    HashMap<uint32_t, Vector<Queue>> queue_indices{}; /**< Map queue family index to corresponding queue array */
    VmaAllocator mem_allocator = VK_NULL_HANDLE;

protected:
    explicit Device(const Instance& instance, const PhysicalDevice& physical_device)
        : instance(instance)
        , physical_device(physical_device) {}

public:
    Device(Device&&);
    ~Device();
    OnConstType(VmaAllocator, mem_allocator);

    static Res<Device> from(const Instance& instance, const PhysicalDevice& phy_dev, DeviceState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
