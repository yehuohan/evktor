#pragma once
#include "scene.hpp"
#include <glm/fwd.hpp>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <tiny_gltf.h>
#include <vktor/core/api/api.hpp>

NAMESPACE_BEGIN(vktscn)

class GLTFLoader : public vkt::NonCopyable {
private:
    const vkt::core::CoreApi& api;
    tinygltf::Model gmodel;

public:
    GLTFLoader(vkt::core::CoreApi& api) : api(api) {}
    vkt::Box<Scene> loadScene(const vkt::String& filename, int32_t scene_index = -1);

protected:
    vkt::Box<Scene> loadScene(int32_t scene_index);
};

NAMESPACE_END(vktscn)
