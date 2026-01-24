#pragma once
#include "vkt_scene/scene.hpp"
#include <tiny_gltf.h>
#include <vktor/core/api/api.hpp>

class GLTFLoader : private NonCopyable {
private:
    const vkt::core::CoreApi& api;
    tinygltf::Model gmodel;

public:
    GLTFLoader(vkt::core::CoreApi& api) : api(api) {}

private:
    inline size_t accessorCount(uint32_t index) const;
    /** @brief Get <buffer, stride, offset> from accessor */
    std::tuple<size_t, size_t, size_t> accessorBufferOffsetStride(uint32_t index) const;
    Vector<uint8_t> accessorData(uint32_t index) const;
    VkFormat accessorFormat(uint32_t index) const;
    VkFormat imageFormat(uint32_t index) const;

protected:
    Box<vktscn::Node> parseNode(size_t gnode_index) const;

protected:
    void loadSamplers(vktscn::Scene& scene) const;
    void loadBuffers(vktscn::Scene& scene) const;
    void loadImages(vktscn::Scene& scene) const;
    void loadTextures(vktscn::Scene& scene) const;
    void loadMaterials(vktscn::Scene& scene) const;
    void loadMeshes(vktscn::Scene& scene) const;
    void loadSceneNodes(vktscn::Scene& scene, int32_t scene_index) const;
    Box<vktscn::Scene> loadScene(int32_t scene_index) const;

public:
    Box<vktscn::Scene> loadScene(const String& filename, int32_t scene_index = -1);
};
