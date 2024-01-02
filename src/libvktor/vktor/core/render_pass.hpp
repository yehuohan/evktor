#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include <cassert>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct RenderPass : public BuiltResource<VkRenderPass, VK_OBJECT_TYPE_RENDER_PASS, Device> {
    RenderPass(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    RenderPass(RenderPass&&);
    ~RenderPass();
};

struct AttachmentOps {
    VkAttachmentLoadOp load = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    VkAttachmentStoreOp store = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    static AttachmentOps input() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_DONT_CARE};
    };
    static AttachmentOps color() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE};
    };
    static AttachmentOps depth() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE};
    };
    static AttachmentOps stencil() {
        return AttachmentOps{VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE};
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
    /** Input attachment indices for `attm_refs` (layout(location) in) */
    Vector<uint32_t> inputs{};
    /** Color attachment indices for `attm_refs` (layout(location) out) */
    Vector<uint32_t> colors{};
    /** Depth stencil attachment index for `attm_refs` */
    uint32_t depthstencil = VK_ATTACHMENT_UNUSED;
};

struct RenderPassInfo : public BuilderInfo {
    /** All attachment description for all subpasses of render pass */
    Vector<VkAttachmentDescription> attm_descs{};
    /** Corresponding attachment indices for `attm_descs` */
    Vector<VkAttachmentReference> attm_refs{};
    Vector<RenderSubpassInfo> subpasses{};
};

class RenderPassBuilder : public Builder<RenderPassBuilder, RenderPass, RenderPassInfo> {
private:
    const Device& device;

public:
    explicit RenderPassBuilder(const Device& device, Name&& name = "RenderPass") : Builder(std::move(name)), device(device) {}
    virtual Built build() override;

    Self addInputAttachment(VkFormat format,
                            VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                            AttachmentOps ops = AttachmentOps::input(),
                            AttachmentLayouts layouts = AttachmentLayouts::input());
    Self addColorAttachment(VkFormat format,
                            VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                            AttachmentOps ops = AttachmentOps::color(),
                            AttachmentLayouts layouts = AttachmentLayouts::color());
    inline Self addPresentAttachment(VkFormat format,
                                     VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                                     AttachmentOps ops = AttachmentOps::color(),
                                     AttachmentLayouts layouts = AttachmentLayouts::present()) {
        return addColorAttachment(format, samples, ops, layouts);
    }
    Self addDepthStencilAttachment(VkFormat format,
                                   VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT,
                                   AttachmentOps depth_ops = AttachmentOps::depth(),
                                   AttachmentOps stencil_ops = AttachmentOps::stencil(),
                                   AttachmentLayouts layouts = AttachmentLayouts::depthstencil());
    Self addSubpass(Vector<uint32_t>&& input, Vector<uint32_t>&& color, uint32_t depthstencil = VK_ATTACHMENT_UNUSED);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
