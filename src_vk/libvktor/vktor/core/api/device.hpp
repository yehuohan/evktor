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

using VkhDevice = VkHandle<VkDevice>;

template <>
struct VkHandle<VkDevice> : public vk_parent_s<VkDevice> {
    VK_HANDLE_IMPL(VkDevice)

protected:
    VmaAllocator mem_allocator = VK_NULL_HANDLE;

public:
    explicit VkHandle(VkDevice h, VmaAllocator _mem_allocator = VK_NULL_HANDLE, VkPhysicalDevice p = VK_NULL_HANDLE)
        : HasPhysicalDevice(p)
        , __handle(h)
        , mem_allocator(_mem_allocator) {}
    OnConstType(VmaAllocator, mem_allocator);

    VkResult createMemAllocator(VkHandle<VkInstance> instance,
                                VkHandle<VkPhysicalDevice> phy_dev,
                                VmaAllocatorCreateFlags flags = 0);

    inline VkMemoryRequirements getMemoryRequirements(VkBuffer buffer) const;
    inline VkMemoryRequirements getMemoryRequirements(VkImage image) const;
};

/**
 * @brief Vulkan core device
 */
struct Device : public CoreHandle<VkDevice> {
    friend class CoreApi;

    CRef<PhysicalDevice> physical_device;

private:
    bool borrowed_mem_allocator = false;

protected:
    explicit Device(CRef<PhysicalDevice> physical_device) : physical_device(physical_device) {
        this->__parent = physical_device.get();
    }
    explicit Device(CRef<PhysicalDevice> physical_device, VkHandle<VkDevice> h)
        : CoreHandle(h)
        , physical_device(physical_device) {
        this->__parent = physical_device.get();
        borrowed_mem_allocator = mem_allocator != VK_NULL_HANDLE;
    }

public:
    Device(Device&&);
    ~Device();
    Device& operator=(Device&&);

    static Res<Device> from(CRef<PhysicalDevice> phy_dev, DeviceState& info);
    /**
     * @brief Borrow device
     *
     * `fpGetDeviceProcAddr != nullptr` is meant to manually initialize Vulkan loader with volk
     */
    static Res<Device> borrow(CRef<PhysicalDevice> phy_dev,
                              VkHandle<VkDevice> handle,
                              PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr = nullptr);
};

template <typename T>
DeviceState::Self DeviceState::setFeatures(std::function<void(T&)> fn) {
    fn(features.get<T>());
    return *this;
}

inline VkMemoryRequirements VkHandle<VkDevice>::getMemoryRequirements(VkBuffer buffer) const {
    VkMemoryRequirements reqs{};
    vkGetBufferMemoryRequirements(__handle, buffer, &reqs);
    return reqs;
}

inline VkMemoryRequirements VkHandle<VkDevice>::getMemoryRequirements(VkImage image) const {
    VkMemoryRequirements reqs{};
    vkGetImageMemoryRequirements(__handle, image, &reqs);
    return reqs;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
