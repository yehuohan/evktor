#pragma once
#include "__core.hpp"
#include "command_buffer.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct CommandPool;

class CommandPoolState : public CoreStater<CommandPoolState> {
    friend struct CommandPool;

private:
    VkCommandPoolCreateFlags flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    uint32_t queue_index = 0;

public:
    explicit CommandPoolState(Name&& name = "CommandPool") : CoreStater(std::move(name)) {}

    Self setFlags(VkCommandPoolCreateFlags flags);
    Self setQueueIndex(uint32_t index);

    Res<CommandPool> into(const Device& device) const;
};

struct CommandPool : public CoreResource<VkCommandPool, VK_OBJECT_TYPE_COMMAND_POOL, Device> {
    Vector<CommandBuffer> primaries{};
    Vector<CommandBuffer> secondaries{};
    uint32_t active_primary_count = 0;
    uint32_t active_secondary_count = 0;

    CommandPool(const Device& device) : CoreResource(device) {}
    CommandPool(CommandPool&&);
    ~CommandPool();
    /**
     * @brief Allocate one command buffer
     *
     * Store allocated CommandBuffer within this CommandPool, so return the referrence of the CommandBuffer.
     * And free CommandBuffer by removing CommandBuffer from `primaries` or `secondaries`.
     */
    Res<Ref<CommandBuffer>> allocate(CommandBuffer::Level level, const Name& name = "CommandBuffer");
    void resetCommandPool();

    static Res<CommandPool> from(const Device& device, const CommandPoolState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
