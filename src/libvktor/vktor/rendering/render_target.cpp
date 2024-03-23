#include "render_target.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

using Self = RenderTarget::Self;

RenderTarget::RenderTarget(Texture&& _texture) : texture(std::move(_texture)) {
    layouts.initial = texture.getImage().layout;
    layouts.final = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

RenderTarget::RenderTarget(RenderTarget&& rhs) : RenderTarget(std::move(rhs.texture)) {
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

Res<RenderTarget> RenderTarget::from(const core::Swapchain& swapchain, uint32_t index) {
    auto image = swapchain.createImage(index);
    OnErr(image);
    auto imageview = swapchain.createImageView(index);
    OnErr(imageview);
    RenderTarget rt(Texture(image.unwrap(), imageview.unwrap()));
    rt.set(AttachmentOps::color());
    rt.set(AttachmentLayouts::present());
    rt.set({0.0f, 0.0f, 0.0f, 1.0f});
    return Ok(std::move(rt));
}

RenderTargetTable::RenderTargetTable(RenderTargetTable&& rhs) {
    extent = rhs.extent;
    targets = std::move(rhs.targets);
};

Vector<VkImageView> RenderTargetTable::getImageViews() const {
    Vector<VkImageView> views{};
    for (const auto& rt : targets) {
        views.push_back(rt.getImageView());
    }
    return std::move(views);
}

Res<RenderTargetTable> RenderTargetTable::from(Vector<RenderTarget>&& targets) {
    if (targets.empty()) {
        return Er("There should be at least one RenderTarget for RenderTargetTable");
    }

    RenderTargetTable rtt;

    static const auto getExtent = [](const RenderTarget& rt) {
        const VkExtent3D e = rt.getImage().extent;
        const uint32_t m = rt.getImageView().subresource_range.baseMipLevel;
        return VkExtent2D{e.width >> m, e.height >> m};
    };

    if (targets.size() == 1) {
        rtt.extent = getExtent(targets[0]);
    } else {
        Vector<VkExtent2D> extents{};
        for (const auto& rt : targets) {
            extents.push_back(getExtent(rt));
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

Res<RenderTargetTable> RenderTargetTable::from(std::initializer_list<MovedRenderTarget> moved_targets) {
    Vector<RenderTarget> rts;
    for (auto item = moved_targets.begin(); item != moved_targets.end(); ++item) {
        // The `item` is const pointer. So move RenderTarget with pointer-to-pointer.
        rts.push_back(std::move(**item));
    }
    return RenderTargetTable::from(std::move(rts));
}

NAMESPACE_END(vkt)
