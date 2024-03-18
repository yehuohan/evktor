#pragma once
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"
#include "vktor/core/render_pass.hpp"

NAMESPACE_BEGIN(vkt)

class RenderTargetTable;

/**
 * @brief Render target for one attachment of render pass and framebuffer
 */
class RenderTarget : private NonCopyable {
    friend struct std::hash<vkt::RenderTarget>;
    friend struct std::hash<vkt::RenderTargetTable>;
    friend class RenderTargetTable;
    friend class RenderPipeline;

protected:
    core::ImageView imageview;
    const VkFormat format;               /**< Alias to imageview.image.format */
    const VkSampleCountFlagBits samples; /**< Alias to imageview.image.samples */
    const VkImageUsageFlags usage;       /**< Alias to imageview.image.usage */

    core::AttachmentOps ops = core::AttachmentOps::ignore();
    core::AttachmentOps stencil_ops = core::AttachmentOps::ignore();
    core::AttachmentLayouts layouts = core::AttachmentLayouts::color();
    VkClearValue clear{};

public:
    using Self = RenderTarget&;

    RenderTarget(core::ImageView&& _imageview);
    RenderTarget(RenderTarget&& rhs);

    Self set(const core::AttachmentOps& ops);
    Self set(const core::AttachmentOps& ops, const core::AttachmentOps& stencil_ops);
    Self set(const core::AttachmentLayouts& layouts);
    Self set(const VkImageLayout final_layout);
    Self set(const VkClearColorValue& color);
    Self set(const VkClearDepthStencilValue& depthstencil);
};

/**
 * @brief Alias RenderTarget* as moved RenderTarget for std::initializer_list
 *
 * std::initializer_list doesn't support std::move(RenderTarget) currently.
 * So move the RenderTarget within std::initializer_list via pointer.
 */
typedef RenderTarget* MovedRenderTarget;

/**
 * @brief All render targets of one render pass and framebuffer
 */
class RenderTargetTable : private NonCopyable {
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
    inline const Vector<RenderTarget>& getTargets() const {
        return targets;
    }
    Vector<VkImageView> getImageViews() const;

    static Res<RenderTargetTable> build(Vector<RenderTarget>&& targets);
    static Res<RenderTargetTable> build(std::initializer_list<MovedRenderTarget> moved_targets);
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

/**
 * @brief RenderTarget hash functor
 *
 * Hashing RenderTarget will NOT include imageview's Vulkan handle
 * (This is mainly for `vkt::core::RenderPass`)
 */
template <>
struct hash<vkt::RenderTarget> {
    size_t operator()(const vkt::RenderTarget& render_target) const {
        size_t res = 0;
        vkt::hashCombine(res, render_target.format);
        vkt::hashCombine(res, render_target.samples);
        vkt::hashCombine(res, render_target.usage);
        vkt::hashCombine(res, render_target.ops.load);
        vkt::hashCombine(res, render_target.ops.store);
        vkt::hashCombine(res, render_target.stencil_ops.load);
        vkt::hashCombine(res, render_target.stencil_ops.store);
        vkt::hashCombine(res, render_target.layouts.initial);
        vkt::hashCombine(res, render_target.layouts.final);
        return res;
    }
};

template <>
struct hash<vkt::Vector<vkt::RenderTarget>> {
    size_t operator()(const vkt::Vector<vkt::RenderTarget>& render_targets) const {
        size_t res = 0;
        for (const auto& rt : render_targets) {
            vkt::hashCombine(res, rt);
        }
        return res;
    }
};

/**
 * @brief RenderTargetTable hash functor
 *
 * Hashing RenderTargetTable will ONLY include imageview's and image's Vulkan handle
 * (This is mainly for `vkt::core::Framebuffer`)
 */
template <>
struct hash<vkt::RenderTargetTable> {
    size_t operator()(const vkt::RenderTargetTable& render_target_table) const {
        size_t res = 0;
        for (const auto& rt : render_target_table.getTargets()) {
            vkt::hashCombine(res, rt.imageview);
            vkt::hashCombine(res, rt.imageview.image);
        }
        return res;
    }
};

NAMESPACE_END(std)
