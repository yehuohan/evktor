#include "descriptor_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DescriptorPoolState::Self;

Self DescriptorPoolState::setFlags(VkDescriptorPoolCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self DescriptorPoolState::setMaxsets(uint32_t _maxsets) {
    maxsets = _maxsets;
    return *this;
}

Res<DescriptorPool> DescriptorPoolState::into(const DescriptorSetLayout& setlayout) const {
    return DescriptorPool::from(setlayout, *this);
}

DescriptorPool::DescriptorPool(DescriptorPool&& rhs)
    : CoreResource(rhs.api)
    , desc_setlayout(rhs.desc_setlayout)
    , maxsets(rhs.maxsets) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

DescriptorPool::~DescriptorPool() {
    if (!__borrowed && handle) {
        // Descriptor set will be freed along with vkDestroyDescriptorPool
        vkDestroyDescriptorPool(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
    count = 0;
}

Res<DescriptorSet> DescriptorPool::allocate(const void* next, const String& name) {
    auto descset = DescriptorSet(*this);
    auto descset_ai = Itor::DescriptorSetAllocateInfo(next);
    descset_ai.descriptorPool = *this;
    descset_ai.descriptorSetCount = 1;
    descset_ai.pSetLayouts = desc_setlayout;
    OnRet(vkAllocateDescriptorSets(api, &descset_ai, descset), "Failed to allocate descriptor set");
    OnName(descset, name);

    count++;
    return Ok(std::move(descset));
}

bool DescriptorPool::free(const DescriptorSet& descset) {
    if (descset.getHandle()) {
        auto res = vkFreeDescriptorSets(api, *this, 1, &descset.getHandle());
        if (res == VK_SUCCESS) {
            count--;
            return true;
        } else {
            vktLogE("Failed to free descriptor set: {}", fmt::ptr(descset.getHandle()));
        }
    } else {
        vktLogW("Try to free a null descriptor set");
    }
    return false;
}

bool DescriptorPool::available() const {
    return count < maxsets;
}

Res<DescriptorPool> DescriptorPool::from(const DescriptorSetLayout& setlayout, const DescriptorPoolState& info) {
    DescriptorPool descriptor_pool(setlayout, info.maxsets);

    // Get poolsize from setlayout
    HashMap<VkDescriptorType, uint32_t> desc_types{};
    for (const auto& item : setlayout.bindings) {
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
    auto descpool_ci = Itor::DescriptorPoolCreateInfo(info.__next);
    descpool_ci.flags = info.flags;
    descpool_ci.maxSets = info.maxsets;
    descpool_ci.poolSizeCount = u32(poolsizes.size());
    descpool_ci.pPoolSizes = poolsizes.data();
    OnRet(vkCreateDescriptorPool(setlayout.api, &descpool_ci, setlayout.api, descriptor_pool),
          "Failed to create descriptor pool");
    OnName(descriptor_pool, info.__name);

    return Ok(std::move(descriptor_pool));
}

DescriptorPooler::DescriptorPooler(DescriptorPooler&& rhs) : desc_setlayout(rhs.desc_setlayout) {
    desc_pools = std::move(rhs.desc_pools);
}

DescriptorPooler::~DescriptorPooler() {
    desc_pools.clear();
}

Res<Ref<DescriptorPool>> DescriptorPooler::request() {
    if (desc_pools.empty() || !desc_pools.back().available()) {
        auto res = DescriptorPoolState()
                       // Enable vkFreeDescriptorSets to free descriptor set
                       .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                       .setMaxsets(VKT_CORE_MAX_SETS)
                       .into(desc_setlayout);
        OnErr(res);
        desc_pools.push_back(res.unwrap());
    }

    return Ok(newRef(desc_pools.back()));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
