#include "sampler.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SamplerState::Self;

Self SamplerState::setFilter(VkFilter mag, VkFilter min) {
    sampler_ci.magFilter = mag;
    sampler_ci.minFilter = min;
    return *this;
}

Self SamplerState::setMipmapMode(VkSamplerMipmapMode mode) {
    sampler_ci.mipmapMode = mode;
    return *this;
}

Self SamplerState::setAddressMode(VkSamplerAddressMode u, VkSamplerAddressMode v, VkSamplerAddressMode w) {
    sampler_ci.addressModeU = u;
    sampler_ci.addressModeV = v;
    sampler_ci.addressModeW = w;
    return *this;
}

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

Res<Sampler> SamplerState::into(const CoreApi& api) const {
    return Sampler::from(api, *this);
}

Sampler::Sampler(Sampler&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

Sampler::~Sampler() {
    if (!__borrowed && handle) {
        vkDestroySampler(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<Sampler> Sampler::from(const CoreApi& api, const SamplerState& info) {
    Sampler sampler(api);

    OnRet(vkCreateSampler(api, &info.sampler_ci, api, sampler), "Failed to create sampler");
    OnName(sampler, info.__name);

    return Ok(std::move(sampler));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
