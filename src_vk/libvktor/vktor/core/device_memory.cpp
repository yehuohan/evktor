#include "device_memory.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DeviceMemoryState::Self;

Self DeviceMemoryState::setPropertyFlags(VkMemoryPropertyFlags flags) {
    prop_flags = flags;
    return *this;
}

Self DeviceMemoryState::setRequirements(VkMemoryRequirements reqs) {
    requirements = reqs;
    return *this;
}

Res<DeviceMemory> DeviceMemoryState::into(const CoreApi& api) const {
    return DeviceMemory::from(api, *this);
}

DeviceMemory::DeviceMemory(DeviceMemory&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

DeviceMemory::~DeviceMemory() {
    if (!__borrowed && handle) {
        vkFreeMemory(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<void*> DeviceMemory::map(VkMemoryMapFlags flags) const {
    void* data;
    OnRet(vkMapMemory(api, handle, 0, size, flags, &data), "Failed to map device memory");
    return Ok(data);
}

void DeviceMemory::unmap() const {
    vkUnmapMemory(api, handle);
}

uint32_t DeviceMemory::findMemoryTypeIndex(VkPhysicalDevice phy_dev, uint32_t type_bits, VkMemoryPropertyFlags flags) {
    VkPhysicalDeviceMemoryProperties props;
    vkGetPhysicalDeviceMemoryProperties(phy_dev, &props);
    for (uint32_t k = 0; k < props.memoryTypeCount; k++) {
        if ((type_bits & (1 << k)) && (props.memoryTypes[k].propertyFlags & flags) == flags) {
            return k;
        }
    }
    return VK_MAX_MEMORY_TYPES;
}

Res<DeviceMemory> DeviceMemory::from(const CoreApi& api, const DeviceMemoryState& info) {
    DeviceMemory memory(api);

    auto memory_ci = Itor::MemoryAllocateInfo(info.__next);
    memory_ci.allocationSize = info.requirements.size;
    memory_ci.memoryTypeIndex = findMemoryTypeIndex(api, info.requirements.memoryTypeBits, info.prop_flags);
    if (memory_ci.memoryTypeIndex >= VK_MAX_MEMORY_TYPES) {
        return Er("Failed to find suitable device memory type");
    }

    OnRet(vkAllocateMemory(api, &memory_ci, api, memory), "Faild to allocate device memory");
    OnName(memory, info.__name);
    memory.size = info.requirements.size;

    return Ok(std::move(memory));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
