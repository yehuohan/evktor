#pragma once
#include "vktor/config.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

VkResult createDebugUtils(VkInstance instance, PFN_vkDebugUtilsMessengerCallbackEXT callback, VkDebugUtilsMessengerEXT* debug);
void destroyDebugUtils(VkInstance instance, VkDebugUtilsMessengerEXT debug);
VkResult setDebugName(VkDevice device, VkObjectType type, uint64_t handle, const char* name);
void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name);
void cmdEndLabel(VkCommandBuffer cmdbuf);
void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name);

/**
 * @brief Handle debug messages come from validation layers.
 *
 * By default, debug messages will be printed to standard error output.
 * Use vkSetDebugUtilsObjectNameEXT to set user friendly object name.
 */
VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                           VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                                           const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                           void* pUserData);

NAMESPACE_END(core)
NAMESPACE_END(vkt)
