#include "shader.hpp"
#include <fstream>
#include <glslang/Include/ShHandle.h>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

NAMESPACE_BEGIN(vkt)

using namespace core;

static Res<VkShaderStageFlagBits> getShaderStage(const std::string& filename) {
    std::string::size_type n = filename.rfind('.');
    if (n == std::string::npos) {
        return Er("Failed to get shader stage: {}", filename);
    }
    std::string suffix = filename.substr(n + 1);

    VkShaderStageFlagBits stage;
    if ("vert" == suffix) {
        stage = VK_SHADER_STAGE_VERTEX_BIT;
    } else if ("frag" == suffix) {
        stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    } else if ("geom" == suffix) {
        stage = VK_SHADER_STAGE_GEOMETRY_BIT;
    } else if ("comp" == suffix) {
        stage = VK_SHADER_STAGE_COMPUTE_BIT;
    } else {
        return Er("Unrecognized shader type: {}", suffix);
    }
    return Ok(stage);
}

static Res<std::string> readShader(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        return Er("Failed to read shader: {}", filename);
    }
    return Ok(std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()}));
}

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

Res<ShaderSource> ShaderSource::from(const std::string& filename) {
    ShaderSource shader_source{};

    auto stage = getShaderStage(filename);
    OnErr(stage);
    shader_source.stage = stage.unwrap();
    shader_source.filename = filename;
    shader_source.entry = "main";
    auto code = readShader(filename);
    OnErr(code);
    shader_source.code = std::move(code.unwrap());
    shader_source.id = hash(shader_source.code);

    return Ok(std::move(shader_source));
}

ShaderSource::ShaderSource(ShaderSource&& rhs) {
    stage = rhs.stage;
    filename = std::move(rhs.filename);
    entry = std::move(rhs.entry);
    code = std::move(rhs.code);
    id = rhs.id;
    rhs.id = 0;
}

Res<Shader> Shader::from(const ShaderSource& source) {
    Shader shader{};

    shader.stage = source.stage;
    shader.filename = source.filename;
    shader.entry = source.entry;
    // Must set stage, filename and entry before glsl2spv()
    auto res = shader.glsl2spv(source.code);
    OnErr(res);
    shader.spv_code = res.unwrap();
    shader.id = hash(std::string{reinterpret_cast<const char*>(shader.spv_code.data()),
                                 reinterpret_cast<const char*>(shader.spv_code.data() + shader.spv_code.size())});

    return Ok(std::move(shader));
}

Shader::Shader(Shader&& rhs) {
    stage = rhs.stage;
    filename = std::move(rhs.filename);
    entry = std::move(rhs.entry);
    spv_code = std::move(rhs.spv_code);
    id = rhs.id;
    rhs.id = 0;
    desc_sets = std::move(rhs.desc_sets);
}

Res<Vector<uint32_t>> Shader::glsl2spv(const std::string& code) {
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
        vktLogE("{}", shader.getInfoLog());
        vktLogE("{}", shader.getInfoDebugLog());
        return Er("Failed to parse shader: {}", filename);
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(messages)) {
        vktLogE("{}", program.getInfoLog());
        vktLogE("{}", program.getInfoDebugLog());
        return Er("Failed to link shader: {}", filename);
    }
    glslang::TIntermediate* intermediate = program.getIntermediate(language);

    Vector<uint32_t> spirv;
    glslang::GlslangToSpv(*intermediate, spirv);

    glslang::FinalizeProcess();

    return Ok(std::move(spirv));
}

Res<core::ShaderModule> Shader::into(const core::Device& device) const {
    return ShaderModuleState("VertShaderModule")
        .setStage(stage)
        .setFilename(filename)
        .setCode(spv_code, id)
        .setEntry(entry)
        .into(device);
}

NAMESPACE_END(vkt)
