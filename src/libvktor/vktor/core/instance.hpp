#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Instance;

struct InstanceState : public CoreStater<InstanceState> {
    friend struct Instance;

private:
    VkApplicationInfo app_info{};
    Vector<const char*> layers{};
    Vector<const char*> extensions{};
    bool enable_debug_utils = false;
    PFN_vkDebugUtilsMessengerCallbackEXT debug_callback = debugUtilsMessengerCallback;

public:
    explicit InstanceState(Name&& name = "Instance") : CoreStater(std::move(name)) {
        app_info = Itor::ApplicationInfo();
        app_info.pApplicationName = "vktor";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "vktor";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;
    }

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

    Res<Instance> into();
};

struct Instance : public CoreHandle<VkInstance> {
    uint32_t api_version = VK_API_VERSION_1_0;
    Vector<const char*> layers{};     /**< Enabled instance layers */
    Vector<const char*> extensions{}; /**< Enabled instance extensions */
    VkDebugUtilsMessengerEXT debug_messenger = nullptr;

    Instance() {}
    Instance(Instance&&);
    ~Instance();
    bool isLayerEnabled(const char* layer) const;
    bool isExtensionEnabled(const char* extension) const;

    static Res<Instance> from(InstanceState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
