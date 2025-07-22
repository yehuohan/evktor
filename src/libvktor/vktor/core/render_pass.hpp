#pragma once
#include "__core.hpp"
#include "swapchain.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct RenderPass;

struct AttachmentOps {
    VkAttachmentLoadOp load = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    VkAttachmentStoreOp store = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    static AttachmentOps ignore() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE};
    };
    static AttachmentOps input() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_DONT_CARE};
    };
    static AttachmentOps color() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE};
    };
    static AttachmentOps depth() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE};
    };
    static AttachmentOps stencil() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE};
    };
};

struct AttachmentLayouts {
    VkImageLayout initial = VK_IMAGE_LAYOUT_UNDEFINED;
    VkImageLayout final = VK_IMAGE_LAYOUT_UNDEFINED;

    static AttachmentLayouts input() {
        return AttachmentLayouts{VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
    }
    static AttachmentLayouts color() {
        return AttachmentLayouts{VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    }
    static AttachmentLayouts present() {
        return AttachmentLayouts{VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR};
    }
    static AttachmentLayouts depthstencil() {
        return AttachmentLayouts{VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    }
};

struct RenderSubpassInfo {
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

class RenderPassState : public CoreStater<RenderPassState> {
    friend struct RenderPass;

private:
    /** All attachment description for all subpasses of render pass */
    Vector<VkAttachmentDescription> attm_descs{};
    Vector<RenderSubpassInfo> subpasses{};

public:
    explicit RenderPassState(String&& name = "RenderPass") : CoreStater(std::move(name)) {}

    Self addAttachment(VkFormat format,
                       VkSampleCountFlagBits samples,
                       AttachmentOps ops,
                       AttachmentOps stencil_ops,
                       AttachmentLayouts layouts);
    inline Self addInputAttachment(VkFormat format, VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT) {
        return addAttachment(format, samples, AttachmentOps::input(), AttachmentOps::ignore(), AttachmentLayouts::input());
    }
    inline Self addColorAttachment(VkFormat format, VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT) {
        return addAttachment(format, samples, AttachmentOps::color(), AttachmentOps::ignore(), AttachmentLayouts::color());
    }
    inline Self addPresentAttachment(VkFormat format, VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT) {
        return addAttachment(format, samples, AttachmentOps::color(), AttachmentOps::ignore(), AttachmentLayouts::present());
    }
    inline Self addDepthStencilAttachment(VkFormat format, VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT) {
        return addAttachment(format,
                             samples,
                             AttachmentOps::depth(),
                             AttachmentOps::stencil(),
                             AttachmentLayouts::depthstencil());
    }
    Self addSubpass(Vector<uint32_t>&& input, Vector<uint32_t>&& color, uint32_t depthstencil = VK_ATTACHMENT_UNUSED);
    Self addSubpass(const RenderSubpassInfo& subpass);

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
struct hash<vkt::core::RenderPass> {
    inline size_t operator()(const vkt::core::RenderPass& render_pass) const {
        return hash<VkRenderPass>{}(render_pass);
    }
};

NAMESPACE_END(std)
