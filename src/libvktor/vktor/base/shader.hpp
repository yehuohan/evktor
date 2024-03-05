#pragma once
#include "vktor/core/shader_module.hpp"

NAMESPACE_BEGIN(vkt)

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

    // std::string name;
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

class Shader : private NonCopyable {
private:
    std::string filename;
    std::string code;
    VkShaderStageFlagBits stage;
    Vector<ShaderDescriptor> descriptors{};

private:
    Shader(){};

public:
    Shader(Shader&&);

    inline const std::string& getFilename() const {
        return filename;
    }
    inline const std::string& getCode() const {
        return code;
    }
    inline VkShaderStageFlagBits getStage() const {
        return stage;
    }
    inline void addDescriptor(ShaderDescriptor::Type type, uint32_t binding, uint32_t set = 0, uint32_t count = 1) {
        descriptors.push_back(ShaderDescriptor(type, set, binding, count));
    }
    inline const Vector<ShaderDescriptor>& getDescriptors() const {
        return descriptors;
    }

    static Res<Shader> load(const std::string& filename);
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::Shader> {
    size_t operator()(const vkt::Shader& shader) const {
        size_t res = 0;
        vkt::hashCombine(res, shader.getFilename());
        return res;
    }
};

template <>
struct hash<vkt::Vector<const vkt::Shader*>> {
    size_t operator()(const vkt::Vector<const vkt::Shader*>& shaders) const {
        size_t res = 0;
        for (const auto s : shaders) {
            if (s) {
                vkt::hashCombine(res, *s);
            }
        }
        return res;
    }
};

NAMESPACE_END(std)
