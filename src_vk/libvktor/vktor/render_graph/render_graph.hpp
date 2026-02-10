#pragma once
#include "vktor/core/api/api.hpp"

NAMESPACE_BEGIN(vkt)

class RenderGraph : private NonCopyable {
private:
    const core::CoreApi& api;

private:
    explicit RenderGraph(const core::CoreApi& api) : api(api) {}

public:
    static Res<RenderGraph> from(const core::CoreApi& api) {
        RenderGraph render_graph(api);
        return Ok(std::move(render_graph));
    }

    RenderGraph(RenderGraph&& rhs) : api(rhs.api) {}
};

NAMESPACE_END(vkt)
