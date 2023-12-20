#include <fmt/core.h>
#include "assets.h"


std::string Assets::dir = std::string(".");

void Assets::setDir(const std::string& dir) {
    Assets::dir = dir;
}

std::string Assets::getTex(const std::string& filename) {
    return fmt::format("{}/textures/{}", Assets::dir, filename);
}

std::string Assets::getFont(const std::string& filename) {
    return fmt::format("{}/fonts/{}", Assets::dir, filename);
}

std::string Assets::getObj(const std::string& filename) {
    return fmt::format("{}/objects/{}", Assets::dir, filename);
}
