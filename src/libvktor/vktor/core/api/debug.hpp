#pragma once
#include "__api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Debug;
struct Instance;

/**
 * @brief Handle debug messages come from validation layers.
 */
VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                           VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                                           const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                           void* pUserData);

struct DebugState : public CoreStater<DebugState> {
    friend struct Debug;
    friend struct Instance;

private:
    VkDebugUtilsMessengerCreateInfoEXT debug_ci{};

public:
    explicit DebugState(Name&& name = "Debug") : CoreStater(std::move(name)) {
        debug_ci = Itor::DebugUtilsMessengerCreateInfoEXT();
        debug_ci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_ci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_ci.pfnUserCallback = debugUtilsMessengerCallback;
    }

    Self setCallback(PFN_vkDebugUtilsMessengerCallbackEXT callback);
    Self setUserData(void* user_data);

    Res<Debug> into(const VkInstance instance) const;
};

struct BaseDebug : public CoreHandle<VkDebugUtilsMessengerEXT> {
public:
    explicit BaseDebug() {}
    virtual ~BaseDebug() {}

    virtual VkResult setDebugName(VkDevice device, VkObjectType type, uint64_t hdl, const char* name) const {
        return VK_SUCCESS;
    }
    virtual void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name) const {}
    virtual void cmdEndLabel(VkCommandBuffer cmdbuf) const {}
    virtual void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name) const {}
};

/**
 * @brief Debug Vulkan with VK_EXT_DEBUG_UTILS_EXTENSION_NAME extension
 *
 * VK_EXT_DEBUG_UTILS_EXTENSION_NAME works after vkCreateInstance and before vkDestroyInstance
 */
struct Debug : public BaseDebug {
    const VkInstance instance;

protected:
    explicit Debug(const VkInstance instance) : instance(instance) {}

public:
    Debug(Debug&&);
    virtual ~Debug();

    /**
     * @brief Set resource name for debug conveniently
     *
     * Although vkSetDebugUtilsObjectNameEXT accept a `const char*`, set debug
     * name from a temporal `String` is okay.
     */
    virtual VkResult setDebugName(VkDevice device, VkObjectType type, uint64_t hdl, const char* name) const override;
    virtual void cmdBeginLabel(VkCommandBuffer cmdbuf, const char* name) const override;
    virtual void cmdEndLabel(VkCommandBuffer cmdbuf) const override;
    virtual void cmdInsertLabel(VkCommandBuffer cmdbuf, const char* name) const override;

    static Res<Debug> from(const VkInstance instance, const DebugState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
