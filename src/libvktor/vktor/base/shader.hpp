#pragma once
#include "vktor/core/api/api.hpp"
#include "vktor/core/shader_module.hpp"

NAMESPACE_BEGIN(vkt)

class Shader;

// class ShaderVariant : private NonCopyable {
//     Self defMacro(const String& macro);
// };

/**
 * @brief Shader glsl source code
 */
class ShaderSource : private NonCopyable {
    friend class Shader;

public:
    enum Stage {
        Vert = VK_SHADER_STAGE_VERTEX_BIT,
        Frag = VK_SHADER_STAGE_FRAGMENT_BIT,
        Comp = VK_SHADER_STAGE_COMPUTE_BIT,
    };

private:
    Stage stage;
    String filename{""};
    String entry = "main";
    String code{""};
    size_t id = 0; /**< id = hash(code) */

private:
    ShaderSource() {};

public:
    static Res<ShaderSource> from(ShaderSource::Stage stage, String&& code);
    ShaderSource(ShaderSource&&);

    inline size_t getId() const {
        return id;
    }
};

struct ShaderDescriptor {
    /** Supported descriptor type */
    enum Type {
        Sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
        ImageSampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        Image = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        ImageStorage = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        TexelBufferUniform = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
        TexelBufferStorage = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
        BufferUniform = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        BufferStorage = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        BufferDynamicUniform = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        BufferDynamicStorage = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
        InputAttachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
    };

    // String name;
    Type type;
    uint32_t set;
    uint32_t binding;
    uint32_t count;

    ShaderDescriptor(Type type, uint32_t set, uint32_t binding, uint32_t count)
        : type(type)
        , set(set)
        , binding(binding)
        , count(count) {}
};

/**
 * @brief Shader spir-v code
 */
class Shader : private NonCopyable {
private:
    VkShaderStageFlagBits stage;
    String filename{""};
    String entry = "main";
    Vector<uint32_t> spv_code{};
    size_t id = 0; /**< id = hash(spv_code) */
    /** Map descriptor set index to it's all descriptor */
    HashMap<uint32_t, Vector<ShaderDescriptor>> desc_sets{};

private:
    Shader() {};

    Res<Vector<uint32_t>> glsl2spv(const String& code);

public:
    static Res<Shader> from(const ShaderSource& source);
    Shader(Shader&&);

    Res<core::ShaderModule> into(const core::CoreApi& api) const;
    inline VkShaderStageFlagBits getStage() const {
        return stage;
    }
    inline const String& getFilename() const {
        return filename;
    }
    inline const String& getEntry() const {
        return entry;
    }
    inline const Vector<uint32_t>& getSpvCode() const {
        return spv_code;
    }
    inline size_t getId() const {
        return id;
    }
    inline void addDescriptor(ShaderDescriptor::Type type, uint32_t binding, uint32_t set = 0, uint32_t count = 1) {
        desc_sets[set].push_back(ShaderDescriptor(type, set, binding, count));
    }
    inline const HashMap<uint32_t, Vector<ShaderDescriptor>>& getDescriptorSets() const {
        return desc_sets;
    }
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

/**
 * @brief Hash vkt::ShaderSource for unique vkt::Shader
 */
template <>
struct hash<vkt::ShaderSource> {
    inline size_t operator()(const vkt::ShaderSource& shader_source) const {
        return shader_source.getId();
    }
};

/**
 * @brief Hash vkt::Shader for unique vkt::core::ShaderModule
 */
template <>
struct hash<vkt::Shader> {
    inline size_t operator()(const vkt::Shader& shader) const {
        return shader.getId();
    }
};

template <>
struct hash<Vector<vkt::Shader>> {
    // C++ doesn't support store Shader& in Vector, so use Shader* instead.
    inline size_t operator()(const Vector<vkt::Shader>& shaders) const {
        size_t res = 0;
        for (const auto& s : shaders) {
            hashCombine(res, s);
        }
        return res;
    }
};

NAMESPACE_END(std)
