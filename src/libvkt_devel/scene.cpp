#include "scene.hpp"
#include "vktor/core/buffer.hpp"
#include <vktor/core/image.hpp>
#include <vktor/core/sampler.hpp>

using namespace vkt;

NAMESPACE_BEGIN(vktdev)

inline VkFilter getMinFilter(int min_filter) {
    switch (min_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: return VK_FILTER_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return VK_FILTER_LINEAR;
    default:
        {
            vktLogW("Unsupported min filter: %d", min_filter);
            return VK_FILTER_NEAREST;
        }
    }
};

inline VkFilter getMagFilter(int mag_filter) {
    switch (mag_filter) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST: return VK_FILTER_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_LINEAR: return VK_FILTER_LINEAR;
    default:
        {
            vktLogW("Unsupported mag filter: %d", mag_filter);
            return VK_FILTER_NEAREST;
        }
    }
};

inline VkSamplerMipmapMode getMipmapMode(int mipmap_mode) {
    switch (mipmap_mode) {
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    default:
        {
            vktLogW("Unsupported mipmap mode: %d", mipmap_mode);
            return VK_SAMPLER_MIPMAP_MODE_LINEAR;
        }
    }
};

inline VkSamplerAddressMode getWrapMode(int wrap_mode) {
    switch (wrap_mode) {
    case TINYGLTF_TEXTURE_WRAP_REPEAT: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    default:
        {
            vktLogW("Unsupported wrap mode: %d", wrap_mode);
            return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        }
    }
};

inline VkFormat getFormat(int component, int component_type) {
    if (1 == component) {
        switch (component_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32_SFLOAT;
        };
    } else if (2 == component) {
        switch (component_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8G8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8G8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16G16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16G16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32G32_SFLOAT;
        };
    } else if (3 == component) {
        switch (component_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8G8B8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16G16B16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32G32B32_SFLOAT;
        };
    } else if (4 == component) {
        switch (component_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8G8B8A8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8A8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16G16B16A16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16A16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32G32B32A32_SFLOAT;
        };
    }
    vktLogW("Unsupported component = {} and type = {}", component, component_type);
    return VK_FORMAT_R8G8B8A8_UNORM;
}

vkt::Box<Scene> SceneLoader::load(const vkt::String& filename) {
    tinygltf::Model gmodel;
    tinygltf::TinyGLTF gloader;
    vkt::String err;
    vkt::String warn;

    bool res = gloader.LoadASCIIFromFile(&gmodel, &err, &warn, filename);
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

    vkt::Box<Scene> scene = newBox<Scene>();

    for (const auto& spl : gmodel.samplers) {
        scene->samplers.push_back(vkt::core::SamplerState()
                                      .setFilter(getMagFilter(spl.magFilter), getMinFilter(spl.minFilter))
                                      .setAddressMode(getWrapMode(spl.wrapS), getWrapMode(spl.wrapT))
                                      .into(api)
                                      .unwrap());
    }

    for (const auto& buf : gmodel.buffers) {
        scene->buffers.push_back(vkt::core::BufferState()
                                     .setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                                     .setSize(buf.data.size())
                                     .into(api)
                                     .unwrap());
    }

    for (size_t k = 0; k < gmodel.images.size(); k++) {
        const auto& img = gmodel.images[k];
        scene->textures.push_back(vkt::Texture2D::from(api,
                                                       getFormat(img.component, img.pixel_type),
                                                       VkExtent2D{u32(img.width), u32(img.height)},
                                                       vkt::Texture::UsageBits::Sampled)
                                      .unwrap());
    }

    // Load the default scene of index 0
    const auto& gscene = gmodel.scenes[0];

    for (size_t kn = 0; kn < gscene.nodes.size(); kn++) {
        const auto& gnode = gmodel.nodes[gscene.nodes[kn]];
        const auto& gmesh = gmodel.meshes[gnode.mesh];
        for (size_t kp = 0; kp < gmesh.primitives.size(); kp++) {
            const auto& gprimitive = gmesh.primitives[kp];
            const auto& gaccessor = gmodel.accessors[gprimitive.attributes.at("POSITION")];
            // gprimitive.indices;
            // [POSITION]: count=3175, type=VEC3, buffer=Buffer.0 + 892756
            // [NORMAL]: count=3175, type=VEC3, buffer=Buffer.0 + 956256
            // [TANGENT]: count=3175, type=VEC4, buffer=Buffer.0 + 994356
            // [TEXCOORD_0]: count=3175, type=VEC2, buffer=Buffer.0 + 930856
            // std::cout << ai << std::endl;
            // gmodel.accessors;
        }
    }

    return scene;
}

NAMESPACE_END(vktdev)
