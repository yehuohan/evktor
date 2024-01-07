#pragma once
#include "__builder.hpp"
#include "command_buffer.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct CommandPool : public BuiltResource<VkCommandPool, VK_OBJECT_TYPE_COMMAND_POOL, Device> {
    Vector<CommandBuffer> primaries{};
    Vector<CommandBuffer> secondaries{};
    uint32_t active_primary_count = 0;
    uint32_t active_secondary_count = 0;

    CommandPool(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    CommandPool(CommandPool&&);
    ~CommandPool();
    /**
     * @brief Allocate one command buffer
     *
     * Store allocated `CommandBuffer` within this `CommandPool`, so return the referrence of the `CommandBuffer`
     */
    Res<Ref<CommandBuffer>> allocateCommandBuffer(CommandBuffer::Level level);
    void resetCommandPool();
};

struct CommandPoolInfo : public BuilderInfo {
    uint32_t queue_index = 0;
    VkCommandPoolCreateFlags flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
};

class CommandPoolBuilder : public Builder<CommandPoolBuilder, CommandPool, CommandPoolInfo> {
private:
    const Device& device;

public:
    explicit CommandPoolBuilder(const Device& device, Name&& name = "CommandPool") : Builder(std::move(name)), device(device) {}
    virtual Built build() override;

    Self setFlags(VkCommandPoolCreateFlags flags);
    Self setQueueIndex(uint32_t index);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
