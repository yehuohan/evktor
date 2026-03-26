// This helper is only for gltf_loader.cpp
#pragma once
#include "gltf_loader.hpp"

template <class T, class Y>
struct TypeCast {
    Y operator()(T value) const noexcept {
        return static_cast<Y>(value);
    }
};

inline static Vector<uint8_t> convertUnderlyingDataStride(const std::vector<uint8_t>& src_data,
                                                          uint32_t src_stride,
                                                          uint32_t dst_stride) {
    Vector<uint8_t> dst(u32(src_data.size()) / src_stride * dst_stride);
    for (uint32_t src_idx = 0, dst_idx = 0; src_idx < src_data.size() && dst_idx < dst.size();
         src_idx += src_stride, dst_idx += dst_stride) {
        std::copy(src_data.begin() + src_idx, src_data.begin() + src_idx + src_stride, dst.begin() + dst_idx);
    }

    return dst;
}

inline static VkFilter toMinFilter(int min_filter) {
    switch (min_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: return VK_FILTER_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return VK_FILTER_LINEAR;
    default:
        {
            vktLogW("Invalid gltf texture min filter: {}", min_filter);
            return VK_FILTER_NEAREST;
        }
    }
};

inline static VkFilter toMagFilter(int mag_filter) {
    switch (mag_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST: return VK_FILTER_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_LINEAR: return VK_FILTER_LINEAR;
    default:
        {
            vktLogW("Invalid gltf texture mag filter: {}", mag_filter);
            return VK_FILTER_NEAREST;
        }
    }
};

inline static VkSamplerMipmapMode toMipmapMode(int mipmap_mode) {
    switch (mipmap_mode) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    default:
        {
            vktLogW("Invalid gltf texture mipmap mode: {}", mipmap_mode);
            return VK_SAMPLER_MIPMAP_MODE_LINEAR;
        }
    }
};

inline static VkSamplerAddressMode toWrapMode(int wrap_mode) {
    switch (wrap_mode) {
    case TINYGLTF_TEXTURE_WRAP_REPEAT: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    default:
        {
            vktLogW("Invalid gltf texture wrap mode: {}", wrap_mode);
            return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        }
    }
};
