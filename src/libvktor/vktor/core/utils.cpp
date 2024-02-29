#include "utils.hpp"
#include <set>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

bool checkInstanceLayers(const Vector<const char*>& layers) {
    Vector<VkLayerProperties> lys{};
    VkResult ret = enumerate(lys, vkEnumerateInstanceLayerProperties);
    if (ret != VK_SUCCESS) {
        LogE("Failed to get properties of instance layers: {}", VkStr(VkResult, ret));
        return false;
    }

    std::set<std::string> instance_lys(layers.begin(), layers.end());
    for (const auto& l : lys) {
        instance_lys.erase(l.layerName);
    }

    return instance_lys.empty();
}

bool checkInstanceExtensions(const Vector<const char*>& extensions) {
    Vector<VkExtensionProperties> exts{};
    VkResult ret = enumerate(exts, vkEnumerateInstanceExtensionProperties, nullptr);
    if (ret != VK_SUCCESS) {
        LogE("Failed to get properties of instance extensions: {}", VkStr(VkResult, ret));
        return false;
    }

    std::set<std::string> instance_exts(extensions.begin(), extensions.end());
    for (const auto& e : exts) {
        instance_exts.erase(e.extensionName);
    }

    return instance_exts.empty();
}

bool checkDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& device_extensions) {
    Vector<VkExtensionProperties> exts{};
    VkResult ret = enumerate(exts, vkEnumerateDeviceExtensionProperties, pd, nullptr);
    if (ret != VK_SUCCESS) {
        LogE("Failed to get properties of device extensions: {}", VkStr(VkResult, ret));
        return false;
    }

    std::set<std::string> device_exts(device_extensions.begin(), device_extensions.end());
    for (const auto& e : exts) {
        device_exts.erase(e.extensionName);
    }

    return device_exts.empty();
}

void printInstanceLayers(const Vector<const char*>& enabled_layers) {
    Vector<VkLayerProperties> lys{};
    VkResult ret = enumerate(lys, vkEnumerateInstanceLayerProperties);
    if (ret != VK_SUCCESS) {
        LogE("Failed to get properties of instance layers: {}", VkStr(VkResult, ret));
        return;
    }

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
    VkResult ret = enumerate(ext_props, vkEnumerateInstanceExtensionProperties, nullptr);
    if (ret != VK_SUCCESS) {
        LogE("Failed to get properties of instance extensions: {}", VkStr(VkResult, ret));
        return;
    }

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
    VkResult ret = enumerate(ext_props, vkEnumerateDeviceExtensionProperties, pd, nullptr);
    if (ret != VK_SUCCESS) {
        LogE("Failed to get properties of device extensions: {}", VkStr(VkResult, ret));
        return;
    }

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
