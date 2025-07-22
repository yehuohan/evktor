#pragma once
#include "__core.hpp"
#include "descriptor_setlayout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct PipelineLayout;

class PipelineLayoutState : public CoreStater<PipelineLayoutState> {
    friend struct PipelineLayout;

private:
    VkPipelineLayoutCreateFlags flags = 0;
    Vector<VkDescriptorSetLayout> desc_setlayouts{};
    Vector<VkPushConstantRange> constant_ranges{};

public:
    explicit PipelineLayoutState(String&& name = "PipelineLayout") : CoreStater(std::move(name)) {}

    Self setFlags(VkPipelineLayoutCreateFlags flags);
    Self addDescriptorSetLayout(VkDescriptorSetLayout setlayout);
    Self addPushConstantRange(const VkPushConstantRange& range);

    Res<PipelineLayout> into(const CoreApi& api) const;
};

struct PipelineLayout : public CoreResource<VkPipelineLayout, VK_OBJECT_TYPE_PIPELINE_LAYOUT> {
protected:
    explicit PipelineLayout(const CoreApi& api) : CoreResource(api) {}

public:
    PipelineLayout(PipelineLayout&&);
    ~PipelineLayout();

    static Res<PipelineLayout> from(const CoreApi& api, const PipelineLayoutState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
