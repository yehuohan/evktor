#include "render_pass.hpp"
#include "image.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = RenderPassBuilder::Self;

RenderPass::RenderPass(RenderPass&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

RenderPass::~RenderPass() {
    if (handle) {
        vkDestroyRenderPass(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Self RenderPassBuilder::addInputAttachment(VkFormat format,
                                           VkSampleCountFlagBits samples,
                                           AttachmentOps ops,
                                           AttachmentLayouts layouts) {
    VkAttachmentReference ref{};
    ref.attachment = u32(info.attm_descs.size());
    ref.layout = layouts.initial;
    if (ref.layout == VK_IMAGE_LAYOUT_UNDEFINED) {
        ref.layout = isDepthStencilFormat(format) ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
                                                  : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }
    info.attm_refs.push_back(ref);

    VkAttachmentDescription desc{};
    desc.format = format;
    desc.samples = samples;
    desc.loadOp = ops.load;
    desc.storeOp = ops.store;
    desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    desc.initialLayout = layouts.initial;
    desc.finalLayout = layouts.final;
    info.attm_descs.push_back(desc);

    return *this;
}

Self RenderPassBuilder::addColorAttachment(VkFormat format,
                                           VkSampleCountFlagBits samples,
                                           AttachmentOps ops,
                                           AttachmentLayouts layouts) {
    VkAttachmentReference ref{};
    ref.attachment = u32(info.attm_descs.size());
    ref.layout = layouts.initial;
    if (ref.layout == VK_IMAGE_LAYOUT_UNDEFINED) {
        ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    info.attm_refs.push_back(ref);

    VkAttachmentDescription desc{};
    desc.format = format;
    desc.samples = samples;
    desc.loadOp = ops.load;
    desc.storeOp = ops.store;
    desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    desc.initialLayout = layouts.initial;
    desc.finalLayout = layouts.final;
    info.attm_descs.push_back(desc);

    return *this;
}

Self RenderPassBuilder::addDepthStencilAttachment(VkFormat format,
                                                  VkSampleCountFlagBits samples,
                                                  AttachmentOps depth_ops,
                                                  AttachmentOps stencil_ops,
                                                  AttachmentLayouts layouts) {
    VkAttachmentReference ref{};
    ref.attachment = u32(info.attm_descs.size());
    ref.layout = layouts.initial;
    if (ref.layout == VK_IMAGE_LAYOUT_UNDEFINED) {
        ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }
    info.attm_refs.push_back(ref);

    VkAttachmentDescription desc{};
    desc.format = format;
    desc.samples = samples;
    desc.loadOp = depth_ops.load;
    desc.storeOp = depth_ops.store;
    desc.stencilLoadOp = stencil_ops.load;
    desc.stencilStoreOp = stencil_ops.store;
    desc.initialLayout = layouts.initial;
    desc.finalLayout = layouts.final;
    info.attm_descs.push_back(desc);

    return *this;
}

Self RenderPassBuilder::addSubpass(Vector<uint32_t>&& input, Vector<uint32_t>&& color, uint32_t depthstencil) {
    RenderSubpass subpass;
    subpass.inputs = std::move(input);
    subpass.colors = std::move(color);
    if (depthstencil != VK_ATTACHMENT_UNUSED) {
        subpass.depthstencil.push_back(depthstencil);
    }
    info.subpasses.push_back(std::move(subpass));
    return *this;
}

RenderPassBuilder::Built RenderPassBuilder::build() {
    uint32_t subpass_count = u32(info.subpasses.size());
    if (subpass_count == 0) {
        return Er("There must be at least one subpass for render pass");
    }
    Vector<VkSubpassDescription> subpasses(subpass_count);
    Vector<Vector<VkAttachmentReference>> inputs(subpass_count);
    Vector<Vector<VkAttachmentReference>> colors(subpass_count);
    Vector<Vector<VkAttachmentReference>> depthstencil(subpass_count);
    Vector<VkSubpassDependency> dependencies(subpass_count - 1);

    for (uint32_t k = 0; k < subpass_count; k++) {
        auto& subpass = subpasses[k];
        auto& inp = inputs[k];
        auto& clr = colors[k];
        auto& ds = depthstencil[k];
        for (auto a : info.subpasses[k].inputs) {
            inp.push_back(info.attm_refs[a]);
        }
        for (auto a : info.subpasses[k].colors) {
            clr.push_back(info.attm_refs[a]);
        }
        for (auto a : info.subpasses[k].depthstencil) {
            ds.push_back(info.attm_refs[a]);
        }
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.inputAttachmentCount = u32(inp.size());
        subpass.pInputAttachments = inp.data();
        subpass.colorAttachmentCount = u32(clr.size());
        subpass.pColorAttachments = clr.data();
        subpass.pResolveAttachments = nullptr;
        subpass.pDepthStencilAttachment = ds.empty() ? nullptr : ds.data();
        subpass.preserveAttachmentCount = 0;
        subpass.pPreserveAttachments = nullptr;
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

    RenderPass render_pass(device, std::move(info.__name));
    OnRet(vkCreateRenderPass(device, &render_pass_ci, nullptr, render_pass), "Failed to create render pass");
    OnName(render_pass);

    return Ok(std::move(render_pass));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
