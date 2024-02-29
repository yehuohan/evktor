#include "shader.hpp"
#include <fstream>

NAMESPACE_BEGIN(vkt)

static Res<VkShaderStageFlagBits> getShaderStage(const std::string& filename) {
    std::string::size_type n = filename.rfind('.');
    if (n == std::string::npos) {
        return Er("Failed to get shader stage: {}", filename);
    }
    std::string suffix = filename.substr(n + 1);

    VkShaderStageFlagBits stage;
    if ("vert" == suffix) {
        stage = VK_SHADER_STAGE_VERTEX_BIT;
    } else if ("frag" == suffix) {
        stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    } else if ("geom" == suffix) {
        stage = VK_SHADER_STAGE_COMPUTE_BIT;
    } else if ("comp" == suffix) {
        stage = VK_SHADER_STAGE_GEOMETRY_BIT;
    } else {
        return Er("Unrecognized shader type: {}", suffix);
    }
    return Ok(stage);
}

static Res<std::string> readShader(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        return Er("Failed to read shader: {}", filename);
    }
    return Ok(std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()}));
}

Shader::Shader(Shader&& rhs) {
    filename = std::move(rhs.filename);
    code = std::move(rhs.code);
    stage = rhs.stage;
}

Res<Shader> Shader::load(const std::string& filename) {
    Shader shader{};

    auto stage = getShaderStage(filename);
    OnErr(stage);
    shader.stage = stage.unwrap();
    auto code = readShader(filename);
    OnErr(code);
    shader.code = std::move(code.unwrap());
    shader.filename = filename;

    return Ok(std::move(shader));
}

NAMESPACE_END(vkt)
