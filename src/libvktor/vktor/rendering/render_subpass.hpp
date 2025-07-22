#pragma once
#include "vktor/base/shader.hpp"
#include "vktor/core/render_pass.hpp"

NAMESPACE_BEGIN(vkt)

class RenderSubpass : private NonCopyable {
private:
    enum {
        VERT,
        FRAG,
    };
    Vector<Shader> shaders{};
    /** Render targets info for subpass
     *
     * By default the color attachment is RT-0
     */
    core::RenderSubpassInfo info{{}, {0}, VK_ATTACHMENT_UNUSED};

public:
    explicit RenderSubpass(Shader&& vert, Shader&& frag) {
        shaders.push_back(std::move(vert));
        shaders.push_back(std::move(frag));
    }
    RenderSubpass(RenderSubpass&&);

    inline const Vector<Shader>& Shaders() const {
        return shaders;
    }
    inline const Shader& vertShader() const {
        return shaders[VERT];
    }
    inline const Shader& fragShader() const {
        return shaders[FRAG];
    }
    /** Set input render targets (alias input attachments) */
    inline void setRTInputs(Vector<uint32_t>&& inputs) {
        info.inputs = std::move(inputs);
    }
    /** Set color render targets (alias color attachments) */
    inline void setRTColors(Vector<uint32_t>&& colors) {
        info.colors = std::move(colors);
    }
    /** Set depth stencil render target (alias depth stencil attachment) */
    inline void setRTDepthStencil(uint32_t depthstencil) {
        info.depthstencil = depthstencil;
    }
    inline const core::RenderSubpassInfo& getInfo() const {
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
            hashCombine(res, a);
        }
        for (const auto a : info.colors) {
            hashCombine(res, a);
        }
        hashCombine(res, info.depthstencil);
        return res;
    }
};

template <>
struct hash<Vector<vkt::RenderSubpass>> {
    size_t operator()(const Vector<vkt::RenderSubpass>& render_subpasses) const {
        size_t res = 0;
        for (const auto& subpass : render_subpasses) {
            hashCombine(res, subpass);
        }
        return res;
    }
};

NAMESPACE_END(std)
