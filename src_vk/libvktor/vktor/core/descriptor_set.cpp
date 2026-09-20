#include "descriptor_set.hpp"
#include "descriptor_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

DescriptorBuffer::DescriptorBuffer(Vector<VkDescriptorBufferInfo>& info, size_t count) : bufs(info) {
    index = 0;
    count = std::max<size_t>(1, count);
    if (bufs.size() != count) {
        bufs.resize(count);
    }
}

DescriptorBuffer& DescriptorBuffer::next() {
    if (index + 1 < bufs.size()) {
        index++;
    } else {
        vktLogW("Going to bind an invalid index + 1 = {} >= {} of DescriptorBuffer", index + 1, bufs.size());
    }
    return *this;
}

DescriptorBuffer& DescriptorBuffer::bind(size_t _index) {
    if (_index < bufs.size()) {
        index = _index;
    } else {
        vktLogW("Going to bind an invalid index = {} >= {} of DescriptorBuffer", _index, bufs.size());
    }
    return *this;
}

DescriptorImage::DescriptorImage(Vector<VkDescriptorImageInfo>& info, size_t count) : imgs(info) {
    index = 0;
    count = std::max<size_t>(1, count);
    if (imgs.size() != count) {
        imgs.resize(count);
    }
}

DescriptorImage& DescriptorImage::next() {
    if (index + 1 < imgs.size()) {
        index++;
    } else {
        vktLogW("Going to bind an invalid index + 1 = {} >= {} of DescriptorImage", index + 1, imgs.size());
    }
    return *this;
}

DescriptorImage& DescriptorImage::bind(size_t _index) {
    if (_index < imgs.size()) {
        index = _index;
    } else {
        vktLogW("Going to bind an invalid index = {} >= {} of DescriptorImage", _index, imgs.size());
    }
    return *this;
}

void VkhDescriptorSet::update(const DescriptorInfo& info, const DescriptorSetLayout& setlayout) const {
    static thread_local Vector<VkWriteDescriptorSet> desc_writes{};
    desc_writes.clear();
    for (const auto& item : info.bufs) {
        const auto& bind = setlayout.getBindings().at(item.first);
        const auto& bufs = item.second;
        auto write = Itor::WriteDescriptorSet();
        write.dstSet = handle();
        write.dstBinding = bind.binding;
        write.dstArrayElement = 0;
        write.descriptorCount = bind.descriptorCount;
        write.descriptorType = bind.descriptorType;
        write.pBufferInfo = bufs.data();
        desc_writes.push_back(write);
    }
    for (const auto& item : info.imgs) {
        const auto& bind = setlayout.getBindings().at(item.first);
        const auto& imgs = item.second;
        auto write = Itor::WriteDescriptorSet();
        write.dstSet = handle();
        write.dstBinding = bind.binding;
        write.dstArrayElement = 0;
        write.descriptorCount = bind.descriptorCount;
        write.descriptorType = bind.descriptorType;
        write.pImageInfo = imgs.data();
        desc_writes.push_back(write);
    }
    vkUpdateDescriptorSets(parent(), desc_writes.size(), desc_writes.data(), 0, nullptr);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
