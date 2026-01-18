#include "instance.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = InstanceState::Self;

Self InstanceState::setAllocationCallbacks(const VkAllocationCallbacks* allocation_callbacks) {
    allocator = allocation_callbacks;
    return *this;
}

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

Self InstanceState::addLayers(const Vector<const char*>& _layers) {
    layers.insert(layers.end(), _layers.begin(), _layers.end());
    return *this;
}

Self InstanceState::tryAddLayer(const char* layer) {
    try_layers.push_back(layer);
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

Self InstanceState::tryAddExtension(const char* extension) {
    try_extensions.push_back(extension);
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
}

Instance::~Instance() {
    if (!__borrowed && handle) {
        vkDestroyInstance(handle, allocator);
    }
    handle = VK_NULL_HANDLE;
};

Instance& Instance::operator=(Instance&& rhs) {
    if (this != &rhs) {
        if (!__borrowed && handle) {
            vkDestroyInstance(handle, allocator);
        }

        handle = rhs.handle;
        rhs.handle = VK_NULL_HANDLE;
        __borrowed = rhs.__borrowed;
        api_version = rhs.api_version;
    }
    return *this;
}

Res<Instance> Instance::from(InstanceState& info) {
    // Initialize Vulkan loader:
    //      * get vkGetInstanceProcAddr from vulkan.so/dll
    //      * call volkGenLoadLoader(VK_NULL_HANDLE, vkGetInstanceProcAddr))
    OnRet(volkInitialize(), "Unable to initialize Vulkan loader");

    Vector<VkLayerProperties> available_layers{};
    OnRet(enumerate(available_layers, vkEnumerateInstanceLayerProperties), "Failed to get properties of instance layers");
    if (!checkExtensions("instance layers", available_layers, info.layers, info.try_layers)) {
        return Er("Not all the required instance layers are supported");
    }
    Vector<VkExtensionProperties> available_extensions{};
    OnRet(enumerate(available_extensions, vkEnumerateInstanceExtensionProperties, nullptr),
          "Failed to get properties of instance extensions");
    if (!checkExtensions("instance extensions", available_extensions, info.extensions, info.try_extensions)) {
        return Er("Not all the required instance extensions are supported");
    }
    if (info.__verbose) {
        printExtensions("instance layers", available_layers, info.layers);
        printExtensions("instance extensions", available_extensions, info.extensions);
    }

    // To debug issue in vkCreateInstance and vkDestroyInstance calls,
    // pass a VkDebugUtilsMessengerCreateInfoEXT struct to `instance_ci.pNext`.
    auto instance_ci = Itor::InstanceCreateInfo(info.__next);
    instance_ci.pApplicationInfo = &info.app_info;
    if (info.layers.size() > 0) {
        instance_ci.enabledLayerCount = u32(info.layers.size());
        instance_ci.ppEnabledLayerNames = info.layers.data();
    }
    if (info.extensions.size() > 0) {
        instance_ci.enabledExtensionCount = u32(info.extensions.size());
        instance_ci.ppEnabledExtensionNames = info.extensions.data();
    }

    Instance instance{};
    OnRet(vkCreateInstance(&instance_ci, info.allocator, instance), "Failed to create instance");
    instance.allocator = info.allocator;
    instance.api_version = info.app_info.apiVersion;

    volkLoadInstance(instance);

    return Ok(std::move(instance));
}

Res<Instance> Instance::borrow(VkInstance handle,
                               PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr,
                               uint32_t api_version,
                               VkAllocationCallbacks* allocator) {
    // Initialize Vulkan loader:
    //      * provide vkGetInstanceProcAddr
    //      * call volkGenLoadLoader(VK_NULL_HANDLE, vkGetInstanceProcAddr))
    volkInitializeCustom(fpGetInstanceProcAddr);

    Instance instance{};
    instance.__borrowed = true;
    instance.handle = handle;
    instance.allocator = allocator;
    instance.api_version = api_version;

    volkLoadInstance(instance);

    return Ok(std::move(instance));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
