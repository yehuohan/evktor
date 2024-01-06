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
    VkSamplerCreateInfo sampler_ci;
};

class SamplerBuilder : public Builder<SamplerBuilder, Sampler, SamplerInfo> {
private:
    const Device& device;

public:
    explicit SamplerBuilder(const Device& device, Name&& name = "Sampler") : Builder(std::move(name)), device(device) {
        info.sampler_ci = Itor::SamplerCreateInfo();
        setNearest();
    }
    virtual Built build() override;

    Self setNearest();
    Self setLinear();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
