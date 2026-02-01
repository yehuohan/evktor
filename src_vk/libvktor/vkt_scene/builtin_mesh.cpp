#include "builtin_mesh.hpp"

NAMESPACE_BEGIN(vktscn)

// clang-format off
const BuiltinMeshData BuiltinMeshData::Triangle {
    Vector<BuiltinMeshData::Vertex> {
        // position,           color,              normal,             texcoord
        {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下角
        {{ 1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // 右下角
        {{ 0.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}, // 上中
    },
    Vector<uint16_t> {
        0, 1, 2,
    },
};

const BuiltinMeshData BuiltinMeshData::Rectangle {
    Vector<BuiltinMeshData::Vertex> {
        // position,           color,              normal,             texcoord
        {{ 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // 右上
        {{ 1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // 右下
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
        {{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // 左上
    },
    Vector<uint16_t> {
        0, 1, 2,
        2, 3, 0,
    },
};

const BuiltinMeshData BuiltinMeshData::Cube {
    Vector<BuiltinMeshData::Vertex> {
        // position,            color,              normal,               texcoord
        // Back face
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // bottom-left
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // top-left
        // Front face
        {{-1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // bottom-left
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 0.0}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}}, // bottom-right
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 0.0}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}}, // top-right
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}}, // top-right
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}}, // top-left
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // bottom-left
        // Left face
        {{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-right
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // top-left
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-left
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-left
        {{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-right
        {{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-right
        // Right face
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-left
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // top-right
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-right
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-left
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-left
        // Bottom face
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}, // top-right
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}}, // top-left
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-left
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-left
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-right
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}, // top-right
        // Top face
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}, // top-left
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}}, // top-right
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-right
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}, // top-left
        {{-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-left
    },
    Vector<uint16_t> {
         0,  1,  2,  3,  4,  5,
         6,  7,  8,  9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35,
    },
};

const BuiltinMeshData BuiltinMeshData::Frustum {
    Vector<BuiltinMeshData::Vertex> {
        // position,            color,              normal,               texcoord
        // Back face
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // bottom-left
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // top-left
        // Front face
        {{-0.5f, -0.5f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // bottom-left
        {{ 0.5f, -0.5f,  1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}}, // bottom-right
        {{ 0.5f,  0.5f,  1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}}, // top-right
        {{ 0.5f,  0.5f,  1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}}, // top-right
        {{-0.5f,  0.5f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}}, // top-left
        {{-0.5f, -0.5f,  1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // bottom-left
        // Left face
        {{-0.5f,  0.5f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-right
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // top-left
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-left
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-left
        {{-0.5f, -0.5f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-right
        {{-0.5f,  0.5f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-right
        // Right face
        {{ 0.5f,  0.5f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-left
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // top-right
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // bottom-right
        {{ 0.5f,  0.5f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // top-left
        {{ 0.5f, -0.5f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-left
        // Bottom face
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}, // top-right
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}}, // top-left
        {{ 0.5f, -0.5f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-left
        {{ 0.5f, -0.5f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-left
        {{-0.5f, -0.5f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-right
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}, // top-right
        // Top face
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}, // top-left
        {{ 0.5f,  0.5f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}}, // top-right
        {{ 0.5f,  0.5f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // bottom-right
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}, // top-left
        {{-0.5f,  0.5f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // bottom-left
    },
    Vector<uint16_t> {
         0,  1,  2,  3,  4,  5,
         6,  7,  8,  9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35,
    },
};
// clang-format on

const Vector<VkVertexInputBindingDescription> BuiltinMesh::vertex_input_bindings{
    VkVertexInputBindingDescription{0, sizeof(BuiltinMeshData::Vertex), VK_VERTEX_INPUT_RATE_VERTEX}
};

const Vector<VkVertexInputAttributeDescription> BuiltinMesh::vertex_input_attrs{
    VkVertexInputAttributeDescription{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(BuiltinMeshData::Vertex,      pos)},
    VkVertexInputAttributeDescription{1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(BuiltinMeshData::Vertex,    color)},
    VkVertexInputAttributeDescription{2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(BuiltinMeshData::Vertex,   normal)},
    VkVertexInputAttributeDescription{3, 0,    VK_FORMAT_R32G32_SFLOAT, offsetof(BuiltinMeshData::Vertex, texcoord)},
};

BuiltinMesh::BuiltinMesh(const BuiltinMeshData& data,
                         vkt::core::Buffer&& index,
                         vkt::core::Buffer&& vertex,
                         Box<vkt::core::Sampler>&& sampler,
                         Box<vkt::Texture2D>&& texture)
    : data(data)
    , index(std::move(index))
    , vertex(std::move(vertex))
    , sampler(std::move(sampler))
    , texture(std::move(texture)) {}

BuiltinMesh::BuiltinMesh(BuiltinMesh&& rhs)
    : data(rhs.data)
    , index(std::move(rhs.index))
    , vertex(std::move(rhs.vertex))
    , sampler(std::move(rhs.sampler))
    , texture(std::move(rhs.texture)) {}

Res<BuiltinMesh> BuiltinMesh::from(const vkt::core::CoreApi& api, const BuiltinMeshData& data, Box<vkt::Texture2D>&& texture) {
    auto res_index = vkt::core::BufferState{}
                         .setSize(data.indices.size() * sizeof(uint16_t))
                         .setUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                         .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                         .into(api);
    OnErr(res_index);
    auto index = res_index.unwrap();
    index.copyFrom(data.indices.data());

    auto res_vertex = vkt::core::BufferState{}
                          .setSize(data.vertices.size() * sizeof(BuiltinMeshData::Vertex))
                          .setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
                          .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                          .into(api);
    OnErr(res_vertex);
    auto vertex = res_vertex.unwrap();
    vertex.copyFrom(data.vertices.data());

    Box<vkt::core::Sampler> sampler = nullptr;
    if (texture) {
        auto res_sampler = vkt::core::SamplerState().setNearest().into(api);
        OnErr(res_sampler);
        sampler = newBox<vkt::core::Sampler>(res_sampler.unwrap());
    }

    return Ok(BuiltinMesh(data, std::move(index), std::move(vertex), std::move(sampler), std::move(texture)));
}

NAMESPACE_END(vktscn)
