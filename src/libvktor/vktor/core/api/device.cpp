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

Self DeviceState::addRequiredExtension(const char* extension) {
    required_extensions.push_back(extension);
    return *this;
}

Self DeviceState::addRequiredExtensions(const Vector<const char*> extensions) {
    required_extensions.insert(required_extensions.end(), extensions.begin(), extensions.end());
    return *this;
}

Self DeviceState::setRequiredFeatures(const VkPhysicalDeviceFeatures& features) {
    required_features = features;
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

    // Add required extensions for memory allocator (>= VK_API_VERSION_1_1)
    info.addRequiredExtension(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
    info.addRequiredExtension(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME);
    info.addRequiredExtension(VK_KHR_BIND_MEMORY_2_EXTENSION_NAME);
    info.addRequiredExtension(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);
    std::sort(info.required_extensions.begin(), info.required_extensions.end(), strLess);
    auto new_end = std::unique(info.required_extensions.begin(), info.required_extensions.end());
    info.required_extensions.erase(new_end, info.required_extensions.end());

    if (!checkDeviceExtensions(phy_dev.get(), info.required_extensions)) {
        return Er("Not all the required device extensions are supported");
    }
    if (!checkDeviceFeatures(phy_dev.get(), info.required_features)) {
        return Er("Not all the required device features are supported");
    }
    if (info.__verbose) {
        printDeviceExtensions(phy_dev.get(), info.required_extensions);
        printDeviceFeatures(phy_dev.get(), info.required_features);
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
    auto dev_ci = Itor::DeviceCreateInfo(info.__next); // Device-only layers are deprecated
    dev_ci.queueCreateInfoCount = u32(queues_ci.size());
    dev_ci.pQueueCreateInfos = queues_ci.data();
    dev_ci.enabledExtensionCount = u32(info.required_extensions.size());
    dev_ci.ppEnabledExtensionNames = info.required_extensions.data();
    dev_ci.pEnabledFeatures = traverse(info.__next,
                                       [](const VkBaseInStructure& base) {
                                           return base.sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
                                       })
                                  ? nullptr
                                  : &info.required_features;

    OnRet(vkCreateDevice(phy_dev.get(), &dev_ci, phy_dev.get().instance.get(), device), "Failed to create device");

    // Support only just one VkDevice object
    volkLoadDevice(device);

    // Create memory allocator
    OnRet(device.createMemAllocator(), "Failed to create memory allocator");

    return Ok(std::move(device));
}

Res<Device> Device::borrow(CRef<PhysicalDevice> phy_dev, VkDevice handle, PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr) {
    Device device{phy_dev};
    device.__borrowed = true;
    device.handle = handle;

    if (fpGetDeviceProcAddr) {
        vkGetDeviceProcAddr = fpGetDeviceProcAddr;
    }
    volkLoadDevice(device);

    OnRet(device.createMemAllocator(), "Failed to create memory allocator");

    return Ok(std::move(device));
}

VkResult Device::createMemAllocator() {
    // Use default VMA_DYNAMIC_VULKAN_FUNCTIONS = 1
    VmaVulkanFunctions fns{};
    fns.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
    fns.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
    VmaAllocatorCreateInfo vma_allocator_ai{};
    vma_allocator_ai.vulkanApiVersion = physical_device.get().instance.get().api_version;
    vma_allocator_ai.instance = physical_device.get().instance.get();
    vma_allocator_ai.physicalDevice = physical_device.get();
    vma_allocator_ai.device = handle;
    vma_allocator_ai.pVulkanFunctions = &fns;
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

bool checkDeviceFeatures(VkPhysicalDevice pd, const VkPhysicalDeviceFeatures& device_features) {
    VkPhysicalDeviceFeatures feats{};
    vkGetPhysicalDeviceFeatures(pd, &feats);

#define Check(f)                         \
    if (device_features.f && !feats.f) { \
        return false;                    \
    }

    Check(robustBufferAccess);
    Check(fullDrawIndexUint32);
    Check(imageCubeArray);
    Check(independentBlend);
    Check(geometryShader);
    Check(tessellationShader);
    Check(sampleRateShading);
    Check(dualSrcBlend);
    Check(logicOp);
    Check(multiDrawIndirect);
    Check(drawIndirectFirstInstance);
    Check(depthClamp);
    Check(depthBiasClamp);
    Check(fillModeNonSolid);
    Check(depthBounds);
    Check(wideLines);
    Check(largePoints);
    Check(alphaToOne);
    Check(multiViewport);
    Check(samplerAnisotropy);
    Check(textureCompressionETC2);
    Check(textureCompressionASTC_LDR);
    Check(textureCompressionBC);
    Check(occlusionQueryPrecise);
    Check(pipelineStatisticsQuery);
    Check(vertexPipelineStoresAndAtomics);
    Check(fragmentStoresAndAtomics);
    Check(shaderTessellationAndGeometryPointSize);
    Check(shaderImageGatherExtended);
    Check(shaderStorageImageExtendedFormats);
    Check(shaderStorageImageMultisample);
    Check(shaderStorageImageReadWithoutFormat);
    Check(shaderStorageImageWriteWithoutFormat);
    Check(shaderUniformBufferArrayDynamicIndexing);
    Check(shaderSampledImageArrayDynamicIndexing);
    Check(shaderStorageBufferArrayDynamicIndexing);
    Check(shaderStorageImageArrayDynamicIndexing);
    Check(shaderClipDistance);
    Check(shaderCullDistance);
    Check(shaderFloat64);
    Check(shaderInt64);
    Check(shaderInt16);
    Check(shaderResourceResidency);
    Check(shaderResourceMinLod);
    Check(sparseBinding);
    Check(sparseResidencyBuffer);
    Check(sparseResidencyImage2D);
    Check(sparseResidencyImage3D);
    Check(sparseResidency2Samples);
    Check(sparseResidency4Samples);
    Check(sparseResidency8Samples);
    Check(sparseResidency16Samples);
    Check(sparseResidencyAliased);
    Check(variableMultisampleRate);
    Check(inheritedQueries);

#undef Check

    return true;
}

void printDeviceFeatures(VkPhysicalDevice pd, const VkPhysicalDeviceFeatures& required_features) {
    VkPhysicalDeviceFeatures feats{};
    vkGetPhysicalDeviceFeatures(pd, &feats);

    String sa("Available device features {\n");
    String sr("Required device features {\n");

#define Print(f)                    \
    if (feats.f) {                  \
        sa += vktFmt("\t{}\n", #f); \
    }                               \
    if (required_features.f) {      \
        sr += vktFmt("\t{}\n", #f); \
    }

    Print(robustBufferAccess);
    Print(fullDrawIndexUint32);
    Print(imageCubeArray);
    Print(independentBlend);
    Print(geometryShader);
    Print(tessellationShader);
    Print(sampleRateShading);
    Print(dualSrcBlend);
    Print(logicOp);
    Print(multiDrawIndirect);
    Print(drawIndirectFirstInstance);
    Print(depthClamp);
    Print(depthBiasClamp);
    Print(fillModeNonSolid);
    Print(depthBounds);
    Print(wideLines);
    Print(largePoints);
    Print(alphaToOne);
    Print(multiViewport);
    Print(samplerAnisotropy);
    Print(textureCompressionETC2);
    Print(textureCompressionASTC_LDR);
    Print(textureCompressionBC);
    Print(occlusionQueryPrecise);
    Print(pipelineStatisticsQuery);
    Print(vertexPipelineStoresAndAtomics);
    Print(fragmentStoresAndAtomics);
    Print(shaderTessellationAndGeometryPointSize);
    Print(shaderImageGatherExtended);
    Print(shaderStorageImageExtendedFormats);
    Print(shaderStorageImageMultisample);
    Print(shaderStorageImageReadWithoutFormat);
    Print(shaderStorageImageWriteWithoutFormat);
    Print(shaderUniformBufferArrayDynamicIndexing);
    Print(shaderSampledImageArrayDynamicIndexing);
    Print(shaderStorageBufferArrayDynamicIndexing);
    Print(shaderStorageImageArrayDynamicIndexing);
    Print(shaderClipDistance);
    Print(shaderCullDistance);
    Print(shaderFloat64);
    Print(shaderInt64);
    Print(shaderInt16);
    Print(shaderResourceResidency);
    Print(shaderResourceMinLod);
    Print(sparseBinding);
    Print(sparseResidencyBuffer);
    Print(sparseResidencyImage2D);
    Print(sparseResidencyImage3D);
    Print(sparseResidency2Samples);
    Print(sparseResidency4Samples);
    Print(sparseResidency8Samples);
    Print(sparseResidency16Samples);
    Print(sparseResidencyAliased);
    Print(variableMultisampleRate);
    Print(inheritedQueries);

#undef Print

    sa += "}\n";
    sr += "}";
    vktOut("{}", sa + sr);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
