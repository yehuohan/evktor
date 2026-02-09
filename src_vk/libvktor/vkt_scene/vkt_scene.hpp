#pragma once
#include "component.hpp"
#include "components/camera.hpp"
#include "components/image.hpp"
#include "components/material.hpp"
#include "components/mesh.hpp"
#include "components/sampler.hpp"
#include "components/texture.hpp"
#include "node.hpp"
#include "subpasses/builtin_subpass.hpp"
#include "subpasses/geometry_subpass.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vktscn)

/**
 * @brief Vktor scene
 *
 * - All nodes and components are stored in `Scene` with ownership
 * - Reference to nodes and components should use raw pointer
 */
class Scene : private NonCopyable {
private:
    String name;
    size_t root_node = 0;
    Vector<Box<Node>> nodes{};
    HashMap<std::type_index, Vector<Box<Component>>> components{};

public:
    Scene() = default;
    Scene(const String& name) : name(name) {}

public:
    inline void addNode(Box<Node>&& _node) {
        nodes.push_back(std::move(_node));
    }
    inline void setNodes(Vector<Box<Node>>&& _nodes, size_t _root_node) {
        nodes = std::move(_nodes);
        root_node = _root_node;
    }
    inline void setRootNode(size_t _root_node) {
        root_node = _root_node;
    }
    inline Node* getRootNode() {
        return root_node < nodes.size() ? nodes[root_node].get() : nullptr;
    }
    Node* findNode(const String& node_name);

public:
    void addComponent(Box<Component>&& component);

    inline void setComponents(const std::type_index& index, Vector<Box<Component>>&& _components);
    template <class T>
    void setComponents(Vector<Box<T>>&& _components);

    const Vector<Box<Component>>& getComponents(const std::type_index& index) const;
    template <class T>
    Vector<T*> getComponents() const;

    template <class T>
    inline void clearComponents();
};

inline void Scene::setComponents(const std::type_index& index, Vector<Box<Component>>&& _components) {
    components[index] = std::move(_components);
}

template <class T>
void Scene::setComponents(Vector<Box<T>>&& _components) {
    Vector<Box<Component>> res(_components.size());
    std::transform(_components.begin(), _components.end(), res.begin(), [](Box<T>& comp) -> Box<Component> {
        return Box<Component>(std::move(comp)); // Cast component type T to the base `Component` pointer
    });
    setComponents(typeid(T), std::move(res));
}

template <class T>
Vector<T*> Scene::getComponents() const {
    Vector<T*> res{};
    auto& comps = getComponents(typeid(T));
    if (!comps.empty()) {
        res.resize(comps.size());
        std::transform(comps.begin(), comps.end(), res.begin(), [](const Box<Component>& comp) -> T* {
            return dynamic_cast<T*>(comp.get()); // Cast base `Component` pointer to component type T
        });
    }
    return res;
}

template <class T>
inline void Scene::clearComponents() {
    setComponents(typeid(T), {});
}

NAMESPACE_END(vktscn)
