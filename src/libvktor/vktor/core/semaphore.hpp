#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Semaphore;

class SemaphoreState : public CoreStater<SemaphoreState> {
    friend struct Semaphore;

private:
    VkSemaphoreCreateInfo semaphore_ci{};

public:
    explicit SemaphoreState(Name&& name = "Semaphore") : CoreStater(std::move(name)) {
        semaphore_ci = Itor::SemaphoreCreateInfo();
    }

    Self setFlags(VkSemaphoreCreateFlags flags);

    Res<Semaphore> into(const Device& device) const;
};

struct Semaphore : public CoreResource<VkSemaphore, VK_OBJECT_TYPE_SEMAPHORE, Device> {
protected:
    explicit Semaphore(const Device& device) : CoreResource(device) {}

public:
    Semaphore(Semaphore&&);
    ~Semaphore();

    static Res<Semaphore> from(const Device& device, const SemaphoreState& info);
};

class SemaphorePool : private NonCopyable {
private:
    uint32_t active_count = 0;
    /** Actived semaphores */
    Vector<Semaphore> semaphores{};
    /** Cached semaphores */
    Vector<Semaphore> semaphores_cache{};

public:
    const Device& device;

    explicit SemaphorePool(const Device& device) : device(device) {}
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
