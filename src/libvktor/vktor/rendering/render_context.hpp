#pragma once
#include "render_frame.hpp"
#include "vktor/base/api.hpp"

NAMESPACE_BEGIN(vkt)

class RenderContext : private NonCopyable {
private:
    const BaseApi& api;

    const size_t thread_count = 1;
    Box<core::Swapchain> swapchain = nullptr;
    Vector<RenderFrame> frames{};
    uint32_t frame_index = 0;

public:
    explicit RenderContext(const BaseApi& api, size_t thread_count = 1) : api(api), thread_count(thread_count) {}

    /* Swapchain */
    OnConstType(VkSwapchainKHR, swapchain->handle);

    Res<Ref<core::Swapchain>> add(core::SwapchainState& info);
    inline const core::Swapchain& getSwapchain() const {
        OnCheck(swapchain, "Swapchain is invalid");
        return *swapchain;
    }
    inline bool hasSwapchain() const {
        return swapchain != nullptr;
    }

    /* Render frame */
    void activateRenderFrame(uint32_t index);
    Res<Ref<RenderFrame>> getRenderFrame();
};

NAMESPACE_END(vkt)
