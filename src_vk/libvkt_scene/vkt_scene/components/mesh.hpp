#pragma once
#include "../component.hpp"
#include "../node.hpp"
#include "buffer.hpp"

NAMESPACE_BEGIN(vktscn)

struct VertexAttribute {
    VkFormat format = VK_FORMAT_UNDEFINED;
    uint32_t stride = 0;
    uint32_t offset = 0;
};

class SubMesh : public Component {
private:
    SubBuffer index_buffer{};
    HashMap<String, SubBuffer> vertex_buffers{};
    HashMap<String, VertexAttribute> vertex_attrs{};

public:
    VkIndexType index_type = VkIndexType::VK_INDEX_TYPE_UINT16;
    uint32_t index_count = 0;  // For vkCmdDrawIndexed
    uint32_t vertex_count = 0; // For vkCmdDraw

public:
    SubMesh(const String& name = "") : Component(name) {}
    virtual ~SubMesh() = default;

    virtual std::type_index getType() const override {
        return typeid(SubMesh);
    }

public:
    inline void setIndexBuffer(const Buffer& buffer, VkDeviceSize offset) {
        index_buffer = SubBuffer(buffer, offset);
    }
    inline const SubBuffer* getIndexBuffer() const {
        return index_buffer.buffer ? &index_buffer : nullptr;
    }
    inline void setVertexBuffer(const String& attr_name, const Buffer& buffer, VkDeviceSize offset) {
        vertex_buffers.insert({attr_name, SubBuffer(buffer, offset)});
    }
    const SubBuffer* getVertexBuffer(const String& attr_name) const;
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
