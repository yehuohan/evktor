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

    Box<Swapchain> swapchain = nullptr;
    Vector<Box<RenderFrame>> frames{};
    uint32_t frame_index = 0;

public:
    explicit RenderContext(const BaseApi& base_api) : api(base_api) {}

    /* Swapchain */
    OnConstType(VkSwapchainKHR, swapchain->handle);

    inline const Swapchain& getSwapchain() {
        assert(swapchain && "Swapchain is invalid");
        return *swapchain;
    }
    inline void add(Swapchain&& _swapchain) {
        swapchain.reset();
        swapchain = newBox<Swapchain>(std::move(_swapchain));
    }
    inline bool hasSwapchain() const {
        return swapchain != nullptr;
    }

    /* RenderFrame */
    void addRenderFrames(uint32_t count);
    void activateRenderFrame(uint32_t index);
    RenderFrame& getRenderFrame();
};

NAMESPACE_END(vkt)
