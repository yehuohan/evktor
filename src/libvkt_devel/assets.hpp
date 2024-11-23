#pragma once
#include <string>
#include <vktor/base/shader.hpp>

NAMESPACE_BEGIN(vktdev)

class Assets {
public:
    static std::string assets;
    static std::string shader;

public:
    Assets() = delete;

    static void setDirs(const std::string& assets_dir, const std::string& shader_dir = ".");

    inline static std::string tex(const std::string& filename) {
        return fmt::format("{}/textures/{}", Assets::assets, filename);
    }
    inline static std::string font(const std::string& filename) {
        return fmt::format("{}/fonts/{}", Assets::assets, filename);
    }
    inline static std::string obj(const std::string& filename) {
        return fmt::format("{}/objects/{}", Assets::assets, filename);
    }
    inline static std::string scene(const std::string& filename) {
        return fmt::format("{}/scenes/{}", Assets::assets, filename);
    }

    inline static std::string shaderFile(const std::string& filename) {
        return fmt::format("{}/{}", Assets::shader, filename);
    }
    static vkt::ShaderSource::Stage shaderStage(const std::string& filename);
    static std::string shaderSource(const std::string& filename);
};

NAMESPACE_END(vktdev)
