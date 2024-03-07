#pragma once
#include "__builder.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorSetLayout : public BuiltResource<VkDescriptorSetLayout, VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, Device> {
    /**
     * @brief Map VkDescriptorSetLayoutBinding::binding to VkDescriptorSetLayoutBinding
     *
     * According to *VUID-VkDescriptorSetLayoutCreateInfo-binding-00279:
     * The VkDescriptorSetLayoutBinding::binding members of the elements of the pBindings array must each have different values.
     * So we can take VkDescriptorSetLayoutBinding::binding as map key.
     */
    Map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};

    DescriptorSetLayout(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    DescriptorSetLayout(DescriptorSetLayout&&);
    ~DescriptorSetLayout();
};

struct DescriptorSetLayoutInfo : public BuilderInfo {
    VkDescriptorSetLayoutCreateFlags flags = 0;
    Map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
};

class DescriptorSetLayoutBuilder : public Builder<DescriptorSetLayoutBuilder, DescriptorSetLayout, DescriptorSetLayoutInfo> {
private:
    const Device& device;

public:
    explicit DescriptorSetLayoutBuilder(const Device& device, Name&& name = "DescriptorSetLayout")
        : Builder(std::move(name))
        , device(device) {}
    virtual Built build() override;

    Self setFlags(VkDescriptorSetLayoutCreateFlags flags);
    Self addBinding(const VkDescriptorSetLayoutBinding& binding);
    Self addBinding(uint32_t binding,
                    VkDescriptorType type,
                    uint32_t count,
                    VkShaderStageFlags flags,
                    const VkSampler* samplers = nullptr);
    Self addBindings(const Vector<VkDescriptorSetLayoutBinding>& bindings);
    inline Self addVertBinding(uint32_t binding, VkDescriptorType type, uint32_t count = 1, const VkSampler* spls = nullptr) {
        return addBinding(binding, type, count, VK_SHADER_STAGE_VERTEX_BIT, spls);
    }
    inline Self addFragBinding(uint32_t binding, VkDescriptorType type, uint32_t count = 1, const VkSampler* spls = nullptr) {
        return addBinding(binding, type, count, VK_SHADER_STAGE_FRAGMENT_BIT, spls);
    }
    inline Self addCompBinding(uint32_t binding, VkDescriptorType type, uint32_t count = 1, const VkSampler* spls = nullptr) {
        return addBinding(binding, type, count, VK_SHADER_STAGE_COMPUTE_BIT, spls);
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::DescriptorSetLayout> {
    size_t operator()(const vkt::core::DescriptorSetLayout& desc_setlayout) const {
        return hash<VkDescriptorSetLayout>{}(desc_setlayout);
    }
};

NAMESPACE_END(std)
