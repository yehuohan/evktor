#pragma once
#include "vktor/base/texture.hpp"
#include "vktor/core/exts/swapchain.hpp"
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
    friend class RenderResource;

protected:
    Texture texture;
    /** The `ops.load/store` is the first/last subpass operator on the `texture` */
    core::AttachmentOps ops = core::AttachmentOps::ignore();
    /** The `stencil_ops.load/store` is the first/last subpass operator on the depth-stencil `texture` */
    core::AttachmentOps stencil_ops = core::AttachmentOps::ignore();
    /** `layouts.initial/final` is `texture` layouts before/after the whole render pass
     *
     * The `texture` layout for subpass is specified by VkAttachmentReference.layout
     */
    core::AttachmentLayouts layouts = core::AttachmentLayouts::color();
    VkClearValue clear{};

public:
    using Self = RenderTarget&;

    /**
     * @brief Construct render target from texture directly
     */
    explicit RenderTarget(Texture&& texture);
    RenderTarget(RenderTarget&&);
    static Res<RenderTarget> from(const core::CoreApi& api, const VkExtent2D& extent, VkFormat format);
    /**
     * @brief Create render target with the swapchain image of Arg<Swapchain>::image_index
     */
    static Res<RenderTarget> from(const core::Arg<core::Swapchain>& swapchain);

    inline const Texture& getTexture() const {
        return texture;
    }
    inline const core::Image& getImage() const {
        return texture.getImage();
    }
    inline const core::ImageView& getImageView() const {
        return texture.getImageView();
    }
    /**
     * @brief Construct rendering attachment from render target
     *
     * Must transit image layout to `layouts.final` manually
     */
    VkRenderingAttachmentInfo getAttachmentInfo(const void* next = nullptr) const;
    Self set(const core::AttachmentOps& ops);
    Self set(const core::AttachmentOps& ops, const core::AttachmentOps& stencil_ops);
    Self set(const core::AttachmentLayouts& layouts);
    Self set(const VkImageLayout final_layout);
    Self set(const VkClearColorValue& color);
    Self set(const VkClearDepthStencilValue& depthstencil);
};

/**
 * @brief All render targets of one render pass and framebuffer
 */
class RenderTargetTable : private NonCopyable {
private:
    Vector<RenderTarget> targets{};
    VkExtent2D extent{};

public:
    explicit RenderTargetTable() {}
    RenderTargetTable(RenderTargetTable&&);
    Res<Ref<RenderTarget>> addTarget(RenderTarget&& target);
    Res<Ref<RenderTarget>> addTarget(Texture&& texture);
    Res<Ref<RenderTarget>> addTarget(const core::CoreApi& api, const VkExtent2D& extent, VkFormat format);
    Res<Ref<RenderTarget>> addTarget(const core::Arg<core::Swapchain>& swapchain);
    Res<Ref<RenderTarget>> operator[](size_t index);

    inline const Vector<RenderTarget>& getTargets() const {
        return targets;
    }
    inline VkExtent2D getExtent() const {
        return extent;
    }
    Vector<VkImageView> getImageViews() const;
    Vector<VkClearValue> getClearValues() const;
    /**
     * @brief Construct rendering attachments from render target table
     *
     * All color attachments will be always placed at the start of vector
     */
    Vector<VkRenderingAttachmentInfo> getAttachmentInfos() const;
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
        hashCombine(res, image.getFormat());
        hashCombine(res, image.getSamples());
        hashCombine(res, image.getUsage());
        hashCombine(res, render_target.ops.load);
        hashCombine(res, render_target.ops.store);
        hashCombine(res, render_target.stencil_ops.load);
        hashCombine(res, render_target.stencil_ops.store);
        hashCombine(res, render_target.layouts.initial);
        hashCombine(res, render_target.layouts.final);
        return res;
    }
};

template <>
struct hash<Vector<vkt::RenderTarget>> {
    size_t operator()(const Vector<vkt::RenderTarget>& render_targets) const {
        size_t res = 0;
        for (const auto& rt : render_targets) {
            hashCombine(res, rt);
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
    size_t operator()(const vkt::RenderTargetTable& rtt) const {
        size_t res = 0;
        for (const auto& rt : rtt.getTargets()) {
            hashCombine(res, rt.getImage());
            hashCombine(res, rt.getImageView());
        }
        return res;
    }
};

NAMESPACE_END(std)
