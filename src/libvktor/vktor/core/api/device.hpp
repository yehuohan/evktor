#pragma once
#include "__api.hpp"
#include "debug.hpp"
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
    const void* next = nullptr;
    uint32_t max_queue_count = 1; /**< The max count of queues for each queue family, must >= 1. */

private:
    VkResult createMemAllocator(const Instance& instance, const PhysicalDevice& physical_device, Device& device) const;

public:
    explicit DeviceState(Name&& name = "Device") : CoreStater(std::move(name)) {}

    Self setNext(const void* next);
    Self setMaxQueueCount(uint32_t count);

    Res<Device> into(const Instance& instance, const PhysicalDevice& phy_dev, const IDebug& debug);
};

struct Device : public CoreHandle<VkDevice> {
    const VkAllocationCallbacks* allocator = nullptr;
    const VkInstance instance = VK_NULL_HANDLE;
    const VkPhysicalDevice physical_device = VK_NULL_HANDLE;

    Queues queues{};                                  /**< Corresponding queues for PhysicalDevice::queue_families */
    HashMap<uint32_t, Vector<Queue>> queue_indices{}; /**< Map queue family index to corresponding queue array */
    VmaAllocator mem_allocator = VK_NULL_HANDLE;

protected:
    explicit Device(const Instance& instance, const PhysicalDevice& physical_device)
        : allocator(instance.allocator)
        , instance(instance)
        , physical_device(physical_device) {}

public:
    Device(Device&&);
    ~Device();
    OnConstType(VmaAllocator, mem_allocator);

    static Res<Device> from(const Instance& instance, const PhysicalDevice& phy_dev, const IDebug& debug, DeviceState& info);
    // static Res<VkDevice> borrow(const Instance& instance, const PhysicalDevice& phy_dev, VkDevice handle);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
