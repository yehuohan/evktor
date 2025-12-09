#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct ShaderModule;

class ShaderModuleState : public CoreState<ShaderModuleState> {
    friend struct ShaderModule;

private:
    const uint32_t* code = nullptr;
    size_t code_size = 0; /**< Size of spir-v `code` in bytes */

public:
    explicit ShaderModuleState(String&& name = "ShaderModule") : CoreState(std::move(name)) {}

    Self setCode(const uint32_t* code, size_t code_size);
    Self setCode(const Vector<uint32_t>& code);

    Res<ShaderModule> into(const CoreApi& api) const;
};

struct ShaderModule : public CoreResource<VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE> {
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

template <>
struct hash<vkt::core::ShaderModule> {
    inline size_t operator()(const vkt::core::ShaderModule& shader_module) const {
        return hash<VkShaderModule>{}(shader_module);
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
