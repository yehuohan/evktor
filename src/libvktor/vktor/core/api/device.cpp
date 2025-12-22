#include "device.hpp"
#include <algorithm>
#include <set>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DeviceState::Self;

Self DeviceState::setMaxQueueCount(uint32_t count) {
    max_queue_count = std::max<uint32_t>(1, count);
    return *this;
}

Self DeviceState::addExtension(const char* extension) {
    extensions.push_back(extension);
    return *this;
}

Self DeviceState::addExtensions(const Vector<const char*> _extensions) {
    extensions.insert(extensions.end(), _extensions.begin(), _extensions.end());
    return *this;
}

Self DeviceState::addExtensionsForVMA() {
    require_extensions_for_vma = true;
    return *this;
}

Res<Device> DeviceState::into(CRef<PhysicalDevice> phy_dev) {
    return Device::from(phy_dev, *this);
}

Device::Device(Device&& rhs) : physical_device(rhs.physical_device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    mem_allocator = rhs.mem_allocator;
    rhs.mem_allocator = VK_NULL_HANDLE;
}

Device::~Device() {
    if (mem_allocator) {
        vmaDestroyAllocator(mem_allocator);
    }
    if (!__borrowed && handle) {
        vkDestroyDevice(handle, physical_device.get().instance.get().allocator);
    }
    handle = VK_NULL_HANDLE;
    mem_allocator = VK_NULL_HANDLE;
}

Device& Device::operator=(Device&& rhs) {
    if (this != &rhs) {
        if (mem_allocator) {
            vmaDestroyAllocator(mem_allocator);
        }
        if (!__borrowed && handle) {
            vkDestroyDevice(handle, physical_device.get().instance.get().allocator);
        }

        handle = rhs.handle;
        rhs.handle = VK_NULL_HANDLE;
        __borrowed = rhs.__borrowed;
        mem_allocator = rhs.mem_allocator;
        rhs.mem_allocator = VK_NULL_HANDLE;
    }
    return *this;
}

Res<Device> Device::from(CRef<PhysicalDevice> phy_dev, DeviceState& info) {
    Device device(phy_dev);

    if (info.require_extensions_for_vma) {
        info.addExtension(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);
        info.addExtension(VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME);
    }
    std::sort(info.extensions.begin(), info.extensions.end(), strLess);
    auto new_end = std::unique(info.extensions.begin(), info.extensions.end());
    info.extensions.erase(new_end, info.extensions.end());

    if (!checkDeviceExtensions(phy_dev.get(), info.extensions)) {
        return Er("Not all the required device extensions are supported");
    }
    if (info.__verbose) {
        printDeviceExtensions(phy_dev.get(), info.extensions);
    }

    // Create all queues
    Vector<VkDeviceQueueCreateInfo> queues_ci{};
    Vector<Vector<float>> priorities(phy_dev.get().queue_family_props.size());
    for (auto& q : phy_dev.get().queue_family_props) {
        // Update the number of queues to create
        q.second.count = std::min<uint32_t>(info.max_queue_count, q.second.count);
        priorities.push_back(Vector<float>(q.second.count, VKT_CORE_QUEUE_PRIORITY));

        auto dev_queue_ci = Itor::DeviceQueueCreateInfo();
        dev_queue_ci.queueFamilyIndex = q.first;
        dev_queue_ci.queueCount = q.second.count;
        dev_queue_ci.pQueuePriorities = priorities.back().data();
        queues_ci.push_back(dev_queue_ci);
    }

    // Create device
    traverseNext(info.__next, [](const VkBaseInStructure& node) {
        if (node.sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2) {
            vktLogW("VkPhysicalDeviceFeatures2 is not unnecessary for Device will always provide it");
        } else if (node.sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES) {
            vktLogW("VkPhysicalDeviceVulkan11Features is not unnecessary for Device will always provide it");
        } else if (node.sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES) {
            vktLogW("VkPhysicalDeviceVulkan12Features is not unnecessary for Device will always provide it");
        } else if (node.sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES) {
            vktLogW("VkPhysicalDeviceVulkan13Features is not unnecessary for Device will always provide it");
        }
        return false;
    });
    auto dev_ci = Itor::DeviceCreateInfo(info.features.into(info.__next)); // Device-only layers are deprecated
    dev_ci.queueCreateInfoCount = u32(queues_ci.size());
    dev_ci.pQueueCreateInfos = queues_ci.data();
    dev_ci.enabledExtensionCount = u32(info.extensions.size());
    dev_ci.ppEnabledExtensionNames = info.extensions.data();
    dev_ci.pEnabledFeatures = nullptr; // Always set features by VkPhysicalDeviceFeatures2.features

    OnRet(vkCreateDevice(phy_dev.get(), &dev_ci, phy_dev.get().instance.get(), device), "Failed to create device");

    // Support only just one VkDevice object
    volkLoadDevice(device);

    // Create memory allocator
    auto vma_flags = 0;
    if (info.require_extensions_for_vma) {
        vma_flags = VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT | VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT;
    }
    OnRet(device.createMemAllocator(vma_flags), "Failed to create memory allocator");

    return Ok(std::move(device));
}

Res<Device> Device::borrow(CRef<PhysicalDevice> phy_dev,
                           VkDevice handle,
                           PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr,
                           VmaAllocator mem_allocator) {
    Device device{phy_dev};
    device.__borrowed = true;
    device.handle = handle;

    if (fpGetDeviceProcAddr) {
        vkGetDeviceProcAddr = fpGetDeviceProcAddr;
    }
    volkLoadDevice(device);

    if (mem_allocator) {
        device.mem_allocator = mem_allocator;
    } else {
        OnRet(device.createMemAllocator(), "Failed to create memory allocator");
    }

    return Ok(std::move(device));
}

VkResult Device::createMemAllocator(VmaAllocatorCreateFlags flags) {
    VmaVulkanFunctions fns{};
    VmaAllocatorCreateInfo vma_allocator_ai{};
    vma_allocator_ai.vulkanApiVersion = physical_device.get().instance.get().api_version;
    vma_allocator_ai.instance = physical_device.get().instance.get();
    vma_allocator_ai.physicalDevice = physical_device.get();
    vma_allocator_ai.device = handle;
    vma_allocator_ai.pVulkanFunctions = &fns;
    vma_allocator_ai.flags = flags;
#if 1
    // Define VMA_STATIC_VULKAN_FUNCTIONS=0 and VMA_DYNAMIC_VULKAN_FUNCTIONS=0 to work with volk
    auto res = vmaImportVulkanFunctionsFromVolk(&vma_allocator_ai, &fns);
    if (VK_SUCCESS != res) {
        vktLogE("Failed to import Vulkan functions from Volk");
        return res;
    }
#else
    // Use default VMA_DYNAMIC_VULKAN_FUNCTIONS=1
    fns.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
    fns.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
#endif
    return vmaCreateAllocator(&vma_allocator_ai, &mem_allocator);
}

bool checkDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& device_extensions) {
    Vector<VkExtensionProperties> exts{};
    VkResult res = enumerate(exts, vkEnumerateDeviceExtensionProperties, pd, nullptr);
    if (res != VK_SUCCESS) {
        vktLogE("Failed to get properties of device extensions: {}", VkStr(VkResult, res));
        return false;
    }

    std::set<String> device_exts(device_extensions.begin(), device_extensions.end());
    for (const auto& e : exts) {
        device_exts.erase(e.extensionName);
    }

    bool empty = device_exts.empty();
    if (!empty) {
        vktLogW("Not supported device extensions:");
        for (const auto& e : device_exts) {
            vktLogW("\t{}", e);
        }
    }
    return empty;
}

void printDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& enabled_extensions) {
    Vector<VkExtensionProperties> ext_props{};
    VkResult res = enumerate(ext_props, vkEnumerateDeviceExtensionProperties, pd, nullptr);
    if (res != VK_SUCCESS) {
        vktLogE("Failed to get properties of device extensions: {}", VkStr(VkResult, res));
        return;
    }

    String str("Available device extensions {\n");
    for (const auto& e : ext_props) {
        str += vktFmt("\t{}\n", e.extensionName);
    }
    str += "}\n";

    str += "Enabled device extensions {\n";
    for (const auto& e : enabled_extensions) {
        str += vktFmt("\t{}\n", e);
    }
    str += "}";

    vktOut("{}", str);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
