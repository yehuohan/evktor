#include "descriptor_set.hpp"
#include "descriptor_pool.hpp"
#include <cassert>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

DescriptorSet::DescriptorSet(const DescriptorPool& pool, Name&& name)
    : BuiltResource(pool.device, std::move(name))
    , desc_pool(pool) {}

DescriptorSet::DescriptorSet(DescriptorSet&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)), desc_pool(rhs.desc_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

DescriptorSet::~DescriptorSet() {
    // Descriptor set will be freed along with `vkDestroyDescriptorPool`
    handle = VK_NULL_HANDLE;
}

void DescriptorSet::update(const DescriptorInfo& desc_info) {
    Vector<VkWriteDescriptorSet> desc_writes{};
    for (const auto& item : desc_info.bufs) {
        const auto& bind = desc_pool.desc_setlayout.bindings.at(item.first);
        assert(1 == bind.descriptorCount && "There should be bind.descriptorCount == 1 for buf");
        auto write = Itor::WriteDescriptorSet();
        write.dstSet = handle;
        write.dstBinding = bind.binding;
        write.dstArrayElement = 0;
        write.descriptorCount = bind.descriptorCount;
        write.descriptorType = bind.descriptorType;
        write.pBufferInfo = &item.second;
        desc_writes.push_back(write);
    }
    for (const auto& item : desc_info.imgs) {
        const auto& bind = desc_pool.desc_setlayout.bindings.at(item.first);
        assert(1 == bind.descriptorCount && "There should be bind.descriptorCount == 1 for img");
        auto write = Itor::WriteDescriptorSet();
        write.dstSet = handle;
        write.dstBinding = bind.binding;
        write.dstArrayElement = 0;
        write.descriptorCount = bind.descriptorCount;
        write.descriptorType = bind.descriptorType;
        write.pImageInfo = &item.second;
        desc_writes.push_back(write);
    }
    vkUpdateDescriptorSets(device, desc_writes.size(), desc_writes.data(), 0, nullptr);
}

void DescriptorSet::update(const DescriptorArrayInfo& desc_arrinfo) {
    Vector<VkWriteDescriptorSet> desc_writes{};
    for (const auto& item : desc_arrinfo.bufs) {
        const auto& bind = desc_pool.desc_setlayout.bindings.at(item.first);
        const auto& bufs = item.second;
        assert(bufs.size() == bind.descriptorCount && "The bufs size should be bind.descriptorCount");
        auto write = Itor::WriteDescriptorSet();
        write.dstSet = handle;
        write.dstBinding = bind.binding;
        write.dstArrayElement = 0;
        write.descriptorCount = bind.descriptorCount;
        write.descriptorType = bind.descriptorType;
        write.pBufferInfo = bufs.data();
        desc_writes.push_back(write);
    }
    for (const auto& item : desc_arrinfo.imgs) {
        const auto& bind = desc_pool.desc_setlayout.bindings.at(item.first);
        const auto& imgs = item.second;
        assert(imgs.size() == bind.descriptorCount && "The imgs size should be bind.descriptorCount");
        auto write = Itor::WriteDescriptorSet();
        write.dstSet = handle;
        write.dstBinding = bind.binding;
        write.dstArrayElement = 0;
        write.descriptorCount = bind.descriptorCount;
        write.descriptorType = bind.descriptorType;
        write.pImageInfo = imgs.data();
        desc_writes.push_back(write);
    }
    vkUpdateDescriptorSets(device, desc_writes.size(), desc_writes.data(), 0, nullptr);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
