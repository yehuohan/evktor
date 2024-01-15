#pragma once
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"
#include "vktor/core/render_pass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

/**
 * @brief Render target for graphics render pass
 */
class RenderTarget : private NonCopyable {
    friend struct std::hash<vkt::RenderTarget>;
    friend class RenderTargetTable;

protected:
    ImageView imageview;
    AttachmentOps ops = AttachmentOps::ignore();
    AttachmentOps stencil_ops = AttachmentOps::ignore();
    AttachmentLayouts layouts = AttachmentLayouts::color();
    VkClearValue clear{};

public:
    using Self = RenderTarget&;

    RenderTarget(ImageView&& _imageview) : imageview(std::move(_imageview)) {
        layouts.initial = _imageview.image.layout;
        layouts.final = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    RenderTarget(RenderTarget&& rhs);

    Self set(const AttachmentOps& ops);
    Self set(const AttachmentOps& ops, const AttachmentOps& stencil_ops);
    Self set(const AttachmentLayouts& layouts);
    Self set(const VkImageLayout final_layout);
    Self set(const VkClearColorValue& color);
    Self set(const VkClearDepthStencilValue& depthstencil);
};

/**
 * @brief All render targets of one graphics render pass
 */
class RenderTargetTable : private NonCopyable {
    friend struct std::hash<RenderTargetTable>;

private:
    VkExtent2D extent{};
    Vector<RenderTarget> targets{};

private:
    explicit RenderTargetTable() {}

public:
    RenderTargetTable(RenderTargetTable&&);
    inline VkExtent2D getExtent() const {
        return extent;
    }
    Vector<VkImageView> getImageViews() const;

    static Res<RenderTargetTable> build(Vector<RenderTarget>&& targets);
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::RenderTarget> {
    size_t operator()(const vkt::RenderTarget& render_target) const {
        size_t res = 0;
        vkt::hashCombine(res, render_target.imageview);
        vkt::hashCombine(res, render_target.imageview.image);
        return res;
    }
};

template <>
struct hash<vkt::RenderTargetTable> {
    size_t operator()(const vkt::RenderTargetTable& render_target_table) const {
        size_t res = 0;
        for (const auto& rt : render_target_table.targets) {
            vkt::hashCombine(res, rt);
        }
        return res;
    }
};

NAMESPACE_END(std)
