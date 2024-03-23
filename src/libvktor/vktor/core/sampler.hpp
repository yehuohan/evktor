#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Sampler;

class SamplerState : public CoreStater<SamplerState> {
    friend struct Sampler;

private:
    VkSamplerCreateInfo sampler_ci{};

public:
    explicit SamplerState(Name&& name = "Sampler") : CoreStater(std::move(name)) {
        sampler_ci = Itor::SamplerCreateInfo();
        setNearest();
    }

    Self setNearest();
    Self setLinear();

    Res<Sampler> into(const Device& device) const;
};

struct Sampler : CoreResource<VkSampler, VK_OBJECT_TYPE_SAMPLER, Device> {
    Sampler(const Device& device) : CoreResource(device) {}
    Sampler(Sampler&&);
    ~Sampler();

    static Res<Sampler> from(const Device& device, const SamplerState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
