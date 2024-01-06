#include "buffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = BufferBuilder::Self;

Buffer::Buffer(Buffer&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    size = rhs.size;
    memory = rhs.memory;
    rhs.memory = VK_NULL_HANDLE;
    allocation = rhs.allocation;
    rhs.allocation = VK_NULL_HANDLE;
}

Buffer::~Buffer() {
    if (handle) {
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

void Buffer::copyFrom(VkDeviceSize dst_offset, const void* src, const VkDeviceSize src_size) const {
    VkDeviceSize copy_size = src_size > 0 ? src_size : size;
    void* data;
    vmaMapMemory(device, allocation, &data);
    std::memcpy((uint8_t*)data + dst_offset, src, (size_t)copy_size);
    vmaUnmapMemory(device, allocation);
}

void Buffer::copyTo(const CommandBuffer& cmdbuf, const Buffer& dst, const VkDeviceSize dst_size) const {
    VkDeviceSize copy_size = dst_size > 0 ? dst_size : size;

    cmdbuf.begin();
    VkBufferCopy copy{};
    copy.srcOffset = 0;
    copy.dstOffset = 0;
    copy.size = copy_size;
    vkCmdCopyBuffer(cmdbuf, handle, dst, 1, &copy);
    cmdbuf.end();

    device.queues.transfer->submit(cmdbuf);
    device.queues.transfer->waitIdle();
}

void Buffer::copyTo(const CommandBuffer& cmdbuf, const Image& dst, const VkDeviceSize dst_size) const {
    VkDeviceSize copy_size = dst_size > 0 ? dst_size : size;

    cmdbuf.begin();
    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferRowLength = 0;
    copy.bufferImageHeight = 0;
    copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    copy.imageSubresource.mipLevel = 0;
    copy.imageSubresource.baseArrayLayer = 0;
    copy.imageSubresource.layerCount = 1;
    copy.imageOffset = VkOffset3D{0, 0, 0};
    copy.imageExtent = VkExtent3D{dst.extent.width, dst.extent.height, 1};
    vkCmdCopyBufferToImage(cmdbuf, handle, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);
    cmdbuf.end();

    device.queues.transfer->submit(cmdbuf);
    device.queues.transfer->waitIdle();
}

Self BufferBuilder::setSize(VkDeviceSize size) {
    info.buffer_ci.size = size;
    return *this;
}

Self BufferBuilder::setUsage(VkBufferUsageFlags flags) {
    info.buffer_ci.usage = flags;
    return *this;
}

Self BufferBuilder::setMemoryFlags(VmaAllocationCreateFlags flags) {
    info.memory_flags = flags;
    return *this;
}

Self BufferBuilder::setMemoryUsage(VmaMemoryUsage usage) {
    info.memory_usage = usage;
    return *this;
}

BufferBuilder::Built BufferBuilder::build() {
    Buffer buffer(device, std::move(info.__name));

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = info.memory_flags;
    allocation_ci.usage = info.memory_usage;
    VmaAllocationInfo allocation_info{};

    OnRet(vmaCreateBuffer(device, &info.buffer_ci, &allocation_ci, buffer, &buffer.allocation, &allocation_info),
          "Failed to create buffer");
    OnName(buffer);
    buffer.size = info.buffer_ci.size;
    buffer.memory = allocation_info.deviceMemory;

    return Ok(std::move(buffer));
}

BufferBuilder::Built BufferBuilder::build_native(VkMemoryPropertyFlags memory_props) {
    Buffer buffer(device, std::move(info.__name));

    OnRet(vkCreateBuffer(device, &info.buffer_ci, nullptr, buffer), "Failed to create buffer");
    OnName(buffer);
    buffer.size = info.buffer_ci.size;

    // Allocate memory for buffer
    VkMemoryRequirements reqs;
    vkGetBufferMemoryRequirements(device, buffer, &reqs);
    VkPhysicalDeviceMemoryProperties props;
    vkGetPhysicalDeviceMemoryProperties(device.physical_device, &props);
    std::optional<uint32_t> memory_typeidx{};
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

    // vkMapMemory(device, memory, 0, copy_size, 0, &data);
    // vkUnmapMemory(device, memory);

    return Ok(std::move(buffer));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
