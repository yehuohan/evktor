#pragma once
#include "components/transform.hpp"
#include <memory>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <typeindex>

NAMESPACE_BEGIN(vktscn)

class Component;

class Node {
public:
    Node(const size_t id, const std::string& name);

    virtual ~Node() = default;

    const size_t get_id() const;

    const std::string& get_name() const;

    Transform& get_transform() {
        return transform;
    }

    void set_parent(Node& parent);

    Node* get_parent() const;

    void add_child(Node& child);

    const std::vector<Node*>& get_children() const;

    void set_component(Component& component);

    template <class T>
    inline T& get_component() {
        return dynamic_cast<T&>(get_component(typeid(T)));
    }

    Component& get_component(const std::type_index index);

    template <class T>
    bool has_component() {
        return has_component(typeid(T));
    }

    bool has_component(const std::type_index index);

private:
    size_t id;

    std::string name;

    Transform transform;

    Node* parent{nullptr};

    std::vector<Node*> children;

    std::unordered_map<std::type_index, Component*> components;
};

NAMESPACE_END(vktscn)
