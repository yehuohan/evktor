#include "debug.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

static bool debug_utils_enabled = false;

VkResult createDebugUtils(VkInstance instance, PFN_vkDebugUtilsMessengerCallbackEXT callback, VkDebugUtilsMessengerEXT* debug) {
    auto debug_ci = Itor::DebugUtilsMessengerCreateInfoEXT();
    debug_ci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_ci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_ci.pfnUserCallback = callback;
    debug_ci.pUserData = nullptr;
    auto res = vkCreateDebugUtilsMessengerEXT(instance, &debug_ci, nullptr, debug);
    if (res == VK_SUCCESS) {
        debug_utils_enabled = true;
    }
    return res;
}

void destroyDebugUtils(VkInstance instance, VkDebugUtilsMessengerEXT debug) {
    debug_utils_enabled = false;
    vkDestroyDebugUtilsMessengerEXT(instance, debug, nullptr);
}

VkResult setDebugName(VkDevice device, VkObjectType type, uint64_t handle, const char* name) {
    if (!debug_utils_enabled) {
        return VK_SUCCESS;
    }
    VkDebugUtilsObjectNameInfoEXT name_info = Itor::DebugUtilsObjectNameInfoEXT();
    name_info.objectType = type;
    name_info.objectHandle = handle;
    name_info.pObjectName = name;
    return vkSetDebugUtilsObjectNameEXT(device, &name_info);
}

void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name) {
    if (!debug_utils_enabled) {
        return;
    }
    VkDebugUtilsLabelEXT label_info = Itor::DebugUtilsLabelEXT();
    label_info.pLabelName = name;
    label_info.color[0] = 0.0f;
    label_info.color[1] = 0.0f;
    label_info.color[2] = 0.0f;
    label_info.color[3] = 1.0f;
    vkCmdBeginDebugUtilsLabelEXT(cmdbuf, &label_info);
}

void cmdEndLabel(VkCommandBuffer cmdbuf) {
    if (!debug_utils_enabled) {
        return;
    }
    vkCmdEndDebugUtilsLabelEXT(cmdbuf);
}

void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name) {
    if (!debug_utils_enabled) {
        return;
    }
    VkDebugUtilsLabelEXT label_info = Itor::DebugUtilsLabelEXT();
    label_info.pLabelName = name;
    label_info.color[0] = 0.0f;
    label_info.color[1] = 0.0f;
    label_info.color[2] = 0.0f;
    label_info.color[3] = 1.0f;
    vkCmdInsertDebugUtilsLabelEXT(cmdbuf, &label_info);
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                           VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                                           const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                           void* pUserData) {
    std::string msg("");
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        msg = "V";
    }
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        msg = "I";
    }
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        msg = "W";
    }
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        msg = "E";
    }
    vktLog(msg, "{}\n", pCallbackData->pMessage);

    return VK_FALSE;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
