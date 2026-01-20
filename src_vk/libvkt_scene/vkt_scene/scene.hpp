#pragma once
#include "component.hpp"
#include "components/image.hpp"
#include "components/mesh.hpp"
#include "components/sampler.hpp"
#include "components/texture.hpp"
#include "node.hpp"
#include <algorithm>

NAMESPACE_BEGIN(vktscn)

/**
 * @brief Vktor scene
 *
 * - All nodes and components are stored in `Scene` with ownership
 * - Reference to nodes and components should use raw pointer
 */
class Scene : public NonCopyable {
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
        nodes.emplace_back(std::move(_node));
    }
    inline void setNodes(Vector<Box<Node>>&& _nodes, size_t _root_node) {
        nodes = std::move(_nodes);
        root_node = _root_node;
    }
    inline void setRootNode(size_t _root_node) {
        root_node = _root_node;
    }
    inline Node& getRootNode() {
        assert(root_node < nodes.size());
        return *nodes[root_node];
    }

public:
    void addComponent(Box<Component>&& component);
    void addComponent(Box<Component>&& component, Node& node);

    template <class T>
    void setComponents(Vector<Box<T>>&& _components);
    inline void setComponents(const std::type_index& index, Vector<Box<Component>>&& _components);

    template <class T>
    Vector<T*> getComponents() const;
    inline const Vector<Box<Component>>& getComponents(const std::type_index& index) const;

    template <class T>
    inline bool hasComponent() const;
    inline bool hasComponent(const std::type_index& type_info) const;

    template <class T>
    inline void clearComponents();
};

template <class T>
void Scene::setComponents(Vector<Box<T>>&& _components) {
    Vector<Box<Component>> res(_components.size());
    // Cast component type T to the base `Component` pointer
    std::transform(_components.begin(), _components.end(), res.begin(), [](Box<T>& comp) -> Box<Component> {
        return Box<Component>(std::move(comp));
    });
    setComponents(typeid(T), std::move(res));
}

inline void Scene::setComponents(const std::type_index& index, Vector<Box<Component>>&& _components) {
    components[index] = std::move(_components);
}

template <class T>
Vector<T*> Scene::getComponents() const {
    Vector<T*> res;
    if (hasComponent(typeid(T))) {
        auto& comps = getComponents(typeid(T));
        res.resize(comps.size());
        // Cast base `Component` pointer to component type T
        std::transform(comps.begin(), comps.end(), res.begin(), [](const Box<Component>& comp) -> T* {
            return dynamic_cast<T*>(comp.get());
        });
    }
    return res;
}

inline const Vector<Box<Component>>& Scene::getComponents(const std::type_index& index) const {
    return components.at(index);
}

template <class T>
inline bool Scene::hasComponent() const {
    return hasComponent(typeid(T));
}

inline bool Scene::hasComponent(const std::type_index& index) const {
    auto comp = components.find(index);
    return (comp != components.end() && !comp->second.empty());
}

template <class T>
inline void Scene::clearComponents() {
    setComponents(typeid(T), {});
}

NAMESPACE_END(vktscn)
