#include "device_memory_pool.hpp"
#include "buffer.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DeviceMemoryPoolState::Self;

Self DeviceMemoryPoolState::setBlockSize(VkDeviceSize size) {
    pool_ci.blockSize = size;
    return *this;
}

#if VK_KHR_external_memory
Self DeviceMemoryPoolState::setExternalHandleType(VkExternalMemoryHandleTypeFlags flags) {
    has_external_memory = true;
    external_hdltype = flags;
    return *this;
}
#endif

Res<DeviceMemoryPool> DeviceMemoryPoolState::into(const CoreApi& api, const BufferState& buf_info) const {
    return DeviceMemoryPool::from(api, *this, buf_info);
}

Res<DeviceMemoryPool> DeviceMemoryPoolState::into(const CoreApi& api, const ImageState& img_info) const {
    return DeviceMemoryPool::from(api, *this, img_info);
}

DeviceMemoryPool::DeviceMemoryPool(DeviceMemoryPool&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    export_memory_ai = std::move(rhs.export_memory_ai);
}

DeviceMemoryPool::~DeviceMemoryPool() {
    if (!__borrowed && handle) {
        vmaDestroyPool(api, handle);
    }
    handle = VK_NULL_HANDLE;
    export_memory_ai.reset();
}

Res<DeviceMemoryPool> DeviceMemoryPool::from(const CoreApi& api,
                                             const DeviceMemoryPoolState& info,
                                             const BufferState& buf_info) {
    DeviceMemoryPool mem_pool(api);

    auto external_memory_ci = Itor::ExternalMemoryBufferCreateInfo();
    buf_info.buffer_ci.pNext = info.__next;
#if VK_KHR_external_memory
    if (info.has_external_memory) {
        external_memory_ci.handleTypes = info.external_hdltype;
        chainNext(buf_info.buffer_ci, &external_memory_ci);

        mem_pool.export_memory_ai = newBox<VkExportMemoryAllocateInfo>(Itor::ExportMemoryAllocateInfo());
        mem_pool.export_memory_ai->handleTypes = info.external_hdltype;
    }
#endif

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = buf_info.memory_flags;
    allocation_ci.usage = buf_info.memory_usage;

    OnRet(vmaFindMemoryTypeIndexForBufferInfo(api, &buf_info.buffer_ci, &allocation_ci, &info.pool_ci.memoryTypeIndex),
          "Failed to get memory type index with buffer create info");
    info.pool_ci.pMemoryAllocateNext = mem_pool.export_memory_ai.get();
    OnRet(vmaCreatePool(api, &info.pool_ci, mem_pool), "Failed to create memory pool with buffer create info");

    return Ok(std::move(mem_pool));
}

Res<DeviceMemoryPool> DeviceMemoryPool::from(const CoreApi& api,
                                             const DeviceMemoryPoolState& info,
                                             const ImageState& img_info) {
    DeviceMemoryPool mem_pool(api);

    auto external_memory_ci = Itor::ExternalMemoryImageCreateInfo();
    img_info.image_ci.pNext = info.__next;
#if VK_KHR_external_memory
    if (info.has_external_memory) {
        external_memory_ci.handleTypes = info.external_hdltype;
        chainNext(img_info.image_ci, &external_memory_ci);

        mem_pool.export_memory_ai = newBox<VkExportMemoryAllocateInfo>(Itor::ExportMemoryAllocateInfo());
        mem_pool.export_memory_ai->handleTypes = info.external_hdltype;
    }
#endif

    VmaAllocationCreateInfo allocation_ci{};
    allocation_ci.flags = img_info.memory_flags;
    allocation_ci.usage = img_info.memory_usage;

    OnRet(vmaFindMemoryTypeIndexForImageInfo(api, &img_info.image_ci, &allocation_ci, &info.pool_ci.memoryTypeIndex),
          "Failed to get memory type index with image create info");
    info.pool_ci.pMemoryAllocateNext = mem_pool.export_memory_ai.get();
    OnRet(vmaCreatePool(api, &info.pool_ci, mem_pool), "Failed to create memory pool with image create info");

    return Ok(std::move(mem_pool));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
