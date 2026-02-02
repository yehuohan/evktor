#pragma once
#include "render_context.hpp"

NAMESPACE_BEGIN(vkt)

class RenderCmdbuf : private NonCopyable {
private:
    RenderContext& rctx;

public:
    const RenderTargetTable& rtt;
    const core::CommandBuffer& cmdbuf;
    const core::RenderPass& render_pass;
    const core::Framebuffer& framebuffer;
    uint32_t subpass_index = 0;

public:
    RenderCmdbuf(RenderContext& rctx,
                 const RenderTargetTable& rtt,
                 const core::CommandBuffer& cmdbuf,
                 const core::RenderPass& render_pass,
                 const core::Framebuffer& framebuffer)
        : rctx(rctx)
        , rtt(rtt)
        , cmdbuf(cmdbuf)
        , render_pass(render_pass)
        , framebuffer(framebuffer) {}
    RenderCmdbuf(RenderCmdbuf&& rhs)
        : rctx(rhs.rctx)
        , rtt(rhs.rtt)
        , cmdbuf(rhs.cmdbuf)
        , render_pass(rhs.render_pass)
        , framebuffer(rhs.framebuffer) {}
    operator RenderContext&() {
        return rctx;
    }
};

NAMESPACE_END(vkt)
