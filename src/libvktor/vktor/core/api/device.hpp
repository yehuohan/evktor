#pragma once
#include "__api.hpp"
#include "physical_device.hpp"
#include <vk_mem_alloc.h>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

class CoreApi;
struct Device;

class DeviceState : public CoreState<DeviceState> {
    friend struct Device;

private:
    uint32_t max_queue_count = 1; /**< The max count of queues for each queue family, must >= 1. */
    Vector<const char*> extensions{};
    VkPhysicalDeviceFeatures features{};
    bool require_extensions_for_vma = false;

public:
    explicit DeviceState(String&& name = "Device") : CoreState(std::move(name)) {}

    Self setMaxQueueCount(uint32_t count);
    Self addExtension(const char* extension);
    Self addExtensions(const Vector<const char*> extensions);
    Self addExtensionsForVMA();
    Self setFeatures(const VkPhysicalDeviceFeatures& features);

    Res<Device> into(CRef<PhysicalDevice> phy_dev);
};

struct Device : public CoreHandle<VkDevice> {
    friend CoreApi;

    CRef<PhysicalDevice> physical_device;

    VmaAllocator mem_allocator = VK_NULL_HANDLE;

protected:
    explicit Device(CRef<PhysicalDevice> physical_device) : physical_device(physical_device) {}

    VkResult createMemAllocator(VmaAllocatorCreateFlags flags = 0);

public:
    Device(Device&&);
    ~Device();
    Device& operator=(Device&&);
    OnConstType(VmaAllocator, mem_allocator);

    inline VkMemoryRequirements getMemoryRequirements(VkBuffer buffer) const;
    inline VkMemoryRequirements getMemoryRequirements(VkImage image) const;

    static Res<Device> from(CRef<PhysicalDevice> phy_dev, DeviceState& info);
    static Res<Device> borrow(CRef<PhysicalDevice> phy_dev,
                              VkDevice handle,
                              PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr = VK_NULL_HANDLE,
                              VmaAllocator mem_allocator = VK_NULL_HANDLE);
};

inline VkMemoryRequirements Device::getMemoryRequirements(VkBuffer buffer) const {
    VkMemoryRequirements reqs{};
    vkGetBufferMemoryRequirements(handle, buffer, &reqs);
    return reqs;
}

inline VkMemoryRequirements Device::getMemoryRequirements(VkImage image) const {
    VkMemoryRequirements reqs{};
    vkGetImageMemoryRequirements(handle, image, &reqs);
    return reqs;
}

bool checkDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& device_extensions);
void printDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& enabled_extensions);
bool checkDeviceFeatures(VkPhysicalDevice pd, const VkPhysicalDeviceFeatures& device_features);
void printDeviceFeatures(VkPhysicalDevice pd, const VkPhysicalDeviceFeatures& enabled_features);

NAMESPACE_END(core)
NAMESPACE_END(vkt)
