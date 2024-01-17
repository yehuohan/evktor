#include "framebuffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = FramebufferBuilder::Self;

Framebuffer::Framebuffer(Framebuffer&& rhs)
    : BuiltResource(rhs.render_pass.device, std::move(rhs.__name))
    , render_pass(rhs.render_pass) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

Framebuffer::~Framebuffer() {
    if (handle) {
        vkDestroyFramebuffer(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Self FramebufferBuilder::addAttachment(VkImageView imageview) {
    info.imageviews.push_back(imageview);
    return *this;
}

Self FramebufferBuilder::addAttachments(const Vector<VkImageView>& imageviews) {
    info.imageviews.insert(info.imageviews.end(), imageviews.begin(), imageviews.end());
    return *this;
}

Self FramebufferBuilder::setExtent(uint32_t width, uint32_t height, uint32_t layers) {
    info.width = width;
    info.height = height;
    info.layers = layers;
    return *this;
}

FramebufferBuilder::Built FramebufferBuilder::build() {
    Framebuffer framebuffer(render_pass, std::move(info.__name));

    auto framebuffer_ci = Itor::FramebufferCreateInfo();
    framebuffer_ci.renderPass = render_pass;
    framebuffer_ci.attachmentCount = u32(info.imageviews.size());
    framebuffer_ci.pAttachments = info.imageviews.data();
    framebuffer_ci.width = info.width;
    framebuffer_ci.height = info.height;
    framebuffer_ci.layers = info.layers;

    OnRet(vkCreateFramebuffer(render_pass.device, &framebuffer_ci, nullptr, framebuffer), "Failed to create framebuffer");
    OnName(framebuffer);

    return Ok(std::move(framebuffer));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
