#pragma once
#include "render_frame.hpp"
#include "render_resource.hpp"
#include "vktor/core/exts/swapchain.hpp"

NAMESPACE_BEGIN(vkt)

class RenderContext : public RenderResource {
private:
    const size_t thread_count = 1;

    uint32_t frame_index = 0;
    bool frame_actived = false;
    Vector<RenderFrame> frames{};

    VkExtent2D surface_extent{0, 0};
    Box<core::Swapchain> swapchain = nullptr;
    Box<core::SwapchainState> swapchain_state = nullptr;
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

private:
    explicit RenderContext(const core::CoreApi& api, size_t thread_count) : RenderResource(api), thread_count(thread_count) {}

public:
    operator const core::CoreApi&() const {
        return api;
    }

    /**
     * @brief Create RenderContext without swapchain
     */
    static Res<RenderContext> from(const core::CoreApi& api, uint32_t frame_count = 3, size_t thread_count = 1);
    /**
     * @brief Create RenderContext with swapchain
     */
    static Res<RenderContext> from(const core::CoreApi& api,
                                   core::SwapchainState&& info,
                                   FnSwapchainRTT fn = nullptr,
                                   size_t thread_count = 1);
    RenderContext(RenderContext&&);

public:
    /**
     * @brief Re-initialize swapchain and render frames with `swapchain_state`
     *
     * The number of render frames to initialize is Swapchain::image_count
     */
    Res<CRef<core::Swapchain>> reinitSwapchain();
    /**
     * @brief Update swapchain with surface changed
     *
     * @return Whether updated swapchain
     */
    bool updateSwapchain(bool force = false);
    inline bool hasSwapchain() const {
        return swapchain != nullptr;
    }
    inline const core::Swapchain& getSwapchain() const {
        OnCheck(swapchain, "Swapchain is invalid");
        return *swapchain;
    }
    inline core::SwapchainState& getSwapchainState() {
        OnCheck(swapchain, "SwapchainState is invalid");
        return *swapchain_state;
    }
    FnSwapchainRTT newSwapchainRTT = RenderContext::defaultFnSwapchainRTT;
    inline const VkExtent2D& getSurfaceExtent() const {
        return surface_extent;
    }

public:
    /**
     * @brief Begin the next render frame as activated render frame
     *
     * @return The main command buffer from the activated render frame with graphics queue
     */
    Res<CRef<core::CommandBuffer>> beginFrame();
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
    inline Ref<RenderFrame> getFrame() {
        OnCheck(frame_index < frames.size(),
                "The activated frame index = {} is out of frames count = {}",
                frame_index,
                frames.size());
        return newRef(frames[frame_index]);
    }
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
    void watchStatus() const;
};

NAMESPACE_END(vkt)
