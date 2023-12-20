#include "descriptor_setlayout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DescriptorSetLayoutBuilder::Self;

DescriptorSetLayout::DescriptorSetLayout(DescriptorSetLayout&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    __name = std::move(rhs.__name);
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    bindings = std::move(rhs.bindings);
}

DescriptorSetLayout::~DescriptorSetLayout() {
    if (handle) {
        vkDestroyDescriptorSetLayout(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Self DescriptorSetLayoutBuilder::setFlags(VkDescriptorSetLayoutCreateFlags flags) {
    info.flags = flags;
    return *this;
}

Self DescriptorSetLayoutBuilder::addBinding(const VkDescriptorSetLayoutBinding& binding) {
    info.bindings[binding.binding] = binding;
    return *this;
}

Self DescriptorSetLayoutBuilder::addBindings(const Vector<VkDescriptorSetLayoutBinding>& bindings) {
    for (const auto& elem : bindings) {
        addBinding(elem);
    }
    return *this;
}

Self DescriptorSetLayoutBuilder::addBinding(uint32_t binding,
                                            VkDescriptorType type,
                                            uint32_t count,
                                            VkShaderStageFlags flags,
                                            const VkSampler* samplers) {
    VkDescriptorSetLayoutBinding bind{};
    bind.binding = binding;
    bind.descriptorType = type;
    bind.descriptorCount = count;
    bind.stageFlags = flags;
    bind.pImmutableSamplers = samplers;
    info.bindings[binding] = bind;
    return *this;
}

DescriptorSetLayoutBuilder::Built DescriptorSetLayoutBuilder::build() {
    DescriptorSetLayout setlayout(device, std::move(info.__name));

    Vector<VkDescriptorSetLayoutBinding> bindings{};
    for (const auto& item : info.bindings) {
        bindings.push_back(item.second);
    }

    auto layout_ci = Itor::DescriptorSetLayoutCreateInfo();
    layout_ci.flags = info.flags;
    layout_ci.bindingCount = u32(bindings.size());
    layout_ci.pBindings = bindings.data();
    OnRet(vkCreateDescriptorSetLayout(device, &layout_ci, nullptr, setlayout), "Failed to create descriptor set layout");
    OnName(setlayout);
    setlayout.bindings = std::move(info.bindings);

    return Ok(std::move(setlayout));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
