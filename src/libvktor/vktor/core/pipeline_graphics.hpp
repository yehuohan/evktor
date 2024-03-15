#pragma once
#include "__core.hpp"
#include "device.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct GraphicsPipeline;

class GraphicsPipelineState : public CoreStater<GraphicsPipelineState> {
    friend struct GraphicsPipeline;

private:
    VkPipelineCreateFlags flags = 0;
    Vector<ShaderModule> shaders{};
    VkPipelineLayout layout = VK_NULL_HANDLE;
    VkRenderPass render_pass = VK_NULL_HANDLE;
    uint32_t subpass = 0;

    Vector<VkVertexInputBindingDescription> vert_input_bindings{};
    Vector<VkVertexInputAttributeDescription> vert_input_attributes{};
    Vector<VkViewport> viewports{};
    Vector<VkRect2D> scissors{};

public:
    GraphicsPipelineState(Name&& name = "GraphicsPipeline") : CoreStater(std::move(name)) {}

    Self setFlags(VkPipelineCreateFlags flags);
    Self addShader(ShaderModule&& shader);
    Self setPipelineLayout(VkPipelineLayout layout);
    Self setRenderPass(VkRenderPass render_pass, uint32_t subpass_index = 0);
    Self addVertexInputBinding(const VkVertexInputBindingDescription& binding);
    Self addVertexInputBindings(const Vector<VkVertexInputBindingDescription>& bindings);
    Self addVertexInputAttribute(const VkVertexInputAttributeDescription& attribute);
    Self addVertexInputAttributes(const Vector<VkVertexInputAttributeDescription>& attributes);
    Self addViewport(const VkViewport& viewport);
    Self addViewport(float x, float y, float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);
    Self addScissor(const VkRect2D& rect);
    Self addScissor(int32_t x, int32_t y, uint32_t width, uint32_t height);

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
