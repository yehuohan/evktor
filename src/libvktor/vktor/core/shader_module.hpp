#pragma once
#include "__builder.hpp"
#include "device.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct Shader : public BuiltResource<VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE, Device> {
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    std::string entry = "main";

    Shader(const Device& device, Name&& name) : BuiltResource(device, std::move(name)) {}
    Shader(Shader&&);
    ~Shader();
};

struct ShaderInfo : public BuilderInfo {
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    std::string name = "shader.glsl";
    std::string code = "";
    std::string entry = "main";
};

class ShaderBuilder : public Builder<ShaderBuilder, Shader, ShaderInfo> {
private:
    const Device& device;

public:
    explicit ShaderBuilder(const Device& device, Name&& name = "ShaderModule") : Builder(std::move(name)), device(device) {}
    virtual Built build() override;

    Self setName(const std::string& name);
    Self setCode(const std::string&& code, VkShaderStageFlagBits stage);
    // Self defMacro(const std::string& macro);
    Self setEntry(const std::string& entry);

private:
    Res<Vector<uint32_t>> glsl2spv();
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
