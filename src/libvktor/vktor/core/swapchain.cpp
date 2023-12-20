#include "swapchain.hpp"
#include "utils.hpp"
#include <cassert>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SwapchainBuilder::Self;

Swapchain::Swapchain(Swapchain&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    images = std::move(rhs.images);
    imageviews = std::move(rhs.imageviews);
    count = rhs.count;
    format = rhs.format;
    extent = rhs.extent;
}

Swapchain::~Swapchain() {
    for (auto view : imageviews) {
        if (view) {
            vkDestroyImageView(device, view, nullptr);
        }
    }
    if (handle) {
        vkDestroySwapchainKHR(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
    images.clear(); // The images will be destroyed along with swapchain's destruction
    imageviews.clear();
}

Self SwapchainBuilder::addDesiredFormat(const VkSurfaceFormatKHR& format) {
    info.desired_formats.push_back(format);
    return *this;
}

Self SwapchainBuilder::addDesiredPresentMode(VkPresentModeKHR mode) {
    info.desired_present_modes.push_back(mode);
    return *this;
}

Self SwapchainBuilder::setDesiredExtent(const VkExtent2D& extent2d) {
    info.desired_extent = extent2d;
    return *this;
}

SwapchainBuilder::Built SwapchainBuilder::build() {
    if ((!device.physical_device.indices.present.has_value()) || (!device.physical_device.indices.graphics.has_value())) {
        return Er("SwapchainBuilder requires valid present and graphics queue family index");
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
    // Specify the amount of layers each image consists of.
    swapchain_ci.imageArrayLayers = 1;
    // Specify what king of operations that the image in the swapchain used for
    swapchain_ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_ci.preTransform = surface_capalibities.currentTransform;
    swapchain_ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_ci.presentMode = present_mode;
    swapchain_ci.clipped = VK_TRUE;
    swapchain_ci.oldSwapchain = VK_NULL_HANDLE;
    uint32_t queues_arr[] = {
        device.physical_device.indices.present.value(),
        device.physical_device.indices.graphics.value(),
    };
    if (device.physical_device.indices.graphics != device.physical_device.indices.present) {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_ci.queueFamilyIndexCount = 2;
        swapchain_ci.pQueueFamilyIndices = queues_arr;
    } else {
        swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchain_ci.queueFamilyIndexCount = 0;
        swapchain_ci.pQueueFamilyIndices = nullptr;
    }

    Swapchain swapchain(device, std::move(info.__name));
    OnRet(vkCreateSwapchainKHR(device, &swapchain_ci, nullptr, swapchain), "Failed to create swapchain");
    OnName(swapchain);
    swapchain.format = surface_format.format;
    swapchain.extent = image_extent;
    swapchain.count = image_count;
    if (info.__verbose) {
        std::string str("Swapchain is created {\n");
        str += vktFmt("\tColor format(VkFormat): {}\n", (int)surface_format.format);
        str += vktFmt("\tImage extent: {}x{}\n", image_extent.width, image_extent.height);
        str += vktFmt("\tImage count: {}\n", image_count);
        str += "}";
        vktPrint("{}", str.c_str());
    }

    // Retrieve handles of swapchain images
    OnRet(enumerate(swapchain.images, vkGetSwapchainImagesKHR, device, swapchain), "Failed get images from swapchain");
    assert(u32(swapchain.images.size()) == swapchain.count);

    // Create image views
    swapchain.imageviews.resize(swapchain.images.size());
    for (int k = 0; k < swapchain.imageviews.size(); k++) {
        auto imageview_ci = Itor::ImageViewCreateInfo(swapchain.images[k], VK_IMAGE_VIEW_TYPE_2D, swapchain.format);
        // Swizzle the color channels around with components(映射颜色通道)
        imageview_ci.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageview_ci.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageview_ci.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageview_ci.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        // Describe what's the image's purpose is and which part of the image should be accessed.
        imageview_ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageview_ci.subresourceRange.baseMipLevel = 0;
        imageview_ci.subresourceRange.levelCount = 1;
        imageview_ci.subresourceRange.baseArrayLayer = 0;
        imageview_ci.subresourceRange.layerCount = 1;

        OnRet(vkCreateImageView(device, &imageview_ci, nullptr, &swapchain.imageviews[k]),
              "Failed to create imageview for swapchain image[{}]",
              k);
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
        // `currentExtent` == UINT32_MAX means that match window's resolution
        // within minImageExtent and maxImageExtent
        VkExtent2D extent2d = info.desired_extent;
        extent2d.width = std::max(capalibities.minImageExtent.width,
                                  std::min(capalibities.maxImageExtent.width, extent2d.width));
        extent2d.height = std::max(capalibities.minImageExtent.height,
                                   std::min(capalibities.maxImageExtent.height, extent2d.height));
        return extent2d;
    }
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
