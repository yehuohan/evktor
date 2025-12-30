#include "shader_glsl.hpp"

NAMESPACE_BEGIN(vkt)

ShaderGlsl::ShaderGlsl() {
    if (glslang::InitializeProcess()) {
        vktLogD("Initialized glslang process");
    } else {
        vktLogE("Failed to initialize glslang process");
    }
}

ShaderGlsl::~ShaderGlsl() {
    glslang::FinalizeProcess();
}

EShLanguage ShaderGlsl::getShaderLanguage(const VkShaderStageFlagBits stage) {
    EShLanguage lang;
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
    default: lang = EShLangCount;
    }
    return lang;
}

Res<Vector<uint32_t>> ShaderGlsl::compile(VkShaderStageFlagBits stage,
                                          const String& code,
                                          const String& entry,
                                          const String& preamble,
                                          const String& filename) {
    const char* shader_strings[] = {code.c_str()};
    const int shader_lengths[] = {(int)code.size()};
    const char* shader_filenames[] = {filename.c_str()};
    const EShLanguage language = getShaderLanguage(stage);
    if (language >= EShLangCount) {
        return Er("Stage = {} is not expected to get an EShLanguage", VkStr(VkShaderStageFlags, stage));
    }

    glslang::TShader shader(language);
    shader.setStringsWithLengthsAndNames(shader_strings, shader_lengths, shader_filenames, 1);
    shader.setSourceEntryPoint(entry.c_str()); // Select entry point of glsl
    shader.setEntryPoint(entry.c_str());       // Rename entry point of spir-v
    shader.setPreamble(preamble.c_str());
    shader.setEnvTarget(spv, spv_version);
    if (!shader.parse(resouce, glsl_version, glsl_profile, false, false, messages, glsl_includer)) {
        vktOut("{}", shader.getInfoLog());
        vktOut("{}", shader.getInfoDebugLog());
        return Er("Failed to parse shader: {}", filename);
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(messages)) {
        vktOut("{}", program.getInfoLog());
        vktOut("{}", program.getInfoDebugLog());
        return Er("Failed to link shader: {}", filename);
    }
    glslang::TIntermediate* intermediate = program.getIntermediate(language);

    Vector<uint32_t> spirv;
    glslang::GlslangToSpv(*intermediate, spirv);

    return Ok(std::move(spirv));
}

NAMESPACE_END(std)
