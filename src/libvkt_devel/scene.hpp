#pragma once
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <tiny_gltf.h>
#include <vktor/core/api/api.hpp>

NAMESPACE_BEGIN(vktdev)

struct Mesh : public vkt::NonCopyable {
public:
};

class Scene : public vkt::NonCopyable {
public:
};

class SceneLoader {
private:
    const vkt::core::CoreApi& api;

public:
    SceneLoader(vkt::core::CoreApi& api) : api(api) {}

    vkt::Box<Scene> load(const vkt::String& filename);
};

NAMESPACE_END(vktdev)
