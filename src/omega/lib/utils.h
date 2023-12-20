/*!
 * @file utils.h
 * @brief 相关纹理加载等函数
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include <glad/gl.h>
#include <string>
#include <vector>
#include "model.h"
#include "mesh_data.h"
#include "shader.h"


/*!
 * @brief Rendering context of MeshData
 *
 */
struct RMeshData {
    uint32_t indices_num;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};

RMeshData loadMeshData(const MeshData& mesh);

/*!
 * @brief Rendering context of Mesh
 *
 */
struct RMesh {
    uint32_t indices_num;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    struct RTexture {
        GLuint id;
        std::string name;
    };
    std::vector<RTexture> texs;

    RMesh() { }
    RMesh(RMesh&& rhs)
        : indices_num(rhs.indices_num)
        , vao(rhs.vao), vbo(rhs.vbo), ebo(rhs.ebo)
        , texs(std::move(rhs.texs))
    { }
};

using RModel = std::vector<RMesh>;

RModel loadModel(const Model& model);

void drawModel(const RModel& rmodel, Shader& shader);

/*!
 * @brief 创建纹理对象
 *
 * 纹理对象使用RGBA8格式。
 *
 */
GLuint createTexture(int tw, int th);

/*!
 * @brief 加载纹理图片
 *
 * 纹理对象根据图片通道，选择使用RED、RGB或RGBA8格式。
 *
 */
GLuint loadTexture(const std::string& filepath);

/*!
 * @brief 加载立方体贴图
 *
 * loads a cubemap texture from 6 individual texture faces
 * order:
 * +X (right)
 * -X (left)
 * +Y (top)
 * -Y (bottom)
 * +Z (front)
 * -Z (back)
 */
GLuint loadCubemap(const std::vector<std::string>& faces);

#endif /* end of include guard: UTILS_H */
