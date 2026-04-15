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
    uint32_t maxsets = VKT_CORE_MAX_SETS;
    mutable Vector<VkDescriptorPoolSize> poolsizes{};

public:
    explicit DescriptorPoolState(String&& name = "DescriptorPool") : CoreState(std::move(name)) {}

    Self setFlags(VkDescriptorPoolCreateFlags flags);
    Self setMaxsets(uint32_t maxsets);
    /** @brief Add descriptor type and count for one descriptor set */
    Self addPoolSize(VkDescriptorType type, uint32_t count);
    Self addPoolSize(VkDescriptorPoolSize poolsize);
    Self setFromSetLayout(const DescriptorSetLayout& setlayout);

    Res<DescriptorPool> into(const CoreApi& api) const;
};

struct DescriptorPool : public CoreResource<VkDescriptorPool, VK_OBJECT_TYPE_DESCRIPTOR_POOL> {
    const uint32_t maxsets;

private:
    VkDescriptorPoolCreateFlags flags = 0;
    /** Counter for allocated descriptor set from this pool */
    uint32_t count = 0;

protected:
    explicit DescriptorPool(const CoreApi& api, const uint32_t maxsets) : CoreResource(api), maxsets(maxsets) {}

public:
    DescriptorPool(DescriptorPool&&);
    ~DescriptorPool();
    /**
     * @brief Allocate once descriptor set
     *
     * This DescriptorPool doesn't store allocated DescriptorSet, so return DescriptorSet.
     */
    Res<DescriptorSet> allocate(VkDescriptorSetLayout setlayout,
                                const void* next = nullptr,
                                const String& name = "DescriptorSet");
    bool free(const DescriptorSet& descset);
    bool available() const;

    static Res<DescriptorPool> from(const CoreApi& api, const DescriptorPoolState& info);
};

/**
 * @brief A array-like DescriptorPool provider
 */
class DescriptorPooler : private NonCopyable {
private:
    Vector<DescriptorPool> desc_pools{};

public:
    explicit DescriptorPooler() {}
    DescriptorPooler(DescriptorPooler&&);
    ~DescriptorPooler();

    Res<Ref<DescriptorPool>> request(const DescriptorSetLayout& setlayout, String&& name = "DescriptorSetPool");
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
