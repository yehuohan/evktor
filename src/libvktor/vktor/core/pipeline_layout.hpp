#pragma once
#include "__builder.hpp"
#include "descriptor_setlayout.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct PipelineLayout : public BuiltResource<VkPipelineLayout, VK_OBJECT_TYPE_PIPELINE_LAYOUT, Device> {
    PipelineLayout(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    PipelineLayout(PipelineLayout&&);
    ~PipelineLayout();
};

struct PipelineLayoutInfo : public BuilderInfo {
    VkPipelineLayoutCreateFlags flags = 0;
    Vector<Ptr<DescriptorSetLayout>> desc_setlayouts{};
    Vector<VkPushConstantRange> constant_ranges{};
};

class PipelineLayoutBuilder : public Builder<PipelineLayoutBuilder, PipelineLayout, PipelineLayoutInfo> {
private:
    const Device& device;

public:
    explicit PipelineLayoutBuilder(const Device& device, Name&& name = "PipelineLayout")
        : Builder(std::move(name))
        , device(device) {}
    virtual Built build() override;

    Self setFlags(VkPipelineLayoutCreateFlags flags);
    Self addDescriptorSetLayout(const Ptr<DescriptorSetLayout>& setlayout);
    Self addPushConstantRange(const VkPushConstantRange& range);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
