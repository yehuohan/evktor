#pragma once
#include "../component.hpp"
#include <vktor/core/sampler.hpp>

NAMESPACE_BEGIN(vktscn)

class Sampler : public Component {
private:
    vkt::core::Sampler sampler;

public:
    Sampler(vkt::core::Sampler&& sampler, const String& name = "") : Component(name), sampler(std::move(sampler)) {}
    virtual ~Sampler() = default;

    OnConstType(VkSampler, sampler.getHandle());

    virtual std::type_index getType() const override {
        return typeid(Sampler);
    }
};

NAMESPACE_END(vktscn)
