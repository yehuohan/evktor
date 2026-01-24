#pragma once
#include "component.hpp"
#include "transform.hpp"

NAMESPACE_BEGIN(vktscn)

class Node {
private:
    Node* parent = nullptr;
    Vector<Node*> children{};
    Transform transform;

    size_t id;
    String name;
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
    inline Transform& getTransform() {
        return transform;
    }
    inline const Transform& getTransform() const {
        return transform;
    }

public:
    inline size_t getId() const {
        return id;
    }
    inline const std::string& getName() const {
        return name;
    }
    /**
     * @brief Set or insert a component to this node
     */
    inline void setComponent(Component& component) {
        components[component.getType()] = &component;
    }
    /**
     * @brief Get component of this node
     *
     * Must check the return != nullptr
     */
    Component* getComponent(const std::type_index& index);
    template <class T>
    inline T* getComponent() {
        return dynamic_cast<T*>(getComponent(typeid(T)));
    }
};

NAMESPACE_END(vktscn)
