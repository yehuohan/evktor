#define VOLK_IMPLEMENTATION
#include "api.hpp"
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include "vktor/rendering/render_pipeline.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<CRef<Instance>> BaseApi::init(InstanceState& info) {
    auto res = info.into();
    OnErr(res);
    instance.reset();
    instance = newBox<Instance>(res.unwrap());
    return Ok(newCRef(*instance));
}

Res<CRef<PhysicalDevice>> BaseApi::init(PhysicalDeviceState& info) {
    auto res = info.into(*this);
    OnErr(res);
    phy_dev.reset();
    phy_dev = newBox<PhysicalDevice>(res.unwrap());
    return Ok(newCRef(*phy_dev));
}

Res<CRef<Device>> BaseApi::init(DeviceState& info) {
    auto res = info.into(*this, *this);
    OnErr(res);
    dev.reset();
    dev = newBox<Device>(res.unwrap());
    return Ok(newCRef(*dev));
}

Res<CRef<Queue>> BaseApi::presentQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.present) {
        return Ok(newCRef(*dev->queues.present));
    } else {
        return Er("Present queue is not supported");
    }
}

Res<CRef<Queue>> BaseApi::graphicsQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.graphics) {
        return Ok(newCRef(*dev->queues.graphics));
    } else {
        return Er("Graphics queue is not supported");
    }
}

Res<CRef<Queue>> BaseApi::computeQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.compute) {
        return Ok(newCRef(*dev->queues.compute));
    } else {
        return Er("Compute queue is not supported");
    }
}

Res<CRef<Queue>> BaseApi::transferQueue() const {
    OnCheck(dev, "Device is invalid");
    if (dev->queues.transfer) {
        return Ok(newCRef(*dev->queues.transfer));
    } else {
        return Er("Transfer queue is not supported");
    }
}

NAMESPACE_END(vkt)
