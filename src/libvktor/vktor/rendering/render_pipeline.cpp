#include "render_pipeline.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderPipeline::RenderPipeline(RenderPipeline&& rhs) : api(rhs.api) {
    subpasses = std::move(rhs.subpasses);
}

Res<RenderPass> RenderPipeline::newRenderPass(const RenderTargetTable& render_target_table) const {
    RenderPassState rso{};

    for (const auto& rt : render_target_table.getTargets()) {
        auto& image = rt.getImage();
        rso.addAttachment(image.format, image.samples, rt.ops, rt.stencil_ops, rt.layouts);
    }
    for (const auto& subpass : subpasses) {
        rso.addSubpass(subpass.getInfo());
    }

    return rso.into(api);
}

NAMESPACE_END(vkt)
