#pragma once
#include "__core.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ShaderModule;

class ShaderModuleState : public CoreStater<ShaderModuleState> {
    friend struct ShaderModule;

private:
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    std::string filename = "shader.glsl";
    std::string entry = "main";
    const uint32_t* code = nullptr;
    size_t code_size = 0; /**< Size of spir-v `code` in bytes */
    size_t code_id = 0;   /**< Hash of spir-v `code` for unique ShaderModule */

public:
    explicit ShaderModuleState(Name&& name = "ShaderModule") : CoreStater(std::move(name)) {}

    Self setStage(VkShaderStageFlagBits stage);
    Self setFilename(const std::string& filename);
    Self setEntry(const std::string& entry);
    Self setCode(const uint32_t* code, size_t code_size, size_t code_id);
    Self setCode(const Vector<uint32_t>& code, size_t code_id);

    Res<ShaderModule> into(const Device& device) const;
};

struct ShaderModule : public CoreResource<VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE, Device> {
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    std::string entry = "main";
    size_t code_id = 0;

protected:
    explicit ShaderModule(const Device& device) : CoreResource(device) {}

public:
    ShaderModule(ShaderModule&&);
    ~ShaderModule();

    static Res<ShaderModule> from(const Device& device, const ShaderModuleState& info);
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
struct hash<vkt::Vector<vkt::core::ShaderModule>> {
    inline size_t operator()(const vkt::Vector<vkt::core::ShaderModule>& shader_modules) const {
        size_t res = 0;
        for (const auto& s : shader_modules) {
            vkt::hashCombine(res, s);
        }
        return res;
    }
};

NAMESPACE_END(std)
