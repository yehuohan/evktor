#pragma once
#include "render_subpass.hpp"
#include "render_target.hpp"
#include "vktor/base/api.hpp"
#include "vktor/core/render_pass.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

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
    Res<RenderPass> createRenderPass(const RenderTargetTable& render_target_table) const;
};

NAMESPACE_END(vkt)
