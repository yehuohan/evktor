#pragma once
#include "component.hpp"
#include "node.hpp"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <vktor/base/texture.hpp>
#include <vktor/core/buffer.hpp>
#include <vktor/core/sampler.hpp>

NAMESPACE_BEGIN(vktscn)

struct MeshData {
    alignas(16) glm::mat4 model;
};

struct Mesh {
public:
    // vkt::CRef<vkt::core::Buffer> index;
    VkBuffer index = VK_NULL_HANDLE;
    size_t index_offset = 0;
    size_t index_count = 0;
    VkIndexType index_type = VkIndexType::VK_INDEX_TYPE_UINT16;

    // vkt::CRef<vkt::core::Buffer> position;
    // vkt::CRef<vkt::core::Buffer> texcoord;
    // vkt::CRef<vkt::core::Buffer> normal;
    // vkt::CRef<vkt::core::Buffer> tangent;
    VkBuffer position = VK_NULL_HANDLE;
    VkBuffer texcoord = VK_NULL_HANDLE;
    VkBuffer normal = VK_NULL_HANDLE;
    VkBuffer tangent = VK_NULL_HANDLE;
    size_t position_offset = 0;
    size_t texcoord_offset = 0;
    size_t normal_offset = 0;
    size_t tangent_offset = 0;

    int32_t tex_idx = -1;

    glm::mat4 model;
};

class Scene : public NonCopyable {
private:
    String name;
    Node* root = nullptr;
    Vector<Box<Node>> nodes{}; /**< tinygltf::Model.nodes */
    HashMap<std::type_index, Vector<Box<Component>>> components{};

public:
    Scene() = default;
    Scene(const String& name) : name(name) {}

    inline void setComponents(const std::type_index& index, Vector<Box<Component>>&& _components) {
        components[index] = std::move(_components);
    }
    template <class T>
    void setComponents(Vector<Box<T>>&& _components) {
        Vector<Box<Component>> res(_components.size());
        // Cast component type T to the base `Component` pointer
        std::transform(_components.begin(), _components.end(), res.begin(), [](Box<T>& comp) -> Box<Component> {
            return Box<Component>(std::move(comp));
        });
        setComponents(typeid(T), std::move(res));
    }

    inline const Vector<Box<Component>>& getComponents(const std::type_index& index) const {
        return components.at(index);
    }
    template <class T>
    Vector<T*> getComponents() const {
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

    template <class T>
    inline bool hasComponent() const {
        return hasComponent(typeid(T));
    }
    inline bool hasComponent(const std::type_index& type_info) const {
        auto comp = components.find(type_info);
        return (comp != components.end() && !comp->second.empty());
    }

    template <class T>
    inline void clearComponents() {
        setComponents(typeid(T), {});
    }

public:
    Vector<vkt::core::Buffer> buffers;
    Vector<vkt::Texture> textures;

    Vector<Mesh> meshes;
};

NAMESPACE_END(vktscn)
