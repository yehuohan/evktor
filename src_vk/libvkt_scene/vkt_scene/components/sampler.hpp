#pragma once
#include "../component.hpp"
#include <vktor/core/sampler.hpp>

NAMESPACE_BEGIN(vktscn)

class Sampler : public Component {
public:
    vkt::core::Sampler sampler;

public:
    Sampler(const String& name, vkt::core::Sampler&& sampler) : Component{name}, sampler{std::move(sampler)} {}
    Sampler(Sampler&& other) = default;
    virtual ~Sampler() = default;

    operator VkSampler() const {
        return (VkSampler)sampler;
    }

    virtual std::type_index getType() const override {
        return typeid(Sampler);
    }
};

NAMESPACE_END(vktscn)
