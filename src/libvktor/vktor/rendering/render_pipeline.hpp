#pragma once
#include "render_subpass.hpp"
#include "render_target.hpp"
#include "vktor/base/texture.hpp"
#include "vktor/core/api/api.hpp"
#include "vktor/core/buffer.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/pipeline_graphics.hpp"

NAMESPACE_BEGIN(vkt)

class RenderPipeline : private NonCopyable {
private:
    const core::CoreApi& api;

    Vector<RenderSubpass> subpasses{};
    core::GraphicsPipelineState pso{};
    Vector<Ptr<core::Buffer>> buffers{};
    Vector<Ptr<core::Image>> images{};
    Vector<Ptr<Texture>> textures{};

public:
    HashMap<uint32_t, core::DescriptorInfo> desc_info{};

    explicit RenderPipeline(const core::CoreApi& api) : api(api) {}
    RenderPipeline(RenderPipeline&&);

    inline void addSubpass(RenderSubpass subpass) {
        subpasses.push_back(std::move(subpass));
    }
    inline const Vector<RenderSubpass>& getSubpasses() const {
        return subpasses;
    }
    Res<core::RenderPass> newRenderPass(const RenderTargetTable& render_target_table) const;

    inline void bindBuffer(const core::Buffer& buffer, uint32_t binding, uint32_t set = 0) {
        auto& buf = desc_info[set].bufs[binding];
        buf.buffer = buffer;
        buf.offset = 0;
        buf.range = buffer.size;
    }
    inline void bindImage(const core::ImageView& imageview,
                          const core::Sampler& sampler,
                          VkImageLayout layout,
                          uint32_t binding,
                          uint32_t set = 0) {
        auto& img = desc_info[set].imgs[binding];
        img.sampler = sampler;
        img.imageView = imageview;
        img.imageLayout = layout;
    }
};

NAMESPACE_END(vkt)
