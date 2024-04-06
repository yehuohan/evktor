#include "descriptor_setlayout.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = DescriptorSetLayoutState::Self;

Self DescriptorSetLayoutState::setFlags(VkDescriptorSetLayoutCreateFlags _flags) {
    flags = _flags;
    return *this;
}

Self DescriptorSetLayoutState::addBinding(const VkDescriptorSetLayoutBinding& binding) {
    bindings[binding.binding] = binding;
    return *this;
}

Self DescriptorSetLayoutState::addBindings(const Vector<VkDescriptorSetLayoutBinding>& _bindings) {
    for (const auto& elem : _bindings) {
        addBinding(elem);
    }
    return *this;
}

Self DescriptorSetLayoutState::addBinding(uint32_t binding,
                                          VkDescriptorType type,
                                          uint32_t count,
                                          VkShaderStageFlags stage_flags,
                                          const VkSampler* samplers) {
    VkDescriptorSetLayoutBinding bind{};
    bind.binding = binding;
    bind.descriptorType = type;
    bind.descriptorCount = count;
    bind.stageFlags = stage_flags;
    bind.pImmutableSamplers = samplers;
    bindings[binding] = bind;
    return *this;
}

Res<DescriptorSetLayout> DescriptorSetLayoutState::into(const Device& device) const {
    return DescriptorSetLayout::from(device, *this);
}

DescriptorSetLayout::DescriptorSetLayout(DescriptorSetLayout&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    bindings = std::move(rhs.bindings);
}

DescriptorSetLayout::~DescriptorSetLayout() {
    if (!__borrowed && handle) {
        vkDestroyDescriptorSetLayout(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<DescriptorSetLayout> DescriptorSetLayout::from(const Device& device, const DescriptorSetLayoutState& info) {
    DescriptorSetLayout setlayout(device);

    Vector<VkDescriptorSetLayoutBinding> bindings{};
    for (const auto& item : info.bindings) {
        bindings.push_back(item.second);
    }

    auto layout_ci = Itor::DescriptorSetLayoutCreateInfo();
    layout_ci.flags = info.flags;
    layout_ci.bindingCount = u32(bindings.size());
    layout_ci.pBindings = bindings.data();
    OnRet(vkCreateDescriptorSetLayout(device, &layout_ci, nullptr, setlayout), "Failed to create descriptor set layout");
    OnName(setlayout, info.__name);
    setlayout.bindings = std::move(info.bindings);

    return Ok(std::move(setlayout));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
