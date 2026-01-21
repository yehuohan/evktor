#pragma once
#include <cstdint>
#include <fmt/core.h>
#include <fstream>
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
    static inline std::vector<uint32_t> loadSpirv(const std::string& filename) {
        return Assets::loadBinary<uint32_t>(Assets::shader(filename));
    }

    /**
     * @brief Load binary
     */
    template <typename T>
    static std::vector<T> loadBinary(const std::string& filename) {
        std::ifstream fin(filename, std::ios::ate | std::ios::binary);
        if (!fin.is_open()) {
            throw std::runtime_error(fmt::format("Failed to load binary: {}", filename));
        }
        size_t bin_size = fin.tellg();
        if (bin_size % sizeof(T)) {
            throw std::runtime_error(fmt::format("Binary size is not a multiplier of T: {}, {}", bin_size, sizeof(T)));
        }
        fin.seekg(0, std::ios::beg);
        std::vector<T> spv(bin_size / sizeof(T));
        fin.read(reinterpret_cast<char*>(spv.data()), bin_size);
        return spv;
    }
};

} // namespace vktdev
