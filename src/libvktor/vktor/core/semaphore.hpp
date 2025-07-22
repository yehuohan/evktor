#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Semaphore;

class SemaphoreState : public CoreStater<SemaphoreState> {
    friend struct Semaphore;

private:
    VkSemaphoreCreateInfo semaphore_ci{};

public:
    explicit SemaphoreState(String&& name = "Semaphore") : CoreStater(std::move(name)) {
        semaphore_ci = Itor::SemaphoreCreateInfo();
    }

    Self setFlags(VkSemaphoreCreateFlags flags);

    Res<Semaphore> into(const CoreApi& api) const;
};

struct Semaphore : public CoreResource<VkSemaphore, VK_OBJECT_TYPE_SEMAPHORE> {
protected:
    explicit Semaphore(const CoreApi& api) : CoreResource(api) {}

public:
    Semaphore(Semaphore&&);
    ~Semaphore();

    static Res<Semaphore> from(const CoreApi& api, const SemaphoreState& info);
};

class SemaphorePool : private NonCopyable {
private:
    uint32_t active_count = 0;
    /** Actived semaphores */
    Vector<Semaphore> semaphores{};
    /** Cached semaphores */
    Vector<Semaphore> semaphores_cache{};

public:
    const CoreApi& api;

    explicit SemaphorePool(const CoreApi& api) : api(api) {}
    SemaphorePool(SemaphorePool&&);
    ~SemaphorePool();

    /** Request semaphore without ownership */
    Res<CRef<Semaphore>> request();
    /** Acquire semaphore with ownership */
    Res<Semaphore> acquire();
    /** Reback acquired semaphore with ownership */
    void reback(Semaphore&& semaphore);
    /** Reset actived semaphores and cached semaphores*/
    void resetPool();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
