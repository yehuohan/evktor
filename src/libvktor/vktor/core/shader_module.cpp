#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ShaderModuleState::Self;

Self ShaderModuleState::setCode(const uint32_t* _code, size_t _code_size) {
    code = _code;
    code_size = _code_size;
    return *this;
}

Self ShaderModuleState::setCode(const Vector<uint32_t>& _code) {
    code = _code.data();
    code_size = _code.size() * sizeof(uint32_t);
    return *this;
}

Res<ShaderModule> ShaderModuleState::into(const CoreApi& api) const {
    return ShaderModule::from(api, *this);
}

ShaderModule::ShaderModule(ShaderModule&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

ShaderModule::~ShaderModule() {
    if (!__borrowed && handle) {
        vkDestroyShaderModule(api, handle, api);
    }
    handle = nullptr;
}

Res<ShaderModule> ShaderModule::from(const CoreApi& api, const ShaderModuleState& info) {
    ShaderModule shader_module(api);

    auto shader_ci = Itor::ShaderModuleCreateInfo(info.__next);
    shader_ci.codeSize = info.code_size;
    shader_ci.pCode = info.code;
    OnRet(vkCreateShaderModule(api, &shader_ci, api, shader_module), "Failed to create shader module");
    OnName(shader_module, info.__name);

    return Ok(std::move(shader_module));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
