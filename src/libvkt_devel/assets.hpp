#pragma once
#include <share/helpers.hpp>
#include <vktor/base/shader.hpp>

NAMESPACE_BEGIN(vktdev)

class Assets {
public:
    static String assets;
    static String shader;

public:
    Assets() = delete;

    static void setDirs(const String& assets_dir, const String& shader_dir = ".");

    inline static String tex(const String& filename) {
        return fmt::format("{}/textures/{}", Assets::assets, filename);
    }
    inline static String font(const String& filename) {
        return fmt::format("{}/fonts/{}", Assets::assets, filename);
    }
    inline static String obj(const String& filename) {
        return fmt::format("{}/objects/{}", Assets::assets, filename);
    }
    inline static String scene(const String& filename) {
        return fmt::format("{}/scenes/{}", Assets::assets, filename);
    }

    inline static String shaderFile(const String& filename) {
        return fmt::format("{}/{}", Assets::shader, filename);
    }
    static vkt::ShaderSource::Stage shaderStage(const String& filename);
    static String shaderSource(const String& filename);
};

NAMESPACE_END(vktdev)
