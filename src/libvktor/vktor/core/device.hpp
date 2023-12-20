#pragma once
#include "__builder.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include <vk_mem_alloc.h>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Device : public BuiltHandle<VkDevice> {
    const Instance& instance;
    const PhysicalDevice& physical_device;

    struct Queues {
        VkQueue present = VK_NULL_HANDLE;
        VkQueue graphics = VK_NULL_HANDLE;
        VkQueue compute = VK_NULL_HANDLE;
        VkQueue transfer = VK_NULL_HANDLE;
    } queues{};
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
    constexpr static const uint32_t QUEUE_COUNT = 1;
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
