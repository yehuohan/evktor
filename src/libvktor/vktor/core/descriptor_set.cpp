#include "descriptor_set.hpp"
#include "descriptor_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

DescriptorInfo& DescriptorInfo::setBuf(uint32_t binding, VkBuffer buf, VkDeviceSize range, VkDeviceSize offset) {
    bufs[binding] = VkDescriptorBufferInfo{buf, offset, range};
    return *this;
}

DescriptorInfo& DescriptorInfo::nextBuf(VkBuffer buf, VkDeviceSize range, VkDeviceSize offset) {
    uint32_t binding = bufs.size() + imgs.size();
    bufs[binding] = VkDescriptorBufferInfo{buf, offset, range};
    return *this;
}

DescriptorInfo& DescriptorInfo::setImg(uint32_t binding, VkImageView img_view, VkImageLayout img_layout, VkSampler sampler) {
    imgs[binding] = VkDescriptorImageInfo{sampler, img_view, img_layout};
    return *this;
}

DescriptorInfo& DescriptorInfo::nextImg(VkImageView img_view, VkImageLayout img_layout, VkSampler sampler) {
    uint32_t binding = bufs.size() + imgs.size();
    imgs[binding] = VkDescriptorImageInfo{sampler, img_view, img_layout};
    return *this;
}

DescriptorArrayInfo& DescriptorArrayInfo::addBuf(uint32_t binding, VkBuffer buf, VkDeviceSize range, VkDeviceSize offset) {
    bufs[binding].push_back(VkDescriptorBufferInfo{buf, offset, range});
    return *this;
}

DescriptorArrayInfo& DescriptorArrayInfo::nextBuf(VkBuffer buf, VkDeviceSize range, VkDeviceSize offset) {
    uint32_t binding = bufs.size() + imgs.size();
    bufs[binding].push_back(VkDescriptorBufferInfo{buf, offset, range});
    return *this;
}

DescriptorArrayInfo& DescriptorArrayInfo::pushBuf(VkBuffer buf, VkDeviceSize range, VkDeviceSize offset) {
    uint32_t binding = bufs.size() + imgs.size();
    binding = binding > 0 ? binding - 1 : 0;
    bufs[binding].push_back(VkDescriptorBufferInfo{buf, offset, range});
    return *this;
}

DescriptorArrayInfo& DescriptorArrayInfo::addImg(uint32_t binding,
                                                 VkImageView img_view,
                                                 VkImageLayout img_layout,
                                                 VkSampler sampler) {
    imgs[binding].push_back(VkDescriptorImageInfo{sampler, img_view, img_layout});
    return *this;
}

DescriptorArrayInfo& DescriptorArrayInfo::nextImg(VkImageView img_view, VkImageLayout img_layout, VkSampler sampler) {
    uint32_t binding = bufs.size() + imgs.size();
    imgs[binding].push_back(VkDescriptorImageInfo{sampler, img_view, img_layout});
    return *this;
}

DescriptorArrayInfo& DescriptorArrayInfo::pushImg(VkImageView img_view, VkImageLayout img_layout, VkSampler sampler) {
    uint32_t binding = bufs.size() + imgs.size();
    binding = binding > 0 ? binding - 1 : 0;
    imgs[binding].push_back(VkDescriptorImageInfo{sampler, img_view, img_layout});
    return *this;
}

DescriptorSet::DescriptorSet(DescriptorPool& pool) : CoreResource(pool.api), desc_pool(pool) {}

DescriptorSet::DescriptorSet(DescriptorSet&& rhs) : CoreResource(rhs.api), desc_pool(rhs.desc_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
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
    vkUpdateDescriptorSets(api, desc_writes.size(), desc_writes.data(), 0, nullptr);
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
    vkUpdateDescriptorSets(api, desc_writes.size(), desc_writes.data(), 0, nullptr);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
