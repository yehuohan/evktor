#pragma once
#include "__api.hpp"
#include "physical_device.hpp"
#include <vk_mem_alloc.h>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Device;

class DeviceState : public CoreState<DeviceState> {
    friend struct Device;

public:
    using VulkanFeatures = NextState<VkPhysicalDeviceFeatures2,
                                     VkPhysicalDeviceVulkan11Features,
                                     VkPhysicalDeviceVulkan12Features,
                                     VkPhysicalDeviceVulkan13Features>;

private:
    uint32_t max_queue_count = 1;         /**< The max count of queues for each queue family, must >= 1. */
    Vector<const char*> extensions{};     /**< Required deivce extensions */
    Vector<const char*> try_extensions{}; /**< Enabled device extensions if available */
    VulkanFeatures features{Itor::PhysicalDeviceFeatures2(),
                            Itor::PhysicalDeviceVulkan11Features(),
                            Itor::PhysicalDeviceVulkan12Features(),
                            Itor::PhysicalDeviceVulkan13Features()};

public:
    explicit DeviceState(String&& name = "Device") : CoreState(std::move(name)) {}

    Self setMaxQueueCount(uint32_t count);
    Self addExtension(const char* extension);
    Self addExtensions(const Vector<const char*>& extensions);
    Self tryAddExtension(const char* extension);
    template <typename T>
    Self setFeatures(std::function<void(T&)> fn);
#if VK_KHR_dynamic_rendering // As a block region
    Self enableDynamicRenderingFeature();
#endif

    Res<Device> into(CRef<PhysicalDevice> phy_dev);
};

struct Device : public CoreHandle<VkDevice> {
    friend class CoreApi;

    CRef<PhysicalDevice> physical_device;

protected:
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

template <typename T>
DeviceState::Self DeviceState::setFeatures(std::function<void(T&)> fn) {
    fn(features.get<T>());
    return *this;
}

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

NAMESPACE_END(core)
NAMESPACE_END(vkt)
