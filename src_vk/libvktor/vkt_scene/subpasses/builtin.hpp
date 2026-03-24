#pragma once
#include "vkt_scene/builtin_mesh.hpp"
#include "vkt_scene/components/camera.hpp"
#include "vktor/rendering/render_subpass.hpp"

NAMESPACE_BEGIN(vktscn)

struct BuiltinUniform {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

/**
 * @brief A simple subpass to draw builtin mesh
 */
class BuiltinSubpass : public vkt::RenderSubpass {
private:
    Camera& camera;
    Box<BuiltinMesh> mesh = nullptr;
    Vector<vkt::core::Buffer> builtin_ubo{};
    Vector<BuiltinUniform*> builtin_ubo_ptr{};

public:
    BuiltinSubpass(vkt::Shader&& vert, vkt::Shader&& frag, Box<BuiltinMesh>&& mesh, Camera& camera);
    ~BuiltinSubpass();

    virtual Res<Void> draw(vkt::RenderCmdbuf& rd_cmdbuf) override;
};

NAMESPACE_END(vktscn)
