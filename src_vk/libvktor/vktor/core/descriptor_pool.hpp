#pragma once
#include "__core.hpp"
#include "descriptor_set.hpp"
#include "descriptor_setlayout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorPool;

class DescriptorPoolState : public CoreState<DescriptorPoolState> {
    friend struct DescriptorPool;

private:
    VkDescriptorPoolCreateFlags flags = 0;
    uint32_t maxsets = 1;

public:
    explicit DescriptorPoolState(String&& name = "DescriptorPool") : CoreState(std::move(name)) {}

    Self setFlags(VkDescriptorPoolCreateFlags flags);
    Self setMaxsets(uint32_t maxsets);

    Res<DescriptorPool> into(const DescriptorSetLayout& setlayout) const;
};

struct DescriptorPool : public CoreResource<VkDescriptorPool, VK_OBJECT_TYPE_DESCRIPTOR_POOL> {
    /** Descriptor set layout for pool (Must destroy this pool before free `desc_setlayout`) */
    const DescriptorSetLayout& desc_setlayout;
    const uint32_t maxsets;

private:
    VkDescriptorPoolCreateFlags flags = 0;
    /** Counter for allocated descriptor set from this pool */
    uint32_t count = 0;

protected:
    explicit DescriptorPool(const DescriptorSetLayout& setlayout, const uint32_t maxsets)
        : CoreResource(setlayout.api)
        , desc_setlayout(setlayout)
        , maxsets(maxsets) {}

public:
    DescriptorPool(DescriptorPool&&);
    ~DescriptorPool();
    OnConstType(VkDescriptorSetLayout, desc_setlayout.getHandle());
    /**
     * @brief Allocate once descriptor set
     *
     * This DescriptorPool doesn't store allocated DescriptorSet, so return DescriptorSet.
     */
    Res<DescriptorSet> allocate(const void* next = nullptr, const String& name = "DescriptorSet");
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

    Res<Ref<DescriptorPool>> request();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
