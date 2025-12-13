#include "assets.hpp"
#include <fstream>

namespace vktdev {

std::string Assets::path_assets = std::string(".");
std::string Assets::path_shader = std::string(".");

void Assets::setDirs(const std::string& assets_dir, const std::string& shader_dir) {
    Assets::path_assets = assets_dir;
    Assets::path_shader = shader_dir;
}

std::string Assets::shaderSource(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw std::runtime_error(fmt::format("Failed to read shader: {}", filename));
    }
    return std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}

} // namespace vktdev
