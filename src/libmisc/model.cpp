#include <cstdint>
#include "model.h"
#include "efmt.h"


void Model::load(const std::string& objpath) {
    Assimp::Importer imp;
    const aiScene* scene = imp.ReadFile(objpath,
        aiProcess_Triangulate | // 将模型所有图元转换成三角形
        aiProcess_FlipUVs);     // 翻转y轴

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
        throw eformat("{}", imp.GetErrorString());
    }

    this->dir = objpath.substr(0, objpath.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    // 处理当前节点所有网络
    for (uint32_t k = 0; k < node->mNumMeshes; k ++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[k]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // 处理所有子节点
    for (uint32_t k = 0; k < node->mNumChildren; k ++) {
        processNode(node->mChildren[k], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<Mesh::Index> indices;
    std::vector<Mesh::Texture> textures;

    uint32_t k;
    for (k = 0; k < mesh->mNumVertices; k ++) {
        Mesh::Vertex v;
        v.pos = glm::vec3(mesh->mVertices[k].x, mesh->mVertices[k].y, mesh->mVertices[k].z);
        if (mesh->mNormals) {
            v.normal = glm::vec3(mesh->mNormals[k].x, mesh->mNormals[k].y, mesh->mNormals[k].z);
        }
        if (mesh->mTextureCoords[0]) {
            v.texcoord = glm::vec2(mesh->mTextureCoords[0][k].x, mesh->mTextureCoords[0][k].y);
        }
        vertices.push_back(v);
    }
    for (k = 0; k < mesh->mNumFaces; k ++) {
        aiFace face = mesh->mFaces[k];
        for (uint32_t j = 0; j < face.mNumIndices; j ++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        using MType = Mesh::Texture::Type;
        std::vector<Mesh::Texture> diffuse = processMaterial(material, aiTextureType_DIFFUSE, MType::Diffuse);
        std::vector<Mesh::Texture> specular = processMaterial(material, aiTextureType_SPECULAR, MType::Specular);
        std::vector<Mesh::Texture> normal = processMaterial(material, aiTextureType_SPECULAR, MType::Normal);
        std::vector<Mesh::Texture> height = processMaterial(material, aiTextureType_SPECULAR, MType::Height);
        textures.insert(textures.end(), diffuse.begin(), diffuse.end());
        textures.insert(textures.end(), specular.begin(), specular.end());
        textures.insert(textures.end(), normal.begin(), normal.end());
        textures.insert(textures.end(), height.begin(), height.end());
    }

    return Mesh(std::move(vertices), std::move(indices), std::move(textures));
}

std::vector<Mesh::Texture> Model::processMaterial(aiMaterial* mat, aiTextureType type, Mesh::Texture::Type tex_type) {
    std::vector<Mesh::Texture> textures;

    for (uint32_t k = 0; k < mat->GetTextureCount(type); k ++) {
        aiString filepath;
        mat->GetTexture(type, k, &filepath);
        Mesh::Texture t;
        t.type = tex_type;
        t.texpath = filepath.C_Str();
        textures.push_back(t);
    }

    return textures;
}
