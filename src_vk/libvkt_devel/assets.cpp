#include "assets.hpp"
#include <stb_image.h>

namespace vktdev {

std::string Assets::path_assets = std::string(".");
std::string Assets::path_shader = std::string(".");

void Assets::setDirs(const std::string& assets_dir, const std::string& shader_dir) {
    Assets::path_assets = assets_dir;
    Assets::path_shader = shader_dir;
}

static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadTexC8(const std::string& filename, int channel) {
    std::vector<uint8_t> pixels{};
    int w, h, c;
    {
        stbi_uc* raw = stbi_load(filename.c_str(), &w, &h, &c, channel);
        if (!raw || c != channel) {
            throw std::runtime_error(fmt::format("Failed to load texture({}) with channel: {} != {}", filename, channel, c));
        }
        pixels = {raw, raw + w * h * c};
        stbi_image_free(raw);
    }
    return {std::move(pixels), w, h};
}

std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> Assets::loadTexRGB8(const std::string& filename) {
    return std::move(loadTexC8(filename, STBI_rgb));
}

std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> Assets::loadTexRGBA8(const std::string& filename) {
    return std::move(loadTexC8(filename, STBI_rgb_alpha));
}

std::string Assets::loadShader(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw std::runtime_error(fmt::format("Failed to load shader: {}", filename));
    }
    return std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}

} // namespace vktdev
