#pragma once
#include "__builder.hpp"
#include "command_buffer.hpp"
#include "device.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Buffer : public BuiltResource<VkBuffer, VK_OBJECT_TYPE_BUFFER, Device> {
    VkDeviceSize size = 0;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;

    Buffer(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    Buffer(Buffer&&);
    ~Buffer();
    OnConstType(VkDeviceMemory, memory);

    /**
     * @brief Copy data `src` from cpu to buffer memory at `src_size`
     *
     * There should be `src_size` <= `size`
     *
     * @param dst_offset The buffer offset to copy into
     * @param src_size Give 0 to use `size`
     */
    void copyFrom(VkDeviceSize dst_offset, const void* src, const VkDeviceSize src_size = 0) const;
    inline void copyFrom(const void* src, const VkDeviceSize src_size = 0) const {
        copyFrom(0, src, src_size);
    }

    /**
     * @brief Copy buffer to buffer `dst` at `dst_size`
     *
     * There should be `size` <= `dst_size`
     *
     * @param dst_size Give 0 to use `size`
     */
    void copyTo(const CommandBuffer& cmdbuf, const Buffer& dst, const VkDeviceSize dst_size = 0) const;

    /**
     * @brief Copy buffer to image `dst` at `dst_size`
     *
     * There should be `size` <= `dst_size`
     *
     * @param dst_size Give 0 to use `size`
     */
    void copyTo(const CommandBuffer& cmdbuf, const Image& dst, const VkDeviceSize dst_size = 0) const;
};

struct BufferInfo : public BuilderInfo {
    VkBufferCreateInfo buffer_ci;
    VmaAllocationCreateFlags memory_flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    VmaMemoryUsage memory_usage = VMA_MEMORY_USAGE_AUTO;
};

class BufferBuilder : public Builder<BufferBuilder, Buffer, BufferInfo> {
private:
    const Device& device;

public:
    explicit BufferBuilder(const Device& device, Name&& name = "Buffer") : Builder(std::move(name)), device(device) {
        info.buffer_ci = Itor::BufferCreateInfo();
        info.buffer_ci.flags = 0;
        info.buffer_ci.size = 0;
        info.buffer_ci.usage = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;
        // TODO: Support exclusive and concurrent mode
        info.buffer_ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.buffer_ci.queueFamilyIndexCount = 0;
        info.buffer_ci.pQueueFamilyIndices = nullptr;
    }
    virtual Built build() override;
    /**
     * @brief Build buffer with native Vulkan api without device.mem_allocator for reference
     */
    Built build_native(VkMemoryPropertyFlags memory_props = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    Self setSize(VkDeviceSize size);
    Self setUsage(VkBufferUsageFlags flags);

    Self setMemoryFlags(VmaAllocationCreateFlags flags);
    Self setMemoryUsage(VmaMemoryUsage usage);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
