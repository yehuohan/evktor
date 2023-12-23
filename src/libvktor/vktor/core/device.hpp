#pragma once
#include "__builder.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "queue.hpp"
#include <vk_mem_alloc.h>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Device : public BuiltHandle<VkDevice> {
    const Instance& instance;
    const PhysicalDevice& physical_device;

    Queues queues{};                                  /**< Corresponding queues for PhysicalDevice::queue_families */
    HashMap<uint32_t, Vector<Queue>> queue_indices{}; /**< Map queue family index to corresponding queue array */
    VmaAllocator mem_allocator = VK_NULL_HANDLE;

    Device(const Instance& instance, const PhysicalDevice& physical_device, Name&& name)
        : BuiltHandle(std::move(name))
        , instance(instance)
        , physical_device(physical_device) {}
    Device(Device&&);
    ~Device();
    OnConstType(VmaAllocator, mem_allocator);
};

struct DeviceInfo : public BuilderInfo {};

class DeviceBuilder : public Builder<DeviceBuilder, Device, DeviceInfo> {
private:
    const Instance& instance;
    const PhysicalDevice& physical_device;
    constexpr static const float QUEUE_PRIORITY = 1.0f;

public:
    explicit DeviceBuilder(const Instance& instance, const PhysicalDevice& phy_dev, Name&& name = "Device")
        : Builder(std::move(name))
        , instance(instance)
        , physical_device(phy_dev) {}
    virtual Built build() override;

private:
    VkResult createMemAllocator(Device& device);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
