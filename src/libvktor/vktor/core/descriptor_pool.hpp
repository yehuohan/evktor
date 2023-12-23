#pragma once
#include "__builder.hpp"
#include "descriptor_set.hpp"
#include "descriptor_setlayout.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorPool : public BuiltResource<VkDescriptorPool, VK_OBJECT_TYPE_DESCRIPTOR_POOL, Device> {
    /** Descriptor set layout for pool (Must destroy this pool before free `desc_setlayout`) */
    const DescriptorSetLayout& desc_setlayout;
    const uint32_t maxsets;

    /** Counter for allocated descriptor set from this pool */
    uint32_t count = 0;

    DescriptorPool(const DescriptorSetLayout& setlayout, const uint32_t maxsets, Name&& name)
        : BuiltResource(setlayout.device, std::move(name))
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
    Res<DescriptorSet> allocate();
    bool available() const;
};

struct DescriptorPoolInfo : public BuilderInfo {
    uint32_t maxsets = 1;
};

class DescriptorPoolBuilder : public Builder<DescriptorPoolBuilder, DescriptorPool, DescriptorPoolInfo> {
private:
    const DescriptorSetLayout& desc_setlayout;

public:
    explicit DescriptorPoolBuilder(const DescriptorSetLayout& setlayout, Name&& name = "DescriptorPool")
        : Builder(std::move(name))
        , desc_setlayout(setlayout) {}
    virtual Built build() override;

    Self setMaxsets(uint32_t maxsets);
};

/**
 * @brief A array-like struct to provide DescriptorPool
 */
struct DescriptorPooler : private NonCopyable {
    const DescriptorSetLayout& desc_setlayout;

    DescriptorPooler(const DescriptorSetLayout& setlayout) : desc_setlayout(setlayout) {}
    DescriptorPooler(DescriptorPooler&&);
    ~DescriptorPooler();

    Res<Ref<DescriptorPool>> get();

private:
    Vector<DescriptorPool> desc_pools{};
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
