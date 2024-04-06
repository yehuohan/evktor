#pragma once
#include "render_frame.hpp"
#include "vktor/base/api.hpp"

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
    static Res<RenderContext> from(const BaseApi& api, const core::SwapchainState& info, size_t thread_count = 1);
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

    /**
     * @brief Begin the next render frame as activated render frame
     *
     * @return The main command buffer from the activated render frame
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
};

NAMESPACE_END(vkt)
