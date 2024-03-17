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
    size_t code_size = 0;

public:
    explicit ShaderModuleState(Name&& name = "ShaderModule") : CoreStater(std::move(name)) {}

    Self setStage(VkShaderStageFlagBits stage);
    Self setFilename(const std::string& filename);
    Self setEntry(const std::string& entry);
    Self setCode(const uint32_t* code, size_t code_size);
    Self setCode(const Vector<uint32_t>& code);

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
