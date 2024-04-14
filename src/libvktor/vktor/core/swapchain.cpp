#include "swapchain.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SwapchainState::Self;

SwapchainState::SwapchainState(SwapchainState&& rhs) : CoreStater(std::move(rhs.__name)), surface(std::move(rhs.surface)) {
    desired_formats = std::move(rhs.desired_formats);
    desired_present_modes = std::move(rhs.desired_present_modes);
    desired_extent = rhs.desired_extent;
    image_layers = rhs.image_layers;
    image_usage = rhs.image_usage;
    old = rhs.old;
}

Self SwapchainState::setSurface(Surface&& _surface) {
    surface = std::move(_surface);
    return *this;
}

Self SwapchainState::addDesiredFormat(const VkSurfaceFormatKHR& format) {
    desired_formats.push_back(format);
    return *this;
}

Self SwapchainState::addDesiredPresentMode(VkPresentModeKHR mode) {
    desired_present_modes.push_back(mode);
    return *this;
}

Self SwapchainState::setDesiredExtent(const VkExtent2D& extent) {
    desired_extent = extent;
    return *this;
}

Self SwapchainState::setOld(VkSwapchainKHR _old) {
    old = _old;
    return *this;
}

VkSurfaceFormatKHR SwapchainState::chooseSurfaceFormat(const Vector<VkSurfaceFormatKHR>& formats) const {
    if (desired_formats.empty()) {
        return VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }
    for (const auto& df : desired_formats) {
        for (const auto& sf : formats) {
            if (df.format == sf.format && df.colorSpace == sf.colorSpace) {
                return df;
            }
        }
    }
    vktLogW("Choose the first VkSurfaceFormatKHR as can't find a desired one");
    return formats[0];
}

VkPresentModeKHR SwapchainState::choosePresentMode(const Vector<VkPresentModeKHR>& modes) const {
    if (desired_present_modes.empty()) {
        return VK_PRESENT_MODE_FIFO_KHR;
    }
    for (const auto& dpm : desired_present_modes) {
        for (const auto& m : modes) {
            if (dpm == m) {
                return dpm;
            }
        }
    }
    vktLogW("Choose VK_PRESENT_MODE_FIFO_KHR as can't find a desired one");
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapchainState::chooseExtent(const VkSurfaceCapabilitiesKHR& capalibities) const {
    if (capalibities.currentExtent.width != UINT32_MAX) {
        return capalibities.currentExtent;
    } else {
        // `currentExtent` == UINT32_MAX means that match window's resolution within minImageExtent and maxImageExtent
        VkExtent2D extent = desired_extent;
        extent.width = std::clamp(extent.width, capalibities.minImageExtent.width, capalibities.maxImageExtent.width);
        extent.height = std::clamp(extent.height, capalibities.minImageExtent.height, capalibities.maxImageExtent.height);
        return extent;
    }
}

Res<Swapchain> SwapchainState::into(const CoreApi& api) const {
    return Swapchain::from(api, *this);
}

Swapchain::Swapchain(Swapchain&& rhs) : CoreResource(rhs.api), surface(std::move(rhs.surface)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    images = std::move(rhs.images);
    image_count = rhs.image_count;
    image_format = rhs.image_format;
    image_extent = rhs.image_extent;
    image_layers = rhs.image_layers;
    image_usage = rhs.image_usage;
}

Swapchain::~Swapchain() {
    if (!__borrowed && handle) {
        vkDestroySwapchainKHR(api, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
    images.clear(); // The images will be destroyed along with swapchain's destruction
}

VkSwapchainKHR Swapchain::take() {
    __borrowed = true;
    return handle;
}

VkResult Swapchain::acquireNextImage(uint32_t& image_index, VkSemaphore semaphore, VkFence fence) const {
    return vkAcquireNextImageKHR(api, handle, UINT64_MAX, semaphore, fence, &image_index);
}

Res<Image> Swapchain::newImage(uint32_t index) const {
    if (index >= images.size()) {
        return Er("The index {} is out of swapchain images", index);
    }
    Image image = Image::borrow(api,
                                images[index],
                                image_format,
                                VkExtent3D{image_extent.width, image_extent.height, 1},
                                1,
                                image_layers,
                                VK_SAMPLE_COUNT_1_BIT,
                                VK_IMAGE_TILING_OPTIMAL,
                                image_usage);
    OnName(image, "SwapchainImage" + std::to_string(index));
    return Ok(std::move(image));
}

Res<ImageView> Swapchain::newImageView(uint32_t index) const {
    if (index >= images.size()) {
        return Er("The index {} is out of swapchain imageviews", index);
    }
    return ImageViewState("SwapchainImageView" + std::to_string(index))
        .setImage(images[index])
        .setType(VK_IMAGE_VIEW_TYPE_2D)
        .setFormat(image_format)
        .setAspect(VK_IMAGE_ASPECT_COLOR_BIT)
        .setMipRange(0, 1)
        .setArrayRange(0, image_layers)
        .into(api);
}

Res<Swapchain> Swapchain::from(const CoreApi& api, const SwapchainState& info) {
    const PhysicalDevice& phy_dev = api;
    if ((!phy_dev.queue_families.present.has_value()) || (!phy_dev.queue_families.graphics.has_value())) {
        return Er("Swapchain requires valid present and graphics queue family index");
    }

    VkSurfaceCapabilitiesKHR surface_capalibities{};
    Vector<VkSurfaceFormatKHR> surface_formats{};
    Vector<VkPresentModeKHR> present_modes{};
    OnRet(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phy_dev, info.surface, &surface_capalibities),
          "Failed to get surface capabilities of physical device");
    OnRet(enumerate(surface_formats, vkGetPhysicalDeviceSurfaceFormatsKHR, phy_dev, info.surface),
          "Failed to get list of surface formats");
    OnRet(enumerate(present_modes, vkGetPhysicalDeviceSurfacePresentModesKHR, phy_dev, info.surface),
          "Failed to get list of present modes");
    VkSurfaceFormatKHR surface_format = info.chooseSurfaceFormat(surface_formats);
    VkPresentModeKHR present_mode = info.choosePresentMode(present_modes);
    VkExtent2D image_extent = info.chooseExtent(surface_capalibities);

    // Specify the number of swapchain images
    uint32_t image_count = surface_capalibities.minImageCount + 1;
    if (surface_capalibities.maxImageCount > 0 && image_count > surface_capalibities.maxImageCount) {
        image_count = surface_capalibities.maxImageCount;
    }

    // Create swapchain
    auto swapchain_ci = Itor::SwapchainCreateInfoKHR();
    swapchain_ci.surface = info.surface;
    swapchain_ci.minImageCount = image_count;
    swapchain_ci.imageFormat = surface_format.format;
    swapchain_ci.imageColorSpace = surface_format.colorSpace;
    swapchain_ci.imageExtent = image_extent;
    swapchain_ci.imageArrayLayers = info.image_layers;
    swapchain_ci.imageUsage = info.image_usage;
    swapchain_ci.preTransform = surface_capalibities.currentTransform;
    swapchain_ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_ci.presentMode = present_mode;
    swapchain_ci.clipped = VK_TRUE;
    swapchain_ci.oldSwapchain = info.old;
    uint32_t queue_family_indices[] = {
        phy_dev.queue_families.present.value(),
        phy_dev.queue_families.graphics.value(),
    };
    if (phy_dev.queue_families.graphics != phy_dev.queue_families.present) {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_ci.queueFamilyIndexCount = 2;
        swapchain_ci.pQueueFamilyIndices = queue_family_indices;
    } else {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchain_ci.queueFamilyIndexCount = 0;
        swapchain_ci.pQueueFamilyIndices = nullptr;
    }

    Swapchain swapchain(api, std::move(info.surface));
    OnRet(vkCreateSwapchainKHR(api, &swapchain_ci, nullptr, swapchain), "Failed to create swapchain");
    if (info.old) {
        vkDestroySwapchainKHR(api, info.old, nullptr);
    }
    OnName(swapchain, info.__name);
    swapchain.image_count = image_count;
    swapchain.image_format = surface_format.format;
    swapchain.image_extent = image_extent;
    swapchain.image_layers = info.image_layers;
    swapchain.image_usage = info.image_usage;
    if (info.__verbose) {
        std::string str("Swapchain is created {\n");
        str += vktFmt("\tColor format(VkFormat): {}\n", VkStr(VkFormat, surface_format.format));
        str += vktFmt("\tImage extent: {}x{}\n", image_extent.width, image_extent.height);
        str += vktFmt("\tImage count: {}\n", image_count);
        str += "}";
        vktOut("{}", str);
    }

    // Retrieve handles of swapchain images
    OnRet(enumerate(swapchain.images, vkGetSwapchainImagesKHR, api, swapchain), "Failed get images from swapchain");
    OnCheck(u32(swapchain.images.size()) == swapchain.image_count, "Get wrong image count from swapchain");

    return Ok(std::move(swapchain));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
