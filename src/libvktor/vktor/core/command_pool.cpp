#include "command_pool.hpp"
#include "command_buffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = CommandPoolState::Self;

Self CommandPoolState::setFlags(VkCommandPoolCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self CommandPoolState::setQueueFamilyIndex(uint32_t index) {
    queue_family_index = index;
    return *this;
}

Res<CommandPool> CommandPoolState::into(const CoreApi& api) const {
    return CommandPool::from(api, *this);
}

CommandPool::CommandPool(CommandPool&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    primaries = std::move(rhs.primaries);
    secondaries = std::move(rhs.secondaries);
    active_primary_count = rhs.active_primary_count;
    rhs.active_primary_count = 0;
    active_secondary_count = rhs.active_secondary_count;
    rhs.active_secondary_count = 0;
}

CommandPool::~CommandPool() {
    primaries.clear();
    secondaries.clear();
    if (!__borrowed && handle) {
        vkDestroyCommandPool(api, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<Ref<CommandBuffer>> CommandPool::allocate(Level level, const Name& name) {
    CommandBuffer* ptr = nullptr;
    switch (level) {
    case Level::Primary:
        {
            if (active_primary_count < primaries.size()) {
                ptr = &primaries[active_primary_count++];
            } else {
                auto cmdbuf = CommandBuffer(*this);
                auto cmdbuf_ai = Itor::CommandBufferAllocateInfo();
                cmdbuf_ai.commandPool = *this;
                cmdbuf_ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                cmdbuf_ai.commandBufferCount = 1;
                OnRet(vkAllocateCommandBuffers(api, &cmdbuf_ai, cmdbuf), "Failed to allocate primary command buffer");
                OnName(cmdbuf, name);

                active_primary_count++;
                primaries.push_back(std::move(cmdbuf));
                ptr = &primaries.back();
            }
            break;
        }
    case Level::Secondary:
        {
            if (active_secondary_count < secondaries.size()) {
                ptr = &secondaries[active_secondary_count++];
            } else {
                auto cmdbuf = CommandBuffer(*this);
                auto cmdbuf_ai = Itor::CommandBufferAllocateInfo();
                cmdbuf_ai.commandPool = *this;
                cmdbuf_ai.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
                cmdbuf_ai.commandBufferCount = 1;
                OnRet(vkAllocateCommandBuffers(api, &cmdbuf_ai, cmdbuf), "Failed to allocate secondary command buffer");
                OnName(cmdbuf, name);

                active_secondary_count++;
                secondaries.push_back(std::move(cmdbuf));
                ptr = &secondaries.back();
            }
            break;
        }
    default:
        return Er("The command buffer level = {} to allocate is not supported",
                  VkStr(VkCommandBufferLevel, (VkCommandBufferLevel)level));
    }

    return Ok(newRef(*ptr));
}

void CommandPool::resetPool() {
    active_primary_count = 0;
    active_secondary_count = 0;
}

Res<CommandPool> CommandPool::from(const CoreApi& api, const CommandPoolState& info) {
    CommandPool cmdpool(api);

    auto cmdpool_ci = Itor::CommandPoolCreateInfo();
    cmdpool_ci.flags = info.flags;
    cmdpool_ci.queueFamilyIndex = info.queue_family_index;
    OnRet(vkCreateCommandPool(api, &cmdpool_ci, nullptr, cmdpool), "Failed to create command pool");
    OnName(cmdpool, info.__name);

    return Ok(std::move(cmdpool));
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
