#include "scene.hpp"

using namespace vkt;

NAMESPACE_BEGIN(vktscn)

void Scene::addComponent(Box<Component>&& component, Node& node) {
    node.setComponent(*component);
    if (component) {
        components[component->getType()].push_back(std::move(component));
    }
}

void Scene::addComponent(Box<Component>&& component) {
    if (component) {
        components[component->getType()].push_back(std::move(component));
    }
}

NAMESPACE_END(vktscn)
