#include <glm/glm.hpp>
#include <stb_image.h>
#include <fmt/core.h>
#include <iostream>
#include "utils.h"


RMeshData loadMeshData(const MeshData& mesh) {
    RMeshData rmdata;
    rmdata.indices_num = mesh.indices.size();

    glGenVertexArrays(1, &rmdata.vao); // Vertex Array Object，顶点数组对象
    glGenBuffers(1, &rmdata.vbo); // Vertex Buffer Object，创建缓冲对象，使用vbo管理显存中的顶点数据
    glGenBuffers(1, &rmdata.ebo); // Element Buffer Object or Index Buffer Object，索引缓冲对象

    // 先绑定vao为顶点数组对象，vao会存储：
    // - glEnableVertexAttribArray和glDisableVertexAttribArray的调用；
    // - 通过glVertexAttribPointer设置的顶点属性配置；
    // - 通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象；
    // 这样，在不同的顶点数据和属性配置之间切换时，只需要绑定不同的VAO即可
    glBindVertexArray(rmdata.vao);
    glBindBuffer(GL_ARRAY_BUFFER, rmdata.vbo); // 绑定vbo到顶点缓冲对象，之后对GL_ARRAY_BUFFER的操作，即是对vbo的操作
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices_bytesize(), mesh.vertices.data(), GL_STATIC_DRAW); // 复制顶点数据到GL_ARRAY_BUFFER，即复制顶点缓冲区vbo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rmdata.ebo); // 绑定veo到索引缓冲对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices_bytesize(), mesh.indices.data(), GL_STATIC_DRAW); // 复制索引数据到veo，用于索引vbo中的顶点数据

    // 设置顶点数据和属性的对应关系
    glVertexAttribPointer(
            0, // layout(location = 0) in vec3 inPos;
            3, // 顶点属性大小，vec3由3个值组成
            GL_FLOAT, // vec3由float类型组成
            GL_FALSE, // 顶点数据是否标准化处理(Normalize)
            sizeof(MeshData::Vertex), // 顶点属性之间的间隔
            (void*)0); // 顶点数据在缓冲区的偏移
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)(9*sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0); // 解绑vao，防止被VAO的操作误修改
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // 解绑vao前，不能解绑ebo

    return rmdata;
}

RModel loadModel(const Model& model) {
    RModel rmodel;
    std::vector<std::pair<std::string, RMesh::RTexture>> loaded;

    for (const auto& mesh : model.meshes) {
        RMesh rm;

        rm.indices_num = mesh.indices.size();
        {
            glGenVertexArrays(1, &rm.vao);
            glGenBuffers(1, &rm.vbo);
            glGenBuffers(1, &rm.ebo);

            glBindVertexArray(rm.vao);

            glBindBuffer(GL_ARRAY_BUFFER, rm.vbo);
            glBufferData(GL_ARRAY_BUFFER, mesh.vertices_bytesize(), mesh.vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rm.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices_bytesize(), mesh.indices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)offsetof(Mesh::Vertex, normal));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)offsetof(Mesh::Vertex, texcoord));

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        uint32_t dn = 0, sn = 0, nn = 0, hn = 0;
        for (const auto& t : mesh.textures) {
            bool skip = false;
            for (const auto& p : loaded) {
                if (p.first == t.texpath) {
                    rm.texs.push_back(p.second);
                    skip = true;
                    break;
                }
            }

            if (!skip) {
                RMesh::RTexture rt;

                rt.id = loadTexture(fmt::format("{}/{}", model.dir, t.texpath));
                // 按纹理“类型+索引”命名材质的属性
                switch (t.type) {
                    case Mesh::Texture::Type::Diffuse:
                        rt.name = "material_diffuse_" + std::to_string(dn++);
                        break;
                    case Mesh::Texture::Type::Specular:
                        rt.name = "material_specular_" + std::to_string(sn++);
                        break;
                    case Mesh::Texture::Type::Normal:
                        rt.name = "material_normal_" + std::to_string(nn++);
                        break;
                    case Mesh::Texture::Type::Height:
                        rt.name = "material_height_" + std::to_string(hn++);
                        break;
                }
                rm.texs.push_back(rt);
                loaded.push_back(std::make_pair(t.texpath, rt));
            }
        }

        rmodel.push_back(std::move(rm));
    }

    return rmodel;
}

void drawModel(const RModel& rmodel, Shader& shader) {
    shader.use();

    for (const auto& mesh : rmodel) {
        for (uint32_t k = 0; k < mesh.texs.size(); k ++) {
            shader.setInt(mesh.texs[k].name, k);
            glActiveTexture(GL_TEXTURE0 + k);
            glBindTexture(GL_TEXTURE_2D, mesh.texs[k].id);
        }

        glBindVertexArray(mesh.vao);
        glDrawElements(GL_TRIANGLES, mesh.indices_num, GL_UNSIGNED_INT, 0);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);
}

GLuint createTexture(int tw, int th) {
    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return id;
}

GLuint loadTexture(const std::string& filepath) {
    GLuint id = 0;
    glGenTextures(1, &id); // 生成1个纹理

    int wid, hei, nch;
    unsigned char* data;
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(filepath.c_str(), &wid, &hei, &nch, 0);
    if (data) {
        GLenum fmt = GL_RGB;
        if (1 == nch) fmt = GL_RED;
        else if (3 == nch) fmt = GL_RGB;
        else if (4 == nch) fmt = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id); // 绑定为2D纹理
        glTexImage2D(
            GL_TEXTURE_2D,
            0, // Mipmap level
            GL_RGBA8, // Internal texture format on GPU
            wid, hei, // Size
            0, // Border, must be 0
            fmt, // Pixels data format
            GL_UNSIGNED_BYTE, // Pixels data channel type
            data); // Pixels data
        glGenerateMipmap(GL_TEXTURE_2D);

        // 设置纹理参数
        // 纹理环绕方式：纹理“面积”比“实际渲染的面积”要小
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        // 设置缩小（Minify）纹理过滤：纹理分辨率高，而渲染的物体很小，纹理怎么采样
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // 设置放大（Magnify）纹理过滤：纹理分辨率低，但是渲染的物体很大，纹理怎么插值
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        throw eformat("Failed to load texture: {}", filepath);
    }
    stbi_image_free(data);

    return id;
}

GLuint loadCubemap(const std::vector<std::string>& faces) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int wid, hei, nch;
    unsigned char* data;
    stbi_set_flip_vertically_on_load(false); // Cubemap不能flip
    for (unsigned int k = 0; k < faces.size(); k ++) {
        data = stbi_load(faces[k].c_str(), &wid, &hei, &nch, 0);
        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + k,
                0, GL_RGBA8, wid, hei, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            throw eformat("Failed to load cubemap texture: {}", faces[k]);
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return id;
}
