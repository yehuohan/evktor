#include "vkt_layer.hpp"

namespace vktlyr {

PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName) {
    return nullptr;
}

} // namespace vktlyr

#ifdef __cplusplus
extern "C" {
#endif

VKTLYR_API VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName) {
    return vktlyr::GetInstanceProcAddr(instance, pName);
}

#ifdef __cplusplus
}
#endif
