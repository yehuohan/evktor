#pragma once
#include <share/helpers.hpp>
#include <vktor/base/shader.hpp>

NAMESPACE_BEGIN(vktdev)

class Assets {
public:
    static vkt::String assets;
    static vkt::String shader;

public:
    Assets() = delete;

    static void setDirs(const vkt::String& assets_dir, const vkt::String& shader_dir = ".");

    inline static vkt::String tex(const vkt::String& filename) {
        return fmt::format("{}/textures/{}", Assets::assets, filename);
    }
    inline static vkt::String font(const vkt::String& filename) {
        return fmt::format("{}/fonts/{}", Assets::assets, filename);
    }
    inline static vkt::String obj(const vkt::String& filename) {
        return fmt::format("{}/objects/{}", Assets::assets, filename);
    }
    inline static vkt::String scene(const vkt::String& filename) {
        return fmt::format("{}/scenes/{}", Assets::assets, filename);
    }

    inline static vkt::String shaderFile(const vkt::String& filename) {
        return fmt::format("{}/{}", Assets::shader, filename);
    }
    static vkt::ShaderSource::Stage shaderStage(const vkt::String& filename);
    static vkt::String shaderSource(const vkt::String& filename);
};

NAMESPACE_END(vktdev)
