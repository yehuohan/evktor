#pragma once
#include "render_cmdbuf.hpp"
#include "vktor/base/shader.hpp"
#include "vktor/core/render_pass.hpp"

NAMESPACE_BEGIN(vkt)

/**
 * @brief Render pipeline subpass with vertex and fragment shader
 */
class RenderSubpass : private NonCopyable {
protected:
    const String name;

    Shader vert_shader;
    Shader frag_shader;

    /** Specify which render targets are required by this subpass
     *
     * By default the color attachment is RT-0
     */
    core::RenderSubpassState state{{}, {0}, VK_ATTACHMENT_UNUSED};

public:
    explicit RenderSubpass(Shader&& vert, Shader&& frag, const String& name = "")
        : name(name)
        , vert_shader(std::move(vert))
        , frag_shader(std::move(frag)) {}
    RenderSubpass(RenderSubpass&&);
    virtual ~RenderSubpass() {}

    inline const Vector<CRef<Shader>> Shaders() const {
        return {newCRef(vert_shader), newCRef(frag_shader)};
    }
    inline const Shader& vertShader() const {
        return vert_shader;
    }
    inline const Shader& fragShader() const {
        return frag_shader;
    }
    inline const String& getName() const {
        return name;
    }

    /** Set input render targets (alias input attachments) */
    RenderSubpass& setRTInputs(const Vector<uint32_t>& inputs);
    /** Set color render targets (alias color attachments) */
    RenderSubpass& setRTColors(const Vector<uint32_t>& colors);
    /** Set depth stencil render target (alias depth stencil attachment) */
    RenderSubpass& setRTDepthStencil(uint32_t depthstencil);
    inline const core::RenderSubpassState& getState() const {
        return state;
    }

    /** @brief Draw custom subpass */
    virtual Res<Void> draw(RenderCmdbuf& rd_cmdbuf) = 0;
};

NAMESPACE_END(vkt)
