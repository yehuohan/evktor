#include "fence.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = FenceState::Self;

Self FenceState::setFlags(VkFenceCreateFlags flags) {
    fence_ci.flags = flags;
    return *this;
}

Res<Fence> FenceState::into(const Device& device) const {
    return Fence::from(device, *this);
}

Fence::Fence(Fence&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

Fence::~Fence() {
    if (!__borrowed && handle) {
        vkDestroyFence(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

VkResult Fence::wait(uint64_t timeout) const {
    return vkWaitForFences(device, 1, &handle, VK_TRUE, timeout);
}

VkResult Fence::reset() const {
    return vkResetFences(device, 1, &handle);
}

Res<Fence> Fence::from(const Device& device, const FenceState& info) {
    Fence fence(device);

    OnRet(vkCreateFence(device, &info.fence_ci, nullptr, fence), "Failed to create fence");
    OnName(fence, info.__name);

    return Ok(std::move(fence));
}

FencePool::FencePool(FencePool&& rhs) : device(rhs.device) {
    fences = std::move(rhs.fences);
}

FencePool::~FencePool() {
    fences.clear();
}

Res<Ref<Fence>> FencePool::request() {
    if (active_count < fences.size()) {
        return Ok(newRef(fences[active_count++]));
    }

    auto res = FenceState().into(device);
    OnErr(res);
    fences.push_back(res.unwrap());
    active_count++;
    return Ok(newRef(fences.back()));
}

void FencePool::resetPool() {
    active_count = 0;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
