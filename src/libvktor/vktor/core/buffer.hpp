#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Buffer;

class BufferState : public CoreStater<BufferState> {
    friend struct Buffer;

private:
    VkBufferCreateInfo buffer_ci{};
    VmaAllocationCreateFlags memory_flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    VmaMemoryUsage memory_usage = VMA_MEMORY_USAGE_AUTO;

public:
    explicit BufferState(Name&& name = "Buffer") : CoreStater(std::move(name)) {
        buffer_ci = Itor::BufferCreateInfo();
        buffer_ci.flags = 0;
        buffer_ci.size = 0;
        buffer_ci.usage = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;
        // TODO: Support exclusive and concurrent mode
        buffer_ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        buffer_ci.queueFamilyIndexCount = 0;
        buffer_ci.pQueueFamilyIndices = nullptr;
    }

    Self setSize(VkDeviceSize size);
    Self setUsage(VkBufferUsageFlags flags);

    Self setMemoryFlags(VmaAllocationCreateFlags flags);
    Self setMemoryUsage(VmaMemoryUsage usage);

    Res<Buffer> into(const Device& device) const;
};

struct Buffer : public CoreResource<VkBuffer, VK_OBJECT_TYPE_BUFFER, Device> {
    VkDeviceSize size = 0;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;

protected:
    explicit Buffer(const Device& device) : CoreResource(device) {}

public:
    Buffer(Buffer&&);
    ~Buffer();
    OnConstType(VkDeviceMemory, memory);

    /**
     * @brief Copy data from cpu memory `src` into gpu buffer memory
     *
     * There should be `copy_size` <= Buffer::size - `dst_offset`
     *
     * @param copy_size The copy size in bytes. Give 0 to use Buffer::size.
     * @param offset The buffer memory offset to copy into
     */
    bool copyFrom(const void* src, const VkDeviceSize copy_size = 0, VkDeviceSize offset = 0) const;
    /**
     * @brief Copy data from gpu buffer memory into cpu memory `dst`
     *
     * There should be `copy_size` <= Buffer::size - `dst_offset`
     *
     * @param copy_size The copy size in bytes. Give 0 to use Buffer::size.
     * @param offset The buffer memory offset to copy from
     */
    bool copyInto(void* dst, const VkDeviceSize copy_size = 0, VkDeviceSize offset = 0) const;
    Res<void*> map() const;
    void unmap() const;

    static Res<Buffer> from(const Device& device, const BufferState& info);
    /**
     * @brief Create buffer with native Vulkan api without device.mem_allocator for reference
     */
    static Res<Buffer> native_from(const Device& device,
                                   const BufferState& info,
                                   VkMemoryPropertyFlags memory_props = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
