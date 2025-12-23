#include "__helpers.hpp"
// libvkt_scene has compiled TINYGLTF_IMPLEMENTATION
#include <tiny_gltf.h>

void case_dep_gltf() {
    using namespace tinygltf;

    const String gltf_file = vktdev::Assets::scene("Sponza/glTF/Sponza.gltf");

    Model gmodel;
    TinyGLTF gloader;
    std::string err;
    std::string warn;

    bool res = gloader.LoadASCIIFromFile(&gmodel, &err, &warn, gltf_file);
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

    tstOut("Used extensions: {}", gmodel.extensionsUsed.size());
    for (const auto& ext : gmodel.extensionsUsed) {
        tstOut("\t{}", ext);
    }

    tstOut("Required extensions: {}", gmodel.extensionsRequired.size());
    for (const auto& ext : gmodel.extensionsRequired) {
        tstOut("\t{}", ext);
    }

    // Resources
    tstOut("Resource samplers: {}", gmodel.samplers.size());
    for (size_t k = 0; k < gmodel.samplers.size(); k++) {
        const auto& spl = gmodel.samplers[k];
        tstOut("\tSampler.{}: min = {}, mag = {}", k, spl.minFilter, spl.magFilter);
    }

    tstOut("Resource buffers: {}", gmodel.buffers.size());
    for (size_t k = 0; k < gmodel.buffers.size(); k++) {
        const auto& buf = gmodel.buffers[k];
        tstOut("\tBuffer.{}: size = {}", k, buf.data.size());
    }

    tstOut("Resource images: {}", gmodel.images.size());
    for (size_t k = 0; k < gmodel.images.size(); k++) {
        const auto& img = gmodel.images[k];
        tstOut("\tImage.{}: size = {}x{}x{}, path = {}", k, img.width, img.height, img.component, img.uri);
    }

    // String conversions
    auto outType = [](int ty) -> std::string {
        if (ty == TINYGLTF_TYPE_SCALAR) {
            return "SCALAR";
        } else if (ty == TINYGLTF_TYPE_VEC2) {
            return "VEC2";
        } else if (ty == TINYGLTF_TYPE_VEC3) {
            return "VEC3";
        } else if (ty == TINYGLTF_TYPE_VEC4) {
            return "VEC4";
        } else if (ty == TINYGLTF_TYPE_MAT2) {
            return "MAT2";
        } else if (ty == TINYGLTF_TYPE_MAT3) {
            return "MAT3";
        } else if (ty == TINYGLTF_TYPE_MAT4) {
            return "MAT4";
        } else {
            return "-1";
        }
    };
    auto outMode = [](int mode) -> std::string {
        if (mode == TINYGLTF_MODE_POINTS) {
            return "POINTS";
        } else if (mode == TINYGLTF_MODE_LINE) {
            return "LINE";
        } else if (mode == TINYGLTF_MODE_LINE_LOOP) {
            return "LINE_LOOP";
        } else if (mode == TINYGLTF_MODE_LINE_STRIP) {
            return "LINE_STRIP";
        } else if (mode == TINYGLTF_MODE_TRIANGLES) {
            return "TRIANGLES";
        } else if (mode == TINYGLTF_MODE_TRIANGLE_STRIP) {
            return "TRIANGLE_STRIP";
        } else if (mode == TINYGLTF_MODE_TRIANGLE_FAN) {
            return "TRIANGLE_FAN";
        } else {
            return "-1";
        }
    };
    auto outBuffer = [&gmodel](int buffer_view) -> std::string {
        const auto& bufview = gmodel.bufferViews[buffer_view];
        return fmt::format("Buffer.{} + {}", bufview.buffer, bufview.byteOffset);
    };
    auto outAccessor = [&outType, &outMode, &outBuffer](const Accessor& gaccessor) -> std::string {
        return fmt::format("count={}, type={}, buffer={}",
                           gaccessor.count,
                           outType(gaccessor.type),
                           outBuffer(gaccessor.bufferView));
    };
    auto outMaterial = [&gmodel](const Material& mat) -> std::string {
        const auto& tex = gmodel.textures[mat.pbrMetallicRoughness.baseColorTexture.index];
        return fmt::format("baseColor=Sampler.{} + Image.{}", tex.sampler, tex.source);
    };

    // Scenes
    for (size_t ks = 0; ks < gmodel.scenes.size(); ks++) {
        const auto& scene = gmodel.scenes[ks];
        tstOut("Scene.{}:", ks);
        tstOut("\t.nodes = {}", scene.nodes.size());

        for (size_t kn = 0; kn < scene.nodes.size(); kn++) {
            const auto& gnode = gmodel.nodes[kn];
            tstOut("\tNode.{}:", kn);
            tstOut("\t\t.lods = {}", gnode.lods.size());
            tstOut("\t\t.children = {}", gnode.children.size());
            tstOut("\t\t.rotation = {}", gnode.rotation.size());

            const auto& gmesh = gmodel.meshes[gnode.mesh];
            tstOut("\t\tMesh:");
            tstOut("\t\t\t.primitives = {}", gmesh.primitives.size());

            for (size_t kp = 0; kp < gmesh.primitives.size(); kp++) {
                const auto& gprimitive = gmesh.primitives[kp];
                tstOut("\t\t\tPrimitive.{}:", kp);
                tstOut("\t\t\t\t.attributes = {}", gprimitive.attributes.size());
                for (const auto& gattr : gprimitive.attributes) {
                    const auto& gaccessor = gmodel.accessors[gattr.second];
                    tstOut("\t\t\t\t\t[{}]: {}", gattr.first, outAccessor(gaccessor));
                }
                tstOut("\t\t\t\t.material = {}", outMaterial(gmodel.materials[gprimitive.material]));
                tstOut("\t\t\t\t.indices = {}", outAccessor(gmodel.accessors[gprimitive.indices]));
                tstOut("\t\t\t\t.mode = {}", outMode(gprimitive.mode));
                break;
            }
        }
    }
}
