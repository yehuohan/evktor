#pragma once
#include "__core.hpp"
#include "device_memory_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Buffer;

class BufferState : public CoreState<BufferState> {
    friend struct Buffer;
    friend struct DeviceMemoryPool;

private:
    mutable VkBufferCreateInfo buffer_ci{};
    VmaAllocationCreateFlags memory_flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    VmaMemoryUsage memory_usage = VMA_MEMORY_USAGE_AUTO;
    const DeviceMemoryPool* memory_pool = nullptr;

public:
    explicit BufferState(String&& name = "Buffer") : CoreState(std::move(name)) {
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
    Self setUsage(VkBufferUsageFlags usage);

    Self setMemoryFlags(VmaAllocationCreateFlags flags);
    Self setMemoryUsage(VmaMemoryUsage usage);
    Self setMemoryPool(const DeviceMemoryPool* pool);

    Res<Buffer> into(const CoreApi& api) const;
};

using VkhBuffer = VkHandle<VkBuffer>;

template <>
struct VkHandle<VkBuffer> : public vk_parent_s<VkBuffer> {
    VK_HANDLE_IMPL(VkBuffer)

protected:
    VkDeviceSize size = 0;

public:
    explicit VkHandle(VkBuffer h, VkDeviceSize _size = 0, VkDevice p = VK_NULL_HANDLE)
        : HasDevice(p)
        , __handle(h)
        , size(_size) {}

    inline VkDeviceSize getSize() const {
        return size;
    }
};

struct Buffer : public CoreResource<VkBuffer, VK_OBJECT_TYPE_BUFFER> {
    friend struct CommandBuffer;

protected:
    VmaAllocation allocation = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    mutable void* memory_mapped = nullptr;
    const bool borrowed_memory_mapped = false;

protected:
    explicit Buffer(const CoreApi& api) : CoreResource(api) {}
    explicit Buffer(const CoreApi& api,
                    VkHandle<VkBuffer> h,
                    VkDeviceMemory _memory = VK_NULL_HANDLE,
                    void* _memory_mapped = nullptr)
        : CoreResource(api, h)
        , memory(_memory)
        , memory_mapped(_memory_mapped)
        , borrowed_memory_mapped(memory_mapped != nullptr) {}

public:
    Buffer(Buffer&&);
    ~Buffer();
    OnConstType(VkDeviceMemory, memory);

    /**
     * @brief Copy data from cpu memory `src` into gpu buffer memory
     *
     * @param copy_size The copy size in bytes. VK_WHOLE_SIZE means Buffer::size.
     * @param offset The buffer memory offset to copy into
     */
    bool copyFrom(const void* src, const VkDeviceSize copy_size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) const;
    /**
     * @brief Copy data from gpu buffer memory into cpu memory `dst`
     *
     * @param copy_size The copy size in bytes. VK_WHOLE_SIZE means Buffer::size.
     * @param offset The buffer memory offset to copy from
     */
    bool copyInto(void* dst, const VkDeviceSize copy_size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) const;
    Res<void*> map() const;
    void unmap() const;
    VkResult getFd(int& fd, VkExternalMemoryHandleTypeFlagBits hdl_type = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT);
#ifdef VK_USE_PLATFORM_WIN32_KHR
    VkResult getWin32Handle(HANDLE& hdl,
                            VkExternalMemoryHandleTypeFlagBits hdl_type = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT);
#endif

    static Res<Buffer> from(const CoreApi& api, const BufferState& info);
    /**
     * @brief Borrow buffer from already created buffer
     */
    static Res<Buffer> borrow(const CoreApi& api,
                              VkHandle<VkBuffer> handle,
                              VkDeviceMemory memory = VK_NULL_HANDLE,
                              void* memory_mapped = nullptr);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
