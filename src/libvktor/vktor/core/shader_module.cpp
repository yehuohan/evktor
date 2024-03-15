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

using Self = ShaderModuleState::Self;

Self ShaderModuleState::setFilename(const std::string& _filename) {
    filename = _filename;
    return *this;
}

Self ShaderModuleState::setCode(std::string&& _code, VkShaderStageFlagBits _stage) {
    code = std::move(_code);
    stage = _stage;
    return *this;
}

Self ShaderModuleState::setEntry(const std::string& _entry) {
    entry = _entry;
    return *this;
}

Res<Vector<uint32_t>> ShaderModuleState::glsl2spv() const {
    const char* shader_strings[] = {code.c_str()};
    const int shader_lengths[] = {(int)code.size()};
    const char* shader_filenames[] = {filename.c_str()};

    EShMessages messages = static_cast<EShMessages>(EShMessages::EShMsgDefault | EShMessages::EShMsgVulkanRules |
                                                    EShMessages::EShMsgSpvRules);
    EShLanguage language;
    if (!getShaderLanguage(language, stage)) {
        return Er("Stage = {} is not expected to get an EShLanguage", VkStr(VkShaderStageFlags, stage));
    }

    glslang::InitializeProcess();

    glslang::TShader shader(language);
    shader.setStringsWithLengthsAndNames(shader_strings, shader_lengths, shader_filenames, 1);
    shader.setEntryPoint(entry.c_str());
    shader.setSourceEntryPoint(entry.c_str());
    shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
    if (!shader.parse(GetDefaultResources(), 100, false, messages)) {
        LogE("{}", shader.getInfoLog());
        LogE("{}", shader.getInfoDebugLog());
        return Er("Failed to parse shader: {}", filename);
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(messages)) {
        LogE("{}", program.getInfoLog());
        LogE("{}", program.getInfoDebugLog());
        return Er("Failed to link shader: {}", filename);
    }
    glslang::TIntermediate* intermediate = program.getIntermediate(language);

    Vector<uint32_t> spirv;
    glslang::GlslangToSpv(*intermediate, spirv);

    glslang::FinalizeProcess();

    return Ok(std::move(spirv));
}

Res<ShaderModule> ShaderModuleState::into(const Device& device) const {
    return ShaderModule::from(device, *this);
}

ShaderModule::ShaderModule(ShaderModule&& rhs) : CoreResource(rhs.device) {
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

Res<ShaderModule> ShaderModule::from(const Device& device, const ShaderModuleState& info) {
    auto res = info.glsl2spv();
    OnErr(res);
    auto spirv = res.unwrap();
    auto shader_ci = Itor::ShaderModuleCreateInfo();
    shader_ci.codeSize = spirv.size() * sizeof(uint32_t);
    shader_ci.pCode = spirv.data();

    ShaderModule shader_module(device);
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
