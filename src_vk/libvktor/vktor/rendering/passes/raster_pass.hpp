#pragma once
#include "vktor/base/shader.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/pipeline_layout.hpp"

NAMESPACE_BEGIN(vkt)

class RasterPass {
protected:
    const core::CoreApi& api;

    core::GraphicsPipelineState pso;
    // Shader shader_vert;
    // Shader shader_frag;

public:
    explicit RasterPass(const core::CoreApi& _api) : api(_api) {}
};

NAMESPACE_END(vkt)
