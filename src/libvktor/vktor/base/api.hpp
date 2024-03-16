#pragma once
#include "vktor/core/buffer.hpp"
#include "vktor/core/command_buffer.hpp"
#include "vktor/core/command_pool.hpp"
#include "vktor/core/descriptor_pool.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/device.hpp"
#include "vktor/core/event.hpp"
#include "vktor/core/fence.hpp"
#include "vktor/core/framebuffer.hpp"
#include "vktor/core/image.hpp"
#include "vktor/core/image_view.hpp"
#include "vktor/core/instance.hpp"
#include "vktor/core/physical_device.hpp"
#include "vktor/core/pipeline_compute.hpp"
#include "vktor/core/pipeline_graphics.hpp"
#include "vktor/core/pipeline_layout.hpp"
#include "vktor/core/queue.hpp"
#include "vktor/core/render_pass.hpp"
#include "vktor/core/sampler.hpp"
#include "vktor/core/semaphore.hpp"
#include "vktor/core/shader_module.hpp"
#include "vktor/core/swapchain.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

class RenderPipeline;

/**
 * @brief Basic Vulkan API for instance and device
 */
class BaseApi : private NonCopyable {
private:
    Box<Instance> instance = nullptr;
    Box<PhysicalDevice> phy_dev = nullptr;
    Box<Device> dev = nullptr;

public:
    explicit BaseApi() {}

    OnConstType(VkInstance, instance->handle);
    OnConstType(VkPhysicalDevice, phy_dev->handle);
    OnConstType(VkDevice, dev->handle);
    operator const Instance&() const {
        Check(instance, "Instance device is invalid");
        return *instance;
    }
    operator const PhysicalDevice&() const {
        Check(phy_dev, "Physical device is invalid");
        return *phy_dev;
    }
    operator const Device&() const {
        Check(dev, "Device is invalid");
        return *dev;
    }

    Res<Ref<Instance>> init(InstanceState& info);
    Res<Ref<PhysicalDevice>> init(PhysicalDeviceState& info);
    Res<Ref<Device>> init(DeviceState& info);
    Res<Ref<Queue>> presentQueue() const;
    Res<Ref<Queue>> graphicsQueue() const;
    Res<Ref<Queue>> computeQueue() const;
    Res<Ref<Queue>> transferQueue() const;

public:
    // Alias core state object `into` function
    inline Res<Swapchain> create(SwapchainState& info) const {
        return info.into(*this);
    }
    inline Res<ShaderModule> create(const ShaderModuleState& info) const {
        return info.into(*this);
    }
    inline Res<Buffer> create(const BufferState& info) const {
        return info.into(*this);
    }
    inline Res<Image> create(const ImageState& info) const {
        return info.into(*this);
    }
    inline Res<ImageView> create(const ImageViewState& info) const {
        return info.into();
    }
    inline Res<Sampler> create(const SamplerState& info) const {
        return info.into(*this);
    }
    inline Res<DescriptorSetLayout> create(const DescriptorSetLayoutState& info) const {
        return info.into(*this);
    }
    inline Res<DescriptorPool> create(const DescriptorPoolState& info, const core::DescriptorSetLayout& setlayout) const {
        return info.into(setlayout);
    }
    inline Res<PipelineLayout> create(const PipelineLayoutState& info) const {
        return info.into(*this);
    }
    inline Res<GraphicsPipeline> create(const GraphicsPipelineState& info) const {
        return info.into(*this);
    }
    inline Res<ComputePipeline> create(const ComputePipelineState& info) const {
        return info.into(*this);
    }
    inline Res<RenderPass> create(const RenderPassState& info) const {
        return info.into(*this);
    }
    inline Res<Framebuffer> create(const FramebufferState& info) const {
        return info.into(*this);
    }
    inline Res<CommandPool> create(const CommandPoolState& info) const {
        return info.into(*this);
    }
    inline Res<Fence> create(const FenceState& info) const {
        return info.into(*this);
    }
    inline Res<Semaphore> create(const SemaphoreState& info) const {
        return info.into(*this);
    }
    inline Res<Event> create(const EventState& info) const {
        return info.into(*this);
    }
};

NAMESPACE_END(vkt)
