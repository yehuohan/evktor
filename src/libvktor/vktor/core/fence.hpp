#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Fence;

class FenceState : public CoreState<FenceState> {
    friend struct Fence;

private:
    mutable VkFenceCreateInfo fence_ci{};

public:
    explicit FenceState(String&& name = "Fence") : CoreState(std::move(name)) {
        fence_ci = Itor::FenceCreateInfo();
    }

    Self setFlags(VkFenceCreateFlags flags);

    Res<Fence> into(const CoreApi& api) const;
};

struct Fence : public CoreResource<VkFence, VK_OBJECT_TYPE_FENCE> {
protected:
    explicit Fence(const CoreApi& api) : CoreResource(api) {}

public:
    Fence(Fence&&);
    ~Fence();

    VkResult wait(uint64_t timeout = UINT64_MAX) const;
    VkResult reset() const;

    static Res<Fence> from(const CoreApi& api, const FenceState& info);
};

class FencePool : private NonCopyable {
private:
    uint32_t active_count = 0;
    /** Actived fences */
    Vector<Fence> fences{};
    /** Cached fences */
    Vector<Fence> fences_cache{};

public:
    const CoreApi& api;

    explicit FencePool(const CoreApi& api) : api(api) {}
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
