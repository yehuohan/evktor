#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "physical_device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Swapchain : public BuiltResource<VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR, Device> {
    Vector<VkImage> images;                /**< Handles of images in swapchain */
    Vector<VkImageView> imageviews;        /**< Views of images */
    uint32_t count = 0;                    /**< Number of images */
    VkFormat format = VK_FORMAT_UNDEFINED; /**< Color format of images */
    VkExtent2D extent{0, 0};               /**< Resolution of images */

    Swapchain(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    Swapchain(Swapchain&&);
    ~Swapchain();
};

struct SwapchainInfo : public BuilderInfo {
    Vector<VkSurfaceFormatKHR> desired_formats{
        VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR}
    };
    Vector<VkPresentModeKHR> desired_present_modes{};
    VkExtent2D desired_extent{256, 256};
    // VkFormatFeatureFlags format_feature_flags = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;
    // VkImageUsageFlags image_usage_flags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
};

class SwapchainBuilder : public Builder<SwapchainBuilder, Swapchain, SwapchainInfo> {
private:
    const Device& device;
    const VkSurfaceKHR& surface;

public:
    explicit SwapchainBuilder(const Device& device, const VkSurfaceKHR& surface, Name&& name = "Swapchain")
        : Builder(std::move(name))
        , device(device)
        , surface(surface) {}
    virtual Built build() override;

    Self addDesiredFormat(const VkSurfaceFormatKHR& format);
    Self addDesiredPresentMode(VkPresentModeKHR mode);
    Self setDesiredExtent(const VkExtent2D& extent2d);

private:
    VkSurfaceFormatKHR chooseSurfaceFormat(const Vector<VkSurfaceFormatKHR>& formats);
    VkPresentModeKHR choosePresentMode(const Vector<VkPresentModeKHR>& modes);
    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capalibities);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
