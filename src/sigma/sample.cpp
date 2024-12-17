#include "vkt_layer.hpp"

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator,
                                              VkInstance* pInstance);
VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo);

class SampleLayer : public vktlyr::VktorLayerImpl {
public:
    SampleLayer()
        : vktlyr::VktorLayerImpl({
              vktlyrHook(, CreateInstance), // Add hook before `vktlyrDefaultHooks()` to override default hooks
              vktlyrDefaultHooks(),
              vktlyrHook(, BeginCommandBuffer),
          }) {}

    virtual const VkLayerProperties& getLayerProps() const {
        static const VkLayerProperties props{
            "VK_LAYER_VKTOR_Sample",
            VK_API_VERSION_1_0,
            1,
            "Sample layer with evktor/libvkt_layer",
        };
        return props;
    }
};

static SampleLayer sample_layer{};
vktlyrSetImpl(sample_layer);

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator,
                                              VkInstance* pInstance) {
    vktlyrOut(">>> Pre-create instance");
    auto res = vktlyr::CreateInstance(pCreateInfo, pAllocator, pInstance);
    vktlyrOut(">>> Post-Create instance");
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) {
    // auto& impl = *vktlyrGetImpl(sample_layer);
    // auto tbl = impl[commandBuffer];
    auto tbl = sample_layer[commandBuffer];
    vktlyrOut(">>> Begin command buffer: {}", fmt::ptr(commandBuffer));
    return tbl->BeginCommandBuffer(commandBuffer, pBeginInfo);
}
