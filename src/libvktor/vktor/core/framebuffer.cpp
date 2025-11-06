#include "framebuffer.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = FramebufferState::Self;

Self FramebufferState::setRenderPass(VkRenderPass _render_pass) {
    render_pass = _render_pass;
    return *this;
}

Self FramebufferState::addAttachment(VkImageView imageview) {
    imageviews.push_back(imageview);
    return *this;
}

Self FramebufferState::addAttachments(const Vector<VkImageView>& _imageviews) {
    imageviews.insert(imageviews.end(), _imageviews.begin(), _imageviews.end());
    return *this;
}

Self FramebufferState::setExtent(uint32_t _width, uint32_t _height, uint32_t _layers) {
    width = _width;
    height = _height;
    layers = _layers;
    return *this;
}

Res<Framebuffer> FramebufferState::into(const CoreApi& api) const {
    return Framebuffer::from(api, *this);
}

Framebuffer::Framebuffer(Framebuffer&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Framebuffer::~Framebuffer() {
    if (!__borrowed && handle) {
        vkDestroyFramebuffer(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<Framebuffer> Framebuffer::from(const CoreApi& api, const FramebufferState& info) {
    Framebuffer framebuffer(api);

    auto framebuffer_ci = Itor::FramebufferCreateInfo(info.__next);
    framebuffer_ci.renderPass = info.render_pass;
    framebuffer_ci.attachmentCount = u32(info.imageviews.size());
    framebuffer_ci.pAttachments = info.imageviews.data();
    framebuffer_ci.width = info.width;
    framebuffer_ci.height = info.height;
    framebuffer_ci.layers = info.layers;

    OnRet(vkCreateFramebuffer(api, &framebuffer_ci, api, framebuffer), "Failed to create framebuffer");
    OnName(framebuffer, info.__name);

    return Ok(std::move(framebuffer));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
