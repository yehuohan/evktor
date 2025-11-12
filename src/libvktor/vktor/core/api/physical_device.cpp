#include "physical_device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = PhysicalDeviceState::Self;

void PhysicalDeviceDetails::print() const {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(physical_device, &props);
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
           VkStr(VkPhysicalDeviceType, props.deviceType),
           VK_API_VERSION_MAJOR(props.apiVersion),
           VK_API_VERSION_MINOR(props.apiVersion),
           VK_API_VERSION_PATCH(props.apiVersion),
           VK_VERSION_MAJOR(props.driverVersion),
           VK_VERSION_MINOR(props.driverVersion),
           VK_VERSION_PATCH(props.driverVersion),
           vec2str(present_indices),
           vec2str(graphics_indices),
           vec2str(compute_indices),
           vec2str(transfer_indices));
}

void PhysicalDeviceDetails::collect() {
    queue_family_props = enumerate<VkQueueFamilyProperties>(vkGetPhysicalDeviceQueueFamilyProperties, physical_device);
    for (uint32_t idx = 0; idx < u32(queue_family_props.size()); idx++) {
        const VkQueueFamilyProperties& p = queue_family_props[idx];
        if (surface) {
            VkBool32 present = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, idx, surface, &present);
            if (present) {
                present_indices.push_back(idx);
            }
        }
        if (p.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphics_indices.push_back(idx);
        }
        if (p.queueFlags & VK_QUEUE_COMPUTE_BIT) {
            compute_indices.push_back(idx);
        }
        if (p.queueFlags & VK_QUEUE_TRANSFER_BIT) {
            transfer_indices.push_back(idx);
        }
    }
}

HashMap<uint32_t, QueueFamilyProps> PhysicalDeviceDetails::convert() const {
    HashMap<uint32_t, QueueFamilyProps> res{};
    for (uint32_t idx : present_indices) {
        res[idx].count = queue_family_props[idx].queueCount;
        res[idx].present = true;
    }
    for (uint32_t idx : graphics_indices) {
        res[idx].count = queue_family_props[idx].queueCount;
        res[idx].graphics = true;
    }
    for (uint32_t idx : compute_indices) {
        res[idx].count = queue_family_props[idx].queueCount;
        res[idx].compute = true;
    }
    for (uint32_t idx : transfer_indices) {
        res[idx].count = queue_family_props[idx].queueCount;
        res[idx].transfer = true;
    }
    return std::move(res);
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

Self PhysicalDeviceState::addChecker(std::function<bool(VkInstance, VkPhysicalDevice)> checker) {
    checkers.push_back(checker);
    return *this;
}

bool PhysicalDeviceState::checkSuitable(VkInstance instance, const PhysicalDeviceDetails& details) {
    if ((require_present_queue && details.present_indices.empty()) ||
        (require_graphics_queue && details.graphics_indices.empty()) ||
        (require_compute_queue && details.compute_indices.empty()) ||
        (require_transfer_queue && details.transfer_indices.empty())) {
        return false;
    }
    for (const auto& checker : checkers) {
        if (checker && !checker(instance, details.physical_device)) {
            return false;
        }
    }
    return true;
}

size_t PhysicalDeviceState::pickBestSuitable(const Vector<PhysicalDeviceDetails>& details) {
    for (size_t k = 0; k < details.size(); k++) {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(details[k].physical_device, &props);
        if (preferred_type == props.deviceType) {
            vktOut("{} is selected", props.deviceName);
            return k;
        }
    }
    vktOut("The first is selected");
    return 0;
}

Res<PhysicalDevice> PhysicalDeviceState::into(const Instance& instance) {
    return PhysicalDevice::from(instance, *this);
}

PhysicalDevice::PhysicalDevice(PhysicalDevice&& rhs) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    queue_family_props = std::move(rhs.queue_family_props);
}

PhysicalDevice::~PhysicalDevice() {
    handle = VK_NULL_HANDLE;
    queue_family_props.clear();
}

Res<PhysicalDevice> PhysicalDevice::from(const Instance& instance, PhysicalDeviceState& info) {
    if (info.require_present_queue && (!info.surface)) {
        return Er("Physical device's supporting 'present' needs a valid surface");
    }

    // Get physical devices list
    Vector<VkPhysicalDevice> devs{};
    OnRet(enumerate(devs, vkEnumeratePhysicalDevices, instance), "Failed to get list of physical devices");
    if (devs.empty()) {
        return Er("There is no Vulkan supported GPU");
    }

    // Get all suitable physical device on account of properties, features and extensions and so on
    Vector<PhysicalDeviceDetails> suitables{};
    for (const auto& d : devs) {
        PhysicalDeviceDetails details{d, info.surface};
        details.collect();
        if (info.__verbose) {
            details.print();
        }
        if (info.checkSuitable(instance, details)) {
            suitables.push_back(std::move(details));
        }
    }
    if (suitables.empty()) {
        return Er("Can not find a suitable GPU device");
    }

    // Pick the best suitable
    size_t best = info.pickBestSuitable(suitables);

    PhysicalDevice phy_dev{};
    phy_dev.handle = suitables[best].physical_device;
    phy_dev.queue_family_props = suitables[best].convert();

    return Ok(phy_dev);
}

Res<PhysicalDevice> PhysicalDevice::borrow(VkPhysicalDevice handle) {
    PhysicalDevice phy_dev{};
    phy_dev.__borrowed = true;
    phy_dev.handle = handle;
    return Ok(phy_dev);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
