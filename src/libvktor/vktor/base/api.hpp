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
#include "vktor/core/surface.hpp"
#include "vktor/core/swapchain.hpp"

NAMESPACE_BEGIN(vkt)

class RenderPipeline;

/**
 * @brief Basic Vulkan API for instance and device
 */
class BaseApi : private NonCopyable {
private:
    Box<core::Instance> instance = nullptr;
    Box<core::PhysicalDevice> phy_dev = nullptr;
    Box<core::Device> dev = nullptr;

public:
    explicit BaseApi() {}

    OnConstType(VkInstance, instance->handle);
    OnConstType(VkPhysicalDevice, phy_dev->handle);
    OnConstType(VkDevice, dev->handle);
    operator const core::Instance&() const {
        OnCheck(instance, "Instance device is invalid");
        return *instance;
    }
    operator const core::PhysicalDevice&() const {
        OnCheck(phy_dev, "Physical device is invalid");
        return *phy_dev;
    }
    operator const core::Device&() const {
        OnCheck(dev, "Device is invalid");
        return *dev;
    }

    /** Initialize instance (the old will be destroyed) */
    Res<CRef<core::Instance>> init(core::InstanceState& info);
    /** Initialize physical device (the old will be destroyed) */
    Res<CRef<core::PhysicalDevice>> init(core::PhysicalDeviceState& info);
    /** Initialize device (the old will be destroyed) */
    Res<CRef<core::Device>> init(core::DeviceState& info);
    Res<CRef<core::Queue>> presentQueue() const;
    Res<CRef<core::Queue>> graphicsQueue() const;
    Res<CRef<core::Queue>> computeQueue() const;
    Res<CRef<core::Queue>> transferQueue() const;
    inline VkResult waitIdle() const {
        OnCheck(dev, "Device is invalid");
        return dev->waitIdle();
    }

public:
    // Alias core state object `into` function
    inline Res<core::Surface> create(VkSurfaceKHR surface) const {
        return core::Surface::from(*this, surface);
    }
    inline Res<core::Swapchain> create(const core::SwapchainState& info) const {
        return info.into(*this);
    }
    inline Res<core::ShaderModule> create(const core::ShaderModuleState& info) const {
        return info.into(*this);
    }
    inline Res<core::Buffer> create(const core::BufferState& info) const {
        return info.into(*this);
    }
    inline Res<core::Image> create(const core::ImageState& info) const {
        return info.into(*this);
    }
    inline Res<core::ImageView> create(const core::ImageViewState& info) const {
        return info.into(*this);
    }
    inline Res<core::Sampler> create(const core::SamplerState& info) const {
        return info.into(*this);
    }
    inline Res<core::DescriptorSetLayout> create(const core::DescriptorSetLayoutState& info) const {
        return info.into(*this);
    }
    inline Res<core::DescriptorPool> create(const core::DescriptorPoolState& info,
                                            const core::DescriptorSetLayout& setlayout) const {
        return info.into(setlayout);
    }
    inline Res<core::PipelineLayout> create(const core::PipelineLayoutState& info) const {
        return info.into(*this);
    }
    inline Res<core::GraphicsPipeline> create(const core::GraphicsPipelineState& info) const {
        return info.into(*this);
    }
    inline Res<core::ComputePipeline> create(const core::ComputePipelineState& info) const {
        return info.into(*this);
    }
    inline Res<core::RenderPass> create(const core::RenderPassState& info) const {
        return info.into(*this);
    }
    inline Res<core::Framebuffer> create(const core::FramebufferState& info) const {
        return info.into(*this);
    }
    inline Res<core::CommandPool> create(const core::CommandPoolState& info) const {
        return info.into(*this);
    }
    inline Res<core::Fence> create(const core::FenceState& info) const {
        return info.into(*this);
    }
    inline Res<core::Semaphore> create(const core::SemaphoreState& info) const {
        return info.into(*this);
    }
    inline Res<core::Event> create(const core::EventState& info) const {
        return info.into(*this);
    }
};

NAMESPACE_END(vkt)
