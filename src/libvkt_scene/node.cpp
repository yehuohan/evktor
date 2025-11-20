#include "node.hpp"
#include "component.hpp"
#include "components/transform.hpp"

NAMESPACE_BEGIN(vktscn)

Node::Node(const size_t id, const String& name) : id{id}, name{name}, transform{*this} {
    setComponent(transform);
}

void Node::setParent(Node& p) {
    parent = &p;
    transform.invalidateWorldMatrix();
}

void Node::setComponent(Component& component) {
    auto it = components.find(component);
    if (it != components.end()) {
        it->second = &component;
    } else {
        components.insert({(std::type_index)component, &component});
    }
}

NAMESPACE_END(vktscn)
