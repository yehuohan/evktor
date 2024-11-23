#include "__helpers.hpp"
#include <assets.hpp>
#include <cstdint>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

std::vector<unsigned int> glsl2spv(const std::string& filename) {
    std::string shader_code = read_shader(filename);
    const char* shader_strings[] = {shader_code.c_str()};
    const int shader_lengths[] = {(int)shader_code.size()};
    const char* shader_filenames[] = {filename.c_str()};
    const char* preamble = "#define TST_ERROR 1";
    const std::vector<std::string> processes{"DTST_ERROR=1"};

    EShMessages messages = static_cast<EShMessages>(EShMessages::EShMsgDefault | EShMessages::EShMsgVulkanRules |
                                                    EShMessages::EShMsgSpvRules);
    EShLanguage language = EShLanguage::EShLangVertex;

    glslang::InitializeProcess();

    glslang::TShader shader(language);
    shader.setStringsWithLengthsAndNames(shader_strings, shader_lengths, shader_filenames, 1);
    shader.setEntryPoint("main");
    shader.setSourceEntryPoint("main");
    // shader.setPreamble(preamble);
    // shader.addProcesses(processes);
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
    const std::string filename = vktdev::Assets::shaderFile("test/triangle.vert");
    std::vector<unsigned int> spirv = glsl2spv(filename);
    tstOut("spv size: {}", spirv.size());
}
