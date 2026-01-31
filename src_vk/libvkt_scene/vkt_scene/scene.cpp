#include "scene.hpp"

NAMESPACE_BEGIN(vktscn)

void Scene::addComponent(Box<Component>&& component) {
    if (component) {
        components[component->getType()].push_back(std::move(component));
    }
}

const Vector<Box<Component>>& Scene::getComponents(const std::type_index& index) const {
    if (auto it = components.find(index); it != components.end()) {
        return it->second;
    } else {
        static const Vector<Box<Component>> res{}; // A empty vector means there's no components for `index` in this scene
        return res;
    }
}

NAMESPACE_END(vktscn)
