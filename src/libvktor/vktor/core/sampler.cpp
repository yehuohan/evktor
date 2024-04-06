#include "sampler.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SamplerState::Self;

Self SamplerState::setNearest() {
    sampler_ci.magFilter = VK_FILTER_NEAREST;
    sampler_ci.minFilter = VK_FILTER_NEAREST;
    sampler_ci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    sampler_ci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.mipLodBias = 0.0f;
    sampler_ci.anisotropyEnable = VK_FALSE;
    sampler_ci.maxAnisotropy = 1.0f;
    sampler_ci.compareEnable = VK_FALSE;
    sampler_ci.compareOp = VK_COMPARE_OP_NEVER;
    sampler_ci.minLod = 0.0f;
    sampler_ci.maxLod = VK_LOD_CLAMP_NONE;
    sampler_ci.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    sampler_ci.unnormalizedCoordinates = VK_FALSE;
    return *this;
}

Self SamplerState::setLinear() {
    sampler_ci.magFilter = VK_FILTER_LINEAR;
    sampler_ci.minFilter = VK_FILTER_LINEAR;
    sampler_ci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sampler_ci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.mipLodBias = 0.0f;
    sampler_ci.anisotropyEnable = VK_FALSE;
    sampler_ci.maxAnisotropy = 1.0f;
    sampler_ci.compareEnable = VK_FALSE;
    sampler_ci.compareOp = VK_COMPARE_OP_NEVER;
    sampler_ci.minLod = 0.0f;
    sampler_ci.maxLod = VK_LOD_CLAMP_NONE;
    sampler_ci.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    sampler_ci.unnormalizedCoordinates = VK_FALSE;
    return *this;
}

Res<Sampler> SamplerState::into(const Device& device) const {
    return Sampler::from(device, *this);
}

Sampler::Sampler(Sampler&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Sampler::~Sampler() {
    if (!__borrowed && handle) {
        vkDestroySampler(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Res<Sampler> Sampler::from(const Device& device, const SamplerState& info) {
    Sampler sampler(device);

    OnRet(vkCreateSampler(device, &info.sampler_ci, nullptr, sampler), "Failed to create sampler");
    OnName(sampler, info.__name);

    return Ok(std::move(sampler));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
