#pragma once
#include "__api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Queue : public CoreHandle<VkQueue> {
    const uint32_t family_index;
    const uint32_t index;

    explicit Queue(uint32_t family_index = 0, uint32_t index = 0) : family_index(family_index), index(index) {}
    Queue(Queue&&);
    ~Queue();

    VkResult submit(const Vector<VkSubmitInfo>& submits, VkFence fence = VK_NULL_HANDLE) const;
    VkResult submit(VkCommandBuffer cmdbuf, VkFence fence = VK_NULL_HANDLE) const;
    VkResult present(VkSwapchainKHR swapchain, uint32_t image_index, VkSemaphore wait_semaphore = VK_NULL_HANDLE) const;
    VkResult waitIdle() const;
};

/**
 * @brief Queue family properties
 */
struct QueueFamilyProps {
    uint32_t count = 1; /**< Count of queues in this queue family that >= 1 */
    VkQueueFlags flags = 0;
    bool present = false;  /**< Queue family supports present */
    bool graphics = false; /**< Queue family supports graphics */
    bool compute = false;  /**< Queue family supports compute */
    bool transfer = false; /**< Queue family supports transfer */
};

/**
 * @brief Queue family indices
 */
struct QueueFamilyIndices {
    uint32_t present = VK_QUEUE_FAMILY_IGNORED;
    uint32_t graphics = VK_QUEUE_FAMILY_IGNORED;
    uint32_t compute = VK_QUEUE_FAMILY_IGNORED;
    uint32_t transfer = VK_QUEUE_FAMILY_IGNORED;
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
