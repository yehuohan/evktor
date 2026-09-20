#pragma once
#include "device.hpp"
#include "exts/debug.hpp"
#include "exts/surface.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "queue.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

/**
 * @brief Vulkan core api
 *
 * CoreApi should not move, as core Vulkan resource constructor need reference `const CoreApi&`.
 */
class CoreApi : private NonCopyable, private NonMoveable {
protected:
    Instance instance;
    PhysicalDevice physical_device;
    Device device;
    Vector<Vector<Queue>> queues{};            /**< Map queue family index to corresponding queue array */
    QueueFamilyIndices queue_family_indices{}; /**< Queue family indices for frequently-used queues */

protected:
    Box<IDebug> debug = newBox<IDebug>();
    Box<Surface> surface = nullptr;

public:
    explicit CoreApi() : instance{}, physical_device(newCRef(instance)), device(newCRef(physical_device)) {}
    virtual ~CoreApi() = default;

    OnConstType(VkInstance, instance.__handle);
    OnConstType(VkPhysicalDevice, physical_device.__handle);
    OnConstType(VkDevice, device.__handle);
    OnConstType(VmaAllocator, device.mem_allocator);
    operator const VkAllocationCallbacks*() const {
        return instance.allocator;
    }
    operator const Instance&() const {
        return instance;
    }
    operator const PhysicalDevice&() const {
        return physical_device;
    }
    operator const Device&() const {
        return device;
    }
    const Instance& inst() const {
        return instance;
    }
    const PhysicalDevice& phyDev() const {
        return physical_device;
    }
    const Device& dev() const {
        return device;
    }

    Res<CRef<Instance>> init(InstanceState& info);
    Res<CRef<PhysicalDevice>> init(PhysicalDeviceState& info);
    Res<CRef<Device>> init(DeviceState& info);
    Res<CRef<Instance>> borrow(VkHandle<VkInstance> handle, PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = nullptr);
    Res<CRef<PhysicalDevice>> borrow(VkHandle<VkPhysicalDevice> handle);
    Res<CRef<Device>> borrow(VkHandle<VkDevice> handle,
                             QueueFamilyIndices indices = {},
                             PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr = nullptr);

    inline const QueueFamilyIndices& queueFamilyIndices() const {
        return queue_family_indices;
    }
    inline Res<VkhQueue> presentQueue(const uint32_t index = 0) const {
        return getQueue(queue_family_indices.present, index);
    }
    inline Res<VkhQueue> graphicsQueue(const uint32_t index = 0) const {
        return getQueue(queue_family_indices.graphics, index);
    }
    inline Res<VkhQueue> computeQueue(const uint32_t index = 0) const {
        return getQueue(queue_family_indices.compute, index);
    }
    inline Res<VkhQueue> transferQueue(const uint32_t index = 0) const {
        return getQueue(queue_family_indices.transfer, index);
    }

protected:
    Res<VkhQueue> getQueue(const uint32_t family_index, const uint32_t index) const;

public:
    inline VkResult waitIdle() const {
        return vkDeviceWaitIdle(device);
    }

public:
    Res<CRef<IDebug>> add(DebugState& info);
    Res<CRef<Surface>> add(VkHandle<VkSurfaceKHR> surface, bool with_ownership);

    operator VkSurfaceKHR() const {
        return surface ? surface->handle() : VK_NULL_HANDLE;
    }

    inline VkResult setDebugName(VkObjectType type, uint64_t handle, const char* name) const {
        return debug->setDebugName(device, type, handle, name);
    }
    inline void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name, const IDebug::Color& color = IDebug::None) const {
        return debug->cmdBeginLabel(cmdbuf, name, color);
    }
    inline void cmdEndLabel(VkCommandBuffer cmdbuf) const {
        return debug->cmdEndLabel(cmdbuf);
    }
    inline void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name, const IDebug::Color& color = IDebug::None) const {
        return debug->cmdInsertLabel(cmdbuf, name, color);
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
