#include "entry.hpp"
#include "vkt_layer.hpp"
#include <mutex>

NAMESPACE_BEGIN(vktlyr)

static std::mutex ldt_mtx;

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetInstanceProcAddr(VkInstance instance, const char* pName) {
    // Hook required addrs of layer implementation
    auto res = __impl.tryHook(instance, pName);
    if (res) {
        return res;
    }
    // Dispatch addrs to next layer
    {
        std::lock_guard<std::mutex> locker(ldt_mtx);
        auto tbl = __impl.ldt_inst.get(instance);
        if (tbl && tbl->GetInstanceProcAddr) {
            return tbl->GetInstanceProcAddr(instance, pName);
        }
    }
    vktlyrLogE("Not supported instance proc addr: {}", pName);
    return VK_NULL_HANDLE;
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetPhysicalDeviceProcAddr(VkInstance instance, const char* pName) {
    std::lock_guard<std::mutex> locker(ldt_mtx);
    auto tbl = __impl.ldt_inst.get(instance);
    if (tbl && tbl->GetPhysicalDeviceProcAddr) {
        return tbl->GetPhysicalDeviceProcAddr(instance, pName);
    }
    return VK_NULL_HANDLE;
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetDeviceProcAddr(VkDevice device, const char* pName) {
    // Hook required addrs of layer implementation
    auto res = __impl.tryHook(device, pName);
    if (res) {
        return res;
    }
    // Dispatch addrs to next layer
    {
        std::lock_guard<std::mutex> locker(ldt_mtx);
        auto tbl = __impl.ldt_dev.get(device);
        if (tbl && tbl->GetDeviceProcAddr) {
            return tbl->GetDeviceProcAddr(device, pName);
        }
    }
    vktlyrLogE("Not supported device proc addr: {}", pName);
    return VK_NULL_HANDLE;
}

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator,
                                              VkInstance* pInstance) {
    VkLayerInstanceCreateInfo* chain_info = __impl.getChainInfo(pCreateInfo, VK_LAYER_LINK_INFO);
    if (!(chain_info && chain_info->u.pLayerInfo)) {
        vktlyrLogE("Invalid instance chain info");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    if (!fpGetInstanceProcAddr) {
        vktlyrLogE("Invalid fpGetInstanceProcAddr");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    // Advance into the next layer
    chain_info->u.pLayerInfo = chain_info->u.pLayerInfo->pNext;

    PFN_vkCreateInstance fpCreateInstance = (PFN_vkCreateInstance)fpGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance");
    if (!fpCreateInstance) {
        vktlyrLogE("Invalid fpCreateInstance");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    VkResult res = fpCreateInstance(pCreateInfo, pAllocator, pInstance);
    if (pInstance && *pInstance) {
        VkLayerInstanceDispatchTable tbl;
        initLDT(tbl, fpGetInstanceProcAddr, *pInstance);
        {
            std::lock_guard<std::mutex> locker(ldt_mtx);
            __impl.ldt_inst.set(*pInstance, tbl);
        }
    }
    return res;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
    PFN_vkDestroyInstance fpDestroyInstance;
    {
        std::lock_guard<std::mutex> locker(ldt_mtx);
        auto tbl = __impl.ldt_inst.get(instance);
        fpDestroyInstance = tbl ? tbl->DestroyInstance : VK_NULL_HANDLE;
        __impl.ldt_inst.del(instance);
    }
    if (fpDestroyInstance) {
        fpDestroyInstance(instance, pAllocator);
    }
}

VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(VkPhysicalDevice physicalDevice,
                                            const VkDeviceCreateInfo* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator,
                                            VkDevice* pDevice) {
    VkLayerDeviceCreateInfo* chain_info = __impl.getChainInfo(pCreateInfo, VK_LAYER_LINK_INFO);
    if (!(chain_info && chain_info->u.pLayerInfo)) {
        vktlyrLogE("Invalid device chain info");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    if (!fpGetInstanceProcAddr) {
        vktlyrLogE("Invalid fpGetInstanceProcAddr");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr = chain_info->u.pLayerInfo->pfnNextGetDeviceProcAddr;
    if (!fpGetDeviceProcAddr) {
        vktlyrLogE("Invalid fpGetDeviceProcAddr");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    // Advance into the next layer
    chain_info->u.pLayerInfo = chain_info->u.pLayerInfo->pNext;

    PFN_vkCreateDevice fpCreateDevice;
    {
        std::lock_guard<std::mutex> locker(ldt_mtx);
        auto tbl = __impl.ldt_inst.get(physicalDevice);
        auto instance = tbl ? tbl->instance : VK_NULL_HANDLE;
        if (!instance) {
            vktlyrLogW("There's no LDT for physical device: {}", fmt::ptr(physicalDevice));
        }
        fpCreateDevice = (PFN_vkCreateDevice)fpGetInstanceProcAddr(instance, "vkCreateDevice");
    }
    if (!fpCreateDevice) {
        vktlyrLogE("Invalid fpCreateDevice");
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    VkResult res = fpCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
    if (pDevice && *pDevice) {
        VkLayerDeviceDispatchTable tbl;
        initLDT(tbl, fpGetDeviceProcAddr, physicalDevice, *pDevice);
        {
            std::lock_guard<std::mutex> locker(ldt_mtx);
            __impl.ldt_dev.set(*pDevice, tbl);
        }
    }
    return res;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
    PFN_vkDestroyDevice fpDestroyDevice;
    {
        std::lock_guard<std::mutex> locker(ldt_mtx);
        auto tbl = __impl.ldt_dev.get(device);
        fpDestroyDevice = tbl ? tbl->DestroyDevice : VK_NULL_HANDLE;
        __impl.ldt_dev.del(device);
    }
    if (fpDestroyDevice) {
        fpDestroyDevice(device, pAllocator);
    }
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties) {
    // Only need provide current layer's properties, then Vulkan loader will merge all layer's properties.
    return __impl.copyLayerProperties(1, &__impl.getLayerProps(), pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName,
                                                                    uint32_t* pPropertyCount,
                                                                    VkExtensionProperties* pProperties) {
    auto& props = __impl.getLayerProps();
    if (pLayerName && !strcmp(pLayerName, props.layerName)) {
        // Append instance extensions required by the custom layer
        auto& exts = __impl.getInstanceExtensions();
        return __impl.copyExtensionProperties(exts.size(), exts.data(), pPropertyCount, pProperties);
    }
    return VK_ERROR_LAYER_NOT_PRESENT;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice,
                                                              uint32_t* pPropertyCount,
                                                              VkLayerProperties* pProperties) {
    return __impl.copyLayerProperties(1, &__impl.getLayerProps(), pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                  const char* pLayerName,
                                                                  uint32_t* pPropertyCount,
                                                                  VkExtensionProperties* pProperties) {
    auto& props = __impl.getLayerProps();
    if (pLayerName && !strcmp(pLayerName, props.layerName)) {
        auto& exts = __impl.getDeviceExtensions();
        return __impl.copyExtensionProperties(exts.size(), exts.data(), pPropertyCount, pProperties);
    }
    {
        std::lock_guard<std::mutex> locker(ldt_mtx);
        auto tbl = __impl.ldt_inst.get(physicalDevice);
        if (tbl && tbl->EnumerateDeviceExtensionProperties) {
            return tbl->EnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
        }
    }
    return VK_SUCCESS;
}

NAMESPACE_END(vktlyr)

#ifdef __cplusplus
extern "C" {
#endif

VKTLYR_API VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName) {
    return vktlyr::GetInstanceProcAddr(instance, pName);
}

VKTLYR_API VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_layerGetPhysicalDeviceProcAddr(VkInstance instance, const char* pName) {
    return vktlyr::GetPhysicalDeviceProcAddr(instance, pName);
}

VKTLYR_API VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName) {
    return vktlyr::GetDeviceProcAddr(device, pName);
}

VKTLYR_API VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                                           const VkAllocationCallbacks* pAllocator,
                                                           VkInstance* pInstance) {
    return vktlyr::CreateInstance(pCreateInfo, pAllocator, pInstance);
}

VKTLYR_API VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount,
                                                                             VkLayerProperties* pProperties) {
    return vktlyr::EnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

VKTLYR_API VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(const char* pLayerName,
                                                                                 uint32_t* pPropertyCount,
                                                                                 VkExtensionProperties* pProperties) {
    return vktlyr::EnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}

VKTLYR_API VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice,
                                                                           uint32_t* pPropertyCount,
                                                                           VkLayerProperties* pProperties) {
    return vktlyr::EnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
}

VKTLYR_API VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                               const char* pLayerName,
                                                                               uint32_t* pPropertyCount,
                                                                               VkExtensionProperties* pProperties) {
    return vktlyr::EnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
}

VKTLYR_API VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface* pVersionStruct) {
    if (pVersionStruct && pVersionStruct->sType == LAYER_NEGOTIATE_INTERFACE_STRUCT) {
        if (pVersionStruct->loaderLayerInterfaceVersion >= 2) {
            pVersionStruct->pfnGetInstanceProcAddr = vkGetInstanceProcAddr;
            pVersionStruct->pfnGetDeviceProcAddr = vkGetDeviceProcAddr;
            pVersionStruct->pfnGetPhysicalDeviceProcAddr = vk_layerGetPhysicalDeviceProcAddr;
        }
    } else {
        vktlyrLogW("Invalid VkNegotiateLayerInterface");
    }
    return VK_SUCCESS;
}

#ifdef __cplusplus
}
#endif
