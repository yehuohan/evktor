#pragma once
#include "render_subpass.hpp"
#include "render_target.hpp"

NAMESPACE_BEGIN(vkt)

/**
 * @brief Render pipeline with subpasses
 */
class RenderPipeline : private NonCopyable {
private:
    RenderContext& rctx;
    const String name;

    Vector<Box<RenderSubpass>> subpasses{};

public:
    explicit RenderPipeline(RenderContext& rctx, const String& name = "Rendering") : rctx(rctx), name(name) {}
    RenderPipeline(RenderPipeline&&);
    operator RenderContext&() {
        return rctx;
    }

    template <std::derived_from<RenderSubpass> T>
    T& addSubpass(T&& subpass);
    template <std::derived_from<RenderSubpass> T, typename... Args>
    T& addSubpass(Shader&& vert, Shader&& frag, Args&&... args);
    template <std::derived_from<RenderSubpass> T>
    Res<Ref<T>> getSubpass(size_t index);

    inline const Vector<Box<RenderSubpass>>& getSubpasses() const {
        return subpasses;
    }
    Vector<CRef<core::RenderSubpassState>> getSubpassStates();

    /** @brief Draw all subpass on render targets */
    Res<Void> draw(const core::CommandBuffer& cmdbuf,
                   const RenderTargetTable& rtt,
                   VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE);
};

template <std::derived_from<RenderSubpass> T>
T& RenderPipeline::addSubpass(T&& subpass) {
    return dynamic_cast<T&>(*subpasses.emplace_back(newBox<T>(std::move(subpass))));
}

template <std::derived_from<RenderSubpass> T, typename... Args>
T& RenderPipeline::addSubpass(Shader&& vert, Shader&& frag, Args&&... args) {
    return dynamic_cast<T&>(*subpasses.emplace_back(newBox<T>(std::move(vert), std::move(frag), std::forward<Args>(args)...)));
}

template <std::derived_from<RenderSubpass> T>
Res<Ref<T>> RenderPipeline::getSubpass(size_t index) {
    if (index >= subpasses.size()) {
        return Er("The subpass index = {} is out of subpasses = {}", index, subpasses.size());
    }
    return Ok(newRef(*dynamic_cast<T*>(subpasses[index].get())));
}

NAMESPACE_END(vkt)
