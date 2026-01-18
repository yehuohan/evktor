#pragma once
#include "component.hpp"
#include "components/transform.hpp"

NAMESPACE_BEGIN(vktscn)

class Node {
private:
    Node* parent{nullptr};
    Vector<Node*> children{};

    size_t id;
    String name;
    Transform transform;
    HashMap<std::type_index, Component*> components{};

public:
    Node(const size_t id, const String& name);
    virtual ~Node() = default;

public:
    void setParent(Node& parent);
    inline Node* getParent() const {
        return parent;
    }
    inline void addChild(Node& child) {
        children.push_back(&child);
    }
    inline const Vector<Node*>& getChildren() const {
        return children;
    }

public:
    inline size_t getId() const {
        return id;
    }
    inline const std::string& getName() const {
        return name;
    }
    inline Transform& getTransform() {
        return transform;
    }
    inline bool hasComponent(const std::type_index index) const {
        return components.count(index) > 0;
    }
    template <class T>
    inline bool hasComponent() const {
        return hasComponent(typeid(T));
    }
    inline Component& getComponent(const std::type_index index) {
        return *components.at(index);
    }
    template <class T>
    inline T& getComponent() {
        return dynamic_cast<T&>(getComponent(typeid(T)));
    }
    void setComponent(Component& component);
};

NAMESPACE_END(vktscn)
