#pragma once
#include "__core.hpp"
#include "device.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct GraphicsPipeline;

class GraphicsPipelineState : public CoreStater<GraphicsPipelineState> {
    friend struct GraphicsPipeline;
    friend struct std::hash<GraphicsPipelineState>;

private:
    VkPipelineCreateFlags flags = 0;
    Vector<ShaderModule> shaders{};
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

public:
    GraphicsPipelineState(Name&& name = "GraphicsPipeline");

    Self setFlags(VkPipelineCreateFlags flags);
    Self addShader(ShaderModule&& shader);
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
    Self setRasterizationCullMode(VkCullModeFlags cull_mode);
    Self setRasterizationFrontFace(VkFrontFace front_face);
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

    Res<GraphicsPipeline> into(const Device& device) const;
};

struct GraphicsPipeline : public CoreResource<VkPipeline, VK_OBJECT_TYPE_PIPELINE, Device> {
    GraphicsPipeline(const Device& device) : CoreResource(device) {}
    GraphicsPipeline(GraphicsPipeline&&);
    ~GraphicsPipeline();

    static Res<GraphicsPipeline> from(const Device& device, const GraphicsPipelineState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::core::GraphicsPipelineState> {
    size_t operator()(const vkt::core::GraphicsPipelineState& pso) const {
        size_t res = 0;
        vkt::hashCombine(res, pso.shaders);
        return res;
    }
};

NAMESPACE_END(std)
