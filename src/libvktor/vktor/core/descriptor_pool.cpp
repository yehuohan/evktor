#include "descriptor_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DescriptorPoolBuilder::Self;

DescriptorPool::DescriptorPool(DescriptorPool&& rhs)
    : BuiltResource(rhs.device, std::move(rhs.__name))
    , desc_setlayout(rhs.desc_setlayout)
    , maxsets(rhs.maxsets) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

DescriptorPool::~DescriptorPool() {
    if (handle) {
        // Descriptor set will be freed along with `vkDestroyDescriptorPool`
        vkDestroyDescriptorPool(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
    count = 0;
}

Res<DescriptorSet> DescriptorPool::allocate() {
    auto descset = DescriptorSet(*this);
    auto descset_ai = Itor::DescriptorSetAllocateInfo();
    descset_ai.descriptorPool = *this;
    descset_ai.descriptorSetCount = 1;
    descset_ai.pSetLayouts = desc_setlayout;
    OnRet(vkAllocateDescriptorSets(device, &descset_ai, descset), "Failed to allocate descriptor set");
    OnName(descset);

    count++;
    return Ok(std::move(descset));
}

bool DescriptorPool::available() const {
    return count < maxsets;
}

Self DescriptorPoolBuilder::setMaxsets(uint32_t maxsets) {
    info.maxsets = maxsets;
    return *this;
}

DescriptorPoolBuilder::Built DescriptorPoolBuilder::build() {
    DescriptorPool descriptor_pool(desc_setlayout, info.maxsets, std::move(info.__name));

    // Get poolsize from setlayout
    HashMap<VkDescriptorType, uint32_t> desc_types{};
    for (const auto& item : desc_setlayout.bindings) {
        const auto& binding = item.second;
        // HashMap operator[] will invoke uint32_t's default construct that will give 0
        desc_types[binding.descriptorType] += binding.descriptorCount;
    }
    Vector<VkDescriptorPoolSize> poolsizes{};
    for (const auto& t : desc_types) {
        poolsizes.push_back(VkDescriptorPoolSize{t.first, t.second * info.maxsets});
    }

    // VkDescriptorSetLayoutBinding: `descriptorCount` specifies the number of `descriptorType` of the set's `binding`;
    // VkDescriptorPoolSize: `descriptorCount` specifies the total number of `type` can be allocated from the pool;
    // VkDescriptorPoolCreateInfo: `maxSets` specifies the number of descriptor set can be allocated from the pool;
    auto descpool_ci = Itor::DescriptorPoolCreateInfo();
    descpool_ci.maxSets = info.maxsets;
    descpool_ci.poolSizeCount = u32(poolsizes.size());
    descpool_ci.pPoolSizes = poolsizes.data();
    OnRet(vkCreateDescriptorPool(desc_setlayout.device, &descpool_ci, nullptr, descriptor_pool),
          "Failed to create descriptor pool");
    OnName(descriptor_pool);

    return Ok(std::move(descriptor_pool));
}

DescriptorPooler::DescriptorPooler(DescriptorPooler&& rhs) : desc_setlayout(rhs.desc_setlayout) {
    desc_pools = std::move(rhs.desc_pools);
}

DescriptorPooler::~DescriptorPooler() {
    desc_pools.clear();
}

Res<Ref<DescriptorPool>> DescriptorPooler::get() {
    if (desc_pools.empty() || !desc_pools.back().available()) {
        auto res = DescriptorPoolBuilder(desc_setlayout).setMaxsets(VKt_CORE_MAX_SETS).build();
        if (res.isErr()) {
            return Err(res.unwrapErr());
        }
        desc_pools.push_back(res.unwrap());
    }

    return Ok(newRef(desc_pools.back()));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
