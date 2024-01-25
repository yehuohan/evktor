#include "render_target.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

using Self = RenderTarget::Self;

RenderTarget::RenderTarget(ImageView&& _imageview)
    : imageview(std::move(_imageview))
    , format(_imageview.image.format)
    , samples(_imageview.image.samples)
    , usage(_imageview.image.usage) {
    layouts.initial = _imageview.image.layout;
    layouts.final = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

RenderTarget::RenderTarget(RenderTarget&& rhs) : RenderTarget(std::move(rhs.imageview)) {
    ops = rhs.ops;
    stencil_ops = rhs.stencil_ops;
    layouts = rhs.layouts;
    clear = rhs.clear;
}

Self RenderTarget::set(const AttachmentOps& _ops) {
    ops = _ops;
    return *this;
}

Self RenderTarget::set(const AttachmentOps& ops, const AttachmentOps& _stencil_ops) {
    stencil_ops = _stencil_ops;
    return *this;
}

Self RenderTarget::set(const AttachmentLayouts& _layouts) {
    layouts = _layouts;
    return *this;
}

Self RenderTarget::set(const VkImageLayout final_layout) {
    layouts.final = final_layout;
    return *this;
}

Self RenderTarget::set(const VkClearColorValue& color) {
    clear.color = color;
    return *this;
}

Self RenderTarget::set(const VkClearDepthStencilValue& depthstencil) {
    clear.depthStencil = depthstencil;
    return *this;
}

RenderTargetTable::RenderTargetTable(RenderTargetTable&& rhs) {
    extent = rhs.extent;
    targets = std::move(rhs.targets);
};

Vector<VkImageView> RenderTargetTable::getImageViews() const {
    Vector<VkImageView> views{};
    for (const auto& rt : targets) {
        views.push_back(rt.imageview);
    }
    return std::move(views);
}

Res<RenderTargetTable> RenderTargetTable::build(Vector<RenderTarget>&& targets) {
    if (targets.empty()) {
        return Er("There should be at least one RenderTarget for RenderTargetTable");
    }

    RenderTargetTable rtt;

    static const auto getExtent = [](const ImageView& view) {
        const VkExtent3D e = view.image.extent;
        const uint32_t m = view.subresource_range.baseMipLevel;
        return VkExtent2D{e.width >> m, e.height >> m};
    };

    if (targets.size() == 1) {
        rtt.extent = getExtent(targets[0].imageview);
    } else {
        Vector<VkExtent2D> extents{};
        for (const auto& rt : targets) {
            extents.push_back(getExtent(rt.imageview));
        }
        rtt.extent = extents[0];
        for (const auto& e : extents) {
            if (!(rtt.extent.width == e.width && rtt.extent.height == e.height)) {
                return Er("RenderTarget's extent should be same for RenderTargetTable");
            }
        }
    }

    rtt.targets = std::move(targets);
    return Ok(std::move(rtt));
}

Res<RenderTargetTable> RenderTargetTable::build(std::initializer_list<MovedRenderTarget> moved_targets) {
    Vector<RenderTarget> rts;
    for (auto item = moved_targets.begin(); item != moved_targets.end(); ++item) {
        // The `item` is const pointer. So move RenderTarget with pointer-to-pointer.
        rts.push_back(std::move(**item));
    }
    return RenderTargetTable::build(std::move(rts));
}

NAMESPACE_END(vkt)
