#include "physical_device.hpp"
#include <algorithm>
#include <set>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = PhysicalDeviceState::Self;

void PhysicalDeviceDetails::collect(PhysicalDeviceDetails& details) {
    details.queue_family_props = enumerate<VkQueueFamilyProperties>(vkGetPhysicalDeviceQueueFamilyProperties,
                                                                    details.physical_device);
    for (uint32_t idx = 0; idx < u32(details.queue_family_props.size()); idx++) {
        const VkQueueFamilyProperties& p = details.queue_family_props[idx];
        if (details.surface) {
            VkBool32 present = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(details.physical_device, idx, details.surface, &present);
            if (present) {
                details.present_indices.push_back(idx);
            }
        }
        if (p.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            details.graphics_indices.push_back(idx);
        }
        if (p.queueFlags & VK_QUEUE_COMPUTE_BIT) {
            details.compute_indices.push_back(idx);
        }
        if (p.queueFlags & VK_QUEUE_TRANSFER_BIT) {
            details.transfer_indices.push_back(idx);
        }
    }
}

void PhysicalDeviceDetails::print(const PhysicalDeviceDetails& details) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(details.physical_device, &props);
    // VkPhysicalDeviceFeatures feats;
    // vkGetPhysicalDeviceFeatures(pd, &feats);

    const char* pdev_type = "Unkown";
    switch (props.deviceType) {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER: pdev_type = "Other"; break;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: pdev_type = "Integrated GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: pdev_type = "Discrete GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: pdev_type = "Virtual GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: pdev_type = "CPU"; break;
    default: break;
    }

    vktOut("{} {{\n"
           "    vender id: {:#04x}\n"
           "    device id: {:#04x}\n"
           "    device type: {}\n"
           "    api version: {}.{}.{}\n"
           "    driver version: {}.{}.{}\n"
           "    present indices: {}\n"
           "    graphics indices: {}\n"
           "    compute indices: {}\n"
           "    transfer indices: {}\n"
           "}}",
           props.deviceName,
           props.vendorID,
           props.deviceID,
           pdev_type,
           VK_API_VERSION_MAJOR(props.apiVersion),
           VK_API_VERSION_MINOR(props.apiVersion),
           VK_API_VERSION_PATCH(props.apiVersion),
           VK_VERSION_MAJOR(props.driverVersion),
           VK_VERSION_MINOR(props.driverVersion),
           VK_VERSION_PATCH(props.driverVersion),
           vec2str(details.present_indices),
           vec2str(details.graphics_indices),
           vec2str(details.compute_indices),
           vec2str(details.transfer_indices));
}

Self PhysicalDeviceState::preferDiscreteGPU() {
    preferred_type = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    return *this;
}

Self PhysicalDeviceState::preferIntegratedGPU() {
    preferred_type = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
    return *this;
}

Self PhysicalDeviceState::requirePresentQueue(VkSurfaceKHR _surface, bool require) {
    surface = _surface;
    require_present_queue = require;
    return *this;
}

Self PhysicalDeviceState::requireGraphicsQueue(bool require) {
    require_graphics_queue = require;
    return *this;
}

Self PhysicalDeviceState::requireComputeQueue(bool require) {
    require_compute_queue = require;
    return *this;
}

Self PhysicalDeviceState::requireTransferQueue(bool require) {
    require_transfer_queue = require;
    return *this;
}

Self PhysicalDeviceState::addRequiredExtension(const char* extension) {
    required_extensions.push_back(extension);
    return *this;
}

Self PhysicalDeviceState::addRequiredExtensions(const Vector<const char*> extensions) {
    required_extensions.insert(required_extensions.end(), extensions.begin(), extensions.end());
    return *this;
}

Self PhysicalDeviceState::addChecker(std::function<bool(VkInstance, VkPhysicalDevice)> checker) {
    checkers.push_back(checker);
    return *this;
}

bool PhysicalDeviceState::checkSuitable(VkInstance instance, const PhysicalDeviceDetails& details) {
    if (require_present_queue && details.present_indices.size() == 0) {
        return false;
    }
    if (require_graphics_queue && details.graphics_indices.size() == 0) {
        return false;
    }
    if (require_compute_queue && details.compute_indices.size() == 0) {
        return false;
    }
    if (require_transfer_queue && details.transfer_indices.size() == 0) {
        return false;
    }
    if (!checkDeviceExtensions(details.physical_device, required_extensions)) {
        return false;
    }
    for (const auto& checker : checkers) {
        if (checker && !checker(instance, details.physical_device)) {
            return false;
        }
    }
    return true;
}

PhysicalDevice PhysicalDeviceState::pickBestSuitable(const Vector<PhysicalDeviceDetails> details) {
    const PhysicalDeviceDetails* pd = nullptr;
    for (const auto& d : details) {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(d.physical_device, &props);
        if (preferred_type == props.deviceType) {
            pd = &d;
            break;
        }
    }
    if (!pd) {
        pd = &details.at(0);
    }
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(pd->physical_device, &props);

    String str(vktFmt("{} is selected {{\n", props.deviceName));
    PhysicalDevice phy_dev{};
    phy_dev.handle = pd->physical_device;

    // Select the first queue family index by default
    if (require_present_queue) {
        uint32_t index = pd->present_indices[0];
        phy_dev.queue_families.present = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].present = true;
        str += vktFmt("    present: index = {}, count = {}\n", index, pd->queue_family_props[index].queueCount);
    }
    if (require_graphics_queue) {
        uint32_t index = pd->graphics_indices[0];
        phy_dev.queue_families.graphics = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].graphics = true;
        str += vktFmt("    graphics: index = {}, count = {}\n", index, pd->queue_family_props[index].queueCount);
    }
    if (require_compute_queue) {
        uint32_t index = pd->compute_indices[0];
        phy_dev.queue_families.compute = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].compute = true;
        str += vktFmt("    compute: index = {}, count = {}\n", index, pd->queue_family_props[index].queueCount);
    }
    if (require_transfer_queue) {
        uint32_t index = pd->transfer_indices[0];
        phy_dev.queue_families.transfer = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].transfer = true;
        str += vktFmt("    transfer: index = {}, count = {}\n", index, pd->queue_family_props[index].queueCount);
    }

    str += "}";
    vktOut("{}", str);

    phy_dev.extensions = std::move(required_extensions);
    return std::move(phy_dev);
}

Res<PhysicalDevice> PhysicalDeviceState::into(const Instance& instance) {
    return PhysicalDevice::from(instance, *this);
}

PhysicalDevice::PhysicalDevice(PhysicalDevice&& rhs) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    queue_families = std::move(rhs.queue_families);
    queue_family_props = std::move(rhs.queue_family_props);
    extensions = std::move(rhs.extensions);
    // features = std::move(rhs.features);
    properties = std::move(rhs.properties);
    memory_properties = std::move(rhs.memory_properties);
}

PhysicalDevice::~PhysicalDevice() {
    handle = VK_NULL_HANDLE;
    queue_families.clear();
    queue_family_props.clear();
    extensions.clear();
}

bool PhysicalDevice::isExtensionEnabled(const char* extension) const {
    return std::find_if(extensions.begin(), extensions.end(), [&extension](auto& ext) {
               return std::strcmp(extension, ext) == 0;
           }) != extensions.end();
}

Res<PhysicalDevice> PhysicalDevice::from(const Instance& instance, PhysicalDeviceState& info) {
    // Add required extensions for memory allocator
    if (instance.api_version >= VK_API_VERSION_1_1) {
        info.addRequiredExtension(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
        info.addRequiredExtension(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME);
        info.addRequiredExtension(VK_KHR_BIND_MEMORY_2_EXTENSION_NAME);
        info.addRequiredExtension(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);
        std::sort(info.required_extensions.begin(), info.required_extensions.end(), strLess);
        auto new_end = std::unique(info.required_extensions.begin(), info.required_extensions.end());
        info.required_extensions.erase(new_end, info.required_extensions.end());
    }

    if (info.require_present_queue && (!info.surface)) {
        return Er("Physical device's supporting 'present' needs a valid surface");
    }

    // Get physical devices list
    Vector<VkPhysicalDevice> devs{};
    OnRet(enumerate(devs, vkEnumeratePhysicalDevices, instance), "Failed to get list of physical devices");
    if (devs.size() == 0) {
        return Er("There is no Vulkan supported GPU");
    }

    // Get all suitable physical device on account of properties, features and extensions and so on
    Vector<PhysicalDeviceDetails> suitables{};
    for (const auto& d : devs) {
        PhysicalDeviceDetails details{d, info.surface};
        PhysicalDeviceDetails::collect(details);
        if (info.__verbose) {
            PhysicalDeviceDetails::print(details);
        }
        if (info.checkSuitable(instance, details)) {
            suitables.push_back(std::move(details));
        }
    }
    if (suitables.size() == 0) {
        return Er("Can NOT find a suitable GPU device");
    }

    // Pick the best suitable
    PhysicalDevice phy_dev = info.pickBestSuitable(suitables);
    vkGetPhysicalDeviceProperties(phy_dev, &phy_dev.properties);
    vkGetPhysicalDeviceMemoryProperties(phy_dev, &phy_dev.memory_properties);
    if (info.__verbose) {
        printDeviceExtensions(phy_dev, phy_dev.extensions);
    }

    return Ok(std::move(phy_dev));
}

bool checkDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& device_extensions) {
    Vector<VkExtensionProperties> exts{};
    VkResult res = enumerate(exts, vkEnumerateDeviceExtensionProperties, pd, nullptr);
    if (res != VK_SUCCESS) {
        vktLogE("Failed to get properties of device extensions: {}", VkStr(VkResult, res));
        return false;
    }

    std::set<String> device_exts(device_extensions.begin(), device_extensions.end());
    for (const auto& e : exts) {
        device_exts.erase(e.extensionName);
    }

    bool empty = device_exts.empty();
    if (!empty) {
        vktLogW("Not supported device extensions:");
        for (const auto& e : device_exts) {
            vktLogW("\t{}", e);
        }
    }
    return empty;
}

void printDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& enabled_extensions) {
    Vector<VkExtensionProperties> ext_props{};
    VkResult res = enumerate(ext_props, vkEnumerateDeviceExtensionProperties, pd, nullptr);
    if (res != VK_SUCCESS) {
        vktLogE("Failed to get properties of device extensions: {}", VkStr(VkResult, res));
        return;
    }

    String str("Available device extensions {\n");
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
