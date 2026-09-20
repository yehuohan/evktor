#include "semaphore.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SemaphoreState::Self;

Self SemaphoreState::setFlags(VkSemaphoreCreateFlags flags) {
    semaphore_ci.flags = flags;
    return *this;
}

Res<Semaphore> SemaphoreState::into(const CoreApi& api) const {
    return Semaphore::from(api, *this);
}

VkResult VkhSemaphore::wait(uint64_t value, uint64_t timeout) const {
    auto info = Itor::SemaphoreWaitInfo();
    info.pValues = &value;
    info.pSemaphores = &__handle;
    info.semaphoreCount = 1;
    return vkWaitSemaphores(parent(), &info, timeout);
}

VkResult VkhSemaphore::signal(uint64_t value) const {
    auto info = Itor::SemaphoreSignalInfo();
    info.semaphore = handle();
    info.value = value;
    return vkSignalSemaphore(parent(), &info);
}

VkResult VkhSemaphore::getCounter(uint64_t* pvalue) const {
    return vkGetSemaphoreCounterValue(parent(), handle(), pvalue);
}

Semaphore::~Semaphore() {
    if (!borrowed() && __handle) {
        vkDestroySemaphore(api, __handle, api);
        __handle = VK_NULL_HANDLE;
    }
}

Res<Semaphore> Semaphore::from(const CoreApi& api, const SemaphoreState& info) {
    Semaphore semaphore(api);

    info.semaphore_ci.pNext = info.__next;
    OnRet(vkCreateSemaphore(api, &info.semaphore_ci, api, semaphore), "Failed to create semaphore: {}", info.__name);
    OnName(semaphore, info.__name);

    return Ok(std::move(semaphore));
}

SemaphorePool::SemaphorePool(SemaphorePool&& rhs) : api(rhs.api) {
    active_count = rhs.active_count;
    rhs.active_count = 0;
    semaphores = std::move(rhs.semaphores);
    semaphores_cache = std::move(rhs.semaphores_cache);
}

SemaphorePool::~SemaphorePool() {
    semaphores.clear();
    semaphores_cache.clear();
}

Res<VkhSemaphore> SemaphorePool::request(String&& name) {
    if (active_count < semaphores.size()) {
        return Ok(semaphores[active_count++].vkhandle());
    }

    OnErr(res, SemaphoreState(std::move(name)).into(api));
    semaphores.push_back(res.unwrap());
    active_count++;
    return Ok(semaphores.back().vkhandle());
}

Res<Semaphore> SemaphorePool::acquire(String&& name) {
    if (active_count < semaphores.size()) {
        auto sem = std::move(semaphores.back());
        semaphores.pop_back();
        return Ok(std::move(sem));
    }
    return SemaphoreState(std::move(name)).into(api);
}

void SemaphorePool::reback(Semaphore&& semaphore) {
    semaphores_cache.push_back(std::move(semaphore));
}

void SemaphorePool::resetPool() {
    active_count = 0;
    for (auto& sem : semaphores_cache) {
        semaphores.push_back(std::move(sem));
    }
    semaphores_cache.clear();
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
