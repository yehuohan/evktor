#include "shader_module.hpp"
#include <fstream>
#include <glslang/Include/ShHandle.h>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

inline static bool getShaderLanguage(EShLanguage& lang, const VkShaderStageFlagBits stage) {
    switch (stage) {
    case VK_SHADER_STAGE_VERTEX_BIT: lang = EShLangVertex; break;
    case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: lang = EShLangTessControl; break;
    case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: lang = EShLangTessEvaluation; break;
    case VK_SHADER_STAGE_GEOMETRY_BIT: lang = EShLangGeometry; break;
    case VK_SHADER_STAGE_FRAGMENT_BIT: lang = EShLangFragment; break;
    case VK_SHADER_STAGE_COMPUTE_BIT: lang = EShLangCompute; break;
    case VK_SHADER_STAGE_RAYGEN_BIT_KHR: lang = EShLangRayGen; break;
    case VK_SHADER_STAGE_ANY_HIT_BIT_KHR: lang = EShLangAnyHit; break;
    case VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR: lang = EShLangClosestHit; break;
    case VK_SHADER_STAGE_MISS_BIT_KHR: lang = EShLangMiss; break;
    case VK_SHADER_STAGE_INTERSECTION_BIT_KHR: lang = EShLangIntersect; break;
    case VK_SHADER_STAGE_CALLABLE_BIT_KHR: lang = EShLangCallable; break;
    case VK_SHADER_STAGE_MESH_BIT_EXT: lang = EShLangMesh; break;
    case VK_SHADER_STAGE_TASK_BIT_EXT: lang = EShLangTask; break;
    default: return false;
    }
    return true;
}

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = ShaderModuleBuilder::Self;

ShaderModule::ShaderModule(ShaderModule&& rhs) : BuiltResource(rhs.device, std::move(rhs.__name)) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    stage = rhs.stage;
    entry = std::move(rhs.entry);
}

ShaderModule::~ShaderModule() {
    if (handle) {
        vkDestroyShaderModule(device, handle, nullptr);
    }
    handle = nullptr;
}

Self ShaderModuleBuilder::setName(const std::string& name) {
    info.name = name;
    return *this;
}

Self ShaderModuleBuilder::setCode(const std::string&& code, VkShaderStageFlagBits stage) {
    info.code = std::move(code);
    info.stage = stage;
    return *this;
}

Self ShaderModuleBuilder::setEntry(const std::string& entry) {
    info.entry = entry;
    return *this;
}

Res<Vector<uint32_t>> ShaderModuleBuilder::glsl2spv() {
    const char* shader_strings[] = {info.code.c_str()};
    const int shader_lengths[] = {(int)info.code.size()};
    const char* shader_filenames[] = {info.name.c_str()};

    EShMessages messages = static_cast<EShMessages>(EShMessages::EShMsgDefault | EShMessages::EShMsgVulkanRules |
                                                    EShMessages::EShMsgSpvRules);
    EShLanguage language;
    if (!getShaderLanguage(language, info.stage)) {
        return Er("Stage = {} is not expected to get an EShLanguage", VkStr(VkShaderStageFlags, info.stage));
    }

    glslang::InitializeProcess();

    glslang::TShader shader(language);
    shader.setStringsWithLengthsAndNames(shader_strings, shader_lengths, shader_filenames, 1);
    shader.setEntryPoint(info.entry.c_str());
    shader.setSourceEntryPoint(info.entry.c_str());
    shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
    if (!shader.parse(GetDefaultResources(), 100, false, messages)) {
        LogE("{}", shader.getInfoLog());
        LogE("{}", shader.getInfoDebugLog());
        return Er("Failed to parse shader: {}", info.name);
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(messages)) {
        LogE("{}", program.getInfoLog());
        LogE("{}", program.getInfoDebugLog());
        return Er("Failed to link shader: {}", info.name);
    }
    glslang::TIntermediate* intermediate = program.getIntermediate(language);

    Vector<uint32_t> spirv;
    glslang::GlslangToSpv(*intermediate, spirv);

    glslang::FinalizeProcess();

    return Ok(std::move(spirv));
}

ShaderModuleBuilder::Built ShaderModuleBuilder::build() {
    auto res_spirv = glsl2spv();
    if (res_spirv.isErr()) {
        return Err(res_spirv.unwrapErr());
    }
    auto spirv = res_spirv.unwrap();
    auto shader_ci = Itor::ShaderModuleCreateInfo();
    shader_ci.codeSize = spirv.size() * sizeof(uint32_t);
    shader_ci.pCode = spirv.data();

    ShaderModule shader_module(device, std::move(info.__name));
    OnRet(vkCreateShaderModule(device, &shader_ci, nullptr, shader_module), "Failed to create shader module for {}", info.name);
    OnName(shader_module);
    shader_module.entry = std::move(info.entry);
    shader_module.stage = info.stage;

    return Ok(std::move(shader_module));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
