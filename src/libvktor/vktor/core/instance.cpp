#include "instance.hpp"
#include "utils.hpp"
#include <algorithm>

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

Self InstanceState::enableValidationLayers(bool enable) {
    if (enable) {
        layers.push_back("VK_LAYER_KHRONOS_validation");
    }
    return *this;
}

Self InstanceState::enableDebugUtils(bool enable, PFN_vkDebugUtilsMessengerCallbackEXT _debug_callback) {
    enable_debug_utils = enable;
    if (_debug_callback) {
        debug_callback = _debug_callback;
    }
    return *this;
}

Res<Instance> InstanceState::into() {
    return Instance::from(*this);
}

Instance::Instance(Instance&& rhs) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    debug_messenger = rhs.debug_messenger;
    rhs.debug_messenger = nullptr;
    api_version = rhs.api_version;
    layers = std::move(rhs.layers);
    extensions = std::move(rhs.extensions);
}

Instance::~Instance() {
    if (!__borrowed && handle) {
        if (debug_messenger) {
            destroyDebugUtils(handle, debug_messenger);
        }
        vkDestroyInstance(handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
    debug_messenger = nullptr;
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
    if (info.enable_debug_utils) {
        // VK_EXT_debug_utils combines the functionality of both VK_EXT_debug_report and VK_EXT_debug_marker
        info.addExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
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
        // Note: To debug issue in vkCreateInstance and vkDestroyInstance calls,
        // pass a VkDebugUtilsMessengerCreateInfoEXT struct to `instance_ci.pNext`.
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

    // Setup debug messenger that works after vkCreateInstance and before vkDestroyInstance
    if (info.enable_debug_utils) {
        OnRet(createDebugUtils(instance, info.debug_callback, &instance.debug_messenger),
              "Failed to create debug utils messenger");
    }

    return Ok(std::move(instance));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
