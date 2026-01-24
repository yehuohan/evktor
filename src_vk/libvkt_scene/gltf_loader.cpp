#include "gltf_helper.hpp"
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <queue>
#include <vktor/core/command_buffer.hpp>
#include <vktor/core/command_pool.hpp>

using namespace vkt;
using namespace vktscn;

size_t GLTFLoader::accessorCount(uint32_t index) const {
    assert(index < gmodel.accessors.size());
    return gmodel.accessors[index].count;
}

std::tuple<size_t, size_t, size_t> GLTFLoader::accessorBufferOffsetStride(uint32_t index) const {
    assert(index < gmodel.accessors.size());
    auto& accessor = gmodel.accessors[index];

    assert(0 <= accessor.bufferView && static_cast<size_t>(accessor.bufferView) < gmodel.bufferViews.size());
    auto& buffer_view = gmodel.bufferViews[accessor.bufferView];

    int buffer = buffer_view.buffer;
    assert(0 <= buffer && static_cast<size_t>(buffer) < gmodel.buffers.size());

    size_t offset = accessor.byteOffset + buffer_view.byteOffset;

    int stride = accessor.ByteStride(buffer_view);
    assert(stride >= 0);

    return std::make_tuple(static_cast<size_t>(buffer), offset, static_cast<size_t>(stride));
}

Vector<uint8_t> GLTFLoader::accessorData(uint32_t index) const {
    assert(index < gmodel.accessors.size());
    auto& accessor = gmodel.accessors[index];

    assert(0 <= accessor.bufferView && static_cast<size_t>(accessor.bufferView) < gmodel.bufferViews.size());
    auto& buffer_view = gmodel.bufferViews[accessor.bufferView];

    assert(0 <= buffer_view.buffer && static_cast<size_t>(buffer_view.buffer) < gmodel.buffers.size());
    auto& buffer = gmodel.buffers[buffer_view.buffer];

    int stride = accessor.ByteStride(buffer_view);
    assert(stride >= 0);
    size_t byte_start = accessor.byteOffset + buffer_view.byteOffset;
    size_t byte_end = byte_start + accessor.count * stride;

    return {buffer.data.begin() + byte_start, buffer.data.begin() + byte_end};
};

VkFormat GLTFLoader::accessorFormat(uint32_t index) const {
    assert(index < gmodel.accessors.size());
    auto& accessor = gmodel.accessors[index];

    VkFormat format;
    switch (accessor.componentType) {
    case TINYGLTF_COMPONENT_TYPE_BYTE:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,       VK_FORMAT_R8_SINT},
                {  TINYGLTF_TYPE_VEC2,     VK_FORMAT_R8G8_SINT},
                {  TINYGLTF_TYPE_VEC3,   VK_FORMAT_R8G8B8_SINT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R8G8B8A8_SINT}
            };
            static const Map<int, VkFormat> mapped_format_normalize = {
                {TINYGLTF_TYPE_SCALAR,       VK_FORMAT_R8_SNORM},
                {  TINYGLTF_TYPE_VEC2,     VK_FORMAT_R8G8_SNORM},
                {  TINYGLTF_TYPE_VEC3,   VK_FORMAT_R8G8B8_SNORM},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R8G8B8A8_SNORM}
            };
            if (accessor.normalized) {
                format = mapped_format_normalize.at(accessor.type);
            } else {
                format = mapped_format.at(accessor.type);
            }
            break;
        }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,       VK_FORMAT_R8_UINT},
                {  TINYGLTF_TYPE_VEC2,     VK_FORMAT_R8G8_UINT},
                {  TINYGLTF_TYPE_VEC3,   VK_FORMAT_R8G8B8_UINT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R8G8B8A8_UINT}
            };
            static const Map<int, VkFormat> mapped_format_normalize = {
                {TINYGLTF_TYPE_SCALAR,       VK_FORMAT_R8_UNORM},
                {  TINYGLTF_TYPE_VEC2,     VK_FORMAT_R8G8_UNORM},
                {  TINYGLTF_TYPE_VEC3,   VK_FORMAT_R8G8B8_UNORM},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R8G8B8A8_UNORM}
            };
            if (accessor.normalized) {
                format = mapped_format_normalize.at(accessor.type);
            } else {
                format = mapped_format.at(accessor.type);
            }
            break;
        }
    case TINYGLTF_COMPONENT_TYPE_SHORT:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R16_SINT},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R16G16_SINT},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R16G16B16_SINT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R16G16B16A16_SINT}
            };
            static const Map<int, VkFormat> mapped_format_normalize = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R16_SNORM},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R16G16_SNORM},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R16G16B16_SNORM},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R16G16B16A16_SNORM}
            };
            if (accessor.normalized) {
                format = mapped_format_normalize.at(accessor.type);
            } else {
                format = mapped_format.at(accessor.type);
            }
            break;
        }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R16_UINT},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R16G16_UINT},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R16G16B16_UINT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R16G16B16A16_UINT}
            };
            static const Map<int, VkFormat> mapped_format_normalize = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R16_UNORM},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R16G16_UNORM},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R16G16B16_UNORM},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R16G16B16A16_UNORM}
            };
            if (accessor.normalized) {
                format = mapped_format_normalize.at(accessor.type);
            } else {
                format = mapped_format.at(accessor.type);
            }
            break;
        }
    case TINYGLTF_COMPONENT_TYPE_INT:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R32_SINT},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R32G32_SINT},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R32G32B32_SINT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R32G32B32A32_SINT}
            };
            format = mapped_format.at(accessor.type);
            break;
        }
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R32_UINT},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R32G32_UINT},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R32G32B32_UINT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R32G32B32A32_UINT}
            };
            format = mapped_format.at(accessor.type);
            break;
        }
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        {
            static const Map<int, VkFormat> mapped_format = {
                {TINYGLTF_TYPE_SCALAR,          VK_FORMAT_R32_SFLOAT},
                {  TINYGLTF_TYPE_VEC2,       VK_FORMAT_R32G32_SFLOAT},
                {  TINYGLTF_TYPE_VEC3,    VK_FORMAT_R32G32B32_SFLOAT},
                {  TINYGLTF_TYPE_VEC4, VK_FORMAT_R32G32B32A32_SFLOAT}
            };
            format = mapped_format.at(accessor.type);
            break;
        }
    default:
        {
            format = VK_FORMAT_UNDEFINED;
            vktLogE("Invalid gltf accessor component type: {}, {}", accessor.componentType, accessor.type);
            break;
        }
    }
    return format;
};

VkFormat GLTFLoader::imageFormat(uint32_t index) const {
    assert(index < gmodel.images.size());
    auto& image = gmodel.images[index];
    int component = image.component;
    int pixel_type = image.pixel_type;

    if (1 == component) {
        switch (pixel_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32_SFLOAT;
        };
    } else if (2 == component) {
        switch (pixel_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8G8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8G8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16G16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16G16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32G32_SFLOAT;
        };
    } else if (3 == component) {
        switch (pixel_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8G8B8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16G16B16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32G32B32_SFLOAT;
        };
    } else if (4 == component) {
        switch (pixel_type) {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return VK_FORMAT_R8G8B8A8_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return VK_FORMAT_R8G8B8A8_UNORM;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return VK_FORMAT_R16G16B16A16_SNORM;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VK_FORMAT_R16G16B16A16_UNORM;
        case TINYGLTF_COMPONENT_TYPE_INT:
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VK_FORMAT_R32G32B32A32_SFLOAT;
        };
    }
    vktLogE("Invalid gltf image: component = {}, pixel type = {}", component, pixel_type);
    return VK_FORMAT_UNDEFINED;
}

Box<Node> GLTFLoader::parseNode(size_t gnode_index) const {
    const auto& gnode = gmodel.nodes[gnode_index];

    auto node = newBox<Node>(gnode_index, gnode.name);
    auto& transform = node->getComponent<Transform>();
    if (!gnode.translation.empty()) {
        glm::vec3 translation;
        std::transform(gnode.translation.begin(),
                       gnode.translation.end(),
                       glm::value_ptr(translation),
                       TypeCast<double, float>{});
        transform.setTranslation(translation);
    }
    if (!gnode.rotation.empty()) {
        glm::quat rotation;
        std::transform(gnode.rotation.begin(), gnode.rotation.end(), glm::value_ptr(rotation), TypeCast<double, float>{});
        transform.setRotation(rotation);
    }

    if (!gnode.scale.empty()) {
        glm::vec3 scale;
        std::transform(gnode.scale.begin(), gnode.scale.end(), glm::value_ptr(scale), TypeCast<double, float>{});
        transform.setScale(scale);
    }
    if (!gnode.matrix.empty()) {
        glm::mat4 matrix;
        std::transform(gnode.matrix.begin(), gnode.matrix.end(), glm::value_ptr(matrix), TypeCast<double, float>{});
        transform.setMatrix(matrix);
    }
    return node;
}

void GLTFLoader::loadSamplers(Scene& scene) const {
    for (size_t k = 0; k < gmodel.samplers.size(); k++) {
        const auto& gsampler = gmodel.samplers[k];

        auto sampler = core::SamplerState(vktFmt("{}", gsampler.name))
                           .setFilter(toMagFilter(gsampler.magFilter), toMinFilter(gsampler.minFilter))
                           .setAddressMode(toWrapMode(gsampler.wrapS), toWrapMode(gsampler.wrapT))
                           .into(api)
                           .unwrap();

        scene.addComponent(newBox<Sampler>(std::move(sampler), gsampler.name));
    }
}

void GLTFLoader::loadBuffers(Scene& scene) const {
    // Prepare command buffer
    auto _queue = api.transferQueue().unwrap();
    auto& queue = _queue.get();
    auto cmdpool = core::CommandPoolState("GLTFLoader.loadSceneBuffers.CommandPool")
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueFamilyIndex(queue.family_index)
                       .into(api)
                       .unwrap();
    auto _cmdbuf = cmdpool.allocate(core::CommandPool::Level::Primary, "GLTFLoader.loadSceneBuffers.CommandBuffer").unwrap();
    auto& cmdbuf = _cmdbuf.get();

    // Load buffers
    for (size_t k = 0; k < gmodel.buffers.size(); k++) {
        const auto& gbuffer = gmodel.buffers[k];

        auto buffer = core::BufferState(vktFmt("{}", k, gbuffer.name))
                          .setSize(gbuffer.data.size())
                          .setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                                    VK_BUFFER_USAGE_TRANSFER_DST_BIT)
                          .into(api)
                          .unwrap();
        auto staging = core::BufferState()
                           .setSize(gbuffer.data.size())
                           .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                           .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                           .into(api)
                           .unwrap();
        staging.copyFrom(gbuffer.data.data());
        cmdbuf.begin();
        cmdbuf.cmdCopyBuffer(staging, buffer);
        cmdbuf.end();
        queue.submit(cmdbuf);
        queue.waitIdle();

        scene.addComponent(newBox<Buffer>(std::move(buffer), gbuffer.name));
    }
}

void GLTFLoader::loadImages(Scene& scene) const {
    // Prepare command buffer
    auto _queue = api.graphicsQueue().unwrap();
    auto& queue = _queue.get();
    auto cmdpool = core::CommandPoolState("GLTFLoader.loadSceneImages.CommandPool")
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueFamilyIndex(queue.family_index)
                       .into(api)
                       .unwrap();
    auto _cmdbuf = cmdpool.allocate(core::CommandPool::Level::Primary, "GLTFLoader.loadSceneImages.CommandBuffer").unwrap();
    auto& cmdbuf = _cmdbuf.get();

    for (size_t k = 0; k < gmodel.images.size(); k++) {
        const auto& gimage = gmodel.images[k];

        uint32_t mip_levels = u32(std::floor(std::log2(std::max<int>(gimage.width, gimage.height)))) + 1;
        auto& image_data = gimage.image;
        if (image_data.empty()) {
            vktLogE("Invalid gltf image {} data, maybe it's an image from web", gimage.name);
        }
        auto image = core::ImageState(vktFmt("{}", gimage.name))
                         .setFormat(imageFormat(k))
                         .setExtent(VkExtent2D{u32(gimage.width), u32(gimage.height)})
                         .setUsage(VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                                   VK_IMAGE_USAGE_TRANSFER_DST_BIT)
                         .setMipLevels(mip_levels)
                         .setSamples(VK_SAMPLE_COUNT_1_BIT)
                         .into(api)
                         .unwrap();
        auto imageview = core::ImageViewState(vktFmt("{}.view", gimage.name)).setFromImage(image).into(api).unwrap();
        auto staging = core::BufferState()
                           .setSize(image_data.size())
                           .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                           .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                           .into(api)
                           .unwrap();
        staging.copyFrom(image_data.data());
        core::Arg arg(image);
        cmdbuf.begin();
        cmdbuf.cmdImageMemoryBarrier(arg,
                                     VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                     VK_PIPELINE_STAGE_TRANSFER_BIT,
                                     VK_ACCESS_NONE,
                                     VK_ACCESS_TRANSFER_WRITE_BIT,
                                     VK_IMAGE_LAYOUT_UNDEFINED,
                                     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        cmdbuf.cmdCopyBufferToImage(staging, arg);
        cmdbuf.cmdGenImageMips(arg, VK_FILTER_LINEAR);
        cmdbuf.end();
        queue.submit(cmdbuf);
        queue.waitIdle();

        scene.addComponent(newBox<Image>(std::move(image), std::move(imageview), gimage.name));
    }
}

void GLTFLoader::loadTextures(Scene& scene) const {
    auto images = scene.getComponents<Image>();
    auto samplers = scene.getComponents<Sampler>();

    auto default_sampler = newBox<Sampler>(
        core::SamplerState(vktFmt("{}", "default.sampler"))
            .setLinear()
            .setAddressMode(VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT)
            .into(api)
            .unwrap(),
        "default.sampler");
    bool require_default_sampler = false;

    for (size_t k = 0; k < gmodel.textures.size(); k++) {
        const auto& gtexture = gmodel.textures[k];

        auto texture = newBox<Texture>(gtexture.name);
        assert(0 <= gtexture.source && static_cast<size_t>(gtexture.source) < images.size());
        texture->setImage(*images[gtexture.source]);
        if (0 <= gtexture.sampler) {
            assert(static_cast<size_t>(gtexture.sampler) < samplers.size());
            texture->setSampler(*samplers[gtexture.sampler]);
        } else {
            texture->setSampler(*default_sampler);
            require_default_sampler = true;
        }

        scene.addComponent(std::move(texture));
    }

    if (require_default_sampler) {
        scene.addComponent(std::move(default_sampler));
    }
}

void GLTFLoader::loadMaterials(Scene& scene) const {
    auto textures = scene.getComponents<Texture>();

    for (size_t k = 0; k < gmodel.materials.size(); k++) {
        const auto& gmaterial = gmodel.materials[k];

        auto material = std::make_unique<PBRMaterial>(gmaterial.name);

        // Basic
        material->emissive_factor = glm::vec3(gmaterial.emissiveFactor[0],
                                              gmaterial.emissiveFactor[1],
                                              gmaterial.emissiveFactor[2]);
        if (gmaterial.alphaMode == "BLEND") {
            material->alpha_mode = AlphaMode::Blend;
        } else if (gmaterial.alphaMode == "OPAQUE") {
            material->alpha_mode = AlphaMode::Opaque;
        } else if (gmaterial.alphaMode == "MASK") {
            material->alpha_mode = AlphaMode::Mask;
        }
        material->alpha_cutoff = gmaterial.alphaCutoff;
        material->double_sided = gmaterial.doubleSided;
        if (0 <= gmaterial.emissiveTexture.index && static_cast<size_t>(gmaterial.emissiveTexture.index)) {
            material->setTexture("emissive_texture", *textures[gmaterial.emissiveTexture.index]);
        }

        // Additional
        material->normal_scale = gmaterial.normalTexture.scale;
        material->occlusion_strength = gmaterial.occlusionTexture.strength;
        if (0 <= gmaterial.normalTexture.index && static_cast<size_t>(gmaterial.normalTexture.index)) {
            material->setTexture("normal_texture", *textures[gmaterial.normalTexture.index]);
        }
        if (0 <= gmaterial.occlusionTexture.index && static_cast<size_t>(gmaterial.occlusionTexture.index)) {
            material->setTexture("occlusion_texture", *textures[gmaterial.occlusionTexture.index]);
        }

        // Metallic-Roughness
        const auto& mr = gmaterial.pbrMetallicRoughness;
        material->base_color_factor = glm::vec4(mr.baseColorFactor[0],
                                                mr.baseColorFactor[1],
                                                mr.baseColorFactor[2],
                                                mr.baseColorFactor[3]);
        material->metallic_factor = mr.metallicFactor;
        material->roughness_factor = mr.roughnessFactor;
        if (0 <= mr.baseColorTexture.index && static_cast<size_t>(mr.baseColorTexture.index) < textures.size()) {
            material->setTexture("base_color_texture", *textures[mr.baseColorTexture.index]);
        }
        if (0 <= mr.metallicRoughnessTexture.index &&
            static_cast<size_t>(mr.metallicRoughnessTexture.index) < textures.size()) {
            material->setTexture("metallic_roughness_texture", *textures[mr.metallicRoughnessTexture.index]);
        }

        scene.addComponent(std::move(material));
    }
}

void GLTFLoader::loadMeshes(Scene& scene) const {
    auto buffers = scene.getComponents<Buffer>();
    auto pbr_materials = scene.getComponents<PBRMaterial>();

    auto default_pbr_material = newBox<PBRMaterial>("default.pbr_material");
    bool require_default_pbr_material = false;

    // Load meshes
    for (const auto& gmesh : gmodel.meshes) {
        auto mesh = newBox<Mesh>(gmesh.name);

        for (size_t kp = 0; kp < gmesh.primitives.size(); kp++) {
            const auto& gprimitive = gmesh.primitives[kp];

            auto submesh_name = vktFmt("{}.primitive[{}]", gmesh.name, kp);
            auto submesh = newBox<SubMesh>(submesh_name);

            // Load vertex buffers
            for (const auto& [_attr_name, attr_idx] : gprimitive.attributes) {
                auto attr_name = _attr_name;
                std::transform(attr_name.begin(), attr_name.end(), attr_name.begin(), ::tolower);
                if (attr_name == "position") {
                    submesh->vertex_count = u32(accessorCount(attr_idx));
                }

                auto [buffer, offset, stride] = accessorBufferOffsetStride(attr_idx);
                submesh->setVertexBuffer(attr_name, *buffers[buffer], offset);

                // Vertex attribute
                VertexAttribute vertex_attr{};
                vertex_attr.format = accessorFormat(attr_idx);
                vertex_attr.stride = u32(stride);
                submesh->setAttribute(attr_name, vertex_attr);
            }

            // Load index buffer
            if (gprimitive.indices >= 0) {
                submesh->index_count = u32(accessorCount(gprimitive.indices));

                auto [buffer, offset, _] = accessorBufferOffsetStride(gprimitive.indices);
                submesh->setIndexBuffer(*buffers[buffer], offset);

                auto format = accessorFormat(gprimitive.indices);
                switch (format) {
                case VK_FORMAT_R8_UINT: submesh->index_type = VK_INDEX_TYPE_UINT8; break;
                case VK_FORMAT_R16_UINT: submesh->index_type = VK_INDEX_TYPE_UINT16; break;
                case VK_FORMAT_R32_UINT: submesh->index_type = VK_INDEX_TYPE_UINT32; break;
                default: vktLogE("{}.index has unsupported format type: {}", submesh_name, VkStr(VkFormat, format)); break;
                }
            } else {
                if (submesh->vertex_count == 0) {
                    vktLogE("{} doesn't has neither vertex position nor index buffer", submesh_name);
                }
            }

            // Setup material
            if (0 <= gprimitive.material && static_cast<size_t>(gprimitive.material) < pbr_materials.size()) {
                submesh->setMaterial(*pbr_materials[gprimitive.material]);
            } else {
                submesh->setMaterial(*default_pbr_material);
                require_default_pbr_material = true;
            }

            mesh->addSubmesh(*submesh);
            scene.addComponent(std::move(submesh));
        }

        scene.addComponent(std::move(mesh));
    }

    if (require_default_pbr_material) {
        scene.addComponent(std::move(default_pbr_material));
    }
}

void GLTFLoader::loadSceneNodes(Scene& scene, int32_t scene_index) const {
    if (scene_index < 0) {
        scene_index = gmodel.defaultScene;
    }
    assert(static_cast<size_t>(scene_index) < gmodel.scenes.size());

    auto meshes = scene.getComponents<Mesh>();

    // Load nodes
    Vector<Box<Node>> nodes{};
    for (size_t k = 0; k < gmodel.nodes.size(); k++) {
        const auto& gnode = gmodel.nodes[k];

        auto node = parseNode(k);

        // Setup node's mesh
        if (gnode.mesh >= 0) {
            assert(static_cast<size_t>(gnode.mesh) < meshes.size());
            auto& mesh = meshes[gnode.mesh];
            node->setComponent(*mesh);
            mesh->addNode(*node); // 一个Mesh可能存在于多个节点
        }
        nodes.push_back(std::move(node));
    }

    // Construct scene's nodes
    const tinygltf::Scene* gscene = &gmodel.scenes[scene_index];
    auto root_node = newBox<Node>(0, gscene->name);

    std::queue<std::pair<Node*, int>> traverse_nodes{};
    for (auto node_index : gscene->nodes) {
        traverse_nodes.push(std::make_pair(root_node.get(), node_index));
    }
    while (!traverse_nodes.empty()) {
        auto [traverse_root_node, current_node_index] = traverse_nodes.front();
        traverse_nodes.pop();

        assert(static_cast<size_t>(current_node_index) < nodes.size());
        auto& current_node = nodes[current_node_index];
        current_node->setParent(*traverse_root_node);
        traverse_root_node->addChild(*current_node);

        for (auto child_node_index : gmodel.nodes[current_node_index].children) {
            traverse_nodes.push(std::make_pair(current_node.get(), child_node_index));
        }
    }

    nodes.push_back(std::move(root_node));
    scene.setNodes(std::move(nodes), nodes.size() - 1);
}

Box<Scene> GLTFLoader::loadScene(int32_t scene_index) const {
    Box<Scene> scene = newBox<Scene>();

    loadSamplers(*scene);
    loadBuffers(*scene);
    loadImages(*scene);
    loadTextures(*scene);                // Require images, samplers
    loadMaterials(*scene);               // Require textures
    loadMeshes(*scene);                  // Require buffers, materials
    loadSceneNodes(*scene, scene_index); // Require meshes

    return scene;
}

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
