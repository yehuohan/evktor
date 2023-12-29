/**
 * @file vktor.hpp
 * @brief Graphics builder framework based on Vulkan
 *
 * @author yehuohan@qq.com
 */

#pragma once

/* vktor */
// clang-format off
#include "vktor/base/api.hpp"
#include "vktor/rendering/render_context.hpp"
#include "vktor/rendering/render_frame.hpp"
#include "vktor/rendering/render_target.hpp"
// clang-format on

NAMESPACE_BEGIN(vkt)

using namespace core;

class Vktor {
public:
    BaseApi api{};
    Box<RenderContext> render_context = nullptr;

public:
    void addRenderContext();

public:
    inline InstanceBuilder Instance() {
        return InstanceBuilder();
    }
    inline PhysicalDeviceSelector PhysicalDevice() {
        return PhysicalDeviceSelector(api);
    }
    inline DeviceBuilder Device() {
        return DeviceBuilder(api, api);
    }
    inline SwapchainBuilder Swapchain(const VkSurfaceKHR& surface) {
        return SwapchainBuilder(api, surface);
    }

    inline ShaderModuleBuilder ShaderModule() {
        return ShaderModuleBuilder(api);
    }
    inline BufferBuilder Buffer() {
        return BufferBuilder(api);
    }
    inline ImageBuilder Image() {
        return ImageBuilder(api);
    }
    inline ImageViewBuilder ImageView(const core::Image& image) {
        return ImageViewBuilder(image);
    }
    inline DescriptorSetLayoutBuilder DescriptorSetLayout() {
        return DescriptorSetLayoutBuilder(api);
    }
    inline DescriptorPoolBuilder DescriptorPool(const core::DescriptorSetLayout& setlayout) {
        return DescriptorPoolBuilder(setlayout);
    }
    inline RenderPassBuilder RenderPass() {
        return RenderPassBuilder(api);
    }
    inline PipelineLayoutBuilder PipelineLayout() {
        return PipelineLayoutBuilder(api);
    }
    inline GraphicsPipelineBuilder GraphicsPipeline(const core::PipelineLayout& layout) {
        return GraphicsPipelineBuilder(layout);
    }
    inline ComputePipelineBuilder ComputePipeline(const core::PipelineLayout& layout) {
        return ComputePipelineBuilder(layout);
    }
    inline FramebufferBuilder Framebuffer(const core::RenderPass& render_pass) {
        return FramebufferBuilder(render_pass);
    }
    inline CommandPoolBuilder CommandPool() {
        return CommandPoolBuilder(api);
    }
    inline SamplerBuilder Sampler() {
        return SamplerBuilder(api);
    }
};

NAMESPACE_END(vkt)
