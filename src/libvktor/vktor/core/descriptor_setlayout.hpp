#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct DescriptorSetLayout;

class DescriptorSetLayoutState : public CoreStater<DescriptorSetLayoutState> {
    friend struct DescriptorSetLayout;

private:
    VkDescriptorSetLayoutCreateFlags flags = 0;
    Map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};

public:
    explicit DescriptorSetLayoutState(Name&& name = "DescriptorSetLayout") : CoreStater(std::move(name)) {}

    Self setFlags(VkDescriptorSetLayoutCreateFlags flags);
    Self addBinding(const VkDescriptorSetLayoutBinding& binding);
    Self addBinding(uint32_t binding,
                    VkDescriptorType type,
                    uint32_t count,
                    VkShaderStageFlags stage_flags,
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

    Res<DescriptorSetLayout> into(const Device& device) const;
};

struct DescriptorSetLayout : public CoreResource<VkDescriptorSetLayout, VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, Device> {
    /**
     * @brief Map VkDescriptorSetLayoutBinding::binding to VkDescriptorSetLayoutBinding
     *
     * According to *VUID-VkDescriptorSetLayoutCreateInfo-binding-00279:
     * The VkDescriptorSetLayoutBinding::binding members of the elements of the pBindings array must each have different values.
     * So we can take VkDescriptorSetLayoutBinding::binding as map key.
     */
    Map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};

protected:
    explicit DescriptorSetLayout(const Device& device) : CoreResource(device) {}

public:
    DescriptorSetLayout(DescriptorSetLayout&&);
    ~DescriptorSetLayout();

    static Res<DescriptorSetLayout> from(const Device& device, const DescriptorSetLayoutState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::DescriptorSetLayout> {
    inline size_t operator()(const vkt::core::DescriptorSetLayout& desc_setlayout) const {
        return hash<VkDescriptorSetLayout>{}(desc_setlayout);
    }
};

NAMESPACE_END(std)
