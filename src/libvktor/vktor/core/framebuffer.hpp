#pragma once
#include "__builder.hpp"
#include "render_pass.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Framebuffer : public BuiltResource<VkFramebuffer, VK_OBJECT_TYPE_FRAMEBUFFER, Device> {
    const RenderPass& render_pass;

    Framebuffer(const RenderPass& render_pass, Name&& name)
        : BuiltResource(render_pass.device, std::move(name))
        , render_pass(render_pass) {}
    Framebuffer(Framebuffer&&);
    ~Framebuffer();
};

struct FramebufferInfo : public BuilderInfo {
    Vector<VkImageView> imageviews{};
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t layers = 0;
};

class FramebufferBuilder : public Builder<FramebufferBuilder, Framebuffer, FramebufferInfo> {
private:
    const RenderPass& render_pass;

public:
    explicit FramebufferBuilder(const RenderPass& render_pass, Name&& name = "Framebuffer")
        : Builder(std::move(name))
        , render_pass(render_pass) {}
    virtual Built build() override;

    Self addAttachment(const VkImageView imageview);
    Self addAttachments(const Vector<VkImageView>& imageviews);
    Self setExtent(uint32_t width, uint32_t height, uint32_t layers = 1);
    inline Self setExtent(const VkExtent2D& extent) {
        return setExtent(extent.width, extent.height);
    }
    inline Self setExtent(const VkExtent3D& extent) {
        return setExtent(extent.width, extent.height, extent.depth);
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
