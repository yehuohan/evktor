#pragma once
#include "component.hpp"
#include "material.hpp"

NAMESPACE_BEGIN(vktscn)

struct VertexAttribute {
    VkFormat format = VK_FORMAT_UNDEFINED;
    uint32_t stride = 0;
    uint32_t offset = 0;
};

class MeshSub : public Component {
private:
    HashMap<String, VertexAttribute> vertex_attributes;
    const Material* material{nullptr};

public:
    MeshSub(const String& name = {}) : Component(name) {}

    virtual ~MeshSub() = default;

    virtual operator std::type_index() override {
        return typeid(MeshSub);
    }
};

NAMESPACE_END(vktscn)
