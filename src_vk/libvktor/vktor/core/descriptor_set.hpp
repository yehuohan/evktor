#pragma once
#include "__core.hpp"
#include "__hash.hpp"
#include "buffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorPool;

struct DescriptorBuffer {
    size_t index;
    Vector<VkDescriptorBufferInfo>& bufs;

    DescriptorBuffer(Vector<VkDescriptorBufferInfo>& info, size_t count);

    DescriptorBuffer& next();
    DescriptorBuffer& bind(size_t index);
    inline DescriptorBuffer& bind(const Buffer& buffer) {
        bufs[index].buffer = buffer;
        bufs[index].offset = 0;
        bufs[index].range = buffer.getSize();
        return *this;
    }
    inline DescriptorBuffer& bind(VkBuffer buffer) {
        bufs[index].buffer = buffer;
        return *this;
    }
    inline DescriptorBuffer& bind(VkDeviceSize offset, VkDeviceSize range) {
        bufs[index].offset = offset;
        bufs[index].range = range;
        return *this;
    }
};

struct DescriptorImage {
    size_t index;
    Vector<VkDescriptorImageInfo>& imgs;

    DescriptorImage(Vector<VkDescriptorImageInfo>& info, size_t count);

    DescriptorImage& next();
    DescriptorImage& bind(size_t index);
    inline DescriptorImage& bind(VkSampler sampler) {
        imgs[index].sampler = sampler;
        return *this;
    }
    inline DescriptorImage& bind(VkImageView image_view) {
        imgs[index].imageView = image_view;
        return *this;
    }
    inline DescriptorImage& bind(VkImageLayout image_layout) {
        imgs[index].imageLayout = image_layout;
        return *this;
    }
};

/**
 * @brief Descriptor info to update bindings of descriptor set
 */
struct DescriptorInfo {
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorBufferInfo array
     * (The array size should be VkDescriptorSetLayoutBinding::descriptorCount)
     */
    HashMap<uint32_t, Vector<VkDescriptorBufferInfo>> bufs{};
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorImageInfo array
     * (The array size should be VkDescriptorSetLayoutBinding::descriptorCount)
     */
    HashMap<uint32_t, Vector<VkDescriptorImageInfo>> imgs{};

    inline uint32_t bindingCount() const {
        return u32(bufs.size() + imgs.size());
    }
    inline DescriptorBuffer setBuf(uint32_t binding, size_t count = 1) {
        return DescriptorBuffer(bufs[binding], count);
    }
    inline DescriptorBuffer addBuf(size_t count = 1) {
        return DescriptorBuffer(bufs[bindingCount()], count);
    }
    inline DescriptorImage setImg(uint32_t binding, size_t count = 1) {
        return DescriptorImage(imgs[binding], count);
    }
    inline DescriptorImage addImg(size_t count = 1) {
        return DescriptorImage(imgs[bindingCount()], count);
    }
};

/**
 * @brief Descriptor set
 *
 * DescriptorSet should be allocated with DescriptorPool::allocate() as vkAllocateDescriptorSets need VkDescriptorPool.
 */
struct DescriptorSet : public CoreResource<VkDescriptorSet, VK_OBJECT_TYPE_DESCRIPTOR_SET> {
    DescriptorPool& desc_pool;

    explicit DescriptorSet(DescriptorPool& pool);
    DescriptorSet(DescriptorSet&&);
    ~DescriptorSet();
    /**
     * @brief Update descriptor set
     */
    void update(const DescriptorInfo& desc_arrinfo) const;
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::DescriptorInfo> {
    size_t operator()(const vkt::core::DescriptorInfo& desc_arrinfo) const {
        size_t res = 0;
        for (const auto& item : desc_arrinfo.bufs) {
            for (const auto& buf : item.second) {
                hashCombine(res, buf);
            }
        }
        for (const auto& item : desc_arrinfo.imgs) {
            for (const auto& img : item.second) {
                hashCombine(res, img);
            }
        }
        return res;
    }
};

NAMESPACE_END(std)
