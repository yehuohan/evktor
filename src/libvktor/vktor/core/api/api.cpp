#define VOLK_IMPLEMENTATION
#define VMA_IMPLEMENTATION
#include "api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Res<CRef<Instance>> CoreApiState::init(InstanceState& info) {
    // Must reset instance before info.into()
    instance.reset();
    auto res = info.into();
    OnErr(res);
    instance = newBox<Instance>(res.unwrap());
    return Ok(newCRef(*instance));
}

Res<CRef<PhysicalDevice>> CoreApiState::init(PhysicalDeviceState& info) {
    if (!instance) {
        return Er("Must have initialized a valid instance");
    }
    // Must reset physical device before info.into()
    physical_device.reset();
    auto res = info.into(*instance);
    OnErr(res);
    physical_device = newBox<PhysicalDevice>(res.unwrap());
    return Ok(newCRef(*physical_device));
}

Res<CRef<Device>> CoreApiState::init(DeviceState& info) {
    if (!instance) {
        return Er("Must have initialized a valid instance");
    }
    if (!physical_device) {
        return Er("Must have initialized a valid physical device");
    }
    // Must reset device before info.into()
    device.reset();
    auto res = info.into(*instance, *physical_device);
    OnErr(res);
    device = newBox<Device>(res.unwrap());
    return Ok(newCRef(*device));
}

Res<CoreApi> CoreApiState::into() {
    if (!instance) {
        return Er("Must have initialized a valid instance");
    }
    if (!physical_device) {
        return Er("Must have initialized a valid physical device");
    }
    if (!device) {
        return Er("Must have initialized a valid device");
    }
    return Ok(CoreApi(std::move(*instance), std::move(*physical_device), std::move(*device)));
}

CoreApi::CoreApi(CoreApi&& rhs)
    : instance(std::move(rhs.instance))
    , physical_device(std::move(rhs.physical_device))
    , device(std::move(rhs.device)) {}

Res<CRef<Queue>> CoreApi::presentQueue() const {
    if (device.queues.present) {
        return Ok(newCRef(*device.queues.present));
    } else {
        return Er("Present queue is not supported");
    }
}

Res<CRef<Queue>> CoreApi::graphicsQueue() const {
    if (device.queues.graphics) {
        return Ok(newCRef(*device.queues.graphics));
    } else {
        return Er("Graphics queue is not supported");
    }
}

Res<CRef<Queue>> CoreApi::computeQueue() const {
    if (device.queues.compute) {
        return Ok(newCRef(*device.queues.compute));
    } else {
        return Er("Compute queue is not supported");
    }
}

Res<CRef<Queue>> CoreApi::transferQueue() const {
    if (device.queues.transfer) {
        return Ok(newCRef(*device.queues.transfer));
    } else {
        return Er("Transfer queue is not supported");
    }
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
