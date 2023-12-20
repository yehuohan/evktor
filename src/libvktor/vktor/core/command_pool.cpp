#include "command_pool.hpp"
#include "command_buffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = CommandPoolBuilder::Self;

CommandPool::CommandPool(CommandPool&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    primaries = std::move(rhs.primaries);
    secondaries = std::move(rhs.secondaries);
    active_primary_count = rhs.active_primary_count;
    active_secondary_count = rhs.active_secondary_count;
}

CommandPool::~CommandPool() {
    primaries.clear();
    secondaries.clear();
    if (handle) {
        vkDestroyCommandPool(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<Ref<CommandBuffer>> CommandPool::requestCommandBuffer(CommandBuffer::Level level) {
    CommandBuffer* ptr = nullptr;
    switch (level) {
    case CommandBuffer::Level::Primary:
        {
            if (active_primary_count < primaries.size()) {
                ptr = &primaries[active_primary_count++];
            } else {
                auto cmdbuf = CommandBuffer(*this);
                auto cmdbuf_ai = Itor::CommandBufferAllocateInfo();
                cmdbuf_ai.commandPool = *this;
                cmdbuf_ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                cmdbuf_ai.commandBufferCount = 1;
                OnRet(vkAllocateCommandBuffers(device, &cmdbuf_ai, cmdbuf), "Failed to allocate primary command buffer");
                OnName(cmdbuf);

                active_primary_count++;
                primaries.push_back(std::move(cmdbuf));
                ptr = &primaries.back();
            }
            break;
        }
    case CommandBuffer::Level::Secondary:
        {
            if (active_secondary_count < secondaries.size()) {
                ptr = &secondaries[active_secondary_count++];
            } else {
                auto cmdbuf = CommandBuffer(*this);
                auto cmdbuf_ai = Itor::CommandBufferAllocateInfo();
                cmdbuf_ai.commandPool = *this;
                cmdbuf_ai.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
                cmdbuf_ai.commandBufferCount = 1;
                OnRet(vkAllocateCommandBuffers(device, &cmdbuf_ai, cmdbuf), "Failed to allocate secondary command buffer");
                OnName(cmdbuf);

                active_secondary_count++;
                secondaries.push_back(std::move(cmdbuf));
                ptr = &secondaries.back();
            }
            break;
        }
    default: return Er("The command buffer level = {} to request is not supported", (int)level);
    }

    return Ok(newRef(*ptr));
}

void CommandPool::resetCommandPool() {
    active_primary_count = 0;
    active_secondary_count = 0;
}

Self CommandPoolBuilder::setFlags(VkCommandPoolCreateFlags flags) {
    info.flags = flags;
    return *this;
}

Self CommandPoolBuilder::setQueueIndex(uint32_t index) {
    info.queue_index = index;
    return *this;
}

CommandPoolBuilder::Built CommandPoolBuilder::build() {
    CommandPool cmdpool(device, std::move(info.__name));

    auto cmdpool_ci = Itor::CommandPoolCreateInfo();
    cmdpool_ci.flags = info.flags;
    cmdpool_ci.queueFamilyIndex = info.queue_index;
    OnRet(vkCreateCommandPool(device, &cmdpool_ci, nullptr, cmdpool), "Failed to create command pool");
    OnName(cmdpool);

    return Ok(std::move(cmdpool));
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
