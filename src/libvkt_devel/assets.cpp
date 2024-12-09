#include "assets.hpp"
#include <fmt/core.h>
#include <fstream>

NAMESPACE_BEGIN(vktdev)

using namespace vkt;

String Assets::assets = String(".");
String Assets::shader = String(".");

void Assets::setDirs(const String& assets_dir, const String& shader_dir) {
    Assets::assets = assets_dir;
    Assets::shader = shader_dir;
}

vkt::ShaderSource::Stage Assets::shaderStage(const String& filename) {
    String::size_type n = filename.rfind('.');
    if (n == String::npos) {
        throw vktErr("Failed to get shader stage: {}", filename);
    }
    String suffix = filename.substr(n + 1);

    ShaderSource::Stage stage;
    if ("vert" == suffix) {
        stage = ShaderSource::Stage::Vert;
    } else if ("frag" == suffix) {
        stage = ShaderSource::Stage::Frag;
    } else if ("comp" == suffix) {
        stage = ShaderSource::Stage::Comp;
    } else {
        throw vktErr("Unrecognized shader type: {}", suffix);
    }
    return stage;
}

String Assets::shaderSource(const String& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw vktErr("Failed to read shader: {}", filename);
    }
    return String({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}

NAMESPACE_END(vktdev)
