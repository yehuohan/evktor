#pragma once
#include "__builder.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Instance : public BuiltHandle<VkInstance> {
    uint32_t api_version = VK_API_VERSION_1_2;
    Vector<const char*> layers{};     /**< Enabled instance layers */
    Vector<const char*> extensions{}; /**< Enabled instance extensions */
    VkDebugUtilsMessengerEXT debug_messenger = nullptr;

    Instance(Name&& name) : BuiltHandle(std::move(name)) {}
    Instance(Instance&&);
    ~Instance();
    bool isLayerEnabled(const char* layer) const;
    bool isExtensionEnabled(const char* extension) const;
};

struct InstanceInfo : public BuilderInfo {
    const char* app_name = "vktor";
    uint32_t app_version = VK_MAKE_VERSION(1, 0, 0);
    const char* engine_name = "vktor";
    uint32_t engine_version = VK_MAKE_VERSION(1, 0, 0);
    uint32_t api_version = VK_API_VERSION_1_0;

    Vector<const char*> layers{};
    Vector<const char*> extensions{};
    bool enable_debug_utils = false;
    PFN_vkDebugUtilsMessengerCallbackEXT debug_callback = debugUtilsMessengerCallback;
};

class InstanceBuilder : public Builder<InstanceBuilder, Instance, InstanceInfo> {
public:
    explicit InstanceBuilder(Name&& name = "Instance") : Builder(std::move(name)) {}
    virtual Built build() override;

    Self setAppName(const char* name);
    Self setAppVerion(uint32_t version);
    Self setEngineName(const char* name);
    Self setEngineVersion(uint32_t version);
    Self setApiVerion(uint32_t version);

    Self addLayer(const char* layer);
    Self addLayers(const Vector<const char*> layers);
    Self addExtension(const char* extension);
    Self addExtensions(const Vector<const char*>& extensions);
    Self enableValidationLayers(bool enable = true);
    Self enableDebugUtils(bool enable = true, PFN_vkDebugUtilsMessengerCallbackEXT debug_callback = nullptr);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
