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

Buffer::Buffer(Buffer&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    size = rhs.size;
    memory = rhs.memory;
    rhs.memory = VK_NULL_HANDLE;
    allocation = rhs.allocation;
    rhs.allocation = VK_NULL_HANDLE;
}

Buffer::~Buffer() {
    if (!__borrowed && handle) {
        if (allocation) {
            vmaDestroyBuffer(api, handle, allocation);
        } else {
            vkFreeMemory(api, memory, api);
            vkDestroyBuffer(api, handle, api);
        }
    }
    handle = VK_NULL_HANDLE;
    memory = VK_NULL_HANDLE;
    allocation = VK_NULL_HANDLE;
}

bool Buffer::copyFrom(const void* src, const VkDeviceSize copy_size, VkDeviceSize offset) const {
    VkDeviceSize mem_size = copy_size > 0 ? copy_size : size;
    void* data;
    auto res = vmaMapMemory(api, allocation, &data);
    if (VK_SUCCESS != res) {
        vktLogE("Failed to map buffer memory: {}", VkStr(VkResult, res));
        return false;
    }
    std::memcpy((uint8_t*)data + offset, src, (size_t)mem_size);
    vmaUnmapMemory(api, allocation);
    return true;
}

bool Buffer::copyInto(void* dst, const VkDeviceSize copy_size, VkDeviceSize offset) const {
    VkDeviceSize mem_size = copy_size > 0 ? copy_size : size;
    void* data;
    auto res = vmaMapMemory(api, allocation, &data);
    if (VK_SUCCESS != res) {
        vktLogE("Failed to map buffer memory: {}", VkStr(VkResult, res));
        return false;
    }
    std::memcpy(dst, (uint8_t*)data + offset, (size_t)mem_size);
    vmaUnmapMemory(api, allocation);
    return true;
}

Res<void*> Buffer::map() const {
    void* data;
    OnRet(vmaMapMemory(api, allocation, &data), "Failed to map buffer memory");
    return Ok(data);
}

void Buffer::unmap() const {
    vmaUnmapMemory(api, allocation);
}

VkResult Buffer::getFd(int& fd, VkExternalMemoryHandleTypeFlagBits hdl_type) {
    auto fd_gi = Itor::MemoryGetFdInfoKHR();
    fd_gi.memory = memory;
    fd_gi.handleType = hdl_type;
    return vkGetMemoryFdKHR(api, &fd_gi, &fd);
}

VkResult Buffer::getWin32Handle(HANDLE& hdl, VkExternalMemoryHandleTypeFlagBits hdl_type) {
    auto hdl_gi = Itor::MemoryGetWin32HandleInfoKHR();
    hdl_gi.memory = memory;
    hdl_gi.handleType = hdl_type;
    return vkGetMemoryWin32HandleKHR(api, &hdl_gi, &hdl);
}

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
          "Failed to create buffer");
    OnName(buffer, info.__name);
    buffer.size = info.buffer_ci.size;
    buffer.memory = allocation_info.deviceMemory;

    return Ok(std::move(buffer));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
