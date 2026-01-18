/*!
 * @brief Built-in mesh data
 */
#pragma once
#include "mesh.h"

/*!
 * @brief Mesh vertex layout for built-in data
 */
struct MeshDataVertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

using MeshData = IMesh<MeshDataVertex, uint16_t>;

extern const MeshData MESH_DATA_Triangle;
extern const MeshData MESH_DATA_Rectangle;
extern const MeshData MESH_DATA_Cube;
extern const MeshData MESH_DATA_Frustum;
