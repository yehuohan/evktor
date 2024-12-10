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
    constant_ranges.push_back(range);
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

    auto pipeline_layout_ci = Itor::PipelineLayoutCreateInfo();
    pipeline_layout_ci.setLayoutCount = u32(info.desc_setlayouts.size());
    pipeline_layout_ci.pSetLayouts = info.desc_setlayouts.data();
    pipeline_layout_ci.pushConstantRangeCount = u32(info.constant_ranges.size());
    pipeline_layout_ci.pPushConstantRanges = info.constant_ranges.data();
    OnRet(vkCreatePipelineLayout(api, &pipeline_layout_ci, api, pipeline_layout), "Failed to create pipeline layout");
    OnName(pipeline_layout, info.__name);

    return Ok(std::move(pipeline_layout));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
