#include "assets.hpp"
#include <fmt/core.h>
#include <fstream>

NAMESPACE_BEGIN(vktdev)

using namespace vkt;

std::string Assets::assets = std::string(".");
std::string Assets::shader = std::string(".");

void Assets::setDirs(const std::string& assets_dir, const std::string& shader_dir) {
    Assets::assets = assets_dir;
    Assets::shader = shader_dir;
}

vkt::ShaderSource::Stage Assets::shaderStage(const std::string& filename) {
    std::string::size_type n = filename.rfind('.');
    if (n == std::string::npos) {
        throw vktErr("Failed to get shader stage: {}", filename);
    }
    std::string suffix = filename.substr(n + 1);

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

std::string Assets::shaderSource(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw vktErr("Failed to read shader: {}", filename);
    }
    return std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}

NAMESPACE_END(vktdev)
