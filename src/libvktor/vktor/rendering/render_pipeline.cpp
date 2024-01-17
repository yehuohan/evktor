#include "render_pipeline.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<RenderPass> RenderPipeline::createRenderPass(const RenderTargetTable& render_target_table) const {
    RenderPassBuilder builder(api);

    for (const auto& rt : render_target_table.getTargets()) {
        builder.addAttachment(rt.format, rt.samples, rt.ops, rt.stencil_ops, rt.layouts);
    }
    for (const auto& subpass : subpasses) {
        builder.addSubpass(subpass.getInfo());
    }

    return builder();
}

NAMESPACE_END(vkt)
