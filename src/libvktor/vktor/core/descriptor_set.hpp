#pragma once
#include "__core.hpp"
#include "__hash.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorPool;

/**
 * @brief Descriptor info to update bindings of descriptor set
 *
 * The descriptor set is not an array (VkDescriptorSetLayoutBinding::descriptorCount == 1).
 */
struct DescriptorInfo {
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorBufferInfo */
    HashMap<uint32_t, VkDescriptorBufferInfo> bufs{};
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorImageInfo */
    HashMap<uint32_t, VkDescriptorImageInfo> imgs{};
};

/**
 * @brief Descriptor info to update bindings of descriptor set
 *
 * The descriptor set may be an array (VkDescriptorSetLayoutBinding::descriptorCount > 1).
 */
struct DescriptorArrayInfo {
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorBufferInfo array
     * (The array size should be VkDescriptorSetLayoutBinding::descriptorCount)
     */
    HashMap<uint32_t, Vector<VkDescriptorBufferInfo>> bufs{};
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorImageInfo array
     * (The array size should be VkDescriptorSetLayoutBinding::descriptorCount)
     */
    HashMap<uint32_t, Vector<VkDescriptorImageInfo>> imgs{};
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
    void update(const DescriptorInfo& desc_info);
    void update(const DescriptorArrayInfo& desc_arrinfo);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::DescriptorInfo> {
    size_t operator()(const vkt::core::DescriptorInfo& desc_info) const {
        size_t res = 0;
        for (const auto& item : desc_info.bufs) {
            vkt::hashCombine(res, item.second);
        }
        for (const auto& item : desc_info.imgs) {
            vkt::hashCombine(res, item.second);
        }
        return res;
    }
};

template <>
struct hash<vkt::core::DescriptorArrayInfo> {
    size_t operator()(const vkt::core::DescriptorArrayInfo& desc_arrinfo) const {
        size_t res = 0;
        for (const auto& item : desc_arrinfo.bufs) {
            for (const auto& buf : item.second) {
                vkt::hashCombine(res, buf);
            }
        }
        for (const auto& item : desc_arrinfo.imgs) {
            for (const auto& img : item.second) {
                vkt::hashCombine(res, img);
            }
        }
        return res;
    }
};

NAMESPACE_END(std)
