#pragma once
#include "vkt_scene/scene.hpp"
#include <tiny_gltf.h>
#include <vktor/core/api/api.hpp>

class GLTFLoader : public NonCopyable {
private:
    const vkt::core::CoreApi& api;
    tinygltf::Model gmodel;

public:
    GLTFLoader(vkt::core::CoreApi& api) : api(api) {}

private:
    inline size_t accessorCount(uint32_t index) const {
        assert(index < gmodel.accessors.size());
        return gmodel.accessors[index].count;
    }
    size_t accessorStride(uint32_t index) const;
    Vector<uint8_t> accessorData(uint32_t index) const;
    VkFormat accessorFormat(uint32_t index) const;

protected:
    Box<vktscn::Sampler> parseSampler(size_t gsampler_index) const;
    Box<vktscn::Node> parseNode(size_t gnode_index) const;

protected:
    void loadSceneSamplers(vktscn::Scene& scene) const;
    void loadSceneMeshes(vktscn::Scene& scene) const;
    void loadSceneNodes(vktscn::Scene& scene) const;
    Box<vktscn::Scene> loadScene(int32_t scene_index) const;

public:
    Box<vktscn::Scene> loadScene(const String& filename, int32_t scene_index = -1);
};
