#pragma once
#include "vktor/core/shader_module.hpp"

NAMESPACE_BEGIN(vkt)

struct ShaderInputOutput {
    uint32_t location;
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
    // uint32_t input_attachment_index;
    uint32_t set;
    uint32_t binding;
    uint32_t count;

    ShaderDescriptor(Type type, uint32_t set, uint32_t binding, uint32_t count)
        : type(type)
        , set(set)
        , binding(binding)
        , count(count) {}
};

struct ShaderPushConstant {
    uint32_t size = 0; /** Size > 0 means shader has push constant */
    uint32_t offset = 0;
};

struct ShaderSpecConstant {
    typedef VkSpecializationMapEntry Entry;
    Vector<uint8_t> data{};
    Vector<Entry> entries{};
};

/**
 * @brief Shader for spir-v
 */
class Shader {
    friend struct std::hash<Shader>;

private:
    String src = "";                              /**< Glsl or slang shader source */
    size_t src_id = 0;                            /**< src_id = hash(src) */
    String src_path = "";                         /**< Source fullpath for debug */
    Vector<std::pair<String, String>> src_defs{}; /**< Source defines */

private:
    VkShaderStageFlagBits stage = (VkShaderStageFlagBits)0;
    String entry = "main";          /**< Shader entry function */
    mutable Vector<uint32_t> spv{}; /**< The spir-v code compiled from `src` */
    mutable size_t spv_id = 0;      /**< spv_id = hash(*this) on this shader compiled the spv */

private:
    // TODO: automating shader resources
    // Vector<ShaderInputOutput> inputs{};
    // Vector<ShaderInputOutput> outputs{};
    HashMap<uint32_t, Vector<ShaderDescriptor>> desc_sets{}; /**< Map descriptor set index to it's all descriptor */
    ShaderPushConstant push_constant{};
    ShaderSpecConstant spec_constant{};

private:
    Shader() = default;

public:
    using Self = Shader&;

    Shader(const Shader& rhs) = default;
    Shader(Shader&&);

    static Shader from(const VkShaderStageFlagBits stage, String&& source, const String& fullpath = "");
    static Shader fromVert(String&& source, const String& fullpath = "") {
        return std::move(from(VK_SHADER_STAGE_VERTEX_BIT, std::move(source), fullpath));
    }
    static Shader fromFrag(String&& source, const String& fullpath = "") {
        return std::move(from(VK_SHADER_STAGE_FRAGMENT_BIT, std::move(source), fullpath));
    }
    static Shader fromComp(String&& source, const String& fullpath = "") {
        return std::move(from(VK_SHADER_STAGE_COMPUTE_BIT, std::move(source), fullpath));
    }

    Res<core::ShaderModule> into(const core::CoreApi& api) const;

public:
    Self setDefine(const String& name, const String& value = "");
    Self delDefine(const String& name);
    Self delAllDefines();
    inline const String& getSourcePath() const {
        return src_path;
    }
    String getPreamble() const;

public:
    Self setEntry(const String& entry);
    inline VkShaderStageFlagBits getStage() const {
        return stage;
    }
    inline const String& getEntry() const {
        return entry;
    }

public:
    Self addDescriptor(ShaderDescriptor::Type type, uint32_t binding, uint32_t set = 0, uint32_t count = 1);
    Self setPushConstant(uint32_t size, uint32_t offset = 0);
    Self addSpecConstant(uint32_t id, const uint8_t* data, size_t data_size);
    inline const HashMap<uint32_t, Vector<ShaderDescriptor>>& getDescriptorSets() const {
        return desc_sets;
    }
    inline const ShaderPushConstant& getPushConstant() const {
        return push_constant;
    }
    inline const ShaderSpecConstant& getSpecConstant() const {
        return spec_constant;
    }
    inline core::ShaderSpecialization getSpecialization() const {
        return core::ShaderSpecialization{spec_constant.data.data(), spec_constant.data.size(), spec_constant.entries};
    }
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::Shader> {
    inline size_t operator()(const vkt::Shader& shader) const {
        size_t res = 0;
        // Source + preamble + stage + entry => unique key for spir-v code or shader module
        hashCombine(res, shader.src_id);
        hashCombine(res, shader.getPreamble());
        hashCombine(res, shader.stage);
        hashCombine(res, shader.entry);
        return res;
    }
};

template <>
struct hash<Vector<CRef<vkt::Shader>>> {
    inline size_t operator()(const Vector<CRef<vkt::Shader>>& shaders) const {
        size_t res = 0;
        for (const auto& s : shaders) {
            hashCombine(res, s.get());
        }
        return res;
    }
};

NAMESPACE_END(std)
