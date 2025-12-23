#pragma once
#include "__api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

class CoreApi;
struct Instance;

struct InstanceState : public CoreState<InstanceState> {
    friend struct Instance;

private:
    const VkAllocationCallbacks* allocator = nullptr;
    VkApplicationInfo app_info{};
    Vector<const char*> layers{};
    Vector<const char*> extensions{};

public:
    explicit InstanceState(String&& name = "Instance") : CoreState(std::move(name)) {
        app_info = Itor::ApplicationInfo();
        app_info.pApplicationName = "vktor";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "vktor";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VKT_CORE_VK_API_VERSION;
    }

    Self setAllocationCallbacks(const VkAllocationCallbacks* allocation_callbacks);
    Self setAppName(const char* name);
    Self setAppVerion(uint32_t version);
    Self setEngineName(const char* name);
    Self setEngineVersion(uint32_t version);
    Self setApiVerion(uint32_t version);
    Self addLayer(const char* layer);
    Self addLayers(const Vector<const char*>& layers);
    Self addExtension(const char* extension);
    Self addExtensions(const Vector<const char*>& extensions);
    inline Self addValidationLayer() {
        return addLayer("VK_LAYER_KHRONOS_validation");
    }
    inline Self addDebugUtilsExtension() {
        return addExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    Res<Instance> into();
};

struct Instance : public CoreHandle<VkInstance> {
    friend CoreApi;

    const VkAllocationCallbacks* allocator = nullptr;
    uint32_t api_version = VKT_CORE_VK_API_VERSION;

protected:
    explicit Instance() {}

public:
    Instance(Instance&&);
    ~Instance();
    Instance& operator=(Instance&&);

    operator const VkAllocationCallbacks*() const {
        return allocator;
    }

    static Res<Instance> from(InstanceState& info);
    static Res<Instance> borrow(VkInstance handle,
                                PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr,
                                uint32_t api_version = VKT_CORE_VK_API_VERSION,
                                VkAllocationCallbacks* allocator = nullptr);
};

bool checkInstanceLayers(const Vector<const char*>& layers);
bool checkInstanceExtensions(const Vector<const char*>& extensions);
void printInstanceLayers(const Vector<const char*>& enabled_layers);
void printInstanceExtensions(const Vector<const char*>& enabled_extensions);

NAMESPACE_END(core)
NAMESPACE_END(vkt)
