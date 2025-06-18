#include "gltf_loader.hpp"
#include <algorithm>
#include <vktor/core/image.hpp>
#include <vktor/rendering/render_frame.hpp>

using namespace vkt;

NAMESPACE_BEGIN(vktscn)

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

template <class T, class Y>
struct TypeCast {
    Y operator()(T value) const noexcept {
        return static_cast<Y>(value);
    }
};

Box<Scene> GLTFLoader::loadScene(const String& filename, int32_t scene_index) {
    std::string err;
    std::string warn;
    tinygltf::TinyGLTF gloader;

    vktOut("Load scene from {}", filename);
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
    return loadScene(scene_index);
}

Box<Scene> GLTFLoader::loadScene(int32_t scene_index) {
    Box<Scene> scene = newBox<Scene>();

    // Load samplers
    Vector<Box<core::Sampler>> samplers(gmodel.samplers.size());
    for (size_t k = 0; k < gmodel.samplers.size(); k++) {
        // samplers[k] = newBox<core::Sampler>(std::move(core::SamplerState().into(api).unwrap()));
    }

    auto& queue = api.transferQueue().unwrap().get();
    auto cmdpool = core::CommandPoolState()
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueFamilyIndex(queue.family_index)
                       .into(api)
                       .unwrap();
    auto& cmdbuf = cmdpool.allocate(core::CommandPool::Level::Primary).unwrap().get();

    for (const auto& spl : gmodel.samplers) {
        scene->samplers.push_back(core::SamplerState()
                                      .setFilter(getMagFilter(spl.magFilter), getMinFilter(spl.minFilter))
                                      .setAddressMode(getWrapMode(spl.wrapS), getWrapMode(spl.wrapT))
                                      .into(api)
                                      .unwrap());
    }

    for (const auto& buf : gmodel.buffers) {
        scene->buffers.push_back(core::BufferState()
                                     .setSize(buf.data.size())
                                     .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                               VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                                     .into(api)
                                     .unwrap());
        auto staging = core::BufferState()
                           .setSize(buf.data.size())
                           .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                           .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                           .into(api)
                           .unwrap();
        staging.copyFrom(buf.data.data());
        cmdbuf.begin();
        cmdbuf.cmdCopyBuffer(staging, scene->buffers.back());
        cmdbuf.end();
        queue.submit(cmdbuf);
        queue.waitIdle();
    }

    for (size_t k = 0; k < gmodel.images.size(); k++) {
        const auto& img = gmodel.images[k];
        uint32_t mip_levels = static_cast<uint32_t>(std::floor(std::log2(std::max<int>(img.width, img.height)))) + 1;
        scene->textures.push_back(Texture2D::from(api,
                                                  getFormat(img.component, img.pixel_type),
                                                  VkExtent2D{u32(img.width), u32(img.height)},
                                                  Texture::Sampled | Texture::Transfer,
                                                  mip_levels)
                                      .unwrap());
        auto staging = core::BufferState()
                           .setSize(img.image.size())
                           .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                           .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                           .into(api)
                           .unwrap();
        core::Arg arg(scene->textures.back().getImage());
        staging.copyFrom(img.image.data());
        cmdbuf.begin();
        cmdbuf.cmdImageMemoryBarrier(arg,
                                     VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                     VK_PIPELINE_STAGE_TRANSFER_BIT,
                                     0,
                                     VK_ACCESS_TRANSFER_WRITE_BIT,
                                     VK_IMAGE_LAYOUT_UNDEFINED,
                                     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        cmdbuf.cmdCopyBufferToImage(staging, arg);
        cmdbuf.cmdGenImageMips(arg, VK_FILTER_LINEAR);
        cmdbuf.end();
        queue.submit(cmdbuf);
        queue.waitIdle();
    }

    // Load the default scene of index 0
    const auto& gscene = gmodel.scenes[0];

    for (size_t kn = 0; kn < gscene.nodes.size(); kn++) {
        const auto& gnode = gmodel.nodes[gscene.nodes[kn]];
        const auto& gmesh = gmodel.meshes[gnode.mesh];

        glm::mat4 node_mat(1.0);
        if (gnode.matrix.size() == 16) {
            std::transform(gnode.matrix.begin(), gnode.matrix.end(), glm::value_ptr(node_mat), TypeCast<double, float>{});
            std::cout << node_mat[0][0] << std::endl;
        } else {
            glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
            glm::quat rotation = glm::quat(1.0, 0.0, 0.0, 0.0);
            glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
            if (!gnode.translation.empty()) {
                std::transform(gnode.translation.begin(),
                               gnode.translation.end(),
                               glm::value_ptr(translation),
                               TypeCast<double, float>{});
            }
            if (!gnode.rotation.empty()) {
                std::transform(gnode.rotation.begin(),
                               gnode.rotation.end(),
                               glm::value_ptr(rotation),
                               TypeCast<double, float>{});
            }
            if (!gnode.scale.empty()) {
                std::transform(gnode.scale.begin(), gnode.scale.end(), glm::value_ptr(scale), TypeCast<double, float>{});
            }
            node_mat = glm::translate(glm::mat4(1.0), translation) * glm::mat4_cast(rotation) *
                       glm::scale(glm::mat4(1.0), scale);
        }

        scene->nodes.push_back(Node{});
        auto& node = scene->nodes.back();

        // for (const auto& child : gnode.children) {}

        for (size_t kp = 0; kp < gmesh.primitives.size(); kp++) {
            // gprimitive.indices;
            // [POSITION]: count=3175, type=VEC3, buffer=Buffer.0 + 892756
            // [NORMAL]: count=3175, type=VEC3, buffer=Buffer.0 + 956256
            // [TANGENT]: count=3175, type=VEC4, buffer=Buffer.0 + 994356
            // [TEXCOORD_0]: count=3175, type=VEC2, buffer=Buffer.0 + 930856
            const auto& gprimitive = gmesh.primitives[kp];
            node.meshes.push_back(Mesh{});
            auto& mesh = node.meshes.back();

            if (gprimitive.material > -1) {
                mesh.tex_idx = gmodel.materials[gprimitive.material].pbrMetallicRoughness.baseColorTexture.index;
            }

            mesh.model = node_mat;

            {
                // Index
                const auto& gaccessor = gmodel.accessors[gprimitive.indices];
                const auto& gbufview = gmodel.bufferViews[gaccessor.bufferView];
                mesh.index = scene->buffers[gbufview.buffer];
                mesh.index_offset = gbufview.byteOffset + gaccessor.byteOffset;
                mesh.index_count = gaccessor.count;
                mesh.index_type = gaccessor.type == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT ? VkIndexType::VK_INDEX_TYPE_UINT32
                                                                                         : VkIndexType::VK_INDEX_TYPE_UINT16;
            }
            {
                // Position
                if (gprimitive.attributes.find("POSITION") != gprimitive.attributes.end()) {
                    const auto& gaccessor = gmodel.accessors[gprimitive.attributes.at("POSITION")];
                    const auto& gbufview = gmodel.bufferViews[gaccessor.bufferView];
                    mesh.position = scene->buffers[gbufview.buffer];
                    mesh.position_offset = gbufview.byteOffset + gaccessor.byteOffset;
                }
            }
            {
                // Texcoord
                if (gprimitive.attributes.find("TEXCOORD_0") != gprimitive.attributes.end()) {
                    const auto& gaccessor = gmodel.accessors[gprimitive.attributes.at("TEXCOORD_0")];
                    const auto& gbufview = gmodel.bufferViews[gaccessor.bufferView];
                    mesh.texcoord = scene->buffers[gbufview.buffer];
                    mesh.texcoord_offset = gbufview.byteOffset + gaccessor.byteOffset;
                }
            }
            {
                // Normal
                if (gprimitive.attributes.find("NORMAL") != gprimitive.attributes.end()) {
                    const auto& gaccessor = gmodel.accessors[gprimitive.attributes.at("NORMAL")];
                    const auto& gbufview = gmodel.bufferViews[gaccessor.bufferView];
                    mesh.normal = scene->buffers[gbufview.buffer];
                    mesh.normal_offset = gbufview.byteOffset + gaccessor.byteOffset;
                }
            }
            {
                // Tangent
                if (gprimitive.attributes.find("TANGENT") != gprimitive.attributes.end()) {
                    const auto& gaccessor = gmodel.accessors[gprimitive.attributes.at("TANGENT")];
                    const auto& gbufview = gmodel.bufferViews[gaccessor.bufferView];
                    mesh.tangent = scene->buffers[gbufview.buffer];
                    mesh.tangent_offset = gbufview.byteOffset + gaccessor.byteOffset;
                }
            }
        }
    }

    return scene;
}

NAMESPACE_END(vktscn)
