#pragma once
#include "vktor/core/render_pass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

class RenderSubpass : private NonCopyable {
private:
    // By default the output attachments is attachment 0
    RenderSubpassInfo info{{}, {0}, VK_ATTACHMENT_UNUSED};

public:
    explicit RenderSubpass() {}
    RenderSubpass(RenderSubpass&&);

    inline void setInputAttachments(Vector<uint32_t>&& inputs) {
        info.inputs = std::move(inputs);
    }
    inline void setColorAttachments(Vector<uint32_t>&& colors) {
        info.colors = std::move(colors);
    }
    inline void setDepthStencilAttachment(uint32_t depthstencil) {
        info.depthstencil = depthstencil;
    }
    inline const RenderSubpassInfo& getInfo() const {
        return info;
    }
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::RenderSubpass> {
    size_t operator()(const vkt::RenderSubpass& render_subpass) const {
        size_t res = 0;
        const auto& info = render_subpass.getInfo();
        for (const auto a : info.inputs) {
            vkt::hashCombine(res, a);
        }
        for (const auto a : info.colors) {
            vkt::hashCombine(res, a);
        }
        vkt::hashCombine(res, info.depthstencil);
        return res;
    }
};

template <>
struct hash<vkt::Vector<vkt::RenderSubpass>> {
    size_t operator()(const vkt::Vector<vkt::RenderSubpass>& render_subpasses) const {
        size_t res = 0;
        for (const auto& subpass : render_subpasses) {
            vkt::hashCombine(res, subpass);
        }
        return res;
    }
};

NAMESPACE_END(std)
