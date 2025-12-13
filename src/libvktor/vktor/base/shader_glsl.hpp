#pragma once
#include "generated/vk_string.hpp"
#include "share/helpers.hpp"
#include "share/result.hpp"
#include "share/share.hpp"
#include "share/traits.hpp"
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

NAMESPACE_BEGIN(vkt)

class ShaderGlslIncluder : public glslang::TShader::Includer {
public:
    virtual void releaseInclude(IncludeResult*) override {}
};

class ShaderGlsl : public Singleton<ShaderGlsl> {
    friend class Singleton<ShaderGlsl>;

private:
    glslang::EShTargetLanguage spv = glslang::EShTargetLanguage::EShTargetSpv;
    glslang::EShTargetLanguageVersion spv_version = glslang::EShTargetLanguageVersion::EShTargetSpv_1_5;

    int glsl_version = 450;
    EProfile glsl_profile = ECoreProfile;
    ShaderGlslIncluder glsl_includer{};
    const TBuiltInResource* resouce = GetDefaultResources();
    EShMessages messages = static_cast<EShMessages>(EShMessages::EShMsgDefault | EShMessages::EShMsgVulkanRules |
                                                    EShMessages::EShMsgSpvRules);

private:
    ShaderGlsl();
    ~ShaderGlsl();

private:
    /**
     * @brief Get shader glsl stage
     *
     * Must check return < EShLangCount
     */
    EShLanguage getShaderLanguage(const VkShaderStageFlagBits stage);

public:
    /**
     * @brief Compile glsl into spir-v code
     */
    Res<Vector<uint32_t>> compile(VkShaderStageFlagBits stage,
                                  const String& filename,
                                  const String& code,
                                  const String& entry,
                                  const String& preamble);
};

NAMESPACE_END(std)
