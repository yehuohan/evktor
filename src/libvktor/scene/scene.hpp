#pragma once
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <tiny_gltf.h>
#include <vktor/base/texture.hpp>
#include <vktor/core/api/api.hpp>

NAMESPACE_BEGIN(vktdev)

struct Mesh : public vkt::NonCopyable {
public:
};

struct Node : public vkt::NonCopyable {
public:
};

class Scene : public vkt::NonCopyable {
public:
};

class Model : public vkt::NonCopyable {
public:
    vkt::Vector<vkt::Box<vkt::Texture>> textures;
};

class SceneLoader {
private:
    const vkt::core::CoreApi& api;

public:
    SceneLoader(vkt::core::CoreApi& api) : api(api) {}

    vkt::Box<Scene> load(const vkt::String& filename);
};

NAMESPACE_END(vktdev)
