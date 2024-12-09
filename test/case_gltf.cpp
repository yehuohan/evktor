#include "__helpers.hpp"
#include <assets.hpp>
#include <string>
// libvkt_devel has compiled TINYGLTF_IMPLEMENTATION
#include <tiny_gltf.h>

void case_gltf() {
    using namespace tinygltf;

    const vkt::String gltf_file = vktdev::Assets::scene("Sponza/glTF/Sponza.gltf");

    Model model;
    TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(&model, &err, &warn, gltf_file);
    if (!res) {
        tstOut("Failed to parse gltf: {}", gltf_file);
        return;
    }
    if (!warn.empty()) {
        tstOut("Warn: {}", warn);
    }
    if (!err.empty()) {
        tstOut("Error: {}", err);
    }

    tstOut("Used extensions: {}", model.extensionsUsed.size());
    for (const auto& ext : model.extensionsUsed) {
        tstOut("\t{}", ext);
    }

    tstOut("Required extensions: {}", model.extensionsRequired.size());
    for (const auto& ext : model.extensionsRequired) {
        tstOut("\t{}", ext);
    }

    tstOut("Buffers: {}", model.buffers.size());
    for (const auto& buf : model.buffers) {
        tstOut("\t{}: size = {}", buf.name, buf.data.size());
    }

    tstOut("BufferViews: {}", model.bufferViews.size());
    for (const auto& buf : model.bufferViews) {
        tstOut("\t{}: buffer = {}, offset = {}, length = {}, stride = {}",
               buf.name,
               buf.buffer,
               buf.byteOffset,
               buf.byteLength,
               buf.byteStride);
    }

    tstOut("Samplers: {}", model.samplers.size());
    for (const auto& spl : model.samplers) {
        tstOut("\t{}: min = {}, mag = {}", spl.name, spl.minFilter, spl.magFilter);
    }

    tstOut("Images: {}", model.images.size());
    for (const auto& img : model.images) {
        tstOut("\t{}: size = {}x{}x{}, path = {}", img.name, img.width, img.height, img.component, img.uri);
    }

    tstOut("Textures: {}", model.textures.size());
    for (const auto& tex : model.textures) {
        tstOut("\t{}: sampler = {}, source = {}", tex.name, tex.sampler, tex.source);
    }

    tstOut("Meshes: {}", model.meshes.size());
    for (const auto& mesh : model.meshes) {
        tstOut("\t{}", mesh.name);
    }

    tstOut("Materials: {}", model.materials.size());
    for (const auto& mat : model.materials) {
        tstOut("\t{}: alpha = {}", mat.name, mat.alphaMode);
    }

    tstOut("Nodes: {}", model.nodes.size());
    for (const auto& node : model.nodes) {
        tstOut("\t{}", node.name);
    }

    tstOut("Scenes: {}", model.scenes.size());
    for (const auto& scene : model.scenes) {
        tstOut("\t{}", scene.name);
    }
}
