#include "descriptor_set.hpp"
#include "descriptor_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

DescriptorBuffer::DescriptorBuffer(Vector<VkDescriptorBufferInfo>& info, size_t count) : bufs(info) {
    index = 0;
    if (index >= count) {
        vktLogW("Going to bind an invalid index = {} of DescriptorBuffer", index);
    }
    if (bufs.size() != count) {
        bufs.resize(count);
    }
}

DescriptorBuffer& DescriptorBuffer::next() {
    index++;
    if (index >= bufs.size()) {
        vktLogW("Going to bind an invalid index = {} of DescriptorBuffer", index);
    }
    return *this;
}

DescriptorBuffer& DescriptorBuffer::bind(size_t _index) {
    index = _index;
    if (index >= bufs.size()) {
        vktLogW("Going to bind an invalid index = {} of DescriptorBuffer", index);
    }
    return *this;
}

DescriptorImage::DescriptorImage(Vector<VkDescriptorImageInfo>& info, size_t count) : imgs(info) {
    index = 0;
    if (index >= count) {
        vktLogW("Going to bind an invalid index = {} of DescriptorImage", index);
    }
    if (imgs.size() != count) {
        imgs.resize(count);
    }
}

DescriptorImage& DescriptorImage::next() {
    index++;
    if (index >= imgs.size()) {
        vktLogW("Going to bind an invalid index = {} of DescriptorImage", index);
    }
    return *this;
}

DescriptorImage& DescriptorImage::bind(size_t _index) {
    index = _index;
    if (index >= imgs.size()) {
        vktLogW("Going to bind an invalid index = {} of DescriptorImage", index);
    }
    return *this;
}

DescriptorSet::DescriptorSet(DescriptorPool& pool) : CoreResource(pool.api), desc_pool(pool) {}

DescriptorSet::DescriptorSet(DescriptorSet&& rhs) : CoreResource(rhs.api), desc_pool(rhs.desc_pool) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

DescriptorSet::~DescriptorSet() {
    if (!__borrowed && handle) {
        // Descriptor set will be freed along with vkDestroyDescriptorPool
    }
    handle = VK_NULL_HANDLE;
}

void DescriptorSet::update(const DescriptorInfo& desc_arrinfo) const {
    Vector<VkWriteDescriptorSet> desc_writes{};
    for (const auto& item : desc_arrinfo.bufs) {
        const auto& bind = desc_pool.desc_setlayout.bindings.at(item.first);
        const auto& bufs = item.second;
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
