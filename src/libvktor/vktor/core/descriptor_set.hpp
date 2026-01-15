#pragma once
#include "__core.hpp"
#include "__hash.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorPool;

/**
 * @brief Descriptor info to update bindings of descriptor set
 *
 * The descriptor is not an array (VkDescriptorSetLayoutBinding::descriptorCount == 1).
 */
struct DescriptorInfo {
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorBufferInfo */
    HashMap<uint32_t, VkDescriptorBufferInfo> bufs{};
    /** Map VkDescriptorSetLayoutBinding::binding to VkDescriptorImageInfo */
    HashMap<uint32_t, VkDescriptorImageInfo> imgs{};

    /**
     * @brief Set buffer descriptor to binding
     */
    DescriptorInfo& setBuf(uint32_t binding, VkBuffer buf, VkDeviceSize range = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    /**
     * @brief Set buffer descriptor to the new next binding
     */
    DescriptorInfo& nextBuf(VkBuffer buf, VkDeviceSize range = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    /**
     * @brief Set image descriptor to binding
     */
    DescriptorInfo& setImg(uint32_t binding,
                           VkImageView img_view,
                           VkImageLayout img_layout,
                           VkSampler sampler = VK_NULL_HANDLE);
    /**
     * @brief Set image descriptor to the new next binding
     */
    DescriptorInfo& nextImg(VkImageView img_view, VkImageLayout img_layout, VkSampler sampler = VK_NULL_HANDLE);
};

/**
 * @brief Descriptor info to update bindings of descriptor set
 *
 * The descriptor may be an array (VkDescriptorSetLayoutBinding::descriptorCount > 1).
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

    /**
     * @brief Add buffer descriptor to binding (as descriptor array)
     */
    DescriptorArrayInfo& addBuf(uint32_t binding, VkBuffer buf, VkDeviceSize range = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    /**
     * @brief Set buffer descriptor to the new next binding
     */
    DescriptorArrayInfo& nextBuf(VkBuffer buf, VkDeviceSize range = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    /**
     * @brief Push buffer descriptor to the last binding (as descriptor array)
     */
    DescriptorArrayInfo& pushBuf(VkBuffer buf, VkDeviceSize range = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    /**
     * @brief Add image descriptor to binding (as descriptor array)
     */
    DescriptorArrayInfo& addImg(uint32_t binding,
                                VkImageView img_view,
                                VkImageLayout img_layout,
                                VkSampler sampler = VK_NULL_HANDLE);
    /**
     * @brief Set image descriptor to the new next binding
     */
    DescriptorArrayInfo& nextImg(VkImageView img_view, VkImageLayout img_layout, VkSampler sampler = VK_NULL_HANDLE);
    /**
     * @brief Push image descriptor to the last binding (as descriptor array)
     */
    DescriptorArrayInfo& pushImg(VkImageView img_view, VkImageLayout img_layout, VkSampler sampler = VK_NULL_HANDLE);
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
            hashCombine(res, item.second);
        }
        for (const auto& item : desc_info.imgs) {
            hashCombine(res, item.second);
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
