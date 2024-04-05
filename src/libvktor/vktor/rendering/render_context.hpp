#pragma once
#include "render_frame.hpp"
#include "vktor/base/api.hpp"

NAMESPACE_BEGIN(vkt)

class RenderContext : private NonCopyable {
private:
    const BaseApi& api;
    const size_t thread_count = 1;

    uint32_t frame_index = 0;
    Vector<RenderFrame> frames{};
    Box<core::Swapchain> swapchain = nullptr;

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

    /** Re-initialize swapchain and render frames (the old will be destroyed) */
    Res<CRef<core::Swapchain>> reinit(const core::SwapchainState& info);
    inline const core::Swapchain& getSwapchain() const {
        OnCheck(swapchain, "Swapchain is invalid");
        return *swapchain;
    }
    inline bool hasSwapchain() const {
        return swapchain != nullptr;
    }

    Res<Ref<RenderFrame>> getFrame();
    inline uint32_t getFrameIndex() const {
        return frame_index;
    }
    void activateRenderFrame(uint32_t index);
};

NAMESPACE_END(vkt)
