#include "__helpers.hpp"
#include <assets.hpp>
#include <cstdint>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

std::vector<unsigned int> glsl2spv(const String& filename) {
    String shader_code = read_shader(filename);
    const char* shader_strings[] = {shader_code.c_str()};
    const int shader_lengths[] = {(int)shader_code.size()};
    const char* shader_filenames[] = {filename.c_str()};
    const char* preamble = "#define TST_ERROR 1\n";

    EShMessages messages = static_cast<EShMessages>(EShMessages::EShMsgDefault | EShMessages::EShMsgVulkanRules |
                                                    EShMessages::EShMsgSpvRules);
    EShLanguage language = EShLanguage::EShLangVertex;

    glslang::InitializeProcess();

    glslang::TShader shader(language);
    shader.setStringsWithLengthsAndNames(shader_strings, shader_lengths, shader_filenames, 1);
    shader.setSourceEntryPoint("main"); // Select entry point of glsl
    shader.setEntryPoint("main");       // Rename entry point of spir-v
    // shader.setPreamble(preamble);
    shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
    if (!shader.parse(GetDefaultResources(), 100, false, messages)) {
        tstOut("{}", shader.getInfoLog());
        tstOut("{}", shader.getInfoDebugLog());
        throw std::runtime_error("Failed to parse shader");
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(messages)) {
        tstOut("{}", program.getInfoLog());
        tstOut("{}", program.getInfoDebugLog());
        throw std::runtime_error("Failed to link shader");
    }
    glslang::TIntermediate* intermediate = program.getIntermediate(language);

    std::vector<unsigned int> spirv;
    glslang::GlslangToSpv(*intermediate, spirv);

    glslang::FinalizeProcess();

    return std::move(spirv);
}

void case_glslang() {
    const String filename = vktdev::Assets::shader("test/triangle.vert");
    std::vector<unsigned int> spirv = glsl2spv(filename);
    tstOut("spv size: {}", spirv.size());
}
