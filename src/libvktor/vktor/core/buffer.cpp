#include "buffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = BufferState::Self;

Self BufferState::setSize(VkDeviceSize size) {
    buffer_ci.size = size;
    return *this;
}

Self BufferState::setUsage(VkBufferUsageFlags flags) {
    buffer_ci.usage = flags;
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

Res<Buffer> BufferState::into(const Device& device) const {
    return Buffer::from(device, *this);
}

Buffer::Buffer(Buffer&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    size = rhs.size;
    memory = rhs.memory;
    rhs.memory = VK_NULL_HANDLE;
    allocation = rhs.allocation;
    rhs.allocation = VK_NULL_HANDLE;
}

Buffer::~Buffer() {
    if (!__borrowed && handle) {
        if (allocation) {
            vmaDestroyBuffer(device, handle, allocation);
        } else {
            vkFreeMemory(device, memory, nullptr);
            vkDestroyBuffer(device, handle, nullptr);
        }
    }
    handle = VK_NULL_HANDLE;
    memory = VK_NULL_HANDLE;
    allocation = VK_NULL_HANDLE;
}

bool Buffer::copyFrom(const void* src, const VkDeviceSize copy_size, VkDeviceSize offset) const {
    VkDeviceSize mem_size = copy_size > 0 ? copy_size : size;
    void* data;
    auto ret = vmaMapMemory(device, allocation, &data);
    if (VK_SUCCESS != ret) {
        vktLogE("Failed to map buffer memory: {}", VkStr(VkResult, ret));
        return false;
    }
    std::memcpy((uint8_t*)data + offset, src, (size_t)mem_size);
    vmaUnmapMemory(device, allocation);
    return true;
}

bool Buffer::copyInto(void* dst, const VkDeviceSize copy_size, VkDeviceSize offset) const {
    VkDeviceSize mem_size = copy_size > 0 ? copy_size : size;
    void* data;
    auto ret = vmaMapMemory(device, allocation, &data);
    if (VK_SUCCESS != ret) {
        vktLogE("Failed to map buffer memory: {}", VkStr(VkResult, ret));
        return false;
    }
    std::memcpy(dst, (uint8_t*)data + offset, (size_t)mem_size);
    vmaUnmapMemory(device, allocation);
    return true;
}

Res<void*> Buffer::map() const {
    void* data;
    OnRet(vmaMapMemory(device, allocation, &data), "Failed to map buffer memory");
    return Ok(data);
}

void Buffer::unmap() const {
    vmaUnmapMemory(device, allocation);
}

Res<Buffer> Buffer::from(const Device& device, const BufferState& info) {
    Buffer buffer(device);

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = info.memory_flags;
    allocation_ci.usage = info.memory_usage;
    VmaAllocationInfo allocation_info{};

    OnRet(vmaCreateBuffer(device, &info.buffer_ci, &allocation_ci, buffer, &buffer.allocation, &allocation_info),
          "Failed to create buffer");
    OnName(buffer, info.__name);
    buffer.size = info.buffer_ci.size;
    buffer.memory = allocation_info.deviceMemory;

    return Ok(std::move(buffer));
}

Res<Buffer> Buffer::native_from(const Device& device, const BufferState& info, VkMemoryPropertyFlags memory_props) {
    Buffer buffer(device);

    OnRet(vkCreateBuffer(device, &info.buffer_ci, nullptr, buffer), "Failed to create buffer");
    OnName(buffer, info.__name);
    buffer.size = info.buffer_ci.size;

    // Allocate memory for buffer
    VkMemoryRequirements reqs;
    vkGetBufferMemoryRequirements(device, buffer, &reqs);
    VkPhysicalDeviceMemoryProperties props;
    vkGetPhysicalDeviceMemoryProperties(device.physical_device, &props);
    Opt<uint32_t> memory_typeidx{};
    for (uint32_t k = 0; k < props.memoryTypeCount; k++) {
        if ((reqs.memoryTypeBits & (1 << k)) && (props.memoryTypes[k].propertyFlags & memory_props) == memory_props) {
            memory_typeidx = k;
            break;
        }
    }
    if (!memory_typeidx.has_value()) {
        return Er("Failed to find suitable memory type for buffer");
    }

    auto memory_ai = Itor::MemoryAllocateInfo();
    memory_ai.allocationSize = reqs.size;
    memory_ai.memoryTypeIndex = memory_typeidx.value();
    OnRet(vkAllocateMemory(device, &memory_ai, nullptr, &buffer.memory), "Failed to allocate buffer memory");
    vkBindBufferMemory(device, buffer, buffer.memory, 0);

    // vkMapMemory(device, memory, 0, size, 0, &data);
    // vkUnmapMemory(device, memory);

    return Ok(std::move(buffer));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
