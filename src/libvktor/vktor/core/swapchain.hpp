#pragma once
#include "__core.hpp"
#include "device.hpp"
#include "image.hpp"
#include "image_view.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Swapchain;

class SwapchainState : public CoreStater<SwapchainState> {
    friend struct Swapchain;

private:
    const VkSurfaceKHR& surface;

    Vector<VkSurfaceFormatKHR> desired_formats{};
    // VkFormatFeatureFlags format_feature_flags = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;
    Vector<VkPresentModeKHR> desired_present_modes{};
    VkExtent2D desired_extent{};
    uint32_t image_layers = 1;
    VkImageUsageFlags image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    VkSwapchainKHR old = VK_NULL_HANDLE;

private:
    VkSurfaceFormatKHR chooseSurfaceFormat(const Vector<VkSurfaceFormatKHR>& formats);
    VkPresentModeKHR choosePresentMode(const Vector<VkPresentModeKHR>& modes);
    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capalibities);

public:
    explicit SwapchainState(const VkSurfaceKHR& surface, Name&& name = "Swapchain")
        : CoreStater(std::move(name))
        , surface(surface) {}

    Self addDesiredFormat(const VkSurfaceFormatKHR& format);
    Self addDesiredPresentMode(VkPresentModeKHR mode);
    Self setDesiredExtent(const VkExtent2D& extent);

    Res<Swapchain> into(const Device& device);
};

struct Swapchain : public CoreResource<VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR, Device> {
    Vector<Image> images;                                                /**< Handles of images in swapchain */
    uint32_t image_count = 0;                                            /**< Image number that has count == images.size() */
    VkFormat image_format = VK_FORMAT_UNDEFINED;                         /**< Image format of images[*].format */
    VkExtent2D image_extent{0, 0};                                       /**< Image extent of images[*].extent */
    uint32_t image_layers = 1;                                           /**< Image extent of images[*].array_layers */
    VkImageUsageFlags image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; /**< Image extent of images[*].usage*/

    Swapchain(const Device& device) : CoreResource(device) {}
    Swapchain(Swapchain&&);
    ~Swapchain();

    /**
     * @brief Create image views for swapchain images
     */
    Vector<ImageView> createImageViews() const;
    /**
     * @brief Create the image view for the index-th swapchain image
     */
    Res<ImageView> createImageView(uint32_t index) const;

    static Res<Swapchain> from(const Device& device, SwapchainState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
