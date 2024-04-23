#pragma once
#include "render_subpass.hpp"
#include "render_target.hpp"
#include "vktor/base/texture.hpp"
#include "vktor/core/api/api.hpp"
#include "vktor/core/buffer.hpp"

NAMESPACE_BEGIN(vkt)

class RenderPipeline : private NonCopyable {
private:
    const core::CoreApi& api;

    Vector<RenderSubpass> subpasses{};

public:
    explicit RenderPipeline(const core::CoreApi& api) : api(api) {}
    RenderPipeline(RenderPipeline&&);

    inline void addSubpass(RenderSubpass subpass) {
        subpasses.push_back(std::move(subpass));
    }
    inline const Vector<RenderSubpass>& getSubpasses() const {
        return subpasses;
    }
    Res<core::RenderPass> newRenderPass(const RenderTargetTable& render_target_table) const;
};

NAMESPACE_END(vkt)
