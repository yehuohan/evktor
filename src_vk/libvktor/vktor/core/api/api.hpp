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
    HashMap<uint32_t, Vector<Queue>> queues{}; /**< Map queue family index to corresponding queue array */
    QueueFamilyIndices queue_family_indices{}; /**< Queue family indices for frequently-used queues */

protected:
    Box<IDebug> debug = newBox<IDebug>();
    Box<Surface> surface = nullptr;

public:
    explicit CoreApi();
    virtual ~CoreApi();

    operator const VkAllocationCallbacks*() const {
        return instance.allocator;
    }
    OnConstType(VkInstance, instance.handle);
    OnConstType(VkPhysicalDevice, physical_device.handle);
    OnConstType(VkDevice, device.handle);
    OnConstType(VmaAllocator, device.mem_allocator);
    operator const Instance&() const {
        return instance;
    }
    operator const PhysicalDevice&() const {
        return physical_device;
    }
    operator const Device&() const {
        return device;
    }

    Res<CRef<Instance>> init(InstanceState& info);
    Res<CRef<PhysicalDevice>> init(PhysicalDeviceState& info);
    Res<CRef<Device>> init(DeviceState& info);
    Res<CRef<Instance>> borrow(VkInstance handle,
                               PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr,
                               uint32_t api_version = VKT_CORE_VK_API_VERSION,
                               VkAllocationCallbacks* allocator = nullptr);
    Res<CRef<PhysicalDevice>> borrow(VkPhysicalDevice handle, VkSurfaceKHR surface = VK_NULL_HANDLE);
    Res<CRef<Device>> borrow(VkDevice handle,
                             PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr = VK_NULL_HANDLE,
                             QueueFamilyIndices indices = {},
                             VmaAllocator mem_allocator = VK_NULL_HANDLE);

    inline const QueueFamilyIndices& queueFamilyIndices() const {
        return queue_family_indices;
    }
    Res<CRef<Queue>> presentQueue(const uint32_t index = 0) const;
    Res<CRef<Queue>> graphicsQueue(const uint32_t index = 0) const;
    Res<CRef<Queue>> computeQueue(const uint32_t index = 0) const;
    Res<CRef<Queue>> transferQueue(const uint32_t index = 0) const;

public:
    inline VkResult waitIdle() const {
        return vkDeviceWaitIdle(device);
    }

public:
    Res<CRef<IDebug>> add(DebugState& info);
    Res<CRef<Surface>> add(VkSurfaceKHR surface, bool with_ownership);

    operator VkSurfaceKHR() const {
        return surface ? surface->getHandle() : VK_NULL_HANDLE;
    }

    inline VkResult setDebugName(VkObjectType type, uint64_t handle, const char* name) const {
        return debug->setDebugName(device, type, handle, name);
    }
    inline void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name) const {
        return debug->cmdBeginLabel(cmdbuf, name);
    }
    inline void cmdEndLabel(VkCommandBuffer cmdbuf) const {
        return debug->cmdEndLabel(cmdbuf);
    }
    inline void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name) const {
        return debug->cmdInsertLabel(cmdbuf, name);
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
