#pragma once
#include "__api.hpp"
#include "instance.hpp"
#include "queue.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

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

    static void collect(PhysicalDeviceDetails& details);
    static void print(const PhysicalDeviceDetails& details);
};

class PhysicalDeviceState : public CoreStater<PhysicalDeviceState> {
    friend struct PhysicalDevice;

private:
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDeviceType preferred_type = VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM;
    bool require_present_queue = false;
    bool require_graphics_queue = false;
    bool require_compute_queue = false;
    bool require_transfer_queue = false;
    Vector<const char*> required_extensions{};
    // VkPhysicalDeviceFeatures required_features{};

private:
    /** Check required items */
    bool checkSuitable(const PhysicalDeviceDetails& details);
    /** Check preferred items */
    PhysicalDevice pickBestSuitable(const Vector<PhysicalDeviceDetails> details);

public:
    explicit PhysicalDeviceState(Name&& name = "PhysicalDevice") : CoreStater(std::move(name)) {}

    Self preferDiscreteGPU();
    Self preferIntegratedGPU();
    Self requirePresentQueue(VkSurfaceKHR surface, bool require = true);
    Self requireGraphicsQueue(bool require = true);
    Self requireComputeQueue(bool require = true);
    Self requireTransferQueue(bool require = true);
    // Self requireDedicatedComputeQueue(bool require = true);
    // Self requireDedicatedTransferQueue(bool require = true);
    // Self requireSeparateComputeQueue(bool require = true);
    // Self requireSeparateTransferQueue(bool require = true);
    Self addRequiredExtension(const char* extension);
    Self addRequiredExtensions(const Vector<const char*> extensions);
    // Self setRequiredFeatures(const VkPhysicalDeviceFeatures& features);

    Res<PhysicalDevice> into(const Instance& instance);
};

struct PhysicalDevice : public CoreHandle<VkPhysicalDevice> {
    QueueFamilies queue_families{};
    HashMap<uint32_t, QueueFamilyProps> queue_family_props{}; /**< Map queue family index to it's properties */
    Vector<const char*> extensions{};                         /**< Enabled extensions for device */
    // VkPhysicalDeviceFeatures features{};
    VkPhysicalDeviceProperties properties{};
    VkPhysicalDeviceMemoryProperties memory_properties{};

protected:
    friend struct PhysicalDeviceState;

    explicit PhysicalDevice() {}

public:
    PhysicalDevice(PhysicalDevice&&);
    ~PhysicalDevice();
    bool isExtensionEnabled(const char* extension) const;

    static Res<PhysicalDevice> from(const Instance& instance, PhysicalDeviceState& info);
    // static Res<PhysicalDevice> borrow(VkPhysicalDevice handle);
};

bool checkDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& device_extensions);
void printDeviceExtensions(VkPhysicalDevice pd, const Vector<const char*>& enabled_extensions);

NAMESPACE_END(core)
NAMESPACE_END(vkt)
