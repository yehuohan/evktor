#pragma once
#include "api.hpp"
#include "common/defs.hpp"
#include "common/traits.hpp"
#include "render_frame.hpp"
#include "vktor/core/swapchain.hpp"
#include <cassert>

NAMESPACE_BEGIN(vkt)

using namespace core;

class RenderContext : private NonCopyable {
private:
    const BaseApi& api;

    const size_t thread_count = 1;
    Box<Swapchain> swapchain = nullptr;
    Vector<RenderFrame> frames{};
    uint32_t frame_index = 0;

public:
    explicit RenderContext(const BaseApi& base_api, size_t thread_count = 1) : api(base_api), thread_count(thread_count) {}

    /* Swapchain */
    OnConstType(VkSwapchainKHR, swapchain->handle);

    void add(Swapchain&& _swapchain);
    inline const Swapchain& getSwapchain() {
        assert(swapchain && "Swapchain is invalid");
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
