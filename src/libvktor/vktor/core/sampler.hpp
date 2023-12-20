#pragma once
#include "__builder.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Sampler : BuiltResource<VkSampler, VK_OBJECT_TYPE_SAMPLER, Device> {
    Sampler(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    Sampler(Sampler&&);
    ~Sampler();
};

struct SamplerInfo : public BuilderInfo {
    VkSamplerCreateFlags flags = 0;
    VkFilter mag_filter = VK_FILTER_NEAREST;
    VkFilter min_filter = VK_FILTER_NEAREST;
    VkSamplerMipmapMode mipmap_mode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    VkSamplerAddressMode address_mode_u = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    VkSamplerAddressMode address_mode_v = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    VkSamplerAddressMode address_mode_w = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    float mip_lod_bias = 0.0f;
    VkBool32 anisotropy = VK_FALSE;
    float max_anisotropy = 0.0f;
    VkBool32 comparable = VK_FALSE;
    VkCompareOp compare_op = VK_COMPARE_OP_NEVER;
    float min_lod = 0.0f;
    float max_lod = 0.0f;
    VkBorderColor border_color = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    VkBool32 unnormalized_coordinates = VK_FALSE;
};

class SamplerBuilder : public Builder<SamplerBuilder, Sampler, SamplerInfo> {
private:
    const Device& device;

public:
    explicit SamplerBuilder(const Device& device, Name&& name = "Sampler") : Builder(std::move(name)), device(device) {}
    virtual Built build() override;

    Self setNearest();
    Self setLinear();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
