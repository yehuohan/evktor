#pragma once
#include "__builder.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Swapchain;
struct CommandBuffer;

struct Queue : public BuiltHandle<VkQueue> {
    const uint32_t family_index;
    const uint32_t index;

    Queue(uint32_t family_index = 0, uint32_t index = 0, Name&& name = "Queue")
        : BuiltHandle(std::move(name))
        , family_index(family_index)
        , index(index) {}
    Queue(Queue&&);
    ~Queue();

    inline VkResult setDebugName(VkDevice device) const {
        return core::setDebugName(device,
                                  VK_OBJECT_TYPE_QUEUE,
                                  u64(reinterpret_cast<uint64_t>(this->handle)),
                                  this->__name.c_str());
    }

    VkResult submit(const std::vector<VkSubmitInfo>& submits, VkFence fence = VK_NULL_HANDLE) const;
    VkResult submit(const CommandBuffer& cmdbuf, VkFence fence = VK_NULL_HANDLE) const;
    VkResult present(const Swapchain& swapchain, uint32_t image_index, const VkSemaphore* semaphore = nullptr) const;
    VkResult waitIdle() const;
};

/**
 * @brief Queue family properties
 */
struct QueueFamilyProps {
    uint32_t count = 1;    /**< Count of queues in this queue family that >= 1. */
    bool present = false;  /**< Queue family supports present */
    bool graphics = false; /**< Queue family supports graphics */
    bool compute = false;  /**< Queue family supports compute */
    bool transfer = false; /**< Queue family supports transfer */
};

/**
 * @brief Queue families with indices
 *
 * If there's no value in optional, the queue family is not required or not supported.
 */
struct QueueFamilies {
    std::optional<uint32_t> present{};
    std::optional<uint32_t> graphics{};
    std::optional<uint32_t> compute{};
    std::optional<uint32_t> transfer{};

    inline void clear() {
        present.reset();
        graphics.reset();
        compute.reset();
        transfer.reset();
    }
};

/**
 * @brief Queues
 *
 * If the queue is nullptr, the queue is not required or not supported.
 */
struct Queues {
    Queue* present = nullptr;
    Queue* graphics = nullptr;
    Queue* compute = nullptr;
    Queue* transfer = nullptr;

    Queues() = default;
    Queues(Queues&& rhs) {
        present = rhs.present;
        graphics = rhs.graphics;
        compute = rhs.compute;
        transfer = rhs.transfer;
        rhs.clear();
    }
    Queues& operator=(Queues&& rhs) {
        present = rhs.present;
        graphics = rhs.graphics;
        compute = rhs.compute;
        transfer = rhs.transfer;
        rhs.clear();
        return *this;
    }

    inline void clear() {
        present = nullptr;
        graphics = nullptr;
        compute = nullptr;
        transfer = nullptr;
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
