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

Res<CRef<IDebug>> CoreApiState::init(DebugState& info) {
    if (!instance) {
        return Er("Must have initialized a valid instance to initialize debug");
    }
    // Must reset debug before info.into()
    debug.reset();
    auto res = info.into(*instance);
    OnErr(res);
    debug = newBox<Debug>(res.unwrap());
    return Ok(newCRef(*debug));
}

Res<CRef<PhysicalDevice>> CoreApiState::init(PhysicalDeviceState& info) {
    if (!instance) {
        return Er("Must have initialized a valid instance to initialize physical device");
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
        return Er("Must have initialized a valid instance to initialize device");
    }
    if (!physical_device) {
        return Er("Must have initialized a valid physical device");
    }
    // Must reset device before info.into()
    device.reset();
    auto res = info.into(*instance, *physical_device, *debug);
    OnErr(res);
    device = newBox<Device>(res.unwrap());
    return Ok(newCRef(*device));
}

Res<Box<CoreApi>> CoreApiState::into() {
    if (!instance) {
        return Er("Must have initialized a valid instance");
    }
    if (!physical_device) {
        return Er("Must have initialized a valid physical device");
    }
    if (!device) {
        return Er("Must have initialized a valid device");
    }
    return Ok(newBox<CoreApi>(std::move(*instance), std::move(*physical_device), std::move(*device), std::move(debug)));
}

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
