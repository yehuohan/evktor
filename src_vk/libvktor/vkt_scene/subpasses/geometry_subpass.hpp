#pragma once
#include "vkt_scene/scene.hpp"
#include "vktor/rendering/render_subpass.hpp"

NAMESPACE_BEGIN(vktscn)

struct PBRUniform {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view_proj;
};

class GeometrySubpass : public vkt::RenderSubpass {
private:
    Box<vktscn::Scene> scene = nullptr;
    Vector<vkt::core::Buffer> pbr_ubo{};
    Vector<PBRUniform*> pbr_ubo_ptr{};

public:
    glm::mat4 camera_view;
    glm::mat4 camera_proj;

public:
    GeometrySubpass(vkt::Shader&& vert, vkt::Shader&& frag, Box<Scene>&& scene);
    ~GeometrySubpass();

    virtual Res<Void> draw(vkt::RenderCmdbuf& rd_cmdbuf) override;
};

NAMESPACE_END(vktscn)
