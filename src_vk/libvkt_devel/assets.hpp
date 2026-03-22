#pragma once
#include <cstdint>
#include <fmt/core.h>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace vktdev {

class Assets {
private:
    static std::string path_assets;
    static std::string path_shader;
    static std::unordered_map<std::string, std::shared_ptr<std::string>> shaders; /**< Map shader filename to shader code */

public:
    Assets() = delete;

    static void setDirs(const std::string& assets_dir, const std::string& shader_dir = ".");

public:
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

public:
    /**
     * @brief Load texture in RGB8 format
     *
     * @return [pixels, width, height] of texture
     */
    static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadTexRGB8(const std::string& filename);
    /**
     * @brief Load texture in RGBA8 format
     *
     * @return [pixels, width, height] of texture
     */
    static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadTexRGBA8(const std::string& filename);
    /**
     * @brief Load cube textures in RGBA8 format
     *
     * @return [pixels, width, height] of textures
     */
    static std::tuple<std::vector<uint8_t>, uint32_t, uint32_t> loadCubeRGBA8(const std::string& right,
                                                                              const std::string& left,
                                                                              const std::string& top,
                                                                              const std::string& bottom,
                                                                              const std::string& front,
                                                                              const std::string& back);

public:
    /**
     * @brief Get shader source code and shader file path
     *
     * @return [code, filepath] of shader
     */
    static std::tuple<const std::shared_ptr<std::string>, const std::string> getShader(const std::string& filename);
    static inline std::vector<uint32_t> loadSpirv(const std::string& filename) {
        return Assets::loadBinary<uint32_t>(Assets::shader(filename));
    }

public:
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
