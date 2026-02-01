#include "node.hpp"

NAMESPACE_BEGIN(vktscn)

Node::Node(const size_t id, const String& name) : transform{*this}, id{id}, name{name} {}

void Node::setParent(Node& p) {
    parent = &p;
    transform.invalidateWorldMatrix(); // Need update this node's global world transform
}

Component* Node::getComponent(const std::type_index& index) {
    if (auto it = components.find(index); it != components.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

NAMESPACE_END(vktscn)
