#pragma once
#include "__builder.hpp"
#include "device.hpp"
#include "pipeline_layout.hpp"
#include "render_pass.hpp"
#include "shader_module.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct GraphicsPipeline : public BuiltResource<VkPipeline, VK_OBJECT_TYPE_PIPELINE, Device> {
    const PipelineLayout& pipeline_layout;

    GraphicsPipeline(const PipelineLayout& layout, Name&& name)
        : BuiltResource(layout.device, std::move(name))
        , pipeline_layout(layout) {}
    GraphicsPipeline(GraphicsPipeline&&);
    ~GraphicsPipeline();
    OnConstType(VkPipelineLayout, pipeline_layout.handle);
};

struct GraphicsPipelineState : public BuilderInfo {
    VkPipelineCreateFlags flags = 0;
    Vector<Shader> shaders{};
    Ptr<RenderPass> render_pass = nullptr;
    uint32_t subpass = 0;

    Vector<VkVertexInputBindingDescription> vert_input_bindings{};
    Vector<VkVertexInputAttributeDescription> vert_input_attributes{};
    Vector<VkViewport> viewports{};
    Vector<VkRect2D> scissors{};
};

class GraphicsPipelineBuilder : public Builder<GraphicsPipelineBuilder, GraphicsPipeline, GraphicsPipelineState> {
private:
    const PipelineLayout& pipeline_layout;

public:
    explicit GraphicsPipelineBuilder(const PipelineLayout& layout, Name&& name = "GraphicsPipeline")
        : Builder(std::move(name))
        , pipeline_layout(layout) {}
    virtual Built build() override;

    Self setFlags(VkPipelineCreateFlags flags);
    Self addShader(Shader&& shader);
    Self setRenderPass(const Ptr<RenderPass>& render_pass, uint32_t subpass_index = 0);

    Self addVertexInputBinding(const VkVertexInputBindingDescription& binding);
    Self addVertexInputBindings(const Vector<VkVertexInputBindingDescription>& bindings);
    Self addVertexInputAttribute(const VkVertexInputAttributeDescription& attribute);
    Self addVertexInputAttributes(const Vector<VkVertexInputAttributeDescription>& attributes);
    Self addViewport(const VkViewport& viewport);
    Self addViewport(float x, float y, float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);
    Self addScissor(const VkRect2D& rect);
    Self addScissor(int32_t x, int32_t y, uint32_t width, uint32_t height);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
