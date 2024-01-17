#include "utils.hpp"
#include <set>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

bool checkInstanceLayers(const Vector<const char*>& layers) {
    Vector<VkLayerProperties> lys{};
    OnPanic(enumerate(lys, vkEnumerateInstanceLayerProperties), "Failed to get properties of instance layers");

    std::set<std::string> instance_lys(layers.begin(), layers.end());
    for (const auto& l : lys) {
        instance_lys.erase(l.layerName);
    }

    return instance_lys.empty();
}

bool checkInstanceExtensions(const Vector<const char*>& extensions) {
    Vector<VkExtensionProperties> exts{};
    OnPanic(enumerate(exts, vkEnumerateInstanceExtensionProperties, nullptr),
            "Failed to get properties of instance extensions");

    std::set<std::string> instance_exts(extensions.begin(), extensions.end());
    for (const auto& e : exts) {
        instance_exts.erase(e.extensionName);
    }

    return instance_exts.empty();
}

bool checkDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& device_extensions) {
    Vector<VkExtensionProperties> exts{};
    OnPanic(enumerate(exts, vkEnumerateDeviceExtensionProperties, pd, nullptr),
            "Failed to get properties of device extensions");

    std::set<std::string> device_exts(device_extensions.begin(), device_extensions.end());
    for (const auto& e : exts) {
        device_exts.erase(e.extensionName);
    }

    return device_exts.empty();
}

void printInstanceLayers(const Vector<const char*>& enabled_layers) {
    Vector<VkLayerProperties> lys{};
    OnPanic(enumerate(lys, vkEnumerateInstanceLayerProperties), "Failed to get properties of instance layers");

    std::string str("Available instance layers {\n");
    for (const auto& y : lys) {
        str += vktFmt("\t{}\n", y.layerName);
    }
    str += "}\n";

    str += "Enabled instance layers {\n";
    for (const auto& y : enabled_layers) {
        str += vktFmt("\t{}\n", y);
    }
    str += "}";

    vktOut("{}", str);
}

void printInstanceExtensions(const Vector<const char*>& enabled_extensions) {
    Vector<VkExtensionProperties> ext_props{};
    OnPanic(enumerate(ext_props, vkEnumerateInstanceExtensionProperties, nullptr),
            "Failed to get properties of instance extensions");

    std::string str("Available instance extensions {\n");
    for (const auto& e : ext_props) {
        str += vktFmt("\t{}\n", e.extensionName);
    }
    str += "}\n";

    str += "Enabled instance extensions {\n";
    for (const auto& e : enabled_extensions) {
        str += vktFmt("\t{}\n", e);
    }
    str += "}";

    vktOut("{}", str);
}

void printDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& enabled_extensions) {
    Vector<VkExtensionProperties> ext_props{};
    OnPanic(enumerate(ext_props, vkEnumerateDeviceExtensionProperties, pd, nullptr),
            "Failed to get properties of device extensions");

    std::string str("Available device extensions {\n");
    for (const auto& e : ext_props) {
        str += vktFmt("\t{}\n", e.extensionName);
    }
    str += "}\n";

    str += "Enabled device extensions {\n";
    for (const auto& e : enabled_extensions) {
        str += vktFmt("\t{}\n", e);
    }
    str += "}";

    vktOut("{}", str);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
