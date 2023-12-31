#include "device.hpp"
#include "utils.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DeviceBuilder::Self;

Device::Device(Device&& rhs)
    : BuiltHandle(std::move(rhs.__name))
    , instance(rhs.instance)
    , physical_device(rhs.physical_device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    queues = std::move(rhs.queues);
    rhs.queues.clear();
    queue_indices = std::move(rhs.queue_indices);
    rhs.queue_indices.clear();
    mem_allocator = rhs.mem_allocator;
    rhs.mem_allocator = VK_NULL_HANDLE;
}

Device::~Device() {
    if (mem_allocator) {
        vmaDestroyAllocator(mem_allocator);
    }
    if (handle) {
        vkDestroyDevice(handle, nullptr);
    }
    queues.clear();
    queue_indices.clear();
    handle = VK_NULL_HANDLE;
    mem_allocator = VK_NULL_HANDLE;
}

DeviceBuilder::Built DeviceBuilder::build() {
    Device device(instance, physical_device, std::move(info.__name));

    const float queue_priority = VKt_CORE_QUEUE_PRIORITY;
    Vector<VkDeviceQueueCreateInfo> queues_ci;
    for (const auto& q : physical_device.queue_family_props) {
        auto dev_queue_ci = Itor::DeviceQueueCreateInfo();
        dev_queue_ci.queueFamilyIndex = q.first;
        dev_queue_ci.queueCount = q.second.count;
        dev_queue_ci.pQueuePriorities = &queue_priority;
        queues_ci.push_back(dev_queue_ci);
    }

    // Create device
    VkPhysicalDeviceFeatures pdev_feats{};
    auto dev_ci = Itor::DeviceCreateInfo();
    dev_ci.queueCreateInfoCount = u32(queues_ci.size());
    dev_ci.pQueueCreateInfos = queues_ci.data();
    // Lastest vulkan implementation, there is no validation layers distinction between instance
    // and device. But it's ok to set validation layers explicitly for compatiblity here.
    //.enabledLayerCount = u32(validation_layers.size()),
    //.ppEnabledLayerNames = validation_layers.data(),
    dev_ci.enabledExtensionCount = u32(physical_device.extensions.size());
    dev_ci.ppEnabledExtensionNames = physical_device.extensions.data();
    dev_ci.pEnabledFeatures = &pdev_feats;

    if (info.__verbose) {
        printDeviceExtensions(physical_device, physical_device.extensions);
    }

    OnRet(vkCreateDevice(physical_device, &dev_ci, nullptr, device), "Failed to create device");
    OnRet(core::setDebugName(device,
                             VK_OBJECT_TYPE_DEVICE,
                             u64(reinterpret_cast<uint64_t>(device.handle)),
                             device.__name.c_str()),
          "Failed to set debug name: {}",
          device.__name);

    // Support only just one VkDevice object
    volkLoadDevice(device);

    // Queues are automatically created along with device, and we need to retrieve their handles.
    for (const auto& q : physical_device.queue_family_props) {
        uint32_t family_index = q.first;
        for (uint32_t index = 0; index < q.second.count; index++) {
            Queue queue(family_index, index, "Queue" + std::to_string(family_index) + "." + std::to_string(index));
            vkGetDeviceQueue(device, family_index, 0, queue);
            OnRet(queue.setDebugName(device), "Failed to set debug name: {}", queue.__name);
            device.queue_indices[family_index].push_back(std::move(queue));
        }
    }

    // Select the first queue index by default
    const auto& indices = physical_device.queue_families;
    if (indices.present.has_value()) {
        device.queues.present = &device.queue_indices[indices.present.value()][0];
    }
    if (indices.graphics.has_value()) {
        device.queues.graphics = &device.queue_indices[indices.graphics.value()][0];
    }
    if (indices.compute.has_value()) {
        device.queues.compute = &device.queue_indices[indices.compute.value()][0];
    }
    if (indices.transfer.has_value()) {
        device.queues.transfer = &device.queue_indices[indices.transfer.value()][0];
    }

    // Create memory allocator
    OnRet(createMemAllocator(device), "Failed to create memory allocator");

    return Ok(std::move(device));
}

VkResult DeviceBuilder::createMemAllocator(Device& device) {
    VmaVulkanFunctions fns{};
    fns.vkGetPhysicalDeviceProperties = vkGetPhysicalDeviceProperties;
    fns.vkGetPhysicalDeviceMemoryProperties = vkGetPhysicalDeviceMemoryProperties;
    fns.vkAllocateMemory = vkAllocateMemory;
    fns.vkFreeMemory = vkFreeMemory;
    fns.vkMapMemory = vkMapMemory;
    fns.vkUnmapMemory = vkUnmapMemory;
    fns.vkFlushMappedMemoryRanges = vkFlushMappedMemoryRanges;
    fns.vkInvalidateMappedMemoryRanges = vkInvalidateMappedMemoryRanges;
    fns.vkBindBufferMemory = vkBindBufferMemory;
    fns.vkBindImageMemory = vkBindImageMemory;
    fns.vkGetBufferMemoryRequirements = vkGetBufferMemoryRequirements;
    fns.vkGetImageMemoryRequirements = vkGetImageMemoryRequirements;
    fns.vkCreateBuffer = vkCreateBuffer;
    fns.vkDestroyBuffer = vkDestroyBuffer;
    fns.vkCreateImage = vkCreateImage;
    fns.vkDestroyImage = vkDestroyImage;
    fns.vkCmdCopyBuffer = vkCmdCopyBuffer;
    if (instance.api_version >= VK_API_VERSION_1_1) {
        if (physical_device.isExtensionEnabled(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME) &&
            physical_device.isExtensionEnabled(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME)) {
            fns.vkGetBufferMemoryRequirements2KHR = vkGetBufferMemoryRequirements2KHR;
            fns.vkGetImageMemoryRequirements2KHR = vkGetImageMemoryRequirements2KHR;
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
        if (physical_device.isExtensionEnabled(VK_KHR_BIND_MEMORY_2_EXTENSION_NAME)) {
            fns.vkBindBufferMemory2KHR = vkBindBufferMemory2KHR;
            fns.vkBindImageMemory2KHR = vkBindImageMemory2KHR;
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
        if (instance.isExtensionEnabled(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME) &&
            physical_device.isExtensionEnabled(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME)) {
            fns.vkGetPhysicalDeviceMemoryProperties2KHR = vkGetPhysicalDeviceMemoryProperties2KHR;
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    if (instance.api_version >= VK_API_VERSION_1_3 || physical_device.isExtensionEnabled(VK_KHR_MAINTENANCE_4_EXTENSION_NAME)) {
        fns.vkGetDeviceBufferMemoryRequirements = vkGetDeviceBufferMemoryRequirements;
        fns.vkGetDeviceImageMemoryRequirements = vkGetDeviceImageMemoryRequirements;
    }

    VmaAllocatorCreateInfo vma_allocator_ai{};
    vma_allocator_ai.vulkanApiVersion = instance.api_version;
    vma_allocator_ai.instance = instance;
    vma_allocator_ai.physicalDevice = physical_device;
    vma_allocator_ai.device = device;
    vma_allocator_ai.pVulkanFunctions = &fns;
    return vmaCreateAllocator(&vma_allocator_ai, &device.mem_allocator);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
