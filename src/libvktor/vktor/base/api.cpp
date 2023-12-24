#include "api.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<Ref<Queue>> BaseApi::presentQueue() const {
    assert(dev && "Device is invalid");
    if (dev->queues.present) {
        return Ok(newRef(*dev->queues.present));
    } else {
        return Er("Present queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::graphicsQueue() const {
    assert(dev && "Device is invalid");
    if (dev->queues.graphics) {
        return Ok(newRef(*dev->queues.graphics));
    } else {
        return Er("Graphics queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::computeQueue() const {
    assert(dev && "Device is invalid");
    if (dev->queues.compute) {
        return Ok(newRef(*dev->queues.compute));
    } else {
        return Er("Compute queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::transferQueue() const {
    assert(dev && "Device is invalid");
    if (dev->queues.transfer) {
        return Ok(newRef(*dev->queues.transfer));
    } else {
        return Er("Transfer queue is not supported");
    }
}

NAMESPACE_END(vkt)
