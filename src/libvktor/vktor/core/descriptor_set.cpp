#include "descriptor_set.hpp"
#include "descriptor_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

DescriptorSet::DescriptorSet(DescriptorPool& pool) : CoreResource(pool.device), desc_pool(pool) {}

DescriptorSet::DescriptorSet(DescriptorSet&& rhs) : CoreResource(rhs.device), desc_pool(rhs.desc_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

DescriptorSet::~DescriptorSet() {
    // Still need check null handle to skip destructor resulted from move constructor
    if (!__borrowed && handle) {
        desc_pool.free(*this);
    }
    handle = VK_NULL_HANDLE;
}

void DescriptorSet::update(const DescriptorInfo& desc_info) {
    Vector<VkWriteDescriptorSet> desc_writes{};
    for (const auto& item : desc_info.bufs) {
        const auto& bind = desc_pool.desc_setlayout.bindings.at(item.first);
        OnCheck(1 == bind.descriptorCount, "There should be bind.descriptorCount == 1 for buf");
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
        OnCheck(1 == bind.descriptorCount, "There should be bind.descriptorCount == 1 for img");
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
        OnCheck(bufs.size() == bind.descriptorCount, "The bufs size should be bind.descriptorCount");
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
        OnCheck(imgs.size() == bind.descriptorCount, "The imgs size should be bind.descriptorCount");
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
