#pragma once
#include "../__core.hpp"
#include "../image.hpp"
#include "../image_view.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Swapchain;

class SwapchainState : public CoreStater<SwapchainState> {
    friend struct Swapchain;

private:
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
    explicit SwapchainState(String&& name = "Swapchain") : CoreStater(std::move(name)) {}
    SwapchainState(SwapchainState&&);

    Self addDesiredFormat(const VkSurfaceFormatKHR& format);
    Self addDesiredPresentMode(VkPresentModeKHR mode);
    Self setDesiredExtent(const VkExtent2D& extent);
    Self setOld(VkSwapchainKHR old);

    Res<Swapchain> into(const CoreApi& api) const;
};

struct Swapchain : public CoreResource<VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR> {
    Vector<VkImage> images{};      /**< Handles of swapchain images */
    uint32_t image_count;          /**< VkImage number that has count == images.size() */
    VkFormat image_format;         /**< VkImage format */
    VkExtent2D image_extent;       /**< VkImage extent */
    uint32_t image_layers;         /**< VkImage array layers  */
    VkImageUsageFlags image_usage; /**< VkImage usage */

protected:
    explicit Swapchain(const CoreApi& api) : CoreResource(api) {}

public:
    Swapchain(Swapchain&&);
    ~Swapchain();

    /**
     * @brief Take out swapchain handle
     *
     * After take out handle, this swapchain will be `__borrowed = true`.
     */
    VkSwapchainKHR take();

    VkResult acquireNextImage(uint32_t& image_index, VkSemaphore semaphore, VkFence fence = VK_NULL_HANDLE) const;
    /** Create image from the index-th swapchain image */
    Res<Image> newImage(uint32_t index) const;
    /** Create the image view for the index-th swapchain image */
    Res<ImageView> newImageView(uint32_t index) const;

    static Res<Swapchain> from(const CoreApi& api, const SwapchainState& info);
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
