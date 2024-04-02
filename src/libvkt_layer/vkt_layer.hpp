#pragma once
#include <vulkan/vulkan.h>

#define VKTLYR_API

namespace vktlyr {

PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName);

}; // namespace vktlyr

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off
VKTLYR_API VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName);
// clang-format on

#ifdef __cplusplus
}
#endif
