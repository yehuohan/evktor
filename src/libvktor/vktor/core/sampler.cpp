#include "sampler.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = SamplerBuilder::Self;

Sampler::Sampler(Sampler&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

Sampler::~Sampler() {
    if (handle) {
        vkDestroySampler(device, handle, nullptr);
    }
    handle = VK_NULL_HANDLE;
}

Self SamplerBuilder::setNearest() {
    info.sampler_ci.magFilter = VK_FILTER_NEAREST;
    info.sampler_ci.minFilter = VK_FILTER_NEAREST;
    info.sampler_ci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    info.sampler_ci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.sampler_ci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.sampler_ci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.sampler_ci.mipLodBias = 0.0f;
    info.sampler_ci.anisotropyEnable = VK_FALSE;
    info.sampler_ci.maxAnisotropy = 1.0f;
    info.sampler_ci.compareEnable = VK_FALSE;
    info.sampler_ci.compareOp = VK_COMPARE_OP_NEVER;
    info.sampler_ci.minLod = 0.0f;
    info.sampler_ci.maxLod = VK_LOD_CLAMP_NONE;
    info.sampler_ci.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    info.sampler_ci.unnormalizedCoordinates = VK_FALSE;
    return *this;
}

Self SamplerBuilder::setLinear() {
    info.sampler_ci.magFilter = VK_FILTER_LINEAR;
    info.sampler_ci.minFilter = VK_FILTER_LINEAR;
    info.sampler_ci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    info.sampler_ci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.sampler_ci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.sampler_ci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.sampler_ci.mipLodBias = 0.0f;
    info.sampler_ci.anisotropyEnable = VK_FALSE;
    info.sampler_ci.maxAnisotropy = 1.0f;
    info.sampler_ci.compareEnable = VK_FALSE;
    info.sampler_ci.compareOp = VK_COMPARE_OP_NEVER;
    info.sampler_ci.minLod = 0.0f;
    info.sampler_ci.maxLod = VK_LOD_CLAMP_NONE;
    info.sampler_ci.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    info.sampler_ci.unnormalizedCoordinates = VK_FALSE;
    return *this;
}

SamplerBuilder::Built SamplerBuilder::build() {
    Sampler sampler(device, std::move(info.__name));

    OnRet(vkCreateSampler(device, &info.sampler_ci, nullptr, sampler), "Failed to create sampler");
    OnName(sampler);

    return Ok(std::move(sampler));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
