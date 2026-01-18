#pragma once
#include "../component.hpp"
#include "../node.hpp"
#include <vktor/core/buffer.hpp>

NAMESPACE_BEGIN(vktscn)

struct VertexAttribute {
    VkFormat format = VK_FORMAT_UNDEFINED;
    uint32_t stride = 0;
    uint32_t offset = 0;
};

class SubMesh : public Component {
private:
    Box<vkt::core::Buffer> index_buffer = nullptr;
    HashMap<String, vkt::core::Buffer> vertex_buffers{};
    HashMap<String, VertexAttribute> vertex_attrs{};

public:
    VkIndexType index_type = VkIndexType::VK_INDEX_TYPE_UINT16;
    VkDeviceSize index_offset = 0;  // For vkCmdBindIndexBuffer
    std::uint32_t index_count = 0;  // For vkCmdDrawIndexed
    std::uint32_t vertex_count = 0; // For vkCmdDraw

public:
    SubMesh(const String& name = "") : Component(name) {}
    virtual ~SubMesh() = default;

    virtual std::type_index getType() const override {
        return typeid(SubMesh);
    }

public:
    inline void setIndexBuffer(Box<vkt::core::Buffer>&& buffer) {
        index_buffer = std::move(buffer);
    }
    inline const vkt::core::Buffer* getIndexBuffer() const {
        return index_buffer ? index_buffer.get() : nullptr;
    }
    inline void setVertexBuffer(const String& attr_name, vkt::core::Buffer&& buffer) {
        vertex_buffers.insert({attr_name, std::move(buffer)});
    }
    const vkt::core::Buffer* getVertexBuffer(const String& attr_name) const;
    inline void setAttribute(const String& attr_name, const VertexAttribute& attribute) {
        vertex_attrs[attr_name] = attribute;
    }
    const VertexAttribute* getAttribute(const String& attr_name) const;
};

class Mesh : public Component {
private:
    Vector<SubMesh*> subs{};
    Vector<Node*> nodes{};

public:
    Mesh(const String& name = "") : Component(name) {}
    virtual ~Mesh() = default;

    virtual std::type_index getType() const override {
        return typeid(Mesh);
    }

public:
    inline void addNode(Node& node) {
        nodes.push_back(&node);
    }
    inline const Vector<Node*>& getNodes() const {
        return nodes;
    }
    inline void addSubmesh(SubMesh& sub) {
        subs.push_back(&sub);
    }
    const Vector<SubMesh*>& getSubmeshes() const {
        return subs;
    }
};

NAMESPACE_END(vktscn)
