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
    info.mag_filter = VK_FILTER_NEAREST;
    info.min_filter = VK_FILTER_NEAREST;
    info.mipmap_mode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    info.address_mode_u = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.address_mode_v = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.address_mode_w = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.mip_lod_bias = 0.0f;
    info.anisotropy = VK_FALSE;
    info.max_anisotropy = 1.0f;
    info.comparable = VK_FALSE;
    info.compare_op = VK_COMPARE_OP_NEVER;
    info.min_lod = 0.0f;
    info.max_lod = VK_LOD_CLAMP_NONE;
    info.border_color = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    info.unnormalized_coordinates = VK_FALSE;
    return *this;
}

Self SamplerBuilder::setLinear() {
    info.mag_filter = VK_FILTER_LINEAR;
    info.min_filter = VK_FILTER_LINEAR;
    info.mipmap_mode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    info.address_mode_u = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.address_mode_v = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.address_mode_w = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    info.mip_lod_bias = 0.0f;
    info.anisotropy = VK_FALSE;
    info.max_anisotropy = 1.0f;
    info.comparable = VK_FALSE;
    info.compare_op = VK_COMPARE_OP_NEVER;
    info.min_lod = 0.0f;
    info.max_lod = VK_LOD_CLAMP_NONE;
    info.border_color = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    info.unnormalized_coordinates = VK_FALSE;
    return *this;
}

SamplerBuilder::Built SamplerBuilder::build() {
    Sampler sampler(device, std::move(info.__name));

    auto sampler_ci = Itor::SamplerCreateInfo();
    sampler_ci.flags = info.flags;
    sampler_ci.magFilter = info.mag_filter;
    sampler_ci.minFilter = info.min_filter;
    sampler_ci.mipmapMode = info.mipmap_mode;
    sampler_ci.addressModeU = info.address_mode_u;
    sampler_ci.addressModeV = info.address_mode_v;
    sampler_ci.addressModeW = info.address_mode_w;
    sampler_ci.mipLodBias = info.mip_lod_bias;
    sampler_ci.anisotropyEnable = info.anisotropy;
    sampler_ci.maxAnisotropy = info.max_anisotropy;
    sampler_ci.compareEnable = info.comparable;
    sampler_ci.compareOp = info.compare_op;
    sampler_ci.minLod = info.min_lod;
    sampler_ci.maxLod = info.max_lod;
    sampler_ci.borderColor = info.border_color;
    sampler_ci.unnormalizedCoordinates = info.unnormalized_coordinates;

    OnRet(vkCreateSampler(device, &sampler_ci, nullptr, sampler), "Failed to create sampler");
    OnName(sampler);

    return Ok(std::move(sampler));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
