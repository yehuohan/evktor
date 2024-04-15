#include "instance.hpp"
#include <algorithm>
#include <set>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = InstanceState::Self;

Self InstanceState::setAppName(const char* name) {
    app_info.pApplicationName = name;
    return *this;
}

Self InstanceState::setAppVerion(uint32_t version) {
    app_info.applicationVersion = version;
    return *this;
}

Self InstanceState::setEngineName(const char* name) {
    app_info.pEngineName = name;
    return *this;
}

Self InstanceState::setEngineVersion(uint32_t version) {
    app_info.engineVersion = version;
    return *this;
}

Self InstanceState::setApiVerion(uint32_t version) {
    app_info.apiVersion = version;
    return *this;
}

Self InstanceState::addLayer(const char* layer) {
    layers.push_back(layer);
    return *this;
}

Self InstanceState::addLayers(const Vector<const char*> _layers) {
    layers.insert(layers.end(), _layers.begin(), _layers.end());
    return *this;
}

Self InstanceState::addExtension(const char* extension) {
    extensions.push_back(extension);
    return *this;
}

Self InstanceState::addExtensions(const Vector<const char*>& _extensions) {
    extensions.insert(extensions.end(), _extensions.begin(), _extensions.end());
    return *this;
}

Res<Instance> InstanceState::into() {
    return Instance::from(*this);
}

Instance::Instance(Instance&& rhs) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    api_version = rhs.api_version;
    layers = std::move(rhs.layers);
    extensions = std::move(rhs.extensions);
    debug = std::move(rhs.debug);
}

Instance::~Instance() {
    // Must resuet debug before destroy instance
    debug.reset();
    if (!__borrowed && handle) {
        vkDestroyInstance(handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
    layers.clear();
    extensions.clear();
};

bool Instance::isLayerEnabled(const char* layer) const {
    return std::find_if(layers.begin(), layers.end(), [&layer](auto& lyr) {
               return std::strcmp(layer, lyr) == 0;
           }) != layers.end();
}

bool Instance::isExtensionEnabled(const char* extension) const {
    return std::find_if(extensions.begin(), extensions.end(), [&extension](auto& ext) {
               return std::strcmp(extension, ext) == 0;
           }) != extensions.end();
}

Res<Instance> Instance::from(InstanceState& info) {
    // Initialize Vulkan loader
    OnRet(volkInitialize(), "Unable to initialize Vulkan loader");

    if (info.app_info.apiVersion >= VK_API_VERSION_1_1) {
        // Add required extensions for memory allocator
        info.addExtension(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }
    std::sort(info.extensions.begin(), info.extensions.end(), strLess);
    auto new_end = std::unique(info.extensions.begin(), info.extensions.end());
    info.extensions.erase(new_end, info.extensions.end());

    auto instance_ci = Itor::InstanceCreateInfo();
    instance_ci.pApplicationInfo = &info.app_info;
    if (info.layers.size() > 0) {
        if (!checkInstanceLayers(info.layers)) {
            return Er("Not all the required layers are supported");
        }
        instance_ci.enabledLayerCount = u32(info.layers.size());
        instance_ci.ppEnabledLayerNames = info.layers.data();
    }
    if (info.extensions.size() > 0) {
        if (!checkInstanceExtensions(info.extensions)) {
            return Er("Not all the required extensions are supported");
        }
        instance_ci.enabledExtensionCount = u32(info.extensions.size());
        instance_ci.ppEnabledExtensionNames = info.extensions.data();
    }
    if (info.debug_state) {
        // To debug issue in vkCreateInstance and vkDestroyInstance calls,
        // pass a VkDebugUtilsMessengerCreateInfoEXT struct to `instance_ci.pNext`.
        instance_ci.pNext = &info.debug_state->debug_ci;
    }

    if (info.__verbose) {
        printInstanceLayers(info.layers);
        printInstanceExtensions(info.extensions);
    }

    Instance instance{};
    OnRet(vkCreateInstance(&instance_ci, nullptr, instance), "Failed to create instance");
    instance.api_version = info.app_info.apiVersion;
    instance.layers = std::move(info.layers);
    instance.extensions = std::move(info.extensions);

    volkLoadInstance(instance);

    if (info.debug_state) {
        auto res = info.debug_state->into(instance);
        if (res.isOk()) {
            instance.debug = newBox<Debug>(res.unwrap());
        } else {
            vktLogW("Failed to create a custom debug utils messenger");
        }
    }
    OnCheck(instance.debug, "Instance must have a valid debugger");

    return Ok(std::move(instance));
}

bool checkInstanceLayers(const Vector<const char*>& layers) {
    Vector<VkLayerProperties> lys{};
    VkResult ret = enumerate(lys, vkEnumerateInstanceLayerProperties);
    if (ret != VK_SUCCESS) {
        vktLogE("Failed to get properties of instance layers: {}", VkStr(VkResult, ret));
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
        vktLogE("Failed to get properties of instance extensions: {}", VkStr(VkResult, ret));
        return false;
    }

    std::set<std::string> instance_exts(extensions.begin(), extensions.end());
    for (const auto& e : exts) {
        instance_exts.erase(e.extensionName);
    }

    return instance_exts.empty();
}

void printInstanceLayers(const Vector<const char*>& enabled_layers) {
    Vector<VkLayerProperties> lys{};
    VkResult ret = enumerate(lys, vkEnumerateInstanceLayerProperties);
    if (ret != VK_SUCCESS) {
        vktLogE("Failed to get properties of instance layers: {}", VkStr(VkResult, ret));
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
        vktLogE("Failed to get properties of instance extensions: {}", VkStr(VkResult, ret));
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

NAMESPACE_END(core)
NAMESPACE_END(vkt)
