#include "fence.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = FenceState::Self;

Self FenceState::setFlags(VkFenceCreateFlags flags) {
    fence_ci.flags = flags;
    return *this;
}

Res<Fence> FenceState::into(const CoreApi& api) const {
    return Fence::from(api, *this);
}

Fence::Fence(Fence&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Fence::~Fence() {
    if (!__borrowed && handle) {
        vkDestroyFence(api, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

VkResult Fence::wait(uint64_t timeout) const {
    return vkWaitForFences(api, 1, &handle, VK_TRUE, timeout);
}

VkResult Fence::reset() const {
    return vkResetFences(api, 1, &handle);
}

Res<Fence> Fence::from(const CoreApi& api, const FenceState& info) {
    Fence fence(api);

    OnRet(vkCreateFence(api, &info.fence_ci, nullptr, fence), "Failed to create fence");
    OnName(fence, info.__name);

    return Ok(std::move(fence));
}

FencePool::FencePool(FencePool&& rhs) : api(rhs.api) {
    active_count = rhs.active_count;
    rhs.active_count = 0;
    fences = std::move(rhs.fences);
    fences_cache = std::move(rhs.fences_cache);
}

FencePool::~FencePool() {
    fences.clear();
    fences_cache.clear();
}

Res<CRef<Fence>> FencePool::request() {
    if (active_count < fences.size()) {
        return Ok(newCRef(fences[active_count++]));
    }

    auto res = FenceState().into(api);
    OnErr(res);
    fences.push_back(res.unwrap());
    active_count++;
    return Ok(newCRef(fences.back()));
}

Res<Fence> FencePool::acquire() {
    if (active_count < fences.size()) {
        auto fen = std::move(fences.back());
        fences.pop_back();
        return Ok(std::move(fen));
    }
    return FenceState().into(api);
}

void FencePool::reback(Fence&& fence) {
    fences_cache.push_back(std::move(fence));
}

VkResult FencePool::waitPool(uint64_t timeout) {
    VkResult ret = VK_SUCCESS;

    if (active_count > 0) {
        Vector<VkFence> actived{};
        for (uint32_t k = 0; k < active_count; k++) {
            actived.push_back(fences[k]);
        }
        ret = vkWaitForFences(api, active_count, actived.data(), true, timeout);
    }

    return ret;
}

VkResult FencePool::resetPool() {
    VkResult ret = VK_SUCCESS;

    if (active_count > 0) {
        Vector<VkFence> actived{};
        for (uint32_t k = 0; k < active_count; k++) {
            actived.push_back(fences[k]);
        }
        // Only reset actived fences.
        // The cached fences should be reset manually.
        ret = vkResetFences(api, active_count, actived.data());
    }
    active_count = 0;
    for (auto& fen : fences_cache) {
        fences.push_back(std::move(fen));
    }
    fences_cache.clear();

    return ret;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
