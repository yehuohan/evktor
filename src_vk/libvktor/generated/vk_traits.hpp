#pragma once

#include <type_traits>
#include <variant>
#include <vulkan/vulkan.h>

namespace vkt {

// clang-format off
struct HasInstance {
protected:
    VkInstance __parent;

public:
    HasInstance(VkInstance p = VK_NULL_HANDLE) : __parent(p) {}
    VkInstance parent() const {
        return __parent;
    }
};

struct HasPhysicalDevice {
protected:
    VkPhysicalDevice __parent;

public:
    HasPhysicalDevice(VkPhysicalDevice p = VK_NULL_HANDLE) : __parent(p) {}
    VkPhysicalDevice parent() const {
        return __parent;
    }
};

struct HasDevice {
protected:
    VkDevice __parent;

public:
    HasDevice(VkDevice p = VK_NULL_HANDLE) : __parent(p) {}
    VkDevice parent() const {
        return __parent;
    }
};

template <typename H> struct vk_child_of_instance : public std::false_type {};
template <typename H> struct vk_child_of_physical_device : public std::false_type {};
template <typename H> struct vk_child_of_device : public std::false_type {};

template <typename H> constexpr bool vk_child_of_instance_v = vk_child_of_instance<H>::value;
template <typename H> constexpr bool vk_child_of_physical_device_v = vk_child_of_physical_device<H>::value;
template <typename H> constexpr bool vk_child_of_device_v = vk_child_of_device<H>::value;
template <typename H> constexpr bool vk_has_parent_v = vk_child_of_instance_v<H> || vk_child_of_physical_device_v<H> || vk_child_of_device_v<H>;

template <typename H> using vk_parent_instance_t = typename std::conditional<vk_child_of_instance_v<H>, VkInstance, std::monostate>::type;
template <typename H> using vk_parent_physical_device_t = typename std::conditional<vk_child_of_physical_device_v<H>, VkPhysicalDevice, std::monostate>::type;
template <typename H> using vk_parent_device_t = typename std::conditional<vk_child_of_device_v<H>, VkDevice, std::monostate>::type;
template <typename H> using vk_parent_t = typename std::conditional<vk_child_of_device_v<H>, VkDevice,
    typename std::conditional<vk_child_of_physical_device_v<H>, VkPhysicalDevice,
        typename std::conditional<vk_child_of_instance_v<H>, VkInstance, std::monostate>::type
    >::type
>::type;

template <typename H> using vk_parent_instance_s = typename std::conditional<vk_child_of_instance_v<H>, HasInstance, std::monostate>::type;
template <typename H> using vk_parent_physical_device_s = typename std::conditional<vk_child_of_physical_device_v<H>, HasPhysicalDevice, std::monostate>::type;
template <typename H> using vk_parent_device_s = typename std::conditional<vk_child_of_device_v<H>, HasDevice, std::monostate>::type;
template <typename H> using vk_parent_s = typename std::conditional<vk_child_of_device_v<H>, HasDevice,
    typename std::conditional<vk_child_of_physical_device_v<H>, HasPhysicalDevice,
        typename std::conditional<vk_child_of_instance_v<H>, HasInstance, std::monostate>::type
    >::type
>::type;

template <> struct vk_child_of_device<VkBuffer> : public std::true_type {};
template <> struct vk_child_of_device<VkImage> : public std::true_type {};
template <> struct vk_child_of_instance<VkPhysicalDevice> : public std::true_type {};
template <> struct vk_child_of_physical_device<VkDevice> : public std::true_type {};
template <> struct vk_child_of_device<VkQueue> : public std::true_type {};
template <> struct vk_child_of_device<VkSemaphore> : public std::true_type {};
template <> struct vk_child_of_device<VkCommandBuffer> : public std::true_type {};
template <> struct vk_child_of_device<VkFence> : public std::true_type {};
template <> struct vk_child_of_device<VkDeviceMemory> : public std::true_type {};
template <> struct vk_child_of_device<VkEvent> : public std::true_type {};
template <> struct vk_child_of_device<VkQueryPool> : public std::true_type {};
template <> struct vk_child_of_device<VkBufferView> : public std::true_type {};
template <> struct vk_child_of_device<VkImageView> : public std::true_type {};
template <> struct vk_child_of_device<VkShaderModule> : public std::true_type {};
template <> struct vk_child_of_device<VkPipelineCache> : public std::true_type {};
template <> struct vk_child_of_device<VkPipelineLayout> : public std::true_type {};
template <> struct vk_child_of_device<VkPipeline> : public std::true_type {};
template <> struct vk_child_of_device<VkRenderPass> : public std::true_type {};
template <> struct vk_child_of_device<VkDescriptorSetLayout> : public std::true_type {};
template <> struct vk_child_of_device<VkSampler> : public std::true_type {};
template <> struct vk_child_of_device<VkDescriptorSet> : public std::true_type {};
template <> struct vk_child_of_device<VkDescriptorPool> : public std::true_type {};
template <> struct vk_child_of_device<VkFramebuffer> : public std::true_type {};
template <> struct vk_child_of_device<VkCommandPool> : public std::true_type {};
template <> struct vk_child_of_device<VkSamplerYcbcrConversion> : public std::true_type {};
template <> struct vk_child_of_device<VkDescriptorUpdateTemplate> : public std::true_type {};
template <> struct vk_child_of_device<VkPrivateDataSlot> : public std::true_type {};
template <> struct vk_child_of_instance<VkSurfaceKHR> : public std::true_type {};
template <> struct vk_child_of_device<VkSwapchainKHR> : public std::true_type {};
template <> struct vk_child_of_physical_device<VkDisplayKHR> : public std::true_type {};
template <> struct vk_child_of_physical_device<VkDisplayModeKHR> : public std::true_type {};
template <> struct vk_child_of_device<VkVideoSessionKHR> : public std::true_type {};
template <> struct vk_child_of_device<VkVideoSessionParametersKHR> : public std::true_type {};
template <> struct vk_child_of_device<VkDeferredOperationKHR> : public std::true_type {};
template <> struct vk_child_of_device<VkPipelineBinaryKHR> : public std::true_type {};
template <> struct vk_child_of_instance<VkDebugReportCallbackEXT> : public std::true_type {};
template <> struct vk_child_of_device<VkCuModuleNVX> : public std::true_type {};
template <> struct vk_child_of_device<VkCuFunctionNVX> : public std::true_type {};
template <> struct vk_child_of_instance<VkDebugUtilsMessengerEXT> : public std::true_type {};
template <> struct vk_child_of_device<VkValidationCacheEXT> : public std::true_type {};
template <> struct vk_child_of_device<VkAccelerationStructureNV> : public std::true_type {};
template <> struct vk_child_of_device<VkPerformanceConfigurationINTEL> : public std::true_type {};
template <> struct vk_child_of_device<VkIndirectCommandsLayoutNV> : public std::true_type {};
#ifdef VK_ENABLE_BETA_EXTENSIONS
template <> struct vk_child_of_device<VkCudaModuleNV> : public std::true_type {};
template <> struct vk_child_of_device<VkCudaFunctionNV> : public std::true_type {};
#endif  // VK_ENABLE_BETA_EXTENSIONS
template <> struct vk_child_of_device<VkAccelerationStructureKHR> : public std::true_type {};
#ifdef VK_USE_PLATFORM_FUCHSIA
template <> struct vk_child_of_device<VkBufferCollectionFUCHSIA> : public std::true_type {};
#endif  // VK_USE_PLATFORM_FUCHSIA
template <> struct vk_child_of_device<VkMicromapEXT> : public std::true_type {};
template <> struct vk_child_of_device<VkTensorARM> : public std::true_type {};
template <> struct vk_child_of_device<VkTensorViewARM> : public std::true_type {};
template <> struct vk_child_of_device<VkOpticalFlowSessionNV> : public std::true_type {};
template <> struct vk_child_of_device<VkShaderEXT> : public std::true_type {};
template <> struct vk_child_of_device<VkDataGraphPipelineSessionARM> : public std::true_type {};
template <> struct vk_child_of_device<VkExternalComputeQueueNV> : public std::true_type {};
template <> struct vk_child_of_device<VkIndirectExecutionSetEXT> : public std::true_type {};
template <> struct vk_child_of_device<VkIndirectCommandsLayoutEXT> : public std::true_type {};
// clang-format on

} // namespace vkt
