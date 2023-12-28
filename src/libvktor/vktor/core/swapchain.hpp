#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "image.hpp"
#include "image_view.hpp"
#include "physical_device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Swapchain : public BuiltResource<VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR, Device> {
    Vector<Image> images;                                                /**< Handles of images in swapchain */
    uint32_t image_count = 0;                                            /**< Image number that has count == images.size() */
    VkFormat image_format = VK_FORMAT_UNDEFINED;                         /**< Image format of images[*].format */
    VkExtent2D image_extent{0, 0};                                       /**< Image extent of images[*].extent */
    uint32_t image_layers = 1;                                           /**< Image extent of images[*].array_layers */
    VkImageUsageFlags image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; /**< Image extent of images[*].usage*/

    Swapchain(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    Swapchain(Swapchain&&);
    ~Swapchain();

    /**
     * @brief Create image views for swapchain images
     */
    Vector<ImageView> createImageViews() const;
};

struct SwapchainInfo : public BuilderInfo {
    Vector<VkSurfaceFormatKHR> desired_formats{};
    // VkFormatFeatureFlags format_feature_flags = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;
    Vector<VkPresentModeKHR> desired_present_modes{};
    VkExtent2D desired_extent{};
    uint32_t image_layers = 1;
    VkImageUsageFlags image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    VkSwapchainKHR old = VK_NULL_HANDLE;
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
    Self setDesiredExtent(const VkExtent2D& extent);

private:
    VkSurfaceFormatKHR chooseSurfaceFormat(const Vector<VkSurfaceFormatKHR>& formats);
    VkPresentModeKHR choosePresentMode(const Vector<VkPresentModeKHR>& modes);
    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capalibities);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
