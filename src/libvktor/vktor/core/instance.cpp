#include "instance.hpp"
#include "utils.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = InstanceBuilder::Self;

Instance::Instance(Instance&& rhs) : BuiltHandle(std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    debug_messenger = rhs.debug_messenger;
    rhs.debug_messenger = nullptr;
    api_version = rhs.api_version;
    layers = std::move(rhs.layers);
    extensions = std::move(rhs.extensions);
}

Instance::~Instance() {
    if (handle) {
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

Self InstanceBuilder::setAppName(const char* name) {
    info.app_name = name;
    return *this;
}

Self InstanceBuilder::setAppVerion(uint32_t version) {
    info.app_version = version;
    return *this;
}

Self InstanceBuilder::setEngineName(const char* name) {
    info.engine_name = name;
    return *this;
}

Self InstanceBuilder::setEngineVersion(uint32_t version) {
    info.engine_version = version;
    return *this;
}

Self InstanceBuilder::setApiVerion(uint32_t version) {
    info.api_version = version;
    return *this;
}

Self InstanceBuilder::addLayer(const char* layer) {
    info.layers.push_back(layer);
    return *this;
}

Self InstanceBuilder::addLayers(const Vector<const char*> layers) {
    info.layers.insert(info.layers.end(), layers.begin(), layers.end());
    return *this;
}

Self InstanceBuilder::addExtension(const char* extension) {
    info.extensions.push_back(extension);
    return *this;
}

Self InstanceBuilder::addExtensions(const Vector<const char*>& extensions) {
    info.extensions.insert(info.extensions.end(), extensions.begin(), extensions.end());
    return *this;
}

Self InstanceBuilder::enableValidationLayers(bool enable) {
    if (enable) {
        info.layers.push_back("VK_LAYER_KHRONOS_validation");
    }
    return *this;
}

Self InstanceBuilder::enableDebugUtils(bool enable, PFN_vkDebugUtilsMessengerCallbackEXT debug_callback) {
    info.enable_debug_utils = enable;
    if (debug_callback) {
        info.debug_callback = debug_callback;
    }
    return *this;
}

InstanceBuilder::Built InstanceBuilder::build() {
    // Initialize Vulkan loader
    OnRet(volkInitialize(), "Unable to initialize Vulkan loader");

    if (info.api_version >= VK_API_VERSION_1_1) {
        // Add required extensions for memory allocator
        addExtension(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }
    if (info.enable_debug_utils) {
        // VK_EXT_debug_utils combines the functionality of both VK_EXT_debug_report and VK_EXT_debug_marker
        addExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    std::sort(info.extensions.begin(), info.extensions.end(), strLess);
    auto new_end = std::unique(info.extensions.begin(), info.extensions.end());
    info.extensions.erase(new_end, info.extensions.end());

    auto app_info = Itor::ApplicationInfo();
    app_info.pApplicationName = info.app_name;
    app_info.applicationVersion = info.app_version;
    app_info.pEngineName = info.engine_name;
    app_info.engineVersion = info.engine_version;
    app_info.apiVersion = info.api_version;
    auto instance_ci = Itor::InstanceCreateInfo();
    instance_ci.pApplicationInfo = &app_info;
    if (info.layers.size() > 0) {
        if (!checkInstanceLayers(info.layers)) {
            return Er("Not all the required layers are supported");
        }
        // Note: To debug issue in `vkCreateInstance` and `vkDestroyInstance` calls,
        // pass a `VkDebugUtilsMessengerCreateInfoEXT` struct to instance_ci.pNext.
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

    Instance instance(std::move(info.__name));
    OnRet(vkCreateInstance(&instance_ci, nullptr, instance), "Failed to create instance");
    instance.api_version = info.api_version;
    instance.layers = std::move(info.layers);
    instance.extensions = std::move(info.extensions);

    volkLoadInstance(instance);

    // Setup debug messenger that works after `vkCreateInstance` and before `vkDestroyInstance`
    if (info.enable_debug_utils) {
        OnRet(createDebugUtils(instance, info.debug_callback, &instance.debug_messenger),
              "Failed to create debug utils messenger");
    }

    return Ok(std::move(instance));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
