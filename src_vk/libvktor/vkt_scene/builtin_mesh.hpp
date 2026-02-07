#pragma once
#include "external/libglm.hpp"
#include "share/share.hpp"
#include "vktor/base/texture.hpp"
#include "vktor/core/buffer.hpp"

NAMESPACE_BEGIN(vktscn)

struct BuiltinMeshData {
    /*!
     * @brief Built-in mesh vertex layout
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

    const Vector<Vertex> vertices;
    const Vector<uint16_t> indices;

    static const BuiltinMeshData Triangle;
    static const BuiltinMeshData Rectangle;
    static const BuiltinMeshData Cube;
    static const BuiltinMeshData Frustum;
};

class BuiltinMesh : private NonCopyable {
    friend class BuiltinSubpass;

private:
    const BuiltinMeshData& data;
    vkt::core::Buffer index;
    vkt::core::Buffer vertex;
    Box<vkt::core::Sampler> sampler = nullptr;
    Box<vkt::Texture2D> texture = nullptr;

    static const Vector<VkVertexInputBindingDescription> vertex_input_bindings;
    static const Vector<VkVertexInputAttributeDescription> vertex_input_attrs;

public:
    BuiltinMesh(const BuiltinMeshData& data,
                vkt::core::Buffer&& index,
                vkt::core::Buffer&& vertex,
                Box<vkt::core::Sampler>&& sampler = nullptr,
                Box<vkt::Texture2D>&& texture = nullptr);
    BuiltinMesh(BuiltinMesh&&);

public:
    static Res<BuiltinMesh> from(const vkt::core::CoreApi& api,
                                 const BuiltinMeshData& data,
                                 Box<vkt::Texture2D>&& texture = nullptr);
};

NAMESPACE_END(vktscn)
