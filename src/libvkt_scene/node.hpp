#pragma once
#include "component.hpp"
#include "components/transform.hpp"
#include <memory>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <typeindex>

NAMESPACE_BEGIN(vktscn)

/**
 * @brief Tree structure node for tinygltf::Node
 */
class Node {
private:
    Node* parent{nullptr};
    Vector<Node*> children{};

    size_t id;                                         /**< The index at tinygltf::Model.nodes */
    String name;                                       /**< tinygltf::Node.name */
    Transform transform;                               /**< tinygltf::Node.rotation/scale ... */
    HashMap<std::type_index, Component*> components{}; /**< tinygltf::Node.camera/mesh/light ... */

public:
    Node(const size_t id, const String& name);
    virtual ~Node() = default;

    operator const size_t() const {
        return id;
    }
    operator const String&() const {
        return name;
    }

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

    void setComponent(Component& component);
    inline Component& getComponent(const std::type_index index) {
        return *components.at(index);
    }
    template <class T>
    inline T& getComponent() {
        return dynamic_cast<T&>(getComponent(typeid(T)));
    }
    inline bool hasComponent(const std::type_index index) const {
        return components.count(index) > 0;
    }
    template <class T>
    inline bool hasComponent() const {
        return hasComponent(typeid(T));
    }

    inline Transform& getTransform() {
        return transform;
    }
};

NAMESPACE_END(vktscn)
