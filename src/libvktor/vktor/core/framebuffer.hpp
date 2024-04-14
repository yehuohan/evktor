#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Framebuffer;

class FramebufferState : public CoreStater<FramebufferState> {
    friend struct Framebuffer;

private:
    VkRenderPass render_pass;
    Vector<VkImageView> imageviews{};
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t layers = 0;

public:
    explicit FramebufferState(Name&& name = "Framebuffer") : CoreStater(std::move(name)) {}

    Self setRenderPass(VkRenderPass render_pass);
    Self addAttachment(VkImageView imageview);
    Self addAttachments(const Vector<VkImageView>& imageviews);
    Self setExtent(uint32_t width, uint32_t height, uint32_t layers = 1);
    inline Self setExtent(const VkExtent2D& extent) {
        return setExtent(extent.width, extent.height);
    }
    inline Self setExtent(const VkExtent3D& extent) {
        return setExtent(extent.width, extent.height, extent.depth);
    }

    Res<Framebuffer> into(const CoreApi& api) const;
};

struct Framebuffer : public CoreResource<VkFramebuffer, VK_OBJECT_TYPE_FRAMEBUFFER> {
protected:
    explicit Framebuffer(const CoreApi& api) : CoreResource(api) {}

public:
    Framebuffer(Framebuffer&&);
    ~Framebuffer();

    static Res<Framebuffer> from(const CoreApi& api, const FramebufferState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
