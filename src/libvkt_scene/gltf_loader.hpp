#pragma once
#include "component.hpp"
#include "components/sampler.hpp"
#include "scene.hpp"
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <share/traits.hpp>
#include <tiny_gltf.h>
#include <vktor/core/api/api.hpp>

NAMESPACE_BEGIN(vktscn)

class GLTFLoader : public NonCopyable {
private:
    const vkt::core::CoreApi& api;
    tinygltf::Model gmodel;

public:
    GLTFLoader(vkt::core::CoreApi& api) : api(api) {}
    Box<Scene> loadScene(const String& filename, int32_t scene_index = -1);

protected:
    Box<Sampler> parseSampler(const tinygltf::Sampler& gsampler) const;

    Box<Scene> loadScene(int32_t scene_index);
};

NAMESPACE_END(vktscn)
