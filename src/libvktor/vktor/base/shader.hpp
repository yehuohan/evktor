#pragma once
#include "vktor/core/shader_module.hpp"

NAMESPACE_BEGIN(vkt)

class Shader : private NonCopyable {
private:
    std::string filename;
    std::string code;
    VkShaderStageFlagBits stage;

private:
    Shader(){};

public:
    Shader(Shader&&);

    inline const std::string& getFilename() const {
        return filename;
    }
    inline const std::string& getCode() const {
        return code;
    }
    inline VkShaderStageFlagBits getStage() const {
        return stage;
    }

    static Res<Shader> load(const std::string& filename);
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::Shader> {
    size_t operator()(const vkt::Shader& shader) const {
        size_t res = 0;
        vkt::hashCombine(res, shader.getFilename());
        return res;
    }
};

NAMESPACE_END(std)
