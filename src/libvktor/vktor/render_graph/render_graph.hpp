#pragma once
#include "vktor/core/api/api.hpp"

NAMESPACE_BEGIN(vkt)

class RenderGraph : public NonCopyable {
private:
    const core::CoreApi& api;

private:
    explicit RenderGraph(const core::CoreApi& api) : api(api) {}

public:
    static Res<RenderGraph> from(const core::CoreApi& api);

    RenderGraph(RenderGraph&&);
};

NAMESPACE_END(vkt)
