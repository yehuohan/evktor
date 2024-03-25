#define VOLK_IMPLEMENTATION
#include "api.hpp"
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include "vktor/rendering/render_pipeline.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<Ref<Instance>> BaseApi::init(InstanceState& info) {
    auto res = info.into();
    OnErr(res);
    instance.reset();
    instance = newBox<Instance>(res.unwrap());
    return Ok(newRef(*instance));
}

Res<Ref<PhysicalDevice>> BaseApi::init(PhysicalDeviceState& info) {
    auto res = info.into(*this);
    OnErr(res);
    phy_dev.reset();
    phy_dev = newBox<PhysicalDevice>(res.unwrap());
    return Ok(newRef(*phy_dev));
}

Res<Ref<Device>> BaseApi::init(DeviceState& info) {
    auto res = info.into(*this, *this);
    OnErr(res);
    dev.reset();
    dev = newBox<Device>(res.unwrap());
    return Ok(newRef(*dev));
}

Res<Ref<Queue>> BaseApi::presentQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.present) {
        return Ok(newRef(*dev->queues.present));
    } else {
        return Er("Present queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::graphicsQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.graphics) {
        return Ok(newRef(*dev->queues.graphics));
    } else {
        return Er("Graphics queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::computeQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.compute) {
        return Ok(newRef(*dev->queues.compute));
    } else {
        return Er("Compute queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::transferQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.transfer) {
        return Ok(newRef(*dev->queues.transfer));
    } else {
        return Er("Transfer queue is not supported");
    }
}

NAMESPACE_END(vkt)
