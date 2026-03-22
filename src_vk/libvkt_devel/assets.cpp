#include "assets.hpp"
#include <stb_image.h>

namespace vktdev {

std::string Assets::path_assets = std::string(".");
std::string Assets::path_shader = std::string(".");

void Assets::setDirs(const std::string& assets_dir, const std::string& shader_dir) {
    Assets::path_assets = assets_dir;
    Assets::path_shader = shader_dir;
}

static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadTex(const std::string& filename, int channel) {
    std::vector<uint8_t> pixels{};
    int w, h, c;
    {
        stbi_uc* raw = stbi_load(filename.c_str(), &w, &h, &c, channel);
        if (!raw) {
            throw std::runtime_error(fmt::format("Failed to load texture({})", filename));
        }
        pixels = {raw, raw + w * h * channel};
        stbi_image_free(raw);
    }
    return {std::move(pixels), w, h};
}

std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> Assets::loadTexRGB8(const std::string& filename) {
    return loadTex(Assets::tex(filename), STBI_rgb);
}

std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> Assets::loadTexRGBA8(const std::string& filename) {
    return loadTex(Assets::tex(filename), STBI_rgb_alpha);
}

std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> Assets::loadCubeRGBA8(const std::string& right,
                                                                           const std::string& left,
                                                                           const std::string& top,
                                                                           const std::string& bottom,
                                                                           const std::string& front,
                                                                           const std::string& back) {
    uint32_t cube_wid = 0, cube_hei = 0;
    std::vector<uint8_t> cube_pixels{};
    for (auto& face : {right, left, top, bottom, front, back}) {
        auto [pixels, w, h] = Assets::loadTexRGBA8(face);
        if ((cube_wid != 0 && cube_wid != w) || (cube_hei != 0 && cube_hei != h)) {
            throw std::runtime_error("Cube textures must have same width and height");
        }
        cube_wid = w;
        cube_hei = h;
        cube_pixels.insert(cube_pixels.end(), pixels.begin(), pixels.end());
    }
    return {std::move(cube_pixels), cube_wid, cube_hei};
}

std::string Assets::loadShader(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw std::runtime_error(fmt::format("Failed to load shader: {}", filename));
    }
    return std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}

} // namespace vktdev
