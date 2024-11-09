#include "vkt_layer.hpp"

NAMESPACE_BEGIN(vktlyr)

VktorLayerImpl::VktorLayerImpl()
    : hooks{
          vktlyrHook(vktlyr, GetInstanceProcAddr),
          vktlyrHook(vktlyr, GetPhysicalDeviceProcAddr),
          vktlyrHook(vktlyr, GetDeviceProcAddr),
          vktlyrHook(vktlyr, CreateInstance),
          vktlyrHook(vktlyr, DestroyInstance),
          vktlyrHook(vktlyr, CreateDevice),
          vktlyrHook(vktlyr, DestroyDevice),
          vktlyrHook(vktlyr, EnumerateInstanceLayerProperties),
          vktlyrHook(vktlyr, EnumerateInstanceExtensionProperties),
          vktlyrHook(vktlyr, EnumerateDeviceLayerProperties),
          vktlyrHook(vktlyr, EnumerateDeviceExtensionProperties),
      } {}

const PFN_vkVoidFunction VktorLayerImpl::tryHook(VkInstance instance, const char* fname) const {
    auto res = hooks.find(fname);
    if (res != hooks.end()) {
        return res->second;
    }
    return VK_NULL_HANDLE;
}

const PFN_vkVoidFunction VktorLayerImpl::tryHook(VkDevice device, const char* fname) const {
    auto res = hooks.find(fname);
    if (res != hooks.end()) {
        return res->second;
    }
    return VK_NULL_HANDLE;
}

const VkLayerProperties& VktorLayerImpl::getLayerProps() const {
    static const VkLayerProperties props{
        "VK_LAYER_VKTOR_Unknow",
        VK_API_VERSION_1_0,
        1,
        "Vulkan layer with evktor/libvkt_layer",
    };
    return props;
}

const vkt::Vector<VkExtensionProperties>& VktorLayerImpl::getInstanceExtensions() const {
    static const vkt::Vector<VkExtensionProperties> props{};
    return props;
}

const vkt::Vector<VkExtensionProperties>& VktorLayerImpl::getDeviceExtensions() const {
    static const vkt::Vector<VkExtensionProperties> props{};
    return props;
}

VkLayerInstanceCreateInfo* VktorLayerImpl::getChainInfo(const VkInstanceCreateInfo* create_info, VkLayerFunction func) {
    VkLayerInstanceCreateInfo* info = (VkLayerInstanceCreateInfo*)create_info->pNext;
    while (info && (info->sType != VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO || info->function != func)) {
        info = (VkLayerInstanceCreateInfo*)info->pNext;
    }
    return info;
}

VkLayerDeviceCreateInfo* VktorLayerImpl::getChainInfo(const VkDeviceCreateInfo* create_info, VkLayerFunction func) {
    VkLayerDeviceCreateInfo* info = (VkLayerDeviceCreateInfo*)create_info->pNext;
    while (info && !(info->sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO && info->function == func)) {
        info = (VkLayerDeviceCreateInfo*)info->pNext;
    }
    return info;
}

VkResult VktorLayerImpl::copyLayerProperties(const uint32_t src_count,
                                             const VkLayerProperties* src_properties,
                                             uint32_t* dst_count,
                                             VkLayerProperties* dst_properties) {
    // The 1st invoking vkEnumerateXXX to get count
    if (dst_count && (dst_properties == nullptr || src_properties == nullptr)) {
        *dst_count = src_count;
        return VK_SUCCESS;
    }

    // The 2nd invoking vkEnumerateXXX to get data
    if (dst_count && src_properties && dst_properties) {
        const uint32_t copy_count = *dst_count < src_count ? *dst_count : src_count;
        if (copy_count > 0) {
            std::memcpy(dst_properties, src_properties, copy_count * sizeof(VkLayerProperties));
        }
        *dst_count = copy_count;
        if (copy_count < src_count) {
            return VK_INCOMPLETE;
        }
    }

    return VK_SUCCESS;
}

VkResult VktorLayerImpl::copyExtensionProperties(const uint32_t src_count,
                                                 const VkExtensionProperties* src_properties,
                                                 uint32_t* dst_count,
                                                 VkExtensionProperties* dst_properties) {
    // The 1st invoking vkEnumerateXXX to get count
    if (dst_count && (dst_properties == nullptr || src_properties == nullptr)) {
        *dst_count = src_count;
        return VK_SUCCESS;
    }

    // The 2nd invoking vkEnumerateXXX to get data
    if (dst_count && src_properties && dst_properties) {
        const uint32_t copy_count = *dst_count < src_count ? *dst_count : src_count;
        if (copy_count > 0) {
            std::memcpy(dst_properties, src_properties, copy_count * sizeof(VkExtensionProperties));
        }
        *dst_count = copy_count;
        if (copy_count < src_count) {
            return VK_INCOMPLETE;
        }
    }

    return VK_SUCCESS;
}

NAMESPACE_END(vktlyr)
