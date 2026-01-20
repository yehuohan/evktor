#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

class BufferState;
class ImageState;
struct DeviceMemoryPool;

class DeviceMemoryPoolState : public CoreState<DeviceMemoryPoolState> {
    friend struct DeviceMemoryPool;

private:
    mutable VmaPoolCreateInfo pool_ci{};
#if VK_KHR_external_memory // As a block region
    bool has_external_memory = false;
    VkExternalMemoryHandleTypeFlags external_hdltype = 0;
#endif

public:
    explicit DeviceMemoryPoolState() : CoreState("") {}

    Self setBlockSize(VkDeviceSize size);
#if VK_KHR_external_memory
    /**
     * @brief Set enable external memory handle type to enable exporting memory handle
     */
    Self setExternalHandleType(VkExternalMemoryHandleTypeFlags flags);
#endif

    Res<DeviceMemoryPool> into(const CoreApi& api, const BufferState& buf_info) const;
    Res<DeviceMemoryPool> into(const CoreApi& api, const ImageState& img_info) const;
};

/**
 * @brief Device memory pool based on VmaPool
 *
 * This device memory pool should only work for vkt::core::{Buffer, Image} who's memory
 * is allocated with VmaAllocator.
 * VmaPool can't work with VK_EXT_debug_utils. So set OBJECT_TYPE to VK_OBJECT_TYPE_MAX_ENUM.
 */
struct DeviceMemoryPool : public CoreResource<VmaPool, VK_OBJECT_TYPE_MAX_ENUM> {
    friend struct Buffer;
    friend struct Image;

protected:
    /** @brief Export memory handle requires device extensions: VK_KHR_external_memory, VK_KHR_external_memory_fd.
     *
     * Must wrap `export_memory_ai` in a pointer, because it is required by VMA later.
     */
    Box<VkExportMemoryAllocateInfo> export_memory_ai = nullptr;

protected:
    explicit DeviceMemoryPool(const CoreApi& api) : CoreResource(api) {}

public:
    DeviceMemoryPool(DeviceMemoryPool&&);
    ~DeviceMemoryPool();

    /**
     * @brief Construct memory pool with BufferState
     */
    static Res<DeviceMemoryPool> from(const CoreApi& api, const DeviceMemoryPoolState& info, const BufferState& buf_info);
    /**
     * @brief Construct memory pool with ImageState
     */
    static Res<DeviceMemoryPool> from(const CoreApi& api, const DeviceMemoryPoolState& info, const ImageState& ima_info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
