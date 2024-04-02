#include "assets.hpp"
#include <fmt/core.h>

namespace vktdev {

std::string Assets::assets = std::string(".");
std::string Assets::shader = std::string(".");

void Assets::setDirs(const std::string& assets_dir, const std::string& shader_dir) {
    Assets::assets = assets_dir;
    Assets::shader = shader_dir;
}

std::string Assets::getTex(const std::string& filename) {
    return fmt::format("{}/textures/{}", Assets::assets, filename);
}

std::string Assets::getFont(const std::string& filename) {
    return fmt::format("{}/fonts/{}", Assets::assets, filename);
}

std::string Assets::getObj(const std::string& filename) {
    return fmt::format("{}/objects/{}", Assets::assets, filename);
}

std::string Assets::getShader(const std::string& filename) {
    return fmt::format("{}/{}", Assets::shader, filename);
}

} // namespace vktdev
