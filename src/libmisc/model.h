/*!
 * @brief Model data
 */
#pragma once
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh.h"


class Model {
public:
    std::string dir;
    std::vector<Mesh> meshes;

public:
    Model() : dir("") { }
    Model(const std::string& filepath) {
        load(filepath);
    }

    /*!
     * @brief 使用assimp加载模型文件
     */
    void load(const std::string& objpath);

    void clear() { this->meshes.clear(); }

private:

    /*!
     * @brief 处理所有的节点数据
     */
    void processNode(aiNode* node, const aiScene* scene);

    /*!
     * @brief Parse aiMesh into Mesh
     */
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    /*!
     * @brief Parse aiMaterial into Mesh::Texture
     */
    std::vector<Mesh::Texture> processMaterial(aiMaterial* mat, aiTextureType type, Mesh::Texture::Type tex_type);
};
