#include "render_pipeline.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderPipeline::RenderPipeline(RenderPipeline&& rhs) : rctx(rhs.rctx), name(rhs.name) {
    subpasses = std::move(rhs.subpasses);
}

Vector<CRef<core::RenderSubpassState>> RenderPipeline::getSubpassStates() {
    Vector<CRef<core::RenderSubpassState>> states;
    for (const auto& subpass : subpasses) {
        states.emplace_back(subpass->getState()); // Construct CRef<core::RenderSubpassState> directly inside vector
    }
    return states;
}

Res<Void> RenderPipeline::draw(const core::CommandBuffer& cmdbuf, const RenderTargetTable& rtt, VkSubpassContents contents) {
    if (subpasses.empty()) {
        return Er("There's no subpass to draw for this render pipeline");
    }

    auto res_render_pass = rctx.requestRenderPass(rtt, getSubpassStates());
    OnErr(res_render_pass);
    auto& render_pass = res_render_pass.unwrap().get();
    auto res_framebuffer = rctx.requestFramebuffer(rtt, render_pass);
    OnErr(res_framebuffer);
    auto& framebuffer = res_framebuffer.unwrap().get();

    const core::CoreApi& api = rctx;
    RenderCmdbuf rd_cmdbuf(rctx, rtt, cmdbuf, render_pass, framebuffer);

    api.cmdBeginLabel(cmdbuf, name.c_str());
    for (size_t k = 0; k < subpasses.size(); k++) {
        auto& subpass = subpasses[k];
        rd_cmdbuf.subpass_index = k;

        if (0 == k) {
            cmdbuf.beginRenderPass(rtt.getExtent(), render_pass, framebuffer, rtt.getClearValues(), contents);
        } else {
            cmdbuf.cmdNextSubpass();
        }

        auto subpass_name = subpass->getName().empty() ? vktFmt("Subpass #{}", k) : subpass->getName();
        api.cmdBeginLabel(cmdbuf, subpass_name.c_str());
        auto res = subpass->draw(rd_cmdbuf);
        OnErr(res);
        api.cmdEndLabel(cmdbuf);
    }
    cmdbuf.endRenderPass();
    api.cmdEndLabel(cmdbuf);

    return Ok(Void{});
}

NAMESPACE_END(vkt)
