#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Fence;

class FenceState : public CoreStater<FenceState> {
    friend struct Fence;

private:
    VkFenceCreateInfo fence_ci{};

public:
    explicit FenceState(Name&& name = "Fence") : CoreStater(std::move(name)) {
        fence_ci = Itor::FenceCreateInfo();
    }

    Self setFlags(VkFenceCreateFlags flags);

    Res<Fence> into(const Device& device) const;
};

struct Fence : public CoreResource<VkFence, VK_OBJECT_TYPE_FENCE, Device> {
protected:
    explicit Fence(const Device& device) : CoreResource(device) {}

public:
    Fence(Fence&&);
    ~Fence();

    VkResult wait(uint64_t timeout = UINT64_MAX) const;
    VkResult reset() const;

    static Res<Fence> from(const Device& device, const FenceState& info);
};

class FencePool : private NonCopyable {
private:
    uint32_t active_count = 0;
    /** Actived fences */
    Vector<Fence> fences{};
    /** Cached fences */
    Vector<Fence> fences_cache{};

public:
    const Device& device;

    explicit FencePool(const Device& device) : device(device) {}
    FencePool(FencePool&&);
    ~FencePool();

    /** Request fence without ownership */
    Res<CRef<Fence>> request();
    /** Acquire fence with ownership */
    Res<Fence> acquire();
    /** Reback acquired fence with ownership */
    void reback(Fence&& fence);
    /** Wait actived fences */
    VkResult waitPool(uint64_t timeout = UINT64_MAX);
    /** Reset actived fences and reback cached fences */
    VkResult resetPool();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
