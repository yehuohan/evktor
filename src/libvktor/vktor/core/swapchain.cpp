#include "swapchain.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cassert>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SwapchainBuilder::Self;

Swapchain::Swapchain(Swapchain&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    images = std::move(rhs.images);
    image_count = rhs.image_count;
    image_format = rhs.image_format;
    image_extent = rhs.image_extent;
    image_layers = rhs.image_layers;
    image_usage = rhs.image_usage;
}

Swapchain::~Swapchain() {
    if (handle) {
        vkDestroySwapchainKHR(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
    images.clear(); // The images will be destroyed along with swapchain's destruction
}

Vector<ImageView> Swapchain::createImageViews() const {
    Vector<ImageView> views{};

    for (uint32_t k = 0; k < images.size(); k++) {
        ImageViewBuilder builder(images[k], "SwapchainImageView" + std::to_string(k));
        auto res = builder.setType(VK_IMAGE_VIEW_TYPE_2D)
                       .setFormat(image_format)
                       .setAspect(VK_IMAGE_ASPECT_COLOR_BIT)
                       .setMipRange(0, 1)
                       .setArrayRange(0, image_layers)
                       .build();
        if (res.isOk()) {
            views.push_back(res.unwrap());
            views.back().setDebugName();
        }
    }

    return std::move(views);
}

Self SwapchainBuilder::addDesiredFormat(const VkSurfaceFormatKHR& format) {
    info.desired_formats.push_back(format);
    return *this;
}

Self SwapchainBuilder::addDesiredPresentMode(VkPresentModeKHR mode) {
    info.desired_present_modes.push_back(mode);
    return *this;
}

Self SwapchainBuilder::setDesiredExtent(const VkExtent2D& extent) {
    info.desired_extent = extent;
    return *this;
}

SwapchainBuilder::Built SwapchainBuilder::build() {
    if ((!device.physical_device.queue_families.present.has_value()) ||
        (!device.physical_device.queue_families.graphics.has_value())) {
        return Er("SwapchainBuilder requires valid present and graphics queue family index");
    }
    if (info.desired_formats.empty()) {
        info.desired_formats.push_back(VkSurfaceFormatKHR{VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR});
    }
    if (info.desired_present_modes.empty()) {
        info.desired_present_modes.push_back(VK_PRESENT_MODE_FIFO_KHR);
    }

    VkSurfaceCapabilitiesKHR surface_capalibities{};
    Vector<VkSurfaceFormatKHR> surface_formats{};
    Vector<VkPresentModeKHR> present_modes{};
    OnRet(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.physical_device, surface, &surface_capalibities),
          "Failed to get surface capabilities of physical device");
    OnRet(enumerate(surface_formats, vkGetPhysicalDeviceSurfaceFormatsKHR, device.physical_device, surface),
          "Failed to get list of surface formats");
    OnRet(enumerate(present_modes, vkGetPhysicalDeviceSurfacePresentModesKHR, device.physical_device, surface),
          "Failed to get list of present modes");
    VkSurfaceFormatKHR surface_format = chooseSurfaceFormat(surface_formats);
    VkPresentModeKHR present_mode = choosePresentMode(present_modes);
    VkExtent2D image_extent = chooseExtent(surface_capalibities);

    // Specify how many images we would like to have in the swap chain
    uint32_t image_count = surface_capalibities.minImageCount + 1;
    if (surface_capalibities.maxImageCount > 0 && image_count > surface_capalibities.maxImageCount) {
        image_count = surface_capalibities.maxImageCount;
    }

    // Create swapchain
    auto swapchain_ci = Itor::SwapchainCreateInfoKHR();
    swapchain_ci.surface = surface;
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
        device.physical_device.queue_families.present.value(),
        device.physical_device.queue_families.graphics.value(),
    };
    if (device.physical_device.queue_families.graphics != device.physical_device.queue_families.present) {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_ci.queueFamilyIndexCount = 2;
        swapchain_ci.pQueueFamilyIndices = queue_family_indices;
    } else {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchain_ci.queueFamilyIndexCount = 0;
        swapchain_ci.pQueueFamilyIndices = nullptr;
    }

    Swapchain swapchain(device, std::move(info.__name));
    OnRet(vkCreateSwapchainKHR(device, &swapchain_ci, nullptr, swapchain), "Failed to create swapchain");
    OnName(swapchain);
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
    Vector<VkImage> images; /**< Handles of images in swapchain */
    OnRet(enumerate(images, vkGetSwapchainImagesKHR, device, swapchain), "Failed get images from swapchain");
    assert(u32(images.size()) == swapchain.image_count);
    for (uint32_t k = 0; k < images.size(); k++) {
        swapchain.images.push_back(Image::build(device,
                                                images[k],
                                                swapchain.image_format,
                                                VkExtent3D{swapchain.image_extent.width, swapchain.image_extent.height, 1},
                                                1,
                                                swapchain.image_layers,
                                                VK_SAMPLE_COUNT_1_BIT,
                                                VK_IMAGE_TILING_OPTIMAL,
                                                swapchain.image_usage,
                                                "SwapchainImage" + std::to_string(k)));
        OnName(swapchain.images.back());
    }

    return Ok(std::move(swapchain));
}

VkSurfaceFormatKHR SwapchainBuilder::chooseSurfaceFormat(const Vector<VkSurfaceFormatKHR>& formats) {
    for (const auto& df : info.desired_formats) {
        for (const auto& sf : formats) {
            if (df.format == sf.format && df.colorSpace == sf.colorSpace) {
                return df;
            }
        }
    }
    return formats[0];
}

VkPresentModeKHR SwapchainBuilder::choosePresentMode(const Vector<VkPresentModeKHR>& modes) {
    for (const auto& dpm : info.desired_present_modes) {
        for (const auto& m : modes) {
            if (dpm == m) {
                return dpm;
            }
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapchainBuilder::chooseExtent(const VkSurfaceCapabilitiesKHR& capalibities) {
    if (capalibities.currentExtent.width != UINT32_MAX) {
        return capalibities.currentExtent;
    } else {
        // `currentExtent` == UINT32_MAX means that match window's resolution within minImageExtent and maxImageExtent
        VkExtent2D extent = info.desired_extent;
        extent.width = std::clamp(extent.width, capalibities.minImageExtent.width, capalibities.maxImageExtent.width);
        extent.height = std::clamp(extent.height, capalibities.minImageExtent.height, capalibities.maxImageExtent.height);
        return extent;
    }
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
