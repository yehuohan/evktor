#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdint>
#include <string>


/*!
 * @brief Mesh vertex layout
 *
 * ```glsl
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexcoord;
 * ```
 */
struct __MeshVertex {
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 normal = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec2 texcoord = glm::vec2(0.0f, 0.0f);
};

/*!
 * @brief Mesh texture
 */
struct __MeshTexture {
    enum Type {
        Diffuse,
        Specular,
        Normal,
        Height,
    };
    Type type;
    std::string texpath;
};


/*!
 * @brief Mesh interface
 *
 */
template<typename V = __MeshVertex, typename I = uint32_t, typename T = __MeshTexture>
class IMesh {
public:
    using Vertex = V;
    using Index = I;
    using Texture = T;

    std::vector<Vertex>     vertices;
    std::vector<Index>      indices;
    std::vector<Texture>    textures;

    IMesh(std::vector<Vertex>&& v, std::vector<Index>&& i, std::vector<Texture>&& t = std::vector<Texture>(0))
        : vertices(std::move(v))
        , indices(std::move(i))
        , textures(std::move(t))
    { }

    IMesh(IMesh&& rhs)
        : vertices(std::move(rhs.vertices))
        , indices(std::move(rhs.indices))
        , textures(std::move(rhs.textures))
    { }

    size_t vertices_bytesize() const { return this->vertices.size() * sizeof(Vertex); }

    size_t indices_bytesize() const { return this->indices.size() * sizeof(Index); }
};

using Mesh = IMesh<__MeshVertex, uint32_t, __MeshTexture>;
