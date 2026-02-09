#include "vkt_scene.hpp"
#include <queue>

NAMESPACE_BEGIN(vktscn)

Node* Scene::findNode(const String& node_name) {
    auto root = getRootNode();
    if (!root) {
        return nullptr;
    }

    for (auto _node : root->getChildren()) {
        std::queue<Node*> traverse_nodes{};
        traverse_nodes.push(_node);

        while (!traverse_nodes.empty()) {
            auto node = traverse_nodes.front();
            traverse_nodes.pop();
            if (node->getName() == node_name) {
                return node;
            }
            for (auto child_node : node->getChildren()) {
                traverse_nodes.push(child_node);
            }
        }
    }

    return nullptr;
}

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
