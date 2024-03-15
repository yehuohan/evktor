#include "render_pass.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = RenderPassState::Self;

Self RenderPassState::addAttachment(VkFormat format,
                                    VkSampleCountFlagBits samples,
                                    AttachmentOps ops,
                                    AttachmentOps stencil_ops,
                                    AttachmentLayouts layouts) {
    VkAttachmentDescription desc{};
    desc.format = format;
    desc.samples = samples;
    desc.loadOp = ops.load;
    desc.storeOp = ops.store;
    desc.stencilLoadOp = stencil_ops.load;
    desc.stencilStoreOp = stencil_ops.store;
    desc.initialLayout = layouts.initial;
    desc.finalLayout = layouts.final;
    attm_descs.push_back(desc);
    return *this;
}

Self RenderPassState::addSubpass(Vector<uint32_t>&& input, Vector<uint32_t>&& color, uint32_t depthstencil) {
    RenderSubpassInfo subpass{};
    subpass.inputs = std::move(input);
    subpass.colors = std::move(color);
    subpass.depthstencil = depthstencil;
    subpasses.push_back(std::move(subpass));
    return *this;
}

Self RenderPassState::addSubpass(const RenderSubpassInfo& subpass) {
    subpasses.push_back(subpass);
    return *this;
}

Res<RenderPass> RenderPassState::into(const Device& device) const {
    return RenderPass::from(device, *this);
}

RenderPass::RenderPass(RenderPass&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

RenderPass::~RenderPass() {
    if (handle) {
        vkDestroyRenderPass(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<RenderPass> RenderPass::from(const Device& device, const RenderPassState& info) {
    uint32_t subpass_count = u32(info.subpasses.size());
    if (subpass_count == 0) {
        return Er("There must be at least one subpass for render pass");
    }
    Vector<VkSubpassDescription> subpasses(subpass_count);
    Vector<Vector<VkAttachmentReference>> inputs(subpass_count);
    Vector<Vector<VkAttachmentReference>> colors(subpass_count);
    Vector<VkAttachmentReference> depthstencils(subpass_count);
    Vector<VkSubpassDependency> dependencies(subpass_count - 1);

    for (uint32_t k = 0; k < subpass_count; k++) {
        auto& subpass = info.subpasses[k];
        auto& inp = inputs[k];
        auto& clr = colors[k];
        VkAttachmentReference* ds = nullptr;
        // Prepare input attachments
        for (const auto a : subpass.inputs) {
            const auto& desc = info.attm_descs[a];
            VkAttachmentReference ref{};
            ref.attachment = a;
            ref.layout = desc.initialLayout;
            if (ref.layout == VK_IMAGE_LAYOUT_UNDEFINED) {
                ref.layout = isDepthStencilFormat(desc.format) ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
                                                               : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            }
            inp.push_back(ref);
        }
        // Prepare color attachments
        for (const auto a : subpass.colors) {
            const auto& desc = info.attm_descs[a];
            VkAttachmentReference ref{};
            ref.attachment = a;
            ref.layout = desc.initialLayout;
            if (ref.layout == VK_IMAGE_LAYOUT_UNDEFINED) {
                ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            }
            clr.push_back(ref);
        }
        // Prepare depth stencil attachments
        if (VK_ATTACHMENT_UNUSED != subpass.depthstencil) {
            const auto& desc = info.attm_descs[subpass.depthstencil];
            VkAttachmentReference ref{};
            ref.attachment = subpass.depthstencil;
            ref.layout = desc.initialLayout;
            if (ref.layout == VK_IMAGE_LAYOUT_UNDEFINED) {
                ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
            }
            depthstencils[k] = ref;
            ds = &depthstencils[k];
        }

        auto& desc = subpasses[k];
        desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        desc.inputAttachmentCount = u32(inp.size());
        desc.pInputAttachments = inp.data();
        desc.colorAttachmentCount = u32(clr.size());
        desc.pColorAttachments = clr.data();
        desc.pResolveAttachments = nullptr;
        desc.pDepthStencilAttachment = ds;
        desc.preserveAttachmentCount = 0;
        desc.pPreserveAttachments = nullptr;
    }

    for (uint32_t k = 0; k < u32(dependencies.size()); k++) {
        auto& dep = dependencies[k];
        dep.srcSubpass = k;
        dep.dstSubpass = k + 1;
        dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dep.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dep.dstAccessMask = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
        dep.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    }

    auto render_pass_ci = Itor::RenderPassCreateInfo();
    render_pass_ci.attachmentCount = u32(info.attm_descs.size());
    render_pass_ci.pAttachments = info.attm_descs.data();
    render_pass_ci.subpassCount = u32(subpasses.size());
    render_pass_ci.pSubpasses = subpasses.data();
    render_pass_ci.dependencyCount = u32(dependencies.size());
    render_pass_ci.pDependencies = dependencies.data();

    RenderPass render_pass(device);
    OnRet(vkCreateRenderPass(device, &render_pass_ci, nullptr, render_pass), "Failed to create render pass");
    OnName(render_pass, info.__name);

    return Ok(std::move(render_pass));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
