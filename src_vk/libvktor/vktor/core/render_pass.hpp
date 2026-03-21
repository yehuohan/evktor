#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct RenderPass;

struct AttachmentOps {
    VkAttachmentLoadOp load = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    VkAttachmentStoreOp store = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    static const AttachmentOps Ignore;
    static const AttachmentOps LoadOnly;
    static const AttachmentOps OnlyStore;
    static const AttachmentOps LoadStore;
    static const AttachmentOps ClearStore;
};

struct AttachmentLayouts {
    VkImageLayout initial = VK_IMAGE_LAYOUT_UNDEFINED;
    VkImageLayout final = VK_IMAGE_LAYOUT_UNDEFINED;

    static const AttachmentLayouts Input;
    static const AttachmentLayouts Color;
    static const AttachmentLayouts Present;
    static const AttachmentLayouts DepthStencil;
};

struct RenderSubpassState {
    /** Input attachment indices for `attm_descs` (layout(input_attachment_index) in)
     *
     * Example:
     * ```
     * inputs[0] = x: attm_descs[x] bind to input_attachment_index = 0
     * inputs[1] = y: attm_descs[y] bind to input_attachment_index = 1
     * ```
     */
    Vector<uint32_t> inputs{};
    /** Color attachment indices for `attm_descs` (layout(location) out)
     *
     * Example:
     * ```
     * colors[0] = x: attm_descs[x] bind to location = 0
     * colors[1] = y: attm_descs[y] bind to location = 1
     * ```
     */
    Vector<uint32_t> colors{};
    // Vector<uint32_t> resolves{};
    /** Depth-stencil attachment index for `attm_descs` (There is only one depth-stencil at most)
     *
     * Example:
     * ```
     * depthstencil = x: attm_descs[x] is for depth test
     * ```
     */
    uint32_t depthstencil = VK_ATTACHMENT_UNUSED;
};

class RenderPassState : public CoreState<RenderPassState> {
    friend struct RenderPass;

private:
    /** All attachment description for all subpasses of render pass */
    Vector<VkAttachmentDescription> attm_descs{};
    Vector<RenderSubpassState> subpasses{};

public:
    explicit RenderPassState(String&& name = "RenderPass") : CoreState(std::move(name)) {}

    Self addAttachment(VkFormat format,
                       VkSampleCountFlagBits samples,
                       AttachmentOps ops,
                       AttachmentOps stencil_ops,
                       AttachmentLayouts layouts);
    inline Self addInputAttachment(VkFormat format,
                                   VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                                   AttachmentOps ops = AttachmentOps::LoadOnly,
                                   AttachmentLayouts layouts = AttachmentLayouts::Input) {
        return addAttachment(format, samples, ops, AttachmentOps::Ignore, layouts);
    }
    inline Self addColorAttachment(VkFormat format,
                                   VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                                   AttachmentOps ops = AttachmentOps::ClearStore,
                                   AttachmentLayouts layouts = AttachmentLayouts::Color) {
        return addAttachment(format, samples, ops, AttachmentOps::Ignore, layouts);
    }
    inline Self addPresentAttachment(VkFormat format,
                                     VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                                     AttachmentOps ops = AttachmentOps::ClearStore,
                                     AttachmentLayouts layouts = AttachmentLayouts::Present) {
        return addAttachment(format, samples, ops, AttachmentOps::Ignore, layouts);
    }
    inline Self addDepthStencilAttachment(VkFormat format,
                                          VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                                          AttachmentOps ops = AttachmentOps::ClearStore,
                                          AttachmentOps stencil_ops = AttachmentOps::ClearStore,
                                          AttachmentLayouts layouts = AttachmentLayouts::DepthStencil) {
        return addAttachment(format, samples, ops, stencil_ops, layouts);
    }
    Self addSubpass(const Vector<uint32_t>& colors, uint32_t depthstencil = VK_ATTACHMENT_UNUSED);
    Self addSubpass(const Vector<uint32_t>& inputs,
                    const Vector<uint32_t>& colors,
                    uint32_t depthstencil = VK_ATTACHMENT_UNUSED);
    Self addSubpass(const RenderSubpassState& subpass);

    Res<RenderPass> into(const CoreApi& api) const;
};

struct RenderPass : public CoreResource<VkRenderPass, VK_OBJECT_TYPE_RENDER_PASS> {
protected:
    explicit RenderPass(const CoreApi& api) : CoreResource(api) {}

public:
    RenderPass(RenderPass&&);
    ~RenderPass();

    static Res<RenderPass> from(const CoreApi& api, const RenderPassState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::RenderSubpassState> {
    size_t operator()(const vkt::core::RenderSubpassState& state) const {
        size_t res = 0;
        for (const auto a : state.inputs) {
            hashCombine(res, a);
        }
        for (const auto a : state.colors) {
            hashCombine(res, a);
        }
        hashCombine(res, state.depthstencil);
        return res;
    }
};

template <>
struct hash<Vector<CRef<vkt::core::RenderSubpassState>>> {
    size_t operator()(const Vector<CRef<vkt::core::RenderSubpassState>>& states) const {
        size_t res = 0;
        for (const auto& s : states) {
            hashCombine(res, s.get());
        }
        return res;
    }
};

template <>
struct hash<vkt::core::RenderPass> {
    inline size_t operator()(const vkt::core::RenderPass& render_pass) const {
        return hash<VkRenderPass>{}(render_pass);
    }
};

NAMESPACE_END(std)
