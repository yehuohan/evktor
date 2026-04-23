#include "render_target.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

using Self = RenderTarget::Self;

RenderTarget::RenderTarget(Texture&& _texture) : texture(std::move(_texture)) {
    auto format = texture.getImage().getFormat();
    if (isDepthOnlyFormat(format)) {
        setOps(AttachmentOps::ClearStore);
        setLayouts(AttachmentLayouts::DepthStencil);
        setClearValue(VkClearDepthStencilValue{0.0, 0}); // Clear with 0.0 for reversed-z
    } else if (isDepthStencilFormat(format)) {
        setOps(AttachmentOps::ClearStore, AttachmentOps::ClearStore);
        setLayouts(AttachmentLayouts::DepthStencil);
        setClearValue(VkClearDepthStencilValue{0.0, 0}); // Clear with 0.0 for reversed-z
    } else {
        setOps(AttachmentOps::ClearStore);
        setLayouts(AttachmentLayouts::Color);
        setClearValue(VkClearColorValue{
            {0.0f, 0.0f, 0.0f, 1.0f}
        });
    }
}

RenderTarget::RenderTarget(RenderTarget&& rhs) : RenderTarget(std::move(rhs.texture)) {
    ops = rhs.ops;
    stencil_ops = rhs.stencil_ops;
    layouts = rhs.layouts;
    clear = rhs.clear;
}

Res<RenderTarget> RenderTarget::from(const CoreApi& api, const VkExtent2D& extent, VkFormat format) {
    bool ds = isDepthStencilFormat(format);
    OnUnwrap(image,
             ImageState(ds ? "RTDepth" : "RTColor")
                 .setFormat(format)
                 .setExtent(extent)
                 .setUsage(ds ? VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT : VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
                 .into(api));
    OnUnwrap(imageview, ImageViewState(ds ? "RTDepthView" : "RTColorView").setFromImage(image).into(api));
    return Ok(RenderTarget(Texture(std::move(image), std::move(imageview))));
}

Res<RenderTarget> RenderTarget::from(const Arg<Swapchain>& swapchain) {
    OnErr(image, swapchain.a.newImage(swapchain.image_index));
    OnErr(imageview, swapchain.a.newImageView(swapchain.image_index));
    RenderTarget rt(Texture(image.unwrap(), imageview.unwrap()));
    rt.setOps(AttachmentOps::ClearStore);
    rt.setLayouts(AttachmentLayouts::Present);
    rt.setClearValue(VkClearColorValue{
        {0.0f, 0.0f, 0.0f, 1.0f}
    });
    return Ok(std::move(rt));
}

VkRenderingAttachmentInfo RenderTarget::getAttachmentInfo(const void* next) const {
    auto info = Itor::RenderingAttachmentInfo(next);
    info.imageView = texture.getImageView();
    info.imageLayout = layouts.final;
    // info.resolveMode;
    // info.resolveImageView;
    // info.resolveImageLayout;
    info.loadOp = ops.load;
    info.storeOp = ops.store;
    info.clearValue = clear;
    return info;
}

Self RenderTarget::setOps(const AttachmentOps& _ops) {
    ops = _ops;
    return *this;
}

Self RenderTarget::setOps(const AttachmentOps& _ops, const AttachmentOps& _stencil_ops) {
    ops = _ops;
    stencil_ops = _stencil_ops;
    return *this;
}

Self RenderTarget::setLayouts(const AttachmentLayouts& _layouts) {
    layouts = _layouts;
    return *this;
}

Self RenderTarget::nextLayout(const VkImageLayout final_layout) {
    layouts.initial = layouts.final;
    layouts.final = final_layout;
    return *this;
}

Self RenderTarget::setClearValue(const VkClearColorValue& color) {
    clear.color = color;
    return *this;
}

Self RenderTarget::setClearValue(const VkClearDepthStencilValue& depthstencil) {
    clear.depthStencil = depthstencil;
    return *this;
}

RenderTargetTable::RenderTargetTable(RenderTargetTable&& rhs) {
    extent = rhs.extent;
    targets = std::move(rhs.targets);
};

RenderTargetTable& RenderTargetTable::operator=(RenderTargetTable&& rhs) {
    if (this != &rhs) {
        extent = rhs.extent;
        targets = std::move(rhs.targets);
    }
    return *this;
}

Res<Ref<RenderTarget>> RenderTargetTable::addTarget(RenderTarget&& target) {
    static const auto getExtent = [](const RenderTarget& rt) {
        const VkExtent3D e = rt.getImage().getExtent();
        const uint32_t m = rt.getImageView().getSubresourceRange().baseMipLevel;
        return VkExtent2D{e.width >> m, e.height >> m};
    };

    if (targets.empty()) {
        extent = getExtent(target);
    } else {
        auto e = getExtent(target);
        if ((e.width != extent.width || e.height != extent.height)) {
            return Er("Can't add a RenderTarget with different extent : {}x{}, {}x{}",
                      e.width,
                      e.height,
                      extent.width,
                      extent.height);
        }
    }

    targets.push_back(std::move(target));
    return Ok(newRef(targets.back()));
}

Res<Ref<RenderTarget>> RenderTargetTable::addTarget(Texture&& texture) {
    return addTarget(RenderTarget(std::move(texture)));
}

Res<Ref<RenderTarget>> RenderTargetTable::addTarget(const CoreApi& api, const VkExtent2D& extent, VkFormat format) {
    OnErr(rt, RenderTarget::from(api, extent, format));
    return addTarget(rt.unwrap());
}

Res<Ref<RenderTarget>> RenderTargetTable::addTarget(const Arg<Swapchain>& swapchain) {
    OnErr(rt, RenderTarget::from(swapchain));
    return addTarget(rt.unwrap());
}

Res<Ref<RenderTarget>> RenderTargetTable::operator[](size_t index) {
    if (index < targets.size()) {
        return Ok(newRef(targets[index]));
    }
    return Er("Access an invalid render target: {}", index);
}

Vector<VkImageView> RenderTargetTable::getImageViews() const {
    Vector<VkImageView> views{};
    for (const auto& rt : targets) {
        views.push_back(rt.getImageView());
    }
    return views;
}

Vector<VkClearValue> RenderTargetTable::getClearValues() const {
    Vector<VkClearValue> clears;
    for (const auto& rt : targets) {
        clears.push_back(rt.clear);
    }
    return clears;
}

Vector<VkRenderingAttachmentInfo> RenderTargetTable::getAttachmentInfos() const {
    Vector<VkRenderingAttachmentInfo> infos{};
    Vector<uint32_t> depthstencil_indices{};
    for (uint32_t k = 0; k < targets.size(); k++) {
        const auto& rt = targets[k];
        const auto format = rt.getImage().getFormat();
        if (isDepthOnlyFormat(format) || isStencilOnlyFormat(format) || isDepthStencilFormat(format)) {
            depthstencil_indices.push_back(k);
        } else {
            infos.push_back(rt.getAttachmentInfo());
        }
    }
    for (const auto& k : depthstencil_indices) {
        infos.push_back(targets[k].getAttachmentInfo());
    }

    return infos;
}

NAMESPACE_END(vkt)
