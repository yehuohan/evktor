#pragma once
#include "__api.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Instance;

struct InstanceState : public CoreState<InstanceState> {
    friend struct Instance;

private:
    const VkAllocationCallbacks* allocator = nullptr;
    VkApplicationInfo app_info{};
    Vector<const char*> layers{};         /**< Required instance layers */
    Vector<const char*> extensions{};     /**< Required instance extensions */
    Vector<const char*> try_layers{};     /**< Enabled instance layers if available */
    Vector<const char*> try_extensions{}; /**< Enabled instance extensions if available */

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
    Self tryAddLayer(const char* layer);
    Self addExtension(const char* extension);
    Self addExtensions(const Vector<const char*>& extensions);
    Self tryAddExtension(const char* extension);
    inline Self tryAddValidationLayer() {
        return tryAddLayer("VK_LAYER_KHRONOS_validation");
    }
    inline Self tryAddDebugUtilsExtension() {
        return tryAddExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    Res<Instance> into();
};

struct Instance : public CoreHandle<VkInstance> {
    friend class CoreApi;
    friend struct Device;

protected:
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

/**
 * @brief Check layers or extensions
 *
 * VkLayerProperties and VkExtensionProperties have same first field: `char[VK_MAX_EXTENSION_NAME_SIZE]`,
 * so this function can work for both of them.
 *
 * - Return false if `required` contains unsupported layer or extension
 * - Copy all supported layer or extension from `desired` into `required`
 * - Remove duplicated layer or extensions from `required`
 */
template <typename T>
bool checkExtensions(const char* text,
                     const Vector<T>& available,
                     Vector<const char*>& required,
                     const Vector<const char*>& desired) {
    Vector<const char*> unsupported{};
    for (const auto& req : required) {
        if (std::find_if(available.begin(), available.end(), [&req](const T& a) -> bool {
                return strcmp(reinterpret_cast<const VkExtensionProperties*>(&a)->extensionName, req) == 0;
            }) == available.end()) {
            unsupported.push_back(req);
        }
    }
    if (!unsupported.empty()) {
        vktLogW("Not supported {}:", text);
        for (const auto& item : unsupported) {
            vktLogW("\t{}", item);
        }
        return false;
    }

    size_t idx = required.size();
    for (const auto& des : desired) {
        if (std::find_if(available.begin(), available.end(), [&des](const T& a) -> bool {
                return strcmp(reinterpret_cast<const VkExtensionProperties*>(&a)->extensionName, des) == 0;
            }) != available.end()) {
            required.push_back(des);
        }
    }
    if (required.size() > idx) {
        vktLogD("Try enabled {}:", text);
        while (idx < required.size()) {
            vktLogD("\t{}", required[idx]);
            idx++;
        }
    }

    std::sort(required.begin(), required.end(), strLess);
    auto new_end = std::unique(required.begin(), required.end());
    required.erase(new_end, required.end());

    return true;
}

/**
 * @brief Print available and enabled layers or extensions
 */
template <typename T>
void printExtensions(const char* text, const Vector<T>& available, const Vector<const char*>& enabled) {
    String str(vktFmt("Available {} {{\n", text));
    for (const auto& a : available) {
        str += vktFmt("\t{}\n", reinterpret_cast<const VkExtensionProperties*>(&a)->extensionName);
    }
    str += "}\n";
    vktOut("{}", str);

    str = vktFmt("Enabled {} {{\n", text);
    for (const auto& e : enabled) {
        str += vktFmt("\t{}\n", e);
    }
    str += "}";
    vktOut("{}", str);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
