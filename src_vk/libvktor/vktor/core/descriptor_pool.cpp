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

Self DescriptorPoolState::addPoolSize(VkDescriptorType type, uint32_t count) {
    poolsizes.emplace_back(type, count);
    return *this;
}

Self DescriptorPoolState::addPoolSize(VkDescriptorPoolSize poolsize) {
    poolsizes.push_back(poolsize);
    return *this;
}

Self DescriptorPoolState::setFromSetLayout(const DescriptorSetLayout& _setlayout) {
    // Get poolsize from setlayout
    HashMap<VkDescriptorType, uint32_t> desc_types{};
    for (const auto& item : _setlayout.bindings) {
        const auto& binding = item.second;
        // HashMap operator[] will invoke uint32_t's default construct that will give 0
        desc_types[binding.descriptorType] += binding.descriptorCount;
    }
    for (const auto& t : desc_types) {
        addPoolSize(t.first, t.second);
    }
    return *this;
}

Res<DescriptorPool> DescriptorPoolState::into(const CoreApi& api) const {
    return DescriptorPool::from(api, *this);
}

DescriptorPool::DescriptorPool(DescriptorPool&& rhs) : CoreResource(rhs.api), maxsets(rhs.maxsets) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    count = rhs.count;
    rhs.count = 0;
}

DescriptorPool::~DescriptorPool() {
    if (!__borrowed && handle) {
        // Descriptor set will be freed along with vkDestroyDescriptorPool
        vkDestroyDescriptorPool(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
    count = 0;
}

Res<DescriptorSet> DescriptorPool::allocate(VkDescriptorSetLayout setlayout, const void* next, const String& name) {
    auto descset = DescriptorSet(api);
    auto descset_ai = Itor::DescriptorSetAllocateInfo(next);
    descset_ai.descriptorPool = *this;
    descset_ai.descriptorSetCount = 1;
    descset_ai.pSetLayouts = &setlayout;
    OnRet(vkAllocateDescriptorSets(api, &descset_ai, descset), "Failed to allocate descriptor set: {}", name);
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

Res<DescriptorPool> DescriptorPool::from(const CoreApi& api, const DescriptorPoolState& info) {
    DescriptorPool descriptor_pool(api, info.maxsets);

    // VkDescriptorSetLayoutBinding: `descriptorCount` specifies the number of `descriptorType` of the set's `binding`;
    // VkDescriptorPoolSize: `descriptorCount` specifies the total number of `type` can be allocated from the pool;
    // VkDescriptorPoolCreateInfo: `maxSets` specifies the number of descriptor set can be allocated from the pool;
    for (auto& item : info.poolsizes) {
        item.descriptorCount *= info.maxsets;
    }

    auto descpool_ci = Itor::DescriptorPoolCreateInfo(info.__next);
    descpool_ci.flags = info.flags;
    descpool_ci.maxSets = info.maxsets;
    descpool_ci.poolSizeCount = u32(info.poolsizes.size());
    descpool_ci.pPoolSizes = info.poolsizes.data();
    OnRet(vkCreateDescriptorPool(api, &descpool_ci, api, descriptor_pool), "Failed to create descriptor pool: {}", info.__name);
    OnName(descriptor_pool, info.__name);
    descriptor_pool.flags = info.flags;

    return Ok(std::move(descriptor_pool));
}

DescriptorPooler::DescriptorPooler(DescriptorPooler&& rhs) {
    desc_pools = std::move(rhs.desc_pools);
}

DescriptorPooler::~DescriptorPooler() {
    desc_pools.clear();
}

Res<Ref<DescriptorPool>> DescriptorPooler::request(const DescriptorSetLayout& setlayout, String&& name) {
    if (desc_pools.empty() || !desc_pools.back().available()) {
        OnErr(res,
              DescriptorPoolState(std::move(name))
                  // Enable vkFreeDescriptorSets to free descriptor set
                  .setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
                  .setMaxsets(VKT_CORE_MAX_SETS)
                  .setFromSetLayout(setlayout)
                  .into(setlayout.api));
        desc_pools.push_back(res.unwrap());
    }

    return Ok(newRef(desc_pools.back()));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
