#pragma once
#include "__core.hpp"
#include "descriptor_set.hpp"
#include "descriptor_setlayout.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorPool;

class DescriptorPoolState : public CoreStater<DescriptorPoolState> {
    friend struct DescriptorPool;

private:
    uint32_t maxsets = 1;

public:
    explicit DescriptorPoolState(Name&& name = "DescriptorPool") : CoreStater(std::move(name)) {}

    Self setMaxsets(uint32_t maxsets);

    Res<DescriptorPool> into(const DescriptorSetLayout& setlayout) const;
};

struct DescriptorPool : public CoreResource<VkDescriptorPool, VK_OBJECT_TYPE_DESCRIPTOR_POOL, Device> {
    /** Descriptor set layout for pool (Must destroy this pool before free `desc_setlayout`) */
    const DescriptorSetLayout& desc_setlayout;
    const uint32_t maxsets;

    /** Counter for allocated descriptor set from this pool */
    uint32_t count = 0;

    DescriptorPool(const DescriptorSetLayout& setlayout, const uint32_t maxsets)
        : CoreResource(setlayout.device)
        , desc_setlayout(setlayout)
        , maxsets(maxsets) {}
    DescriptorPool(DescriptorPool&&);
    ~DescriptorPool();
    OnConstType(VkDescriptorSetLayout, desc_setlayout.handle);
    /**
     * @brief Allocate once descriptor set
     *
     * This `DescriptorPool` doesn't store allocated `DescriptorSet`, so return DescriptorSet.
     */
    Res<DescriptorSet> allocate(const Name& name = "DescriptorSet");
    bool free(const DescriptorSet& descset);
    bool available() const;

    /**
     * @brief Create descriptor set pool
     *
     * This need DescriptorSetLayout::bindings, so get Device from DescriptorSetLayout for creation
     */
    static Res<DescriptorPool> from(const DescriptorSetLayout& setlayout, const DescriptorPoolState& info);
};

/**
 * @brief A array-like DescriptorPool provider
 */
class DescriptorPooler : private NonCopyable {
private:
    Vector<DescriptorPool> desc_pools{};

public:
    const DescriptorSetLayout& desc_setlayout;

    explicit DescriptorPooler(const DescriptorSetLayout& setlayout) : desc_setlayout(setlayout) {}
    DescriptorPooler(DescriptorPooler&&);
    ~DescriptorPooler();

    Res<Ref<DescriptorPool>> get();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::DescriptorPool> {
    size_t operator()(const vkt::core::DescriptorPool& desc_pool) const {
        return hash<VkDescriptorPool>{}(desc_pool);
    }
};

NAMESPACE_END(std)
