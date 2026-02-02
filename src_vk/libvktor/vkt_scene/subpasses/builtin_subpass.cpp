#include "builtin_subpass.hpp"
#include "vktor/core/descriptor_set.hpp"

NAMESPACE_BEGIN(vktscn)

BuiltinSubpass::BuiltinSubpass(vkt::Shader&& vert, vkt::Shader&& frag, Box<BuiltinMesh>&& mesh)
    : RenderSubpass(std::move(vert), std::move(frag), "Builtin")
    , mesh(std::move(mesh)) {}

BuiltinSubpass::~BuiltinSubpass() {
    mesh.reset();
    for (auto& ubo : builtin_ubo) {
        ubo.unmap();
    }
    builtin_ubo.clear();
    builtin_ubo_ptr.clear();
}

Res<Void> BuiltinSubpass::draw(vkt::RenderCmdbuf& rd_cmdbuf) {
    vkt::RenderContext& rctx = rd_cmdbuf;
    auto& rfrm = rctx.getFrame().get();
    auto rfrm_idx = rctx.getFrameIndex();
    const auto& cmdbuf = rd_cmdbuf.cmdbuf;
    const auto extent = rd_cmdbuf.rtt.getExtent();
    vkt::core::DescriptorInfo desc_info{};

    for (size_t k = builtin_ubo.size(); k < rctx.getFrameCount(); k++) {
        auto res_ubo = vkt::core::BufferState{}
                           .setSize(sizeof(BuiltinUniform))
                           .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                           .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                           .into(rctx);
        OnErr(res_ubo);
        builtin_ubo.push_back(res_ubo.unwrap());

        auto res_ptr = builtin_ubo.back().map();
        OnErr(res_ptr);
        builtin_ubo_ptr.push_back(static_cast<BuiltinUniform*>(res_ptr.unwrap()));
    }
    auto& ubo_ptr = builtin_ubo_ptr[rfrm_idx];
    ubo_ptr->model = glm::mat4(1.0);
    ubo_ptr->view = camera_view;
    ubo_ptr->proj = camera_proj;

    desc_info.setBuf(0).bind(builtin_ubo[rfrm_idx]);
    if (mesh->texture) {
        desc_info.setImg(1).bind(*mesh->texture).bind(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL).bind(*mesh->sampler);
    }

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
        .addVertexInputBindings(BuiltinMesh::vertex_input_bindings)
        .addVertexInputAttributes(BuiltinMesh::vertex_input_attrs)
        .addViewport(0.0, extent.height, extent.width, -float(extent.height))
        .addScissor(0, 0, extent.width, extent.height)
        .setDepthTest(VK_TRUE, VK_TRUE)
        .addColorBlendAttachment(color_blend_attm_state);
    auto res_pipeline = rctx.requestGraphicsPipeline(pso);
    OnErr(res_pipeline);
    auto& pipeline = res_pipeline.unwrap().get();
    cmdbuf.cmdBindGraphicsPipeline(pipeline);

    auto res_desc_set = rfrm.requestDescriptorSet(desc_setlayout, desc_info);
    OnErr(res_desc_set);
    auto& desc_set = res_desc_set.unwrap().get();

    cmdbuf.cmdBindGraphicsDescriptorSets(pipeline_layout, 0, {desc_set})
        .cmdBindIndexBufferU16(mesh->index)
        .cmdBindVertexBuffers({mesh->vertex})
        .cmdDrawIndexed(u32(mesh->data.indices.size()));

    return Ok(Void{});
}

NAMESPACE_END(vktscn)
