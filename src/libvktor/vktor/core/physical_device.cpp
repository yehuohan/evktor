#include "physical_device.hpp"
#include "utils.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = PhysicalDeviceSelector::Self;

PhysicalDevice::PhysicalDevice(PhysicalDevice&& rhs) : BuiltHandle(std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    queue_families = std::move(rhs.queue_families);
    queue_family_props = std::move(rhs.queue_family_props);
    extensions = std::move(rhs.extensions);
    // features = std::move(rhs.features);
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

Self PhysicalDeviceSelector::preferDiscreteGPU() {
    info.preferred_type = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    return *this;
}

Self PhysicalDeviceSelector::preferIntegratedGPU() {
    info.preferred_type = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
    return *this;
}

Self PhysicalDeviceSelector::requirePresentQueue(const VkSurfaceKHR surface, bool require) {
    info.surface = surface;
    info.require_present_queue = require;
    return *this;
}

Self PhysicalDeviceSelector::requireGraphicsQueue(bool require) {
    info.require_graphics_queue = require;
    return *this;
}

Self PhysicalDeviceSelector::requireComputeQueue(bool require) {
    info.require_compute_queue = require;
    return *this;
}

Self PhysicalDeviceSelector::requireTransferQueue(bool require) {
    info.require_transfer_queue = require;
    return *this;
}

Self PhysicalDeviceSelector::addRequiredExtension(const char* extension) {
    info.required_extensions.push_back(extension);
    return *this;
}

Self PhysicalDeviceSelector::addRequiredExtensions(const Vector<const char*> extensions) {
    info.required_extensions.insert(info.required_extensions.end(), extensions.begin(), extensions.end());
    return *this;
}

PhysicalDeviceSelector::Built PhysicalDeviceSelector::select() {
    // Add required extensions for memory allocator
    if (instance.api_version >= VK_API_VERSION_1_1) {
        addRequiredExtension(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
        addRequiredExtension(VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME);
        addRequiredExtension(VK_KHR_BIND_MEMORY_2_EXTENSION_NAME);
        addRequiredExtension(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);
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
        if (checkSuitable(details)) {
            suitables.push_back(details);
        }
    }
    if (suitables.size() == 0) {
        return Er("Can NOT find a suitable GPU device");
    }

    // Pick the best suitable
    PhysicalDevice phy_dev = pickBestSuitable(suitables);
    return Ok(std::move(phy_dev));
}

bool PhysicalDeviceSelector::checkSuitable(const PhysicalDeviceDetails& details) {
    if (info.require_present_queue && details.present_indices.size() == 0) {
        return false;
    }
    if (info.require_graphics_queue && details.graphics_indices.size() == 0) {
        return false;
    }
    if (info.require_compute_queue && details.compute_indices.size() == 0) {
        return false;
    }
    if (info.require_transfer_queue && details.transfer_indices.size() == 0) {
        return false;
    }
    if (!checkDeviceExtensions(details.physical_device, info.required_extensions)) {
        return false;
    }

    return true;
}

PhysicalDevice PhysicalDeviceSelector::pickBestSuitable(const Vector<PhysicalDeviceDetails> details) {
    const PhysicalDeviceDetails* pd = nullptr;
    for (const auto& d : details) {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(d.physical_device, &props);
        if (info.preferred_type == props.deviceType) {
            pd = &d;
            break;
        }
    }
    if (!pd) {
        pd = &details.at(0);
    }
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(pd->physical_device, &props);

    std::string str(vktFmt("{} is selected {{\n", props.deviceName));
    PhysicalDevice phy_dev(std::move(info.__name));
    phy_dev.handle = pd->physical_device;

    // Select the first queue family index by default
    if (info.require_present_queue) {
        uint32_t index = pd->present_indices[0];
        phy_dev.queue_families.present = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].present = true;
        str += vktFmt("    present index: {}\n", index);
    }
    if (info.require_graphics_queue) {
        uint32_t index = pd->graphics_indices[0];
        phy_dev.queue_families.graphics = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].graphics = true;
        str += vktFmt("    graphics index: {}\n", index);
    }
    if (info.require_compute_queue) {
        uint32_t index = pd->compute_indices[0];
        phy_dev.queue_families.compute = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].compute = true;
        str += vktFmt("    compute index: {}\n", index);
    }
    if (info.require_transfer_queue) {
        uint32_t index = pd->transfer_indices[0];
        phy_dev.queue_families.transfer = index;
        phy_dev.queue_family_props[index].count = pd->queue_family_props[index].queueCount;
        phy_dev.queue_family_props[index].transfer = true;
        str += vktFmt("    transfer index: {}\n", index);
    }

    str += "}";
    vktOut("{}", str);
    phy_dev.extensions = std::move(info.required_extensions);

    return std::move(phy_dev);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
