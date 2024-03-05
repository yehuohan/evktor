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

Res<Ref<DescriptorSetLayout>> BaseApi::requestDescriptorSetLayout(const uint32_t set, const Vector<const Shader*>& shaders) {
    Check(dev, "Device is invalid");

    size_t key = hash(set, shaders);
    return resource_cache.descriptor_setlayouts.request(key, [this, set, &shaders]() -> Res<DescriptorSetLayout> {
        DescriptorSetLayoutBuilder builder(*dev);
        for (const auto s : shaders) {
            if (!s) {
                continue;
            }
            switch (s->getStage()) {
            case VK_SHADER_STAGE_VERTEX_BIT:
            case VK_SHADER_STAGE_FRAGMENT_BIT:
            case VK_SHADER_STAGE_COMPUTE_BIT:
                for (const auto& d : s->getDescriptors()) {
                    if (set == d.set) {
                        builder.addBinding(d.binding, static_cast<VkDescriptorType>(d.type), d.count, s->getStage());
                    }
                }
                break;
            default:
                return Er("Request with unsupported shader ({}) stage: {}",
                          s->getFilename(),
                          VkStr(VkShaderStageFlags, s->getStage()));
            }
        }
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
