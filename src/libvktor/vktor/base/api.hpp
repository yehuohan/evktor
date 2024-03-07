#pragma once
#include "vktor/core/buffer.hpp"
#include "vktor/core/command_buffer.hpp"
#include "vktor/core/command_pool.hpp"
#include "vktor/core/descriptor_pool.hpp"
#include "vktor/core/descriptor_set.hpp"
#include "vktor/core/descriptor_setlayout.hpp"
#include "vktor/core/device.hpp"
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
    operator Instance&() const {
        Check(instance, "Instance device is invalid");
        return *instance;
    }
    operator const PhysicalDevice&() const {
        Check(phy_dev, "Physical device is invalid");
        return *phy_dev;
    }
    operator Device&() const {
        Check(dev, "Device is invalid");
        return *dev;
    }

    inline void add(Instance&& _instance) {
        instance.reset();
        instance = newBox<struct Instance>(std::move(_instance));
    }
    inline void add(PhysicalDevice&& _phy_dev) {
        phy_dev.reset();
        phy_dev = newBox<struct PhysicalDevice>(std::move(_phy_dev));
    }
    inline void add(Device&& _dev) {
        dev.reset();
        dev = newBox<struct Device>(std::move(_dev));
    }

    Res<Ref<Queue>> presentQueue() const;
    Res<Ref<Queue>> graphicsQueue() const;
    Res<Ref<Queue>> computeQueue() const;
    Res<Ref<Queue>> transferQueue() const;

public:
    inline InstanceBuilder Instance() {
        return InstanceBuilder();
    }
    inline PhysicalDeviceSelector PhysicalDevice() {
        return PhysicalDeviceSelector(*this);
    }
    inline DeviceBuilder Device() {
        return DeviceBuilder(*this, *this);
    }
    inline SwapchainBuilder Swapchain(const VkSurfaceKHR& surface) {
        return SwapchainBuilder(*this, surface);
    }

    inline ShaderModuleBuilder ShaderModule() {
        return ShaderModuleBuilder(*this);
    }
    inline BufferBuilder Buffer() {
        return BufferBuilder(*this);
    }
    inline ImageBuilder Image() {
        return ImageBuilder(*this);
    }
    inline ImageViewBuilder ImageView(const core::Image& image) {
        return ImageViewBuilder(image);
    }
    inline SamplerBuilder Sampler() {
        return SamplerBuilder(*this);
    }
    inline DescriptorSetLayoutBuilder DescriptorSetLayout() {
        return DescriptorSetLayoutBuilder(*this);
    }
    inline DescriptorPoolBuilder DescriptorPool(const core::DescriptorSetLayout& setlayout) {
        return DescriptorPoolBuilder(setlayout);
    }
    inline PipelineLayoutBuilder PipelineLayout() {
        return PipelineLayoutBuilder(*this);
    }
    inline GraphicsPipelineBuilder GraphicsPipeline(const core::PipelineLayout& layout) {
        return GraphicsPipelineBuilder(layout);
    }
    inline ComputePipelineBuilder ComputePipeline(const core::PipelineLayout& layout) {
        return ComputePipelineBuilder(layout);
    }
    inline RenderPassBuilder RenderPass() {
        return RenderPassBuilder(*this);
    }
    inline FramebufferBuilder Framebuffer(const core::RenderPass& render_pass) {
        return FramebufferBuilder(render_pass);
    }
    inline CommandPoolBuilder CommandPool() {
        return CommandPoolBuilder(*this);
    }
};

NAMESPACE_END(vkt)
