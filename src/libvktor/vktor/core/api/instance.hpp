#pragma once
#include "__api.hpp"
#include "debug.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Instance;

struct InstanceState : public CoreStater<InstanceState> {
    friend struct Instance;

private:
    VkApplicationInfo app_info{};
    Vector<const char*> layers{};
    Vector<const char*> extensions{};
    DebugState* debug_state = nullptr;

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
    inline Self enableLayerValidation() {
        return addLayer("VK_LAYER_KHRONOS_validation");
    }
    inline Self enableExtensionDebugUtils(DebugState* _debug_state = nullptr) {
        debug_state = _debug_state;
        return addExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    Res<Instance> into();
};

struct Instance : public CoreHandle<VkInstance> {
    uint32_t api_version = VK_API_VERSION_1_0;
    Vector<const char*> layers{};               /**< Enabled instance layers */
    Vector<const char*> extensions{};           /**< Enabled instance extensions */
    Box<BaseDebug> debug = newBox<BaseDebug>(); /**< Debugger for Vulkan (always valid in Instance) */

protected:
    explicit Instance() {}

public:
    Instance(Instance&&);
    ~Instance();

    bool isLayerEnabled(const char* layer) const;
    bool isExtensionEnabled(const char* extension) const;

    static Res<Instance> from(InstanceState& info);
    // static Res<Instance> borrow(VkInstance handle);
};

bool checkInstanceLayers(const Vector<const char*>& layers);
bool checkInstanceExtensions(const Vector<const char*>& extensions);
void printInstanceLayers(const Vector<const char*>& enabled_layers);
void printInstanceExtensions(const Vector<const char*>& enabled_extensions);

NAMESPACE_END(core)
NAMESPACE_END(vkt)
