#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ShaderModule;

class ShaderModuleState : public CoreState<ShaderModuleState> {
    friend struct ShaderModule;

private:
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    String filename = "shader.glsl";
    String entry = "main";
    const uint32_t* code = nullptr;
    size_t code_size = 0; /**< Size of spir-v `code` in bytes */
    size_t code_id = 0;   /**< Hash of spir-v `code` for unique ShaderModule */

public:
    explicit ShaderModuleState(String&& name = "ShaderModule") : CoreState(std::move(name)) {}

    Self setStage(VkShaderStageFlagBits stage);
    Self setFilename(const String& filename);
    Self setEntry(const String& entry);
    Self setCode(const uint32_t* code, size_t code_size, size_t code_id);
    Self setCode(const Vector<uint32_t>& code, size_t code_id);

    Res<ShaderModule> into(const CoreApi& api) const;
};

struct ShaderModule : public CoreResource<VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE> {
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    String entry = "main";
    size_t code_id = 0;

protected:
    explicit ShaderModule(const CoreApi& api) : CoreResource(api) {}

public:
    ShaderModule(ShaderModule&&);
    ~ShaderModule();

    static Res<ShaderModule> from(const CoreApi& api, const ShaderModuleState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

/**
 * @brief Hash vkt::core::ShaderModule with vkt::Shader::id
 */
template <>
struct hash<vkt::core::ShaderModule> {
    inline size_t operator()(const vkt::core::ShaderModule& shader_module) const {
        return shader_module.code_id;
    }
};

template <>
struct hash<Vector<vkt::core::ShaderModule>> {
    inline size_t operator()(const Vector<vkt::core::ShaderModule>& shader_modules) const {
        size_t res = 0;
        for (const auto& s : shader_modules) {
            hashCombine(res, s);
        }
        return res;
    }
};

NAMESPACE_END(std)
