#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <vulkan/vulkan.h>

NAMESPACE_BEGIN(vktdev)

/**
 * @brief Simple mesh
 */
class SimpleMesh {
public:
    using Index = uint16_t;
    /*!
     * @brief Built-in simple mesh vertex layout
     *
     * ```glsl
     * layout(location = 0) in vec3 inp_pos;
     * layout(location = 1) in vec3 inp_color;
     * layout(location = 2) in vec3 inp_normal;
     * layout(location = 3) in vec2 inp_texcoord;
     * ```
     */
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

    struct UBO {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    const Vector<Vertex> vertices;
    const Vector<Index> indices;

public:
    SimpleMesh(Vector<Vertex>&& vertices, Vector<Index>&& indices)
        : vertices(std::move(vertices))
        , indices(std::move(indices)) {}
    SimpleMesh(SimpleMesh&& rhs) : vertices(std::move(rhs.vertices)), indices(std::move(rhs.indices)) {}

    /** Indices size in bytes */
    size_t indices_size() const {
        return indices.size() * sizeof(Index);
    }

    /** Vertices size in bytes */
    size_t vertices_size() const {
        return vertices.size() * sizeof(Vertex);
    }

    VkVertexInputBindingDescription vertexBindings(uint32_t binding = 0) const {
        return VkVertexInputBindingDescription{
            binding,
            sizeof(SimpleMesh::Vertex),
            VK_VERTEX_INPUT_RATE_VERTEX,
        };
    }

    Vector<VkVertexInputAttributeDescription> vertexAttributes(uint32_t binding = 0) const {
        Vector<VkVertexInputAttributeDescription> attrs{};
        attrs.push_back(VkVertexInputAttributeDescription{
            0,
            binding,
            VK_FORMAT_R32G32B32_SFLOAT,
            offsetof(SimpleMesh::Vertex, pos),
        });
        attrs.push_back(VkVertexInputAttributeDescription{
            1,
            binding,
            VK_FORMAT_R32G32B32_SFLOAT,
            offsetof(SimpleMesh::Vertex, color),
        });
        attrs.push_back(VkVertexInputAttributeDescription{
            2,
            binding,
            VK_FORMAT_R32G32B32_SFLOAT,
            offsetof(SimpleMesh::Vertex, normal),
        });
        attrs.push_back(VkVertexInputAttributeDescription{
            3,
            binding,
            VK_FORMAT_R32G32_SFLOAT,
            offsetof(SimpleMesh::Vertex, texcoord),
        });
        return attrs;
    }
};

extern const SimpleMesh MESH_Triangle;
extern const SimpleMesh MESH_Rectangle;
extern const SimpleMesh MESH_Cube;
extern const SimpleMesh MESH_Frustum;

NAMESPACE_END(vktdev)
