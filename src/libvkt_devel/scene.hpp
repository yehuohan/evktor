#pragma once
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <tiny_gltf.h>
#include <vktor/base/texture.hpp>
#include <vktor/core/api/api.hpp>
#include <vktor/core/buffer.hpp>

NAMESPACE_BEGIN(vktdev)

struct Mesh : public vkt::NonCopyable {
public:
    VkBuffer index;

    vkt::CRef<vkt::core::Buffer> position;
    vkt::CRef<vkt::core::Buffer> normal;
    vkt::CRef<vkt::core::Buffer> tangent;
    vkt::CRef<vkt::core::Buffer> texcoord;
};

struct Node : public vkt::NonCopyable {
public:
    vkt::Vector<Mesh> meshes;
};

class Scene : public vkt::NonCopyable {
public:
    vkt::Vector<vkt::core::Sampler> samplers;
    vkt::Vector<vkt::core::Buffer> buffers;
    vkt::Vector<vkt::Texture> textures;

    vkt::Vector<Node> nodes;
};

class SceneLoader {
private:
    const vkt::core::CoreApi& api;

public:
    SceneLoader(vkt::core::CoreApi& api) : api(api) {}

    vkt::Box<Scene> load(const vkt::String& filename);
};

NAMESPACE_END(vktdev)
