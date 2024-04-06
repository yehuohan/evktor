#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ShaderModuleState::Self;

Self ShaderModuleState::setStage(VkShaderStageFlagBits _stage) {
    stage = _stage;
    return *this;
}

Self ShaderModuleState::setFilename(const std::string& _filename) {
    filename = _filename;
    return *this;
}

Self ShaderModuleState::setCode(const uint32_t* _code, size_t _code_size, size_t _code_id) {
    code = _code;
    code_size = _code_size;
    code_id = _code_id;
    return *this;
}

Self ShaderModuleState::setCode(const Vector<uint32_t>& _code, size_t _code_id) {
    code = _code.data();
    code_size = _code.size() * sizeof(uint32_t);
    code_id = _code_id;
    return *this;
}

Self ShaderModuleState::setEntry(const std::string& _entry) {
    entry = _entry;
    return *this;
}

Res<ShaderModule> ShaderModuleState::into(const Device& device) const {
    return ShaderModule::from(device, *this);
}

ShaderModule::ShaderModule(ShaderModule&& rhs) : CoreResource(rhs.device) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    stage = rhs.stage;
    entry = std::move(rhs.entry);
    code_id = rhs.code_id;
}

ShaderModule::~ShaderModule() {
    if (!__borrowed && handle) {
        vkDestroyShaderModule(device, handle, nullptr);
    }
    handle = nullptr;
}

Res<ShaderModule> ShaderModule::from(const Device& device, const ShaderModuleState& info) {
    ShaderModule shader_module(device);

    auto shader_ci = Itor::ShaderModuleCreateInfo();
    shader_ci.codeSize = info.code_size;
    shader_ci.pCode = info.code;
    OnRet(vkCreateShaderModule(device, &shader_ci, nullptr, shader_module),
          "Failed to create shader module for {}",
          info.filename);
    OnName(shader_module, info.__name);
    shader_module.entry = std::move(info.entry);
    shader_module.stage = info.stage;

    return Ok(std::move(shader_module));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
