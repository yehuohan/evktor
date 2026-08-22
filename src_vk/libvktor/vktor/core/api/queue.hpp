#pragma once
#include "__api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

template <>
struct VkHandle<VkQueue> {
    VK_HANDLE_IMPL(VkQueue)

public:
    const uint32_t family_index = 0;
    const uint32_t index = 0;

public:
    explicit VkHandle(VkQueue h, uint32_t family_index = 0, uint32_t index = 0)
        : __handle(h)
        , family_index(family_index)
        , index(index) {}

    VkResult submit(const VkSubmitInfo& submit, VkFence fence = VK_NULL_HANDLE) const;
    VkResult submit(VkCommandBuffer cmdbuf, VkFence fence = VK_NULL_HANDLE) const;
    VkResult present(VkSwapchainKHR swapchain, uint32_t image_index, VkSemaphore wait_semaphore = VK_NULL_HANDLE) const;
    VkResult waitIdle() const;
};

/**
 * @brief Vulkan core queue
 */
struct Queue : public CoreHandle<VkQueue> {
protected:
    explicit Queue(uint32_t family_index, uint32_t index)
        // Construct a temporal VkHandle<VkQueue> to assign const members
        : CoreHandle(VkHandle<VkQueue>(VK_NULL_HANDLE, family_index, index)) {}

public:
    // Construct a temporal VkHandle<VkQueue> to assign const members
    Queue(Queue&& rhs) : CoreHandle(VkHandle<VkQueue>(rhs, rhs.family_index, rhs.index)) {
        // Perform move operation
        moveFrom(std::move(rhs));
    }

    static Queue from(VkDevice device, uint32_t family_index = 0, uint32_t index = 0);
};

struct QueueSubmitter {
    const VkHandle<VkQueue>& queue;
    VkSubmitInfo info = Itor::SubmitInfo();

    QueueSubmitter(const Queue& queue) : queue(queue) {}
    QueueSubmitter(const VkHandle<VkQueue>& queue) : queue(queue) {}
    QueueSubmitter& wait(uint32_t count, const VkSemaphore* semaphores, const VkPipelineStageFlags* stages);
    QueueSubmitter& signal(uint32_t count, const VkSemaphore* semaphores);
    VkResult submit(VkCommandBuffer cmdbuf, VkFence fence = VK_NULL_HANDLE);
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
