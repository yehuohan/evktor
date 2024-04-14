#pragma once
#include "__core.hpp"

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

    Res<Sampler> into(const CoreApi& api) const;
};

struct Sampler : CoreResource<VkSampler, VK_OBJECT_TYPE_SAMPLER> {
protected:
    explicit Sampler(const CoreApi& api) : CoreResource(api) {}

public:
    Sampler(Sampler&&);
    ~Sampler();

    static Res<Sampler> from(const CoreApi& api, const SamplerState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
