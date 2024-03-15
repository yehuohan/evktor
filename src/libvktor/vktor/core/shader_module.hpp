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
    std::string code = "";
    std::string entry = "main";

private:
    Res<Vector<uint32_t>> glsl2spv() const;

public:
    explicit ShaderModuleState(Name&& name = "ShaderModule") : CoreStater(std::move(name)) {}

    Self setFilename(const std::string& filename);
    Self setCode(std::string&& code, VkShaderStageFlagBits stage);
    Self setEntry(const std::string& entry);

    Res<ShaderModule> into(const Device& device) const;
};

struct ShaderModule : public CoreResource<VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE, Device> {
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    std::string entry = "main";

    ShaderModule(const Device& device) : CoreResource(device) {}
    ShaderModule(ShaderModule&&);
    ~ShaderModule();

    static Res<ShaderModule> from(const Device& device, const ShaderModuleState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
