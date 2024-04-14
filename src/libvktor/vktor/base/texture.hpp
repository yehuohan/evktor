#pragma once
#include "vktor/core/api/api.hpp"
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"
#include "vktor/core/sampler.hpp"

NAMESPACE_BEGIN(vkt)

class Texture : private NonCopyable {
private:
    core::Image image;
    core::ImageView imageview;

public:
    enum UsageBits {
        TransferSrc = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
        TransferDst = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        Transfer = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        Sampled = VK_IMAGE_USAGE_SAMPLED_BIT,
        Storage = VK_IMAGE_USAGE_STORAGE_BIT,
        Image = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT,
        Color = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        DepthStencil = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        Transient = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
        Input = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
        MaxUsage = VK_IMAGE_USAGE_FLAG_BITS_MAX_ENUM,
    };
    typedef VkFlags Usage;

    enum Sample {
        S1 = VK_SAMPLE_COUNT_1_BIT,
        S2 = VK_SAMPLE_COUNT_2_BIT,
        S4 = VK_SAMPLE_COUNT_4_BIT,
        S8 = VK_SAMPLE_COUNT_8_BIT,
        S16 = VK_SAMPLE_COUNT_16_BIT,
        S32 = VK_SAMPLE_COUNT_32_BIT,
        S64 = VK_SAMPLE_COUNT_64_BIT,
    };

public:
    explicit Texture(core::Image&& image, core::ImageView&& imageview);
    Texture(Texture&&);
    OnConstType(VkImage, image.handle);
    OnConstType(VkImageView, imageview.handle);

    inline const core::Image& getImage() const {
        return image;
    }
    inline const core::ImageView& getImageView() const {
        return imageview;
    }
};

class Texture2D : public Texture {
public:
    explicit Texture2D(core::Image&& image, core::ImageView&& imageview);

    static Res<Texture2D> from(const core::CoreApi& api,
                               VkFormat format,
                               const VkExtent2D& extent,
                               Usage usage,
                               uint32_t mip_levels = 1,
                               Sample samples = S1);
};

class Texture2DArray : public Texture2D {};

class Texture3D : public Texture {};

class TextureCube : public Texture {};

NAMESPACE_END(vkt)
