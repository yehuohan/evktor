#include "render_target.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderTarget::RenderTarget(RenderTarget&& rhs) : RenderTarget(rhs.api) {
    extent = rhs.extent;
    imageviews = std::move(rhs.imageviews);
};

Vector<VkImageView> RenderTarget::getImageViews() const {
    Vector<VkImageView> views{};
    for (const auto& view : imageviews) {
        views.push_back(view);
    }
    return std::move(views);
}

Res<RenderTarget> RenderTarget::build(const BaseApi& api, Vector<ImageView>&& imageviews) {
    if (imageviews.empty()) {
        return Er("There should be at least one ImageView for RenderTarget");
    }

    RenderTarget rt(api);

    static const auto getExtent = [](const ImageView& view) {
        const VkExtent3D e = view.image.extent;
        const uint32_t m = view.subresource_range.baseMipLevel;
        return VkExtent2D{e.width >> m, e.height >> m};
    };

    if (imageviews.size() == 1) {
        rt.extent = getExtent(imageviews[0]);
    } else {
        Vector<VkExtent2D> extents{};
        for (const auto& view : imageviews) {
            extents.push_back(getExtent(view));
        }
        rt.extent = extents[0];
        for (const auto& e : extents) {
            if (!(rt.extent.width == e.width && rt.extent.height == e.height)) {
                return Er("ImageView extent should be same for RenderTarget");
            }
        }
    }

    rt.imageviews = std::move(imageviews);
    return Ok(std::move(rt));
}

NAMESPACE_END(vkt)
