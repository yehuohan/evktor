#include "semaphore.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SemaphoreState::Self;

Self SemaphoreState::setFlags(VkSemaphoreCreateFlags flags) {
    semaphore_ci.flags = flags;
    return *this;
}

Res<Semaphore> SemaphoreState::into(const Device& device) const {
    return Semaphore::from(device, *this);
}

Semaphore::Semaphore(Semaphore&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

Semaphore::~Semaphore() {
    if (!__borrowed && handle) {
        vkDestroySemaphore(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<Semaphore> Semaphore::from(const Device& device, const SemaphoreState& info) {
    Semaphore semaphore(device);

    OnRet(vkCreateSemaphore(device, &info.semaphore_ci, nullptr, semaphore), "Failed to create semaphore");
    OnName(semaphore, info.__name);

    return Ok(std::move(semaphore));
}

SemaphorePool::SemaphorePool(SemaphorePool&& rhs) : device(rhs.device) {
    semaphores = std::move(rhs.semaphores);
}

SemaphorePool::~SemaphorePool() {
    semaphores.clear();
}

Res<Ref<Semaphore>> SemaphorePool::request() {
    if (active_count < semaphores.size()) {
        return Ok(newRef(semaphores[active_count++]));
    }

    auto res = SemaphoreState().into(device);
    OnErr(res);
    semaphores.push_back(res.unwrap());
    active_count++;
    return Ok(newRef(semaphores.back()));
}

void SemaphorePool::resetPool() {
    active_count = 0;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
