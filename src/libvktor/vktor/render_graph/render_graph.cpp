#include "render_graph.hpp"

NAMESPACE_BEGIN(vkt)

Res<RenderGraph> RenderGraph::from(const core::CoreApi& api) {
    RenderGraph render_graph(api);
    return Ok(std::move(render_graph));
}

RenderGraph::RenderGraph(RenderGraph&& rhs) : api(rhs.api) {}

NAMESPACE_END(vkt)
