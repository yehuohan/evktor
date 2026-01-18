#pragma once
#include "__api.hpp"
#include "instance.hpp"
#include "queue.hpp"
#include <functional>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

class CoreApi;
struct PhysicalDevice;

/**
 * @brief Details of physical device for helping pick best suitable one
 *
 * Require a valid physical device handle when construct.
 */
struct PhysicalDeviceDetails {
    const VkPhysicalDevice& physical_device; /**< The physical device to get details */
    const VkSurfaceKHR& surface;             /**< Surface for collecting presence indices */
    Vector<uint32_t> present_indices{};      /**< Present queue family index for queue_family_props */
    Vector<uint32_t> graphics_indices{};     /**< Graphics queue family index for queue_family_props */
    Vector<uint32_t> compute_indices{};      /**< Compute queue family index for queue_family_props */
    Vector<uint32_t> transfer_indices{};     /**< Transfer queue family index for queue_family_props */
    Vector<VkQueueFamilyProperties> queue_family_props{};

    void print() const;
    void collect();
    HashMap<uint32_t, QueueFamilyProps> convert() const;
};

class PhysicalDeviceState : public CoreState<PhysicalDeviceState> {
    friend struct PhysicalDevice;

private:
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDeviceType preferred_type = VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM;
    bool require_present_queue = false;
    bool require_graphics_queue = false;
    bool require_compute_queue = false;
    bool require_transfer_queue = false;
    Vector<std::function<bool(VkInstance, VkPhysicalDevice)>> checkers{};

private:
    /** Check required items */
    bool checkSuitable(VkInstance instance, const PhysicalDeviceDetails& details);
    /** Check preferred items */
    size_t pickBestSuitable(const Vector<PhysicalDeviceDetails>& details);

public:
    explicit PhysicalDeviceState(String&& name = "PhysicalDevice") : CoreState(std::move(name)) {}

    // Self selectGPU();
    Self preferDiscreteGPU();
    Self preferIntegratedGPU();
    Self requirePresentQueue(VkSurfaceKHR surface, bool require = true);
    Self requireGraphicsQueue(bool require = true);
    Self requireComputeQueue(bool require = true);
    Self requireTransferQueue(bool require = true);
    Self addChecker(std::function<bool(VkInstance, VkPhysicalDevice)> checker);

    Res<PhysicalDevice> into(CRef<Instance> instance);
};

struct PhysicalDevice : public CoreHandle<VkPhysicalDevice> {
    friend CoreApi;

    CRef<Instance> instance;

    /** Map queue family index to it's properties
     *  - For `PhysicalDevice`: it's available queues to create for `Device`
     *  - For `Device`: it's available queues to get from the `Device` (the `Device` may update `QueueFamilyProps.count`)
     */
    mutable HashMap<uint32_t, QueueFamilyProps> queue_family_props{};

protected:
    friend struct PhysicalDeviceState;

    explicit PhysicalDevice(CRef<Instance> instance) : instance(instance) {}

public:
    PhysicalDevice(PhysicalDevice&&);
    ~PhysicalDevice();
    PhysicalDevice& operator=(PhysicalDevice&&);

    inline VkPhysicalDeviceFeatures getPhysicalDeviceFeatures() const;
    inline VkPhysicalDeviceProperties getPhysicalDeviceProperties() const;
    inline VkPhysicalDeviceMemoryProperties getPhysicalDeviceMemoryProperties() const;

    static Res<PhysicalDevice> from(CRef<Instance> instance, PhysicalDeviceState& info);
    static Res<PhysicalDevice> borrow(CRef<Instance> instance, VkPhysicalDevice handle, VkSurfaceKHR surface = VK_NULL_HANDLE);
};

inline VkPhysicalDeviceFeatures PhysicalDevice::getPhysicalDeviceFeatures() const {
    VkPhysicalDeviceFeatures feats{};
    vkGetPhysicalDeviceFeatures(handle, &feats);
    return feats;
}

inline VkPhysicalDeviceProperties PhysicalDevice::getPhysicalDeviceProperties() const {
    VkPhysicalDeviceProperties props{};
    vkGetPhysicalDeviceProperties(handle, &props);
    return props;
}

inline VkPhysicalDeviceMemoryProperties PhysicalDevice::getPhysicalDeviceMemoryProperties() const {
    VkPhysicalDeviceMemoryProperties props{};
    vkGetPhysicalDeviceMemoryProperties(handle, &props);
    return props;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
