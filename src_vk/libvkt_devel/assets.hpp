#pragma once
#include <cstdint>
#include <fmt/core.h>
#include <string>
#include <vector>

namespace vktdev {

class Assets {
public:
    static std::string path_assets;
    static std::string path_shader;

public:
    Assets() = delete;

    static void setDirs(const std::string& assets_dir, const std::string& shader_dir = ".");

    inline static std::string tex(const std::string& filename) {
        return fmt::format("{}/textures/{}", Assets::path_assets, filename);
    }
    inline static std::string obj(const std::string& filename) {
        return fmt::format("{}/objects/{}", Assets::path_assets, filename);
    }
    inline static std::string scene(const std::string& filename) {
        return fmt::format("{}/scenes/{}", Assets::path_assets, filename);
    }
    inline static std::string shader(const std::string& filename) {
        return fmt::format("{}/{}", Assets::path_shader, filename);
    }
    inline static std::string font(const std::string& filename) {
        return fmt::format("{}/fonts/{}", Assets::path_assets, filename);
    }

    /**
     * @brief Load texture in RGB8 format
     *
     * @return The return contains [pixels, width, height]
     */
    static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadTexRGB8(const std::string& filename);
    /**
     * @brief Load texture in RGBA8 format
     *
     * @return The return contains [pixels, width, height]
     */
    static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadTexRGBA8(const std::string& filename);
    static std::string loadShader(const std::string& filename);
};

} // namespace vktdev
