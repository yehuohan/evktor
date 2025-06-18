#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <vktor/base/texture.hpp>
#include <vktor/core/buffer.hpp>
#include <vktor/core/sampler.hpp>

NAMESPACE_BEGIN(vktscn)

struct MeshData {
    alignas(16) glm::mat4 model;
};

struct Mesh {
public:
    // vkt::CRef<vkt::core::Buffer> index;
    VkBuffer index = VK_NULL_HANDLE;
    size_t index_offset = 0;
    size_t index_count = 0;
    VkIndexType index_type = VkIndexType::VK_INDEX_TYPE_UINT16;

    // vkt::CRef<vkt::core::Buffer> position;
    // vkt::CRef<vkt::core::Buffer> texcoord;
    // vkt::CRef<vkt::core::Buffer> normal;
    // vkt::CRef<vkt::core::Buffer> tangent;
    VkBuffer position = VK_NULL_HANDLE;
    VkBuffer texcoord = VK_NULL_HANDLE;
    VkBuffer normal = VK_NULL_HANDLE;
    VkBuffer tangent = VK_NULL_HANDLE;
    size_t position_offset = 0;
    size_t texcoord_offset = 0;
    size_t normal_offset = 0;
    size_t tangent_offset = 0;

    int32_t tex_idx = -1;

    glm::mat4 model;
    VkDescriptorSet desc_set;
};

struct Node {
public:
    vkt::Vector<Mesh> meshes;
};

class Scene {
public:
    vkt::Vector<vkt::core::Sampler> samplers;
    vkt::Vector<vkt::core::Buffer> buffers;
    vkt::Vector<vkt::Texture> textures;

    vkt::Vector<Node> nodes;
};

NAMESPACE_END(vktscn)
