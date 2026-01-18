#include "gltf_helper.hpp"
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <vktor/core/command_buffer.hpp>
#include <vktor/core/command_pool.hpp>

using namespace vkt;
using namespace vktscn;

size_t GLTFLoader::accessorStride(uint32_t index) const {
    assert(index < gmodel.accessors.size());
    auto& accessor = gmodel.accessors[index];

    assert(accessor.bufferView < gmodel.bufferViews.size());
    auto& buffer_view = gmodel.bufferViews[accessor.bufferView];

    int stride = accessor.ByteStride(buffer_view);
    assert(stride >= 0);

    return static_cast<size_t>(stride);
};

Vector<uint8_t> GLTFLoader::accessorData(uint32_t index) const {
    assert(index < gmodel.accessors.size());
    auto& accessor = gmodel.accessors[index];

    assert(accessor.bufferView < gmodel.bufferViews.size());
    auto& buffer_view = gmodel.bufferViews[accessor.bufferView];

    assert(buffer_view.buffer < gmodel.buffers.size());
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
            vktLogW("Invalid gltf accessor component type: {}, {}", accessor.componentType, accessor.type);
            break;
        }
    }
    return format;
};

Box<Sampler> GLTFLoader::parseSampler(size_t gsampler_index) const {
    const auto& gsampler = gmodel.samplers[gsampler_index];
    auto core_sampler = core::SamplerState(vktFmt("{}", gsampler.name))
                            .setFilter(toMagFilter(gsampler.magFilter), toMinFilter(gsampler.minFilter))
                            .setAddressMode(toWrapMode(gsampler.wrapS), toWrapMode(gsampler.wrapT))
                            .into(api)
                            .unwrap();
    return newBox<Sampler>(gsampler.name, std::move(core_sampler));
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

void GLTFLoader::loadSceneSamplers(vktscn::Scene& scene) const {
    Vector<Box<Sampler>> samplers(gmodel.samplers.size());
    for (size_t ks = 0; ks < gmodel.samplers.size(); ks++) {
        samplers[ks] = parseSampler(ks);
    }
    scene.setComponents(std::move(samplers));
}

void GLTFLoader::loadSceneMeshes(Scene& scene) const {
    // Prepare command buffer
    auto _queue = api.transferQueue().unwrap();
    auto& queue = _queue.get();
    auto cmdpool = core::CommandPoolState("GLTFLoader.loadSceneMeshes.CommandPool")
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueFamilyIndex(queue.family_index)
                       .into(api)
                       .unwrap();
    auto _cmdbuf = cmdpool.allocate(core::CommandPool::Level::Primary, "GLTFLoader.loadSceneMeshes.CommandBuffer").unwrap();
    auto& cmdbuf = _cmdbuf.get();

    // Load meshes
    for (const auto& gmesh : gmodel.meshes) {
        auto mesh = newBox<Mesh>(gmesh.name);

        for (size_t kp = 0; kp < gmesh.primitives.size(); kp++) {
            auto gprimitive = gmesh.primitives[kp];
            auto submesh_name = vktFmt("{}.primitive[{}]", gmesh.name, kp);
            auto submesh = newBox<SubMesh>(submesh_name);

            // Load vertex buffers
            for (const auto& [_attr_name, attr_idx] : gprimitive.attributes) {
                auto attr_name = _attr_name;
                std::transform(attr_name.begin(), attr_name.end(), attr_name.begin(), ::tolower);
                if (attr_name == "position") {
                    submesh->vertex_count = u32(accessorCount(attr_idx));
                }

                // Vertex buffer
                auto vertex_data = accessorData(attr_idx);
                auto vertex_buffer = core::BufferState(vktFmt("{}.vertex[{}]", submesh_name, _attr_name))
                                         .setSize(vertex_data.size())
                                         .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
                                         .into(api)
                                         .unwrap();
                auto staging = core::BufferState()
                                   .setSize(vertex_data.size())
                                   .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                   .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                   .into(api)
                                   .unwrap();
                staging.copyFrom(vertex_data.data());
                cmdbuf.begin();
                cmdbuf.cmdCopyBuffer(staging, vertex_buffer);
                cmdbuf.end();
                queue.submit(cmdbuf);
                queue.waitIdle();
                submesh->setVertexBuffer(attr_name, std::move(vertex_buffer));

                // Vertex attribute
                VertexAttribute vertex_attr{};
                vertex_attr.format = accessorFormat(attr_idx);
                vertex_attr.stride = u32(accessorStride(attr_idx));
                submesh->setAttribute(attr_name, vertex_attr);
            }

            // Load index buffer
            if (gprimitive.indices >= 0) {
                submesh->index_count = u32(accessorCount(gprimitive.indices));

                auto index_data = accessorData(gprimitive.indices);
                auto format = accessorFormat(gprimitive.indices);
                switch (format) {
                case VK_FORMAT_R8_UINT:
                    // Convert uint8 data into uint16 data to use uint16 index type
                    index_data = convertUnderlyingDataStride(index_data, 1, 2);
                    submesh->index_type = VK_INDEX_TYPE_UINT16;
                    break;
                case VK_FORMAT_R16_UINT: submesh->index_type = VK_INDEX_TYPE_UINT16; break;
                case VK_FORMAT_R32_UINT: submesh->index_type = VK_INDEX_TYPE_UINT32; break;
                default: vktLogE("{}.index has unsupported format type: {}", submesh_name, VkStr(VkFormat, format)); break;
                }

                auto index_buffer = newBox<core::Buffer>(
                    core::BufferState(vktFmt("{}.index", submesh_name))
                        .setSize(index_data.size())
                        .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                        .into(api)
                        .unwrap());
                auto staging = core::BufferState()
                                   .setSize(index_data.size())
                                   .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                   .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                   .into(api)
                                   .unwrap();
                staging.copyFrom(index_data.data());
                cmdbuf.begin();
                cmdbuf.cmdCopyBuffer(staging, *index_buffer);
                cmdbuf.end();
                queue.submit(cmdbuf);
                queue.waitIdle();
                submesh->setIndexBuffer(std::move(index_buffer));
            } else {
                if (submesh->vertex_count == 0) {
                    vktLogE("{} doesn't has neither vertex position nor index buffer", submesh_name);
                }
            }

            // TODO: Setup material
            // if (gprimitive.material >= 0) {
            //     submesh->setMaterial(*materials[gprimitive.material]);
            // } else {
            //     submesh->setMaterial(*default_material);
            // }

            mesh->addSubmesh(*submesh);
            scene.addComponent(std::move(submesh));
        }

        scene.addComponent(std::move(mesh));
    }
}

void GLTFLoader::loadSceneNodes(vktscn::Scene& scene) const {
    auto meshes = scene.getComponents<Mesh>();

    // Load nodes
    Vector<Box<Node>> nodes{};
    for (size_t kn = 0; kn < gmodel.nodes.size(); kn++) {
        const auto& gnode = gmodel.nodes[kn];

        auto node = parseNode(kn);

        // Node with mesh
        if (gnode.mesh >= 0) {
            assert(gnode.mesh < meshes.size());
            auto& mesh = meshes[gnode.mesh];
            node->setComponent(*mesh);
            mesh->addNode(*node); // 一个Mesh可能存在于多个节点
        }
        nodes.push_back(std::move(node));
    }
}

Box<Scene> GLTFLoader::loadScene(int32_t scene_index) const {
    Box<Scene> scene = newBox<Scene>();

    loadSceneSamplers(*scene);
    loadSceneMeshes(*scene);
    loadSceneNodes(*scene);

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
