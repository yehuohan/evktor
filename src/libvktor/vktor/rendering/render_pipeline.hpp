#pragma once
#include "render_subpass.hpp"
#include "render_target.hpp"
#include "vktor/base/api.hpp"

NAMESPACE_BEGIN(vkt)

class RenderPipeline : private NonCopyable {
private:
    const BaseApi& api;

    Vector<RenderSubpass> subpasses{};

public:
    explicit RenderPipeline(const BaseApi& api) : api(api) {}

    inline void addSubpass(RenderSubpass subpass) {
        subpasses.push_back(std::move(subpass));
    }
    inline const Vector<RenderSubpass>& getSubpasses() const {
        return subpasses;
    }
    Res<core::RenderPass> createRenderPass(const RenderTargetTable& render_target_table) const;
};

NAMESPACE_END(vkt)
