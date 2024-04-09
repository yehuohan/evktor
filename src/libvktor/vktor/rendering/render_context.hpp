#pragma once
#include "render_frame.hpp"
#include "render_pipeline.hpp"
#include "render_subpass.hpp"
#include "render_target.hpp"
#include "vktor/base/api.hpp"
#include "vktor/base/resource_cache.hpp"
#include "vktor/base/shader.hpp"
#include <functional>

NAMESPACE_BEGIN(vkt)

class RenderContext : private NonCopyable {
private:
    const BaseApi& api;
    const size_t thread_count = 1;

    uint32_t frame_index = 0;
    bool frame_actived = false;
    Vector<RenderFrame> frames{};
    Box<core::Swapchain> swapchain = nullptr;
    /** Semaphore to signal after acquired the next swapchain image */
    Box<core::Semaphore> acquisition = nullptr;

public:
    using FnSwapchainRTT = std::function<Res<RenderTargetTable>(const core::Arg<core::Swapchain>& swapchain)>;
    /**
     * @brief The default function to create render target table for swapchain
     *
     * The table to create will have 2 render targets:
     * - RT-0: Color render target with the swapchain image of Arg<Swapchain>::image_index
     * - RT-1: Depth render target with VK_FORMAT_D32_SFLOAT
     */
    static const FnSwapchainRTT defaultFnSwapchainRTT;

    /** Render context's resources */
    struct Resources {
        ResourceCache<Shader> shaders{};
        ResourceCache<core::DescriptorSetLayout> descriptor_setlayouts{};
        ResourceCache<core::PipelineLayout> pipeline_layouts{};
        ResourceCache<core::GraphicsPipeline> graphics_pipelines{};
        ResourceCache<core::ComputePipeline> compute_pipelines{};
        ResourceCache<core::RenderPass> render_passes{};
        ResourceCache<core::Framebuffer> framebuffers{};
    };

private:
    Resources resources{};

private:
    explicit RenderContext(const BaseApi& api, size_t thread_count) : api(api), thread_count(thread_count) {}

public:
    /**
     * @brief Create RenderContext without swapchain
     */
    static Res<RenderContext> from(const BaseApi& api, uint32_t frame_count = 3, size_t thread_count = 1);
    /**
     * @brief Create RenderContext with swapchain
     */
    static Res<RenderContext> from(const BaseApi& api,
                                   const core::SwapchainState& info,
                                   FnSwapchainRTT fn = RenderContext::defaultFnSwapchainRTT,
                                   size_t thread_count = 1);
    RenderContext(RenderContext&&);

    /**
     * @brief Re-initialize swapchain and render frames (the old will be destroyed)
     *
     * The number of render frames to initialize is Swapchain::image_count.
     */
    Res<CRef<core::Swapchain>> reinit(const core::SwapchainState& info);
    inline const core::Swapchain& getSwapchain() const {
        OnCheck(swapchain, "Swapchain is invalid");
        return *swapchain;
    }
    inline bool hasSwapchain() const {
        return swapchain != nullptr;
    }
    FnSwapchainRTT createSwapchainRTT = RenderContext::defaultFnSwapchainRTT;

    /**
     * @brief Begin the next render frame as activated render frame
     *
     * @return The main command buffer from the activated render frame with graphics queue
     */
    Res<Ref<core::CommandBuffer>> beginFrame();
    /**
     * @brief End the activated render frame
     *
     * With swapchain, present the activated swapchain image.
     * Without swapchain, provide VK_NULL_HANDLE as `wait_semaphore`.
     *
     * @param wait_semaphore Semaphore to wait before present the activated swapchain image
     */
    Res<Void> endFrame(VkSemaphore wait_semaphore = VK_NULL_HANDLE);
    /**
     * @brief Submit command buffer
     *
     * With swapchain, execute the command buffer after acquired the activated swapchain image.
     * Without swapchain, execute the command buffer directly.
     *
     * @return Semaphore to signal after the command buffer executed
     */
    Res<CRef<core::Semaphore>> submit(const core::CommandBuffer& cmdbuf);
    /**
     * @brief Get the activated render frame
     */
    Ref<RenderFrame> getFrame();
    /**
     * @brief Get the activated render frame index
     *
     * With swapchain enabled, it's also the swapchain index.
     */
    inline uint32_t getFrameIndex() const {
        return frame_index;
    }
    /**
     * @brief Get the render frames count
     *
     * With swapchain enabled, it's also the swapchain images count.
     */
    inline uint32_t getFrameCount() const {
        return frames.size();
    }

public:
    Res<Ref<Shader>> requestShader(const ShaderSource& shader_source);
    Res<Ref<core::DescriptorSetLayout>> requestDescriptorSetLayout(const uint32_t set, const Vector<Shader>& shaders);
    Res<Ref<core::PipelineLayout>> requestPipelineLayout(const Vector<Shader>& shaders);
    Res<Ref<core::GraphicsPipeline>> requestGraphicsPipeline(const core::GraphicsPipelineState& pso);
    Res<Ref<core::ComputePipeline>> requestComputePipeline(const core::ComputePipelineState& pso);
    Res<Ref<core::RenderPass>> requestRenderPass(const RenderTargetTable& render_target_table,
                                                 const RenderPipeline& render_pipeline);
    Res<Ref<core::Framebuffer>> requestFramebuffer(const RenderTargetTable& render_target_table,
                                                   const core::RenderPass& render_pass);
};

NAMESPACE_END(vkt)
