#pragma once
#include "__core.hpp"
#include "device.hpp"
#include "image.hpp"
#include "image_view.hpp"
#include "surface.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Swapchain;

class SwapchainState : public CoreStater<SwapchainState> {
    friend struct Swapchain;

private:
    mutable Surface surface;

    Vector<VkSurfaceFormatKHR> desired_formats{};
    // VkFormatFeatureFlags format_feature_flags = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;
    Vector<VkPresentModeKHR> desired_present_modes{};
    VkExtent2D desired_extent{};
    uint32_t image_layers = 1; /**< Swapchain image array layers */
    VkImageUsageFlags image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    VkSwapchainKHR old = VK_NULL_HANDLE;

private:
    VkSurfaceFormatKHR chooseSurfaceFormat(const Vector<VkSurfaceFormatKHR>& formats) const;
    VkPresentModeKHR choosePresentMode(const Vector<VkPresentModeKHR>& modes) const;
    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capalibities) const;

public:
    explicit SwapchainState(Surface&& surface, Name&& name = "Swapchain")
        : CoreStater(std::move(name))
        , surface(std::move(surface)) {}

    Self addDesiredFormat(const VkSurfaceFormatKHR& format);
    Self addDesiredPresentMode(VkPresentModeKHR mode);
    Self setDesiredExtent(const VkExtent2D& extent);

    Res<Swapchain> into(const Device& device) const;
};

struct Swapchain : public CoreResource<VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR, Device> {
    Surface surface;               /**< Swapchain take surface's ownership */
    Vector<VkImage> images{};      /**< Handles of swapchain images */
    uint32_t image_count;          /**< VkImage number that has count == images.size() */
    VkFormat image_format;         /**< VkImage format */
    VkExtent2D image_extent;       /**< VkImage extent */
    uint32_t image_layers;         /**< VkImage array layers  */
    VkImageUsageFlags image_usage; /**< VkImage usage */

protected:
    explicit Swapchain(const Device& device, Surface&& surface) : CoreResource(device), surface(std::move(surface)) {}

public:
    Swapchain(Swapchain&&);
    ~Swapchain();

    VkResult acquireNextImage(uint32_t& image_index, VkSemaphore semaphore, VkFence fence = VK_NULL_HANDLE) const;

    /** Create image from the index-th swapchain image */
    Res<Image> createImage(uint32_t index) const;
    /** Create the image view for the index-th swapchain image */
    Res<ImageView> createImageView(uint32_t index) const;

    static Res<Swapchain> from(const Device& device, const SwapchainState& info);
};

template <>
class Arg<Swapchain> : private NonCopyable {
public:
    /** The swapchain image index going to access */
    uint32_t image_index = 0;

public:
    const Swapchain& a;

public:
    explicit Arg(const Swapchain& a) : a(a) {}
    explicit Arg(const Swapchain& a, uint32_t image_index) : a(a), image_index(image_index) {}
    OnConstType(VkSwapchainKHR, a.handle);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
