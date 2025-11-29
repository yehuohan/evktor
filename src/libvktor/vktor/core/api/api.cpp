#include "api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Res<CRef<Instance>> CoreApi::init(InstanceState& info) {
    auto res = info.into();
    OnErr(res);
    instance = std::move(res.unwrap());

    // Reset objects that depends on instance
    debug = newBox<IDebug>();

    return Ok(newCRef(instance));
}

Res<CRef<PhysicalDevice>> CoreApi::init(PhysicalDeviceState& info) {
    if (!instance.handle) {
        return Er("Must have initialized a valid instance to initialize physical device");
    }
    auto res = info.into(newCRef(instance));
    OnErr(res);
    physical_device = std::move(res.unwrap());
    return Ok(newCRef(physical_device));
}

static uint32_t findQueueFamilyIndex(const HashMap<uint32_t, QueueFamilyProps>& props, VkQueueFlags flags) {
    // Find present queue
    if (flags == 0) {
        uint32_t index = VK_QUEUE_FAMILY_IGNORED;
        for (const auto& q : props) {
            const auto& prop = q.second;
            if (prop.present && !prop.graphics) {
                return q.first;
            }
            if (prop.present) {
                index = q.first;
            }
        }
        return index;
    }

    // Prefer dedicated queue
    const VkQueueFlags tmp = VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
    for (const auto& q : props) {
        const auto& prop = q.second;
        if ((prop.flags & tmp) == flags) {
            return q.first;
        }
    }

    // Prefer non-graphics queue
    uint32_t index = VK_QUEUE_FAMILY_IGNORED;
    for (const auto& q : props) {
        const auto& prop = q.second;
        if ((prop.flags & flags) && (!prop.graphics)) {
            return q.first;
        }
        if (prop.flags & flags) {
            index = q.first;
        }
    }
    return index;

    return VK_QUEUE_FAMILY_IGNORED;
}

Res<CRef<Device>> CoreApi::init(DeviceState& info) {
    if (!instance.handle) {
        return Er("Must have initialized a valid instance to initialize device");
    }
    if (!physical_device.handle) {
        return Er("Must have initialized a valid physical device");
    }
    auto res = info.into(newCRef(physical_device));
    OnErr(res);
    device = std::move(res.unwrap());

    OnRet(setDebugName(VK_OBJECT_TYPE_DEVICE, reinterpret_cast<uint64_t>(device.handle), info.__name.c_str()),
          "Failed to set debug name: {}",
          info.__name);

    // Queues are automatically created along with device, and we need to retrieve their handles.
    queues.clear();
    for (const auto& q : physical_device.queue_family_props) {
        uint32_t family_index = q.first;
        const auto& prop = q.second;
        for (uint32_t index = 0; index < prop.count; index++) {
            Queue queue(family_index, index);
            vkGetDeviceQueue(device, family_index, index, queue);

            const String name = "Queue" + std::to_string(family_index) + "." + std::to_string(index);
            OnRet(setDebugName(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(queue.handle), name.c_str()),
                  "Failed to set debug name: {}",
                  name);

            queues[family_index].push_back(std::move(queue));
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

static Res<CRef<Queue>> getQueue(const HashMap<uint32_t, Vector<Queue>>& queues,
                                 const uint32_t family_index,
                                 const uint32_t index) {
    auto& list = queues.at(family_index);
    if (index < list.size()) {
        return Ok(newCRef(list[index]));
    } else {
        return Er("The queue index = {} is out of created family queues = {}", index, family_index);
    }
}

Res<CRef<Queue>> CoreApi::presentQueue(const uint32_t index) const {
    if (queue_family_indices.present != VK_QUEUE_FAMILY_IGNORED) {
        return getQueue(queues, queue_family_indices.present, index);
    } else {
        return Er("Present queue is not supported");
    }
}

Res<CRef<Queue>> CoreApi::graphicsQueue(const uint32_t index) const {
    if (queue_family_indices.graphics != VK_QUEUE_FAMILY_IGNORED) {
        return getQueue(queues, queue_family_indices.graphics, index);
    } else {
        return Er("Graphics queue is not supported");
    }
}

Res<CRef<Queue>> CoreApi::computeQueue(const uint32_t index) const {
    if (queue_family_indices.compute != VK_QUEUE_FAMILY_IGNORED) {
        return getQueue(queues, queue_family_indices.compute, index);
    } else {
        return Er("Compute queue is not supported");
    }
}

Res<CRef<Queue>> CoreApi::transferQueue(const uint32_t index) const {
    if (queue_family_indices.transfer != VK_QUEUE_FAMILY_IGNORED) {
        return getQueue(queues, queue_family_indices.transfer, index);
    } else {
        return Er("Transfer queue is not supported");
    }
}

Res<CRef<IDebug>> CoreApi::add(DebugState& info) {
    if (!instance.handle) {
        return Er("Must have initialized a valid instance to initialize debug");
    }
    auto res = info.into(instance);
    OnErr(res);
    debug = newBox<Debug>(res.unwrap());
    return Ok(newCRef(*debug));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
