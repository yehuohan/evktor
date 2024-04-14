#pragma once
#include "device.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "queue.hpp"
#include "surface.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

class CoreApi;

class CoreApiState : private NonCopyable {
protected:
    Box<Instance> instance = nullptr;
    Box<PhysicalDevice> physical_device = nullptr;
    Box<Device> device = nullptr;

public:
    /** Initialize instance (the old will be destroyed) */
    Res<CRef<Instance>> init(InstanceState& info);
    /** Initialize physical device (the old will be destroyed) */
    Res<CRef<PhysicalDevice>> init(PhysicalDeviceState& info);
    /** Initialize device (the old will be destroyed) */
    Res<CRef<Device>> init(DeviceState& info);
    /** Initialize core api */
    Res<CoreApi> into();
};

class CoreApi : private NonCopyable {
protected:
    Instance instance;
    PhysicalDevice physical_device;
    Device device;

public:
    CoreApi(Instance&& instance, PhysicalDevice&& physical_device, Device&& device)
        : instance(std::move(instance))
        , physical_device(std::move(physical_device))
        , device(std::move(device)) {}
    CoreApi(CoreApi&&);
    virtual ~CoreApi() {}

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
    static Res<CoreApi> from(CoreApiState& info) {
        return info.into();
    }
    inline Res<Surface> newSurface(VkSurfaceKHR& surface) const {
        return Surface::from(*this, surface);
    }

    inline VkResult setDebugName(VkObjectType type, uint64_t handle, const char* name) const {
        return instance.debug->setDebugName(device, type, handle, name);
    }
    inline void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name) const {
        return instance.debug->cmdBeginLabel(cmdbuf, name);
    }
    inline void cmdEndLabel(VkCommandBuffer cmdbuf) const {
        return instance.debug->cmdEndLabel(cmdbuf);
    }
    inline void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name) const {
        return instance.debug->cmdInsertLabel(cmdbuf, name);
    }

    Res<CRef<Queue>> presentQueue() const;
    Res<CRef<Queue>> graphicsQueue() const;
    Res<CRef<Queue>> computeQueue() const;
    Res<CRef<Queue>> transferQueue() const;

    inline VkResult waitIdle() const {
        return vkDeviceWaitIdle(device);
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
