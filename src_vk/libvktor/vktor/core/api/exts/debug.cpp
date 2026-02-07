#include "debug.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DebugState::Self;

VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                           [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                                           const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                           [[maybe_unused]] void* pUserData) {
    FmtLevel level = FmtLevel::N;
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        level = FmtLevel::V;
    }
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        level = FmtLevel::I;
    }
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        level = FmtLevel::W;
    }
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        level = FmtLevel::E;
    }
    vktLog(level, "{}\n", pCallbackData->pMessage);

    return VK_FALSE;
}

Self DebugState::setMessageSeverity(bool verbose, bool info, bool warning, bool error) {
    VkDebugUtilsMessageSeverityFlagsEXT severity = 0;
    if (verbose) {
        severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    }
    if (info) {
        severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
    }
    if (warning) {
        severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
    }
    if (error) {
        severity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    }
    debug_ci.messageSeverity = severity;
    return *this;
}

Self DebugState::setMessageType(bool general, bool validation, bool performance, bool device_address_binding) {
    VkDebugUtilsMessageTypeFlagsEXT type = 0;
    if (general) {
        type |= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;
    }
    if (validation) {
        type |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    }
    if (performance) {
        type |= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    }
    if (device_address_binding) {
        type |= VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
    }
    debug_ci.messageType = type;
    return *this;
}

Self DebugState::setCallback(PFN_vkDebugUtilsMessengerCallbackEXT callback) {
    if (callback) {
        debug_ci.pfnUserCallback = callback;
    }
    return *this;
}

Self DebugState::setUserData(void* user_data) {
    debug_ci.pUserData = user_data;
    return *this;
}

Res<Debug> DebugState::into(CRef<Instance> instance) const {
    return Debug::from(instance, *this);
}

Debug::Debug(Debug&& rhs) : instance(rhs.instance) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Debug::~Debug() {
    if (!__borrowed && handle) {
        vkDestroyDebugUtilsMessengerEXT(instance.get(), handle, instance.get());
    }
    handle = VK_NULL_HANDLE;
}

VkResult Debug::setDebugName(VkDevice device, VkObjectType type, uint64_t hdl, const char* name) const {
    VkDebugUtilsObjectNameInfoEXT name_info = Itor::DebugUtilsObjectNameInfoEXT();
    name_info.objectType = type;
    name_info.objectHandle = hdl;
    name_info.pObjectName = name;
    return vkSetDebugUtilsObjectNameEXT(device, &name_info);
}

void Debug::cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name) const {
    VkDebugUtilsLabelEXT label_info = Itor::DebugUtilsLabelEXT();
    label_info.pLabelName = name;
    label_info.color[0] = 0.0f;
    label_info.color[1] = 0.0f;
    label_info.color[2] = 0.0f;
    label_info.color[3] = 1.0f;
    vkCmdBeginDebugUtilsLabelEXT(cmdbuf, &label_info);
}

void Debug::cmdEndLabel(VkCommandBuffer cmdbuf) const {
    vkCmdEndDebugUtilsLabelEXT(cmdbuf);
}

void Debug::cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name) const {
    VkDebugUtilsLabelEXT label_info = Itor::DebugUtilsLabelEXT();
    label_info.pLabelName = name;
    label_info.color[0] = 0.0f;
    label_info.color[1] = 0.0f;
    label_info.color[2] = 0.0f;
    label_info.color[3] = 1.0f;
    vkCmdInsertDebugUtilsLabelEXT(cmdbuf, &label_info);
}

Res<Debug> Debug::from(CRef<Instance> instance, const DebugState& info) {
    Debug debug(instance);
    info.debug_ci.pNext = info.__next;
    OnRet(vkCreateDebugUtilsMessengerEXT(instance.get(), &info.debug_ci, instance.get(), &debug.handle),
          "Failed to create debug utils messenger");
    return Ok(std::move(debug));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
