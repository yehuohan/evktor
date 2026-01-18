#include "pipeline_layout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = PipelineLayoutState::Self;

Self PipelineLayoutState::setFlags(VkPipelineLayoutCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self PipelineLayoutState::addDescriptorSetLayout(VkDescriptorSetLayout setlayout) {
    desc_setlayouts.push_back(setlayout);
    return *this;
}

Self PipelineLayoutState::addPushConstantRange(const VkPushConstantRange& range) {
    push_constants.push_back(range);
    return *this;
}

Self PipelineLayoutState::addPushConstantRange(VkShaderStageFlags stage, uint32_t size, uint32_t offset) {
    push_constants.push_back(VkPushConstantRange{stage, offset, size});
    return *this;
}

Self PipelineLayoutState::addGraphicsPushConstantRange(uint32_t size, uint32_t offset) {
    push_constants.push_back(VkPushConstantRange{VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, offset, size});
    return *this;
}

Self PipelineLayoutState::addVertPushConstantRange(uint32_t size, uint32_t offset) {
    push_constants.push_back(VkPushConstantRange{VK_SHADER_STAGE_VERTEX_BIT, offset, size});
    return *this;
}

Self PipelineLayoutState::addFragPushConstantRange(uint32_t size, uint32_t offset) {
    push_constants.push_back(VkPushConstantRange{VK_SHADER_STAGE_FRAGMENT_BIT, offset, size});
    return *this;
}

Self PipelineLayoutState::addCompPushConstantRange(uint32_t size, uint32_t offset) {
    push_constants.push_back(VkPushConstantRange{VK_SHADER_STAGE_COMPUTE_BIT, offset, size});
    return *this;
}

Res<PipelineLayout> PipelineLayoutState::into(const CoreApi& api) const {
    return PipelineLayout::from(api, *this);
}

PipelineLayout::PipelineLayout(PipelineLayout&& rhs) : PipelineLayout(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

PipelineLayout::~PipelineLayout() {
    if (!__borrowed && handle) {
        vkDestroyPipelineLayout(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<PipelineLayout> PipelineLayout::from(const CoreApi& api, const PipelineLayoutState& info) {
    PipelineLayout pipeline_layout(api);

    auto pipeline_layout_ci = Itor::PipelineLayoutCreateInfo(info.__next);
    pipeline_layout_ci.setLayoutCount = u32(info.desc_setlayouts.size());
    pipeline_layout_ci.pSetLayouts = info.desc_setlayouts.data();
    pipeline_layout_ci.pushConstantRangeCount = u32(info.push_constants.size());
    pipeline_layout_ci.pPushConstantRanges = info.push_constants.data();
    OnRet(vkCreatePipelineLayout(api, &pipeline_layout_ci, api, pipeline_layout), "Failed to create pipeline layout");
    OnName(pipeline_layout, info.__name);

    return Ok(std::move(pipeline_layout));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
