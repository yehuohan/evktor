#pragma once
#include "__core.hpp"
#include "descriptor_setlayout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct PipelineLayout;

class PipelineLayoutState : public CoreState<PipelineLayoutState> {
    friend struct PipelineLayout;

private:
    VkPipelineLayoutCreateFlags flags = 0;
    Vector<VkDescriptorSetLayout> desc_setlayouts{};
    Vector<VkPushConstantRange> push_constants{};

public:
    explicit PipelineLayoutState(String&& name = "PipelineLayout") : CoreState(std::move(name)) {}

    Self setFlags(VkPipelineLayoutCreateFlags flags);
    Self addDescriptorSetLayout(VkDescriptorSetLayout setlayout);
    Self addPushConstantRange(const VkPushConstantRange& range);
    Self addPushConstantRange(VkShaderStageFlags stage, uint32_t size, uint32_t offset = 0);
    Self addGraphicsPushConstantRange(uint32_t size, uint32_t offset = 0);
    Self addVertPushConstantRange(uint32_t size, uint32_t offset = 0);
    Self addFragPushConstantRange(uint32_t size, uint32_t offset = 0);
    Self addCompPushConstantRange(uint32_t size, uint32_t offset = 0);

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
