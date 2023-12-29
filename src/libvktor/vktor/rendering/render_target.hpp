#pragma once
#include "vktor/base/api.hpp"
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"

NAMESPACE_BEGIN(vkt)

class RenderTarget : public NonCopyable {
private:
    const BaseApi& api;

    VkExtent2D extent{};

    explicit RenderTarget(const BaseApi& api) : api(api) {}

public:
    Vector<ImageView> imageviews{};

    RenderTarget(RenderTarget&&);

    static Res<RenderTarget> build(const BaseApi& api, Vector<ImageView>&& imageviews);
};

NAMESPACE_END(vkt)
