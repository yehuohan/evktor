#include "buffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = BufferState::Self;

Self BufferState::setSize(VkDeviceSize size) {
    buffer_ci.size = size;
    return *this;
}

Self BufferState::setUsage(VkBufferUsageFlags usage) {
    buffer_ci.usage = usage;
    return *this;
}

Self BufferState::setMemoryFlags(VmaAllocationCreateFlags flags) {
    memory_flags = flags;
    return *this;
}

Self BufferState::setMemoryUsage(VmaMemoryUsage usage) {
    memory_usage = usage;
    return *this;
}

Self BufferState::setMemoryPool(const DeviceMemoryPool* pool) {
    memory_pool = pool;
    return *this;
}

Res<Buffer> BufferState::into(const CoreApi& api) const {
    return Buffer::from(api, *this);
}

Buffer::Buffer(Buffer&& rhs) : CoreResource(std::move(rhs)), borrowed_memory_mapped(rhs.borrowed_memory_mapped) {
    size = rhs.size;
    allocation = rhs.allocation;
    memory = rhs.memory;
    memory_mapped = rhs.memory_mapped;
    rhs.allocation = VK_NULL_HANDLE;
    rhs.memory = VK_NULL_HANDLE;
    rhs.memory_mapped = nullptr;
}

Buffer::~Buffer() {
    unmap();
    if (!borrowed() && __handle) {
        if (allocation) {
            vmaDestroyBuffer(api, __handle, allocation);
        } else {
            // This's a dead branch currently
            if (memory) {
                vkFreeMemory(api, memory, api);
            }
            vkDestroyBuffer(api, __handle, api);
        }
    }
    __handle = VK_NULL_HANDLE;
    allocation = VK_NULL_HANDLE;
    memory = VK_NULL_HANDLE;
    memory_mapped = nullptr;
}

bool Buffer::copyFrom(const void* src, const VkDeviceSize copy_size, VkDeviceSize offset) const {
    VkDeviceSize mem_size = copy_size == VK_WHOLE_SIZE ? size : copy_size;
    if (memory_mapped) {
        std::memcpy((uint8_t*)memory_mapped + offset, src, (size_t)mem_size);
    } else {
        auto res = map();
        if (res.isErr()) {
            return false;
        }
        void* data = res.unwrap();
        std::memcpy((uint8_t*)data + offset, src, (size_t)mem_size);
        unmap();
    }
    return true;
}

bool Buffer::copyInto(void* dst, const VkDeviceSize copy_size, VkDeviceSize offset) const {
    VkDeviceSize mem_size = copy_size == VK_WHOLE_SIZE ? size : copy_size;
    if (memory_mapped) {
        std::memcpy(dst, (uint8_t*)memory_mapped + offset, (size_t)mem_size);
    } else {
        auto res = map();
        if (res.isErr()) {
            return false;
        }
        void* data = res.unwrap();
        std::memcpy(dst, (uint8_t*)data + offset, (size_t)mem_size);
        unmap();
    }
    return true;
}

Res<void*> Buffer::map() const {
    if (!memory_mapped) {
        if (allocation) {
            OnRet(vmaMapMemory(api, allocation, &memory_mapped), "Failed to map buffer memory with allocation");
        } else if (memory) {
            OnRet(vkMapMemory(api, memory, 0, size, 0, &memory_mapped), "Failed to map buffer memory");
        } else {
            return Er("The buffer seemed doesn't borrow a memory to map");
        }
    }
    return Ok(memory_mapped);
}

void Buffer::unmap() const {
    if (borrowed_memory_mapped) {
        return;
    }
    if (memory_mapped) {
        if (allocation) {
            vmaUnmapMemory(api, allocation);
        } else if (memory) {
            vkUnmapMemory(api, memory);
        }
    }
    memory_mapped = nullptr;
}

VkResult Buffer::getFd(int& fd, VkExternalMemoryHandleTypeFlagBits hdl_type) {
    auto fd_gi = Itor::MemoryGetFdInfoKHR();
    fd_gi.memory = memory;
    fd_gi.handleType = hdl_type;
    return vkGetMemoryFdKHR(api, &fd_gi, &fd);
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
VkResult Buffer::getWin32Handle(HANDLE& hdl, VkExternalMemoryHandleTypeFlagBits hdl_type) {
    auto hdl_gi = Itor::MemoryGetWin32HandleInfoKHR();
    hdl_gi.memory = memory;
    hdl_gi.handleType = hdl_type;
    return vkGetMemoryWin32HandleKHR(api, &hdl_gi, &hdl);
}
#endif

Res<Buffer> Buffer::from(const CoreApi& api, const BufferState& info) {
    Buffer buffer(api);

    info.buffer_ci.pNext = info.__next;

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = info.memory_flags;
    allocation_ci.usage = info.memory_usage;

    auto external_memory_ci = Itor::ExternalMemoryBufferCreateInfo();
    if (info.memory_pool && info.memory_pool->export_memory_ai) {
        external_memory_ci.handleTypes = info.memory_pool->export_memory_ai->handleTypes;
        chainNext(info.buffer_ci, &external_memory_ci);
        allocation_ci.pool = *info.memory_pool;
    }

    VmaAllocationInfo allocation_info{};

    OnRet(vmaCreateBuffer(api, &info.buffer_ci, &allocation_ci, buffer, &buffer.allocation, &allocation_info),
          "Failed to create buffer: {}",
          info.__name);
    OnName(buffer, info.__name);
    buffer.size = info.buffer_ci.size;
    buffer.memory = allocation_info.deviceMemory;

    return Ok(std::move(buffer));
}

Res<Buffer> Buffer::borrow(const CoreApi& api, VkHandle<VkBuffer> handle, VkDeviceMemory memory, void* memory_mapped) {
    if (!handle.valid()) {
        return Er("Borrow requires a valid VkHandle for VkBuffer");
    }
    return Ok(Buffer(api, handle, memory, memory_mapped));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
