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
    uint32_t max_queue_count = 1; /**< The max count of queues for each queue family, must >= 1. */
    Vector<const char*> required_extensions{};
    // VkPhysicalDeviceFeatures required_features{};

private:
    VkResult createMemAllocator(const Instance& instance, const PhysicalDevice& physical_device, Device& device) const;

public:
    explicit DeviceState(String&& name = "Device") : CoreStater(std::move(name)) {}

    Self setMaxQueueCount(uint32_t count);
    Self addRequiredExtension(const char* extension);
    Self addRequiredExtensions(const Vector<const char*> extensions);
    // Self setRequiredFeatures(const VkPhysicalDeviceFeatures& features);

    Res<Device> into(const Instance& instance, const PhysicalDevice& phy_dev);
};

struct Device : public CoreHandle<VkDevice> {
    const VkAllocationCallbacks* allocator = nullptr;
    const VkInstance instance = VK_NULL_HANDLE;
    const VkPhysicalDevice physical_device = VK_NULL_HANDLE;

    VmaAllocator mem_allocator = VK_NULL_HANDLE;
    QueueFamilyIndices queue_family_indices{};
    Vector<const char*> extensions{}; /**< Enabled extensions for device */

protected:
    explicit Device(const Instance& instance, const PhysicalDevice& physical_device)
        : allocator(instance.allocator)
        , instance(instance)
        , physical_device(physical_device) {}

public:
    Device(Device&&);
    ~Device();
    OnConstType(VmaAllocator, mem_allocator);

    bool isExtensionEnabled(const char* extension) const;
    inline VkMemoryRequirements getMemoryRequirements(VkBuffer buffer) const;
    inline VkMemoryRequirements getMemoryRequirements(VkImage image) const;

    static Res<Device> from(const Instance& instance, const PhysicalDevice& phy_dev, DeviceState& info);
    static Res<VkDevice> borrow(VkInstance instance,
                                VkPhysicalDevice phy_dev,
                                VkDevice handle,
                                PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr,
                                const QueueFamilyIndices& queue_family_indices = QueueFamilyIndices{},
                                const VkAllocationCallbacks* allocator = nullptr);
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
