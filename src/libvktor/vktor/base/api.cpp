#include "api.hpp"
#include "vktor/rendering/render_pipeline.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

Res<Ref<Queue>> BaseApi::presentQueue() const {
    Check(dev, "Device is invalid");
    if (dev->queues.present) {
        return Ok(newRef(*dev->queues.present));
    } else {
        return Er("Present queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::graphicsQueue() const {
    Check(dev, "Device is invalid");
    if (dev->queues.graphics) {
        return Ok(newRef(*dev->queues.graphics));
    } else {
        return Er("Graphics queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::computeQueue() const {
    Check(dev, "Device is invalid");
    if (dev->queues.compute) {
        return Ok(newRef(*dev->queues.compute));
    } else {
        return Er("Compute queue is not supported");
    }
}

Res<Ref<Queue>> BaseApi::transferQueue() const {
    Check(dev, "Device is invalid");
    if (dev->queues.transfer) {
        return Ok(newRef(*dev->queues.transfer));
    } else {
        return Er("Transfer queue is not supported");
    }
}

Res<Ref<ShaderModule>> BaseApi::requestShaderModule(const Shader& shader) {
    Check(dev, "Device is invalid");

    size_t key = hash(shader);
    return resource_cache.shader_modules.request(key, [this, &shader]() {
        ShaderModuleBuilder builder(*dev);
        builder.setFilename(shader.getFilename());
        builder.setCode(std::string(shader.getCode()), shader.getStage());
        builder.setEntry("main");
        return builder();
    });
}

Res<Ref<RenderPass>> BaseApi::requestRenderPass(const RenderTargetTable& render_target_table,
                                                const RenderPipeline& render_pipeline) {
    Check(dev, "Device is invalid");

    size_t key = hash(render_target_table.getTargets(), render_pipeline.getSubpasses());
    return resource_cache.render_passes.request(key, [&render_target_table, &render_pipeline]() {
        return render_pipeline.createRenderPass(render_target_table);
    });
}

Res<Ref<Framebuffer>> BaseApi::requestFramebuffer(const RenderTargetTable& render_target_table, const RenderPass& render_pass) {
    Check(dev, "Device is invalid");

    size_t key = hash(render_target_table, render_pass);
    return resource_cache.framebuffers.request(key, [&render_target_table, &render_pass]() {
        FramebufferBuilder builder(render_pass);
        builder.addAttachments(render_target_table.getImageViews());
        builder.setExtent(render_target_table.getExtent());
        return builder();
    });
}

NAMESPACE_END(vkt)
