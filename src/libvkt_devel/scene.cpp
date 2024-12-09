#include "scene.hpp"
#include "vktor/core/buffer.hpp"
#include <vktor/core/image.hpp>
#include <vktor/core/sampler.hpp>

NAMESPACE_BEGIN(vktdev)

inline VkFilter getMinFilter(int min_filter) {
    switch (min_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: return VK_FILTER_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return VK_FILTER_LINEAR;
    default: return VK_FILTER_LINEAR;
    }
};

inline VkFilter getMagFilter(int mag_filter) {
    switch (mag_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST: return VK_FILTER_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_LINEAR: return VK_FILTER_LINEAR;
    default: return VK_FILTER_LINEAR;
    }
};

inline VkSamplerMipmapMode getMipmapMode(int min_filter) {
    switch (min_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    default: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    }
};

inline VkSamplerAddressMode getWrapMode(int wrap) {
    switch (wrap) {
    case TINYGLTF_TEXTURE_WRAP_REPEAT: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    default: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    }
};

vkt::Box<Scene> SceneLoader::load(const vkt::String& filename) {
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    vkt::String err;
    vkt::String warn;

    bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    if (!res) {
        vktLogE("Failed to parse gltf: {}", filename);
        return nullptr;
    }
    if (!err.empty()) {
        vktLogE("{}", err);
        return nullptr;
    }
    if (!warn.empty()) {
        vktLogW("{}", warn);
    }

    const auto& scene = model.scenes[0];

    for (size_t k = 0; k < scene.nodes.size(); k++) {
        const auto& node = model.nodes[scene.nodes[k]];
    }

    // vkt::Vector<vkt::core::Buffer> buffers{};
    // for (const auto& buf : model.buffers) {
    //     buffers.push_back(vkt::core::BufferState().setUsage().setSize(buf.data.size()).into(api).unwrap());
    // }

    // vkt::Vector<vkt::core::Sampler> samplers{};
    // for (const auto& spl : model.samplers) {
    //     samplers.push_back(vkt::core::SamplerState()
    //                            .setFilter(getMagFilter(spl.magFilter), getMinFilter(spl.minFilter))
    //                            .setAddressMode(getWrapMode(spl.wrapS), getWrapMode(spl.wrapT))
    //                            .into(api)
    //                            .unwrap());
    // }

    // vkt::Vector<vkt::core::Image> images;
    // for (const auto& img : model.images) {
    //     images.push_back(vkt::core::ImageState().setExtent(img.width, img.height, img.component).into(api).unwrap());
    // }

    // vkt::Box<Scene> scene = nullptr;
    // return scene;
    return nullptr;
}

NAMESPACE_END(vktdev)
