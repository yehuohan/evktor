#include "api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Res<CRef<Instance>> CoreApi::init(InstanceState& info) {
    OnErr(res, info.into());
    instance = res.unwrap();

    // Reset objects that depends on instance
    debug = newBox<IDebug>();
    surface.reset();

    return Ok(newCRef(instance));
}

Res<CRef<Instance>> CoreApi::borrow(VkHandle<VkInstance> handle, PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr) {
    OnErr(res, Instance::borrow(handle, fpGetInstanceProcAddr));
    instance = res.unwrap();

    // Reset objects that depends on instance
    debug = newBox<IDebug>();
    surface.reset();

    return Ok(newCRef(instance));
}

Res<CRef<PhysicalDevice>> CoreApi::init(PhysicalDeviceState& info) {
    if (!instance.__handle) {
        return Er("Must have initialized a valid instance to initialize physical device");
    }
    OnErr(res, info.into(newCRef(instance)));
    physical_device = res.unwrap();
    return Ok(newCRef(physical_device));
}

Res<CRef<PhysicalDevice>> CoreApi::borrow(VkHandle<VkPhysicalDevice> handle) {
    if (!instance.__handle) {
        return Er("Must have borrowed a valid instance to initialize physical device");
    }
    OnErr(res, PhysicalDevice::borrow(newCRef(instance), handle));
    physical_device = res.unwrap();
    return Ok(newCRef(physical_device));
}

static uint32_t findQueueFamilyIndex(const Vector<QueueFamilyProps>& props, VkQueueFlags flags) {
    // Find present queue
    if (flags == 0) {
        uint32_t index = VK_QUEUE_FAMILY_IGNORED;
        for (uint32_t fi = 0; fi < props.size(); fi++) {
            const auto& prop = props[fi];
            if (prop.present && !prop.graphics) {
                return fi;
            }
            if (prop.present) {
                index = fi;
            }
        }
        return index;
    }

    uint32_t index = VK_QUEUE_FAMILY_IGNORED;
    if (flags & VK_QUEUE_GRAPHICS_BIT) {
        // Prefer graphics queue with more abilities
        for (uint32_t fi = 0; fi < props.size(); fi++) {
            const auto& prop = props[fi];
            const VkQueueFlags tmp = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
            if (prop.flags & flags) {
                if (prop.flags & tmp) {
                    return fi;
                }
                index = fi;
            }
        }
    } else {
        // Prefer dedicated queue without graphics queue
        for (uint32_t fi = 0; fi < props.size(); fi++) {
            const auto& prop = props[fi];
            if (prop.flags & flags) {
                if (!prop.graphics) {
                    return fi;
                }
                index = fi;
            }
        }
    }
    return index;
}

Res<CRef<Device>> CoreApi::init(DeviceState& info) {
    if (!instance.__handle) {
        return Er("Must have initialized a valid instance to initialize device");
    }
    if (!physical_device.__handle) {
        return Er("Must have initialized a valid physical device");
    }
    OnErr(res, info.into(newCRef(physical_device)));
    device = res.unwrap();

    OnRet(setDebugName(VK_OBJECT_TYPE_DEVICE, reinterpret_cast<uint64_t>(device.__handle), info.__name.c_str()),
          "Failed to set device debug name: {}",
          info.__name);

    // Queues are automatically created along with device, and we need to retrieve their handles.
    queues.resize(physical_device.queue_family_props.size());
    for (uint32_t fi = 0; fi < physical_device.queue_family_props.size(); fi++) {
        const auto& prop = physical_device.queue_family_props[fi];
        for (uint32_t index = 0; index < prop.count; index++) {
            auto queue = Queue::from(device, fi, index);
            const String name = "Queue." + std::to_string(fi) + "." + std::to_string(index);
            OnRet(setDebugName(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(queue.handle()), name.c_str()),
                  "Failed to set queue debug name: {}",
                  name);
            queues[fi].push_back(std::move(queue));
        }
    }

    queue_family_indices.present = findQueueFamilyIndex(physical_device.queue_family_props, 0);
    queue_family_indices.graphics = findQueueFamilyIndex(physical_device.queue_family_props, VK_QUEUE_GRAPHICS_BIT);
    queue_family_indices.compute = findQueueFamilyIndex(physical_device.queue_family_props, VK_QUEUE_COMPUTE_BIT);
    queue_family_indices.transfer = findQueueFamilyIndex(physical_device.queue_family_props, VK_QUEUE_TRANSFER_BIT);
    vktLogD("Selected queues: {{\n"
            "\tpresent: {}\n"
            "\tgraphics: {}\n"
            "\tcompute: {}\n"
            "\ttransfer: {}\n"
            "}}",
            queue_family_indices.present,
            queue_family_indices.graphics,
            queue_family_indices.compute,
            queue_family_indices.transfer);

    return Ok(newCRef(device));
}

Res<CRef<Device>> CoreApi::borrow(VkHandle<VkDevice> handle,
                                  QueueFamilyIndices indices,
                                  PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr) {
    if (!instance.__handle) {
        return Er("Must have borrowed a valid instance to initialize device");
    }
    if (!physical_device.__handle) {
        return Er("Must have borrowed a valid physical device");
    }
    OnErr(res, Device::borrow(newCRef(physical_device), handle, fpGetDeviceProcAddr));
    device = res.unwrap();

    // Only get one queue for each queue family
    queues.resize(indices.maxIndex() + 1);
    for (auto fi : std::initializer_list<uint32_t>{indices.present, indices.graphics, indices.compute, indices.transfer}) {
        if (fi != VK_QUEUE_FAMILY_IGNORED && queues[fi].empty()) {
            queues[fi].push_back(Queue::from(device, fi, 0));
        }
    }
    queue_family_indices = indices;

    return Ok(newCRef(device));
}

/**
 * @brief Get queue according to indices
 *
 * Queue reference is safe for CoreApi.queues will only initialize once at
 * CoreApi::init(DeviceState&) or CoreApi::borrow(VkDevice).
 */
Res<CRef<Queue>> CoreApi::getQueue(const uint32_t family_index, const uint32_t index) const {
    if (family_index < queues.size()) {
        const auto& que = queues[family_index];
        if (index < que.size()) {
            return Ok(newCRef(que[index]));
        } else {
            return Er("The queue index = {} is out of created queues = {}", index, que.size());
        }
    } else {
        return Er("The queue family index = {} is out of created queues = {}", family_index, queues.size());
    }
}

Res<CRef<IDebug>> CoreApi::add(DebugState& info) {
    if (!instance.__handle) {
        return Er("Must have initialized or borrowed a valid instance to add debug utils messenger");
    }
    OnErr(res, info.into(instance));
    debug = newBox<Debug>(res.unwrap());
    return Ok(newCRef(*debug));
}

Res<CRef<Surface>> CoreApi::add(VkHandle<VkSurfaceKHR> _surface, bool with_ownership) {
    if (!instance.__handle) {
        return Er("Must have initialized or borrowed a valid instance to add surface");
    }
    OnErr(res, with_ownership ? Surface::from(newCRef(instance), _surface) : Surface::borrow(newCRef(instance), _surface));
    surface = newBox<Surface>(res.unwrap());
    return Ok(newCRef(*surface));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
