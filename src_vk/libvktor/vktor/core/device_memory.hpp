#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DeviceMemory;

class DeviceMemoryState : public CoreState<DeviceMemoryState> {
    friend struct DeviceMemory;

private:
    VkMemoryRequirements requirements{};
    VkMemoryPropertyFlags prop_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

public:
    explicit DeviceMemoryState(String&& name = "DeviceMemory") : CoreState(std::move(name)) {}

    Self setPropertyFlags(VkMemoryPropertyFlags flags);
    Self setRequirements(VkMemoryRequirements reqs);

    Res<DeviceMemory> into(const CoreApi& api) const;
};

struct DeviceMemory : public CoreResource<VkDeviceMemory, VK_OBJECT_TYPE_DEVICE_MEMORY> {
protected:
    VkDeviceSize size = 0;

protected:
    explicit DeviceMemory(const CoreApi& api) : CoreResource(api) {}

public:
    DeviceMemory(DeviceMemory&&);
    ~DeviceMemory();

    inline VkDeviceSize getSize() const {
        return size;
    }
    inline VkResult bind(VkBuffer buffer, VkDeviceSize offset = 0) const {
        return vkBindBufferMemory(api, buffer, handle, offset);
    }
    inline VkResult bind(VkImage image, VkDeviceSize offset = 0) const {
        return vkBindImageMemory(api, image, handle, offset);
    }
    Res<void*> map(VkMemoryMapFlags flags = 0) const;
    void unmap() const;

    /**
     * @brief Find an valid VkMemoryAllocateInfo.memoryTypeIndex
     *
     * Must check whether the return < VK_MAX_MEMORY_TYPES or not
     */
    static uint32_t findMemoryTypeIndex(VkPhysicalDevice phy_dev, uint32_t type_bits, VkMemoryPropertyFlags flags);
    static Res<DeviceMemory> from(const CoreApi& api, const DeviceMemoryState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
