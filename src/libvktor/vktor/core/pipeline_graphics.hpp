#pragma once
#include "__core.hpp"
#include "__hash.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct GraphicsPipeline;

class GraphicsPipelineState : public CoreState<GraphicsPipelineState> {
    friend struct GraphicsPipeline;
    friend struct std::hash<GraphicsPipelineState>;

public:
    struct ShaderSpecialization {
        const void* data = nullptr;
        size_t data_size = 0;
        Vector<VkSpecializationMapEntry> entries{};
    };
    struct Shader {
        VkShaderModule shader = VK_NULL_HANDLE;
        VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
        String entry = "main";
        ShaderSpecialization spec{};
    };

private:
    VkPipelineCreateFlags flags = 0;
    Vector<Shader> shaders{};
    struct VertexInputState {
        Vector<VkVertexInputBindingDescription> bindings{};
        Vector<VkVertexInputAttributeDescription> attributes{};
    } vertex_input{};
    VkPipelineInputAssemblyStateCreateInfo input_assembly;
    VkPipelineTessellationStateCreateInfo tessellation;
    Vector<VkViewport> viewports{};
    Vector<VkRect2D> scissors{};
    VkPipelineRasterizationStateCreateInfo rasterization;
    VkPipelineMultisampleStateCreateInfo multisample;
    VkPipelineDepthStencilStateCreateInfo depth_stencil;
    struct ColorBlendState {
        VkBool32 enable_logic_op = VK_FALSE;
        VkLogicOp logic_op = VK_LOGIC_OP_CLEAR;
        Vector<VkPipelineColorBlendAttachmentState> attachments{};
        float constants[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    } color_blend{};
    Vector<VkDynamicState> dynamics{};
    VkPipelineLayout layout = VK_NULL_HANDLE;
    VkRenderPass render_pass = VK_NULL_HANDLE;
    uint32_t subpass = 0;

private:
#if VK_KHR_dynamic_rendering // As a block region
    bool has_rendering = false;
    Vector<VkFormat> color_formats{};
    VkFormat depth_format = VK_FORMAT_UNDEFINED;
    VkFormat stencil_format = VK_FORMAT_UNDEFINED;
#endif

public:
    explicit GraphicsPipelineState(String&& name = "GraphicsPipeline");

    Self setFlags(VkPipelineCreateFlags flags);
    Self addShader(VkShaderModule shader,
                   VkShaderStageFlagBits stage,
                   const String& entry = "main",
                   const ShaderSpecialization& spec = {nullptr, 0, {}});
    Self addVertShader(VkShaderModule shader,
                       const String& entry = "main",
                       const ShaderSpecialization& spec = {nullptr, 0, {}});
    Self addFragShader(VkShaderModule shader,
                       const String& entry = "main",
                       const ShaderSpecialization& spec = {nullptr, 0, {}});
    Self addVertexInputBinding(const VkVertexInputBindingDescription& binding);
    Self addVertexInputBindings(const Vector<VkVertexInputBindingDescription>& bindings);
    Self addVertexInputAttribute(const VkVertexInputAttributeDescription& attribute);
    Self addVertexInputAttributes(const Vector<VkVertexInputAttributeDescription>& attributes);
    Self setInputAssembly(VkPrimitiveTopology topology, VkBool32 enable_primitive_restart);
    // Self setTessellation();
    Self addViewport(const VkViewport& viewport);
    Self addViewport(float x, float y, float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);
    Self addScissor(const VkRect2D& rect);
    Self addScissor(int32_t x, int32_t y, uint32_t width, uint32_t height);
    Self setRasterizationDepthClamp(VkBool32 enable_depth_clamp);
    Self setRasterizationDiscard(VkBool32 enable_rasterizer_discard);
    Self setRasterizationPolygonMode(VkPolygonMode polygon_mode);
    Self setRasterizationCullFace(VkCullModeFlags cull_mode, VkFrontFace front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE);
    Self setRasterizationDepthBias(VkBool32 enable, float constant = 0.0f, float clamp = 0.0f, float slope = 0.0f);
    Self setRasterizationLineWith(float line_width);
    Self setMultisampleCount(VkSampleCountFlagBits sample_count);
    Self setMultisampleShading(VkBool32 enable, float min_sample_shading = 0.0f);
    Self setDepthTest(VkBool32 enable_test, VkBool32 enable_write, VkCompareOp op = VK_COMPARE_OP_LESS);
    Self setDepthBoundsTest(VkBool32 enable, float min_depth = 0.0f, float max_depth = 1.0f);
    Self setStencilTest(VkBool32 enable,
                        const VkStencilOpState& front = VkStencilOpState{},
                        const VkStencilOpState& back = VkStencilOpState{});
    Self setColorBlendLogicOp(VkBool32 enable, VkLogicOp op = VK_LOGIC_OP_CLEAR);
    Self addColorBlendAttachment(const VkPipelineColorBlendAttachmentState& attachment);
    Self addColorBlendAttachments(const Vector<VkPipelineColorBlendAttachmentState>& attachments);
    Self setColorBlendConstants(float c0, float c1, float c2, float c3);
    Self addDynamic(VkDynamicState dynamic);
    Self addDynamics(const Vector<VkDynamicState>& dynamics);
    Self setPipelineLayout(VkPipelineLayout layout);
    Self setRenderPass(VkRenderPass render_pass, uint32_t subpass_index = 0);

public:
#if VK_KHR_dynamic_rendering
    /**
     * @brief Chain VkPipelineRenderingCreateInfo for dynamic rendering
     */
    Self chainRendering(const Vector<VkFormat>& colors,
                        VkFormat depth = VK_FORMAT_UNDEFINED,
                        VkFormat stencil = VK_FORMAT_UNDEFINED);
#endif

    Res<GraphicsPipeline> into(const CoreApi& api) const;
};

struct GraphicsPipeline : public CoreResource<VkPipeline, VK_OBJECT_TYPE_PIPELINE> {
protected:
    explicit GraphicsPipeline(const CoreApi& api) : CoreResource(api) {}

public:
    GraphicsPipeline(GraphicsPipeline&&);
    ~GraphicsPipeline();

    static Res<GraphicsPipeline> from(const CoreApi& api, const GraphicsPipelineState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::GraphicsPipelineState> {
    size_t operator()(const vkt::core::GraphicsPipelineState& pso) const {
        // TODO: Hash according to what contained in GraphicsPipelineState::dynamics
        size_t res = 0;
        for (const auto& s : pso.shaders) {
            hashCombine(res, s.stage);
            hashCombine(res, s.shader);
            hashCombine(res, s.entry);
            if (s.spec.data) {
                for (const auto& e : s.spec.entries) {
                    hashCombine(res, e.constantID);
                    for (uint32_t k = 0; k < e.size; k++) {
                        hashCombine(res, ((uint8_t*)s.spec.data)[e.offset + k]);
                    }
                }
            }
        }
        for (const auto& item : pso.vertex_input.bindings) {
            hashCombine(res, item);
        }
        for (const auto& item : pso.vertex_input.attributes) {
            hashCombine(res, item);
        }
        hashCombine(res, pso.input_assembly);
        // hashCombine(res, pso.tessellation);
        for (const auto& item : pso.viewports) {
            hashCombine(res, item);
        }
        for (const auto& item : pso.scissors) {
            hashCombine(res, item);
        }
        hashCombine(res, pso.rasterization);
        hashCombine(res, pso.multisample);
        hashCombine(res, pso.depth_stencil);
        hashCombine(res, pso.color_blend.enable_logic_op);
        hashCombine(res, pso.color_blend.logic_op);
        for (const auto& item : pso.color_blend.attachments) {
            hashCombine(res, item);
        }
        hashCombine(res, pso.color_blend.constants[0]);
        hashCombine(res, pso.color_blend.constants[1]);
        hashCombine(res, pso.color_blend.constants[2]);
        hashCombine(res, pso.color_blend.constants[3]);
        for (const auto& item : pso.dynamics) {
            hashCombine(res, item);
        }
        hashCombine(res, pso.layout);
        hashCombine(res, pso.render_pass);
        hashCombine(res, pso.subpass);
        return res;
    }
};

NAMESPACE_END(std)
