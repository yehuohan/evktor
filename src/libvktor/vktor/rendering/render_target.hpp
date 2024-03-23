#pragma once
#include "vktor/base/texture.hpp"
#include "vktor/core/render_pass.hpp"
#include "vktor/core/swapchain.hpp"

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
    Texture texture;
    core::AttachmentOps ops = core::AttachmentOps::ignore();
    core::AttachmentOps stencil_ops = core::AttachmentOps::ignore();
    core::AttachmentLayouts layouts = core::AttachmentLayouts::color();
    VkClearValue clear{};

public:
    using Self = RenderTarget&;

    explicit RenderTarget(Texture&& texture);
    RenderTarget(RenderTarget&&);

    inline const core::Image& getImage() const {
        return texture.getImage();
    }
    inline const core::ImageView& getImageView() const {
        return texture.getImageView();
    }
    Self set(const core::AttachmentOps& ops);
    Self set(const core::AttachmentOps& ops, const core::AttachmentOps& stencil_ops);
    Self set(const core::AttachmentLayouts& layouts);
    Self set(const VkImageLayout final_layout);
    Self set(const VkClearColorValue& color);
    Self set(const VkClearDepthStencilValue& depthstencil);

    static Res<RenderTarget> from(const core::Swapchain& swapchain, uint32_t index);
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

    static Res<RenderTargetTable> from(Vector<RenderTarget>&& targets);
    static Res<RenderTargetTable> from(std::initializer_list<MovedRenderTarget> moved_targets);
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

/**
 * @brief RenderTarget hash functor
 *
 * Hashing RenderTarget will NOT include imageview's Vulkan handle
 * (This is mainly for core::RenderPass)
 */
template <>
struct hash<vkt::RenderTarget> {
    size_t operator()(const vkt::RenderTarget& render_target) const {
        size_t res = 0;
        auto& image = render_target.getImage();
        vkt::hashCombine(res, image.format);
        vkt::hashCombine(res, image.samples);
        vkt::hashCombine(res, image.usage);
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
 * (This is mainly for core::Framebuffer)
 */
template <>
struct hash<vkt::RenderTargetTable> {
    size_t operator()(const vkt::RenderTargetTable& render_target_table) const {
        size_t res = 0;
        for (const auto& rt : render_target_table.getTargets()) {
            vkt::hashCombine(res, rt.getImage());
            vkt::hashCombine(res, rt.getImageView());
        }
        return res;
    }
};

NAMESPACE_END(std)
