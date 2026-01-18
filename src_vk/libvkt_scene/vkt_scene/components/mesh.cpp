#include "mesh.hpp"

NAMESPACE_BEGIN(vktscn)

const vkt::core::Buffer* SubMesh::getVertexBuffer(const String& attr_name) const {
    if (auto it = vertex_buffers.find(attr_name); it != vertex_buffers.end()) {
        return &it->second;
    }
    return nullptr;
}

const VertexAttribute* SubMesh::getAttribute(const String& attr_name) const {
    if (auto it = vertex_attrs.find(attr_name); it != vertex_attrs.end()) {
        return &it->second;
    }
    return nullptr;
}

NAMESPACE_END(vktscn)
