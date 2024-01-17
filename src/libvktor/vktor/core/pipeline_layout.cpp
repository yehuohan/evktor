#include "pipeline_layout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = PipelineLayoutBuilder::Self;

PipelineLayout::PipelineLayout(PipelineLayout&& rhs) : PipelineLayout(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

PipelineLayout::~PipelineLayout() {
    if (handle) {
        vkDestroyPipelineLayout(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Self PipelineLayoutBuilder::setFlags(VkPipelineLayoutCreateFlags flags) {
    info.flags = flags;
    return *this;
}

Self PipelineLayoutBuilder::addDescriptorSetLayout(VkDescriptorSetLayout setlayout) {
    info.desc_setlayouts.push_back(setlayout);
    return *this;
}

Self PipelineLayoutBuilder::addPushConstantRange(const VkPushConstantRange& range) {
    info.constant_ranges.push_back(range);
    return *this;
}

PipelineLayoutBuilder::Built PipelineLayoutBuilder::build() {
    PipelineLayout pipeline_layout(device, std::move(info.__name));

    auto pipeline_layout_ci = Itor::PipelineLayoutCreateInfo();
    pipeline_layout_ci.setLayoutCount = u32(info.desc_setlayouts.size());
    pipeline_layout_ci.pSetLayouts = info.desc_setlayouts.data();
    pipeline_layout_ci.pushConstantRangeCount = u32(info.constant_ranges.size());
    pipeline_layout_ci.pPushConstantRanges = info.constant_ranges.data();
    OnRet(vkCreatePipelineLayout(device, &pipeline_layout_ci, nullptr, pipeline_layout), "Failed to create pipeline layout");
    OnName(pipeline_layout);

    return Ok(std::move(pipeline_layout));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
