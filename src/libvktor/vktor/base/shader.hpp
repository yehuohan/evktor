#pragma once
#include "vktor/core/api/api.hpp"
#include "vktor/core/shader_module.hpp"

NAMESPACE_BEGIN(vkt)

class Shader;

/**
 * @brief Shader source code to compile to spir-v code
 */
class ShaderSource : private NonCopyable {
    friend class Shader;
    friend struct std::hash<ShaderSource>;

private:
    String filename{""};
    String code{""};
    size_t id = 0; /**< id = hash(code) */

public:
    ShaderSource(const String& filename, String&& code);
    ShaderSource(ShaderSource&&);
};

/**
 * @brief Shader state for compiling glsl
 */
class ShaderState : private NonCopyable {
    friend class Shader;
    friend struct std::hash<ShaderState>;

private:
    VkShaderStageFlagBits stage = (VkShaderStageFlagBits)0;
    String entry = "main";
    Vector<std::pair<String, String>> defines{};

public:
    using Self = ShaderState&;

    inline Self setStage(VkShaderStageFlagBits _stage) {
        stage = _stage;
        return *this;
    }
    inline Self setEntry(const String& _entry) {
        entry = _entry;
        return *this;
    }

    Self setDefine(const String& name, const String& value = "");
    Self delDefine(const String& name);
    Self delAllDefines();
    String getPreamble() const;
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
    friend struct std::hash<Shader>;

private:
    const VkShaderStageFlagBits stage;
    const String filename;
    const String entry;
    Vector<uint32_t> spv_code{};
    size_t id = 0; /**< id = hash(spv_code) */

    /** Map descriptor set index to it's all descriptor */
    HashMap<uint32_t, Vector<ShaderDescriptor>> desc_sets{};

private:
    Shader(const VkShaderStageFlagBits stage, const String& filename, const String& entry)
        : stage(stage)
        , filename(filename)
        , entry(entry) {}

public:
    Shader(Shader&&);

    static Res<Shader> from(const ShaderSource& source, const ShaderState& state);
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
        return shader_source.id;
    }
};

/**
 * @brief Hash vkt::ShaderSource for unique vkt::Shader
 */
template <>
struct hash<vkt::ShaderState> {
    inline size_t operator()(const vkt::ShaderState& shader_state) const {
        size_t res = 0;
        hashCombine(res, shader_state.stage);
        hashCombine(res, shader_state.entry);
        return res;
    }
};

/**
 * @brief Hash vkt::Shader for unique vkt::core::ShaderModule
 */
template <>
struct hash<vkt::Shader> {
    inline size_t operator()(const vkt::Shader& shader) const {
        return shader.id;
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
