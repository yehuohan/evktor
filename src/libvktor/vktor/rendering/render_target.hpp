#pragma once
#include "vktor/base/api.hpp"
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

class RenderTarget : public NonCopyable {
    friend class std::hash<RenderTarget>;

private:
    const BaseApi& api;

    VkExtent2D extent{};
    Vector<ImageView> imageviews{};

private:
    explicit RenderTarget(const BaseApi& api) : api(api) {}

public:
    RenderTarget(RenderTarget&&);
    inline VkExtent2D getExtent() const {
        return extent;
    }
    Vector<VkImageView> getImageViews() const;

    static Res<RenderTarget> build(const BaseApi& api, Vector<ImageView>&& imageviews);
};

NAMESPACE_END(vkt)

NAMESPACE_BEGIN(std)

template <>
struct hash<vkt::RenderTarget> {
    size_t operator()(const vkt::RenderTarget& render_target) const {
        size_t res = 0;
        for (const auto& view : render_target.imageviews) {
            vkt::hashCombine(res, view);
            vkt::hashCombine(res, view.image);
        }
        return res;
    }
};

NAMESPACE_END(std)
