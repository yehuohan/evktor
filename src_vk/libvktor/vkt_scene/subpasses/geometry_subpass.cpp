#include "geometry_subpass.hpp"
#include "vktor/core/descriptor_set.hpp"
#include <queue>

NAMESPACE_BEGIN(vktscn)

/*
 * layout(location = 0) in vec3 position; // GLTF: POSITION
 * layout(location = 1) in vec2 texcoord_0; // GLTF: TEXCOORD_0
 * layout(location = 2) in vec3 normal; // GLTF: NORMAL
 */
static const auto vertex_input_bindings = Vector<VkVertexInputBindingDescription>{
    VkVertexInputBindingDescription{0, sizeof(glm::vec3), VK_VERTEX_INPUT_RATE_VERTEX},
    VkVertexInputBindingDescription{1, sizeof(glm::vec2), VK_VERTEX_INPUT_RATE_VERTEX},
    VkVertexInputBindingDescription{2, sizeof(glm::vec3), VK_VERTEX_INPUT_RATE_VERTEX},
};

static const auto vertex_input_attrs = Vector<VkVertexInputAttributeDescription>{
    VkVertexInputAttributeDescription{0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0},
    VkVertexInputAttributeDescription{1, 1,    VK_FORMAT_R32G32_SFLOAT, 0},
    VkVertexInputAttributeDescription{2, 2, VK_FORMAT_R32G32B32_SFLOAT, 0},
};

GeometrySubpass::GeometrySubpass(vkt::Shader&& vert, vkt::Shader&& frag, Box<Scene>&& scene)
    : RenderSubpass(std::move(vert), std::move(frag), "OpaquePass")
    , scene(std::move(scene)) {}

GeometrySubpass::~GeometrySubpass() {
    scene.reset();
    for (auto& ubo : pbr_ubo) {
        ubo.unmap();
    }
    pbr_ubo.clear();
    pbr_ubo_ptr.clear();
}

Res<Void> GeometrySubpass::draw(vkt::RenderCmdbuf& rd_cmdbuf) {
    vkt::RenderContext& rctx = rd_cmdbuf;
    auto& rfrm = rctx.getFrame().get();
    auto rfrm_idx = rctx.getFrameIndex();
    const auto& cmdbuf = rd_cmdbuf.cmdbuf;
    const auto extent = rd_cmdbuf.rtt.getExtent();
    vkt::core::DescriptorInfo desc_info{};

    for (size_t k = pbr_ubo.size(); k < rctx.getFrameCount(); k++) {
        auto res_ubo = vkt::core::BufferState{}
                           .setSize(sizeof(PBRUniform))
                           .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                           .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                           .into(rctx);
        OnErr(res_ubo);
        pbr_ubo.push_back(res_ubo.unwrap());

        auto res_ptr = pbr_ubo.back().map();
        OnErr(res_ptr);
        pbr_ubo_ptr.push_back(static_cast<PBRUniform*>(res_ptr.unwrap()));
    }
    desc_info.setBuf(0, pbr_ubo[rfrm_idx]);
    auto& ubo_ptr = pbr_ubo_ptr[rfrm_idx];

    auto res_desc_setlayout = rctx.requestDescriptorSetLayout(0, Shaders());
    OnErr(res_desc_setlayout);
    auto& desc_setlayout = res_desc_setlayout.unwrap().get();

    auto res_pipeline_layout = rctx.requestPipelineLayout(Shaders());
    OnErr(res_pipeline_layout);
    auto& pipeline_layout = res_pipeline_layout.unwrap().get();

    auto res_vert = rctx.requestShaderModule(vert_shader);
    OnErr(res_vert);
    auto& vert = res_vert.unwrap().get();
    auto res_frag = rctx.requestShaderModule(frag_shader);
    OnErr(res_frag);
    auto& frag = res_frag.unwrap().get();

    VkPipelineColorBlendAttachmentState color_blend_attm_state{};
    color_blend_attm_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                                            VK_COLOR_COMPONENT_A_BIT;
    vkt::core::GraphicsPipelineState pso{};
    pso.setRenderPass(rd_cmdbuf.render_pass, rd_cmdbuf.subpass_index)
        .addVertShader(vert, vert_shader.getEntry())
        .addFragShader(frag, frag_shader.getEntry())
        .setPipelineLayout(pipeline_layout)
        .addVertexInputBindings(vertex_input_bindings)
        .addVertexInputAttributes(vertex_input_attrs)
        .addViewport(0.0, extent.height, extent.width, -float(extent.height))
        .addScissor(0, 0, extent.width, extent.height)
        .setDepthTest(VK_TRUE, VK_TRUE)
        .addColorBlendAttachment(color_blend_attm_state);
    auto res_pipeline = rctx.requestGraphicsPipeline(pso);
    OnErr(res_pipeline);
    auto& pipeline = res_pipeline.unwrap().get();
    cmdbuf.cmdBindGraphicsPipeline(pipeline);

    auto& root = *scene->getRootNode();
    std::queue<Node*> nodes(std::deque<Node*>(root.getChildren().begin(), root.getChildren().end()));
    while (!nodes.empty()) {
        auto& node = *nodes.front();
        nodes.pop();

        if (auto mesh = node.getComponent<Mesh>(); mesh) {
            for (auto& sub : mesh->getSubmeshes()) {
                ubo_ptr->model = node.getTransform().getWorldMatrix();
                ubo_ptr->view_proj = camera_proj * camera_view;

                auto* pbr_mat = sub->getPBRMaterial();
                if (pbr_mat) {
                    if (auto tex = pbr_mat->getTexture("base_color_texture"); tex) {
                        desc_info.setImg(1, *tex->getImage(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, *tex->getSampler());
                    }
                }
                auto res_desc_set = rfrm.requestDescriptorSet(desc_setlayout, desc_info);
                OnErr(res_desc_set);
                auto& desc_set = res_desc_set.unwrap().get();

                cmdbuf.cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set})
                    .cmdBindVertexBuffers(
                        {
                            *sub->getVertexBuffer("position"),
                            *sub->getVertexBuffer("texcoord_0"),
                            *sub->getVertexBuffer("normal"),
                        },
                        {
                            sub->getVertexBuffer("position")->offset,
                            sub->getVertexBuffer("texcoord_0")->offset,
                            sub->getVertexBuffer("normal")->offset,

                        });
                if (sub->index_count > 0) {
                    cmdbuf.cmdBindIndexBuffer(*sub->getIndexBuffer(), sub->getIndexBuffer()->offset, sub->index_type);
                    cmdbuf.cmdDrawIndexed(u32(sub->index_count));
                } else {
                    cmdbuf.cmdDraw(sub->vertex_count);
                }
            }
        }
        for (const auto& child : node.getChildren()) {
            nodes.push(child);
        }
    }

    return Ok(Void{});
}

NAMESPACE_END(vktscn)
