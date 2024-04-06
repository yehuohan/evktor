#pragma once
#include "__core.hpp"
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
    VkResult createMemAllocator(Device& device) const;

public:
    explicit DeviceState(Name&& name = "Device") : CoreStater(std::move(name)) {}

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

    VkResult waitIdle() const;

    static Res<Device> from(const Instance& instance, const PhysicalDevice& phy_dev, DeviceState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
