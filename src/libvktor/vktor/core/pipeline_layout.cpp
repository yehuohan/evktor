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

Res<PipelineLayout> PipelineLayoutState::into(const Device& device) const {
    return PipelineLayout::from(device, *this);
}

PipelineLayout::PipelineLayout(PipelineLayout&& rhs) : PipelineLayout(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

PipelineLayout::~PipelineLayout() {
    if (!__borrowed && handle) {
        vkDestroyPipelineLayout(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<PipelineLayout> PipelineLayout::from(const Device& device, const PipelineLayoutState& info) {
    PipelineLayout pipeline_layout(device);

    auto pipeline_layout_ci = Itor::PipelineLayoutCreateInfo();
    pipeline_layout_ci.setLayoutCount = u32(info.desc_setlayouts.size());
    pipeline_layout_ci.pSetLayouts = info.desc_setlayouts.data();
    pipeline_layout_ci.pushConstantRangeCount = u32(info.constant_ranges.size());
    pipeline_layout_ci.pPushConstantRanges = info.constant_ranges.data();
    OnRet(vkCreatePipelineLayout(device, &pipeline_layout_ci, nullptr, pipeline_layout), "Failed to create pipeline layout");
    OnName(pipeline_layout, info.__name);

    return Ok(std::move(pipeline_layout));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
