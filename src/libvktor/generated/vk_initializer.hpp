#pragma once

#include <vulkan/vulkan.h>

namespace vkt {
namespace Itor {

inline VkBufferMemoryBarrier BufferMemoryBarrier(const void* next = nullptr) {
    VkBufferMemoryBarrier info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    info.pNext = next;
    return info;
}

inline VkImageMemoryBarrier ImageMemoryBarrier(const void* next = nullptr) {
    VkImageMemoryBarrier info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    info.pNext = next;
    return info;
}

inline VkMemoryBarrier MemoryBarrier(const void* next = nullptr) {
    VkMemoryBarrier info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    info.pNext = next;
    return info;
}

inline VkApplicationInfo ApplicationInfo(const void* next = nullptr) {
    VkApplicationInfo info{};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pNext = next;
    return info;
}

inline VkInstanceCreateInfo InstanceCreateInfo(const void* next = nullptr) {
    VkInstanceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceQueueCreateInfo DeviceQueueCreateInfo(const void* next = nullptr) {
    VkDeviceQueueCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceCreateInfo DeviceCreateInfo(const void* next = nullptr) {
    VkDeviceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkSubmitInfo SubmitInfo(const void* next = nullptr) {
    VkSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = next;
    return info;
}

inline VkMappedMemoryRange MappedMemoryRange(const void* next = nullptr) {
    VkMappedMemoryRange info{};
    info.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    info.pNext = next;
    return info;
}

inline VkMemoryAllocateInfo MemoryAllocateInfo(const void* next = nullptr) {
    VkMemoryAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkBindSparseInfo BindSparseInfo(const void* next = nullptr) {
    VkBindSparseInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
    info.pNext = next;
    return info;
}

inline VkFenceCreateInfo FenceCreateInfo(const void* next = nullptr) {
    VkFenceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkSemaphoreCreateInfo SemaphoreCreateInfo(const void* next = nullptr) {
    VkSemaphoreCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkEventCreateInfo EventCreateInfo(const void* next = nullptr) {
    VkEventCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkQueryPoolCreateInfo QueryPoolCreateInfo(const void* next = nullptr) {
    VkQueryPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkBufferCreateInfo BufferCreateInfo(const void* next = nullptr) {
    VkBufferCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkBufferViewCreateInfo BufferViewCreateInfo(const void* next = nullptr) {
    VkBufferViewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkImageCreateInfo ImageCreateInfo(const void* next = nullptr) {
    VkImageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkImageViewCreateInfo ImageViewCreateInfo(const void* next = nullptr) {
    VkImageViewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkShaderModuleCreateInfo ShaderModuleCreateInfo(const void* next = nullptr) {
    VkShaderModuleCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineCacheCreateInfo PipelineCacheCreateInfo(const void* next = nullptr) {
    VkPipelineCacheCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo(const void* next = nullptr) {
    VkPipelineShaderStageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkComputePipelineCreateInfo ComputePipelineCreateInfo(const void* next = nullptr) {
    VkComputePipelineCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo(const void* next = nullptr) {
    VkPipelineVertexInputStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo(const void* next = nullptr) {
    VkPipelineInputAssemblyStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo(const void* next = nullptr) {
    VkPipelineTessellationStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(const void* next = nullptr) {
    VkPipelineViewportStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo(const void* next = nullptr) {
    VkPipelineRasterizationStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo(const void* next = nullptr) {
    VkPipelineMultisampleStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo(const void* next = nullptr) {
    VkPipelineDepthStencilStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo(const void* next = nullptr) {
    VkPipelineColorBlendStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(const void* next = nullptr) {
    VkPipelineDynamicStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo(const void* next = nullptr) {
    VkGraphicsPipelineCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(const void* next = nullptr) {
    VkPipelineLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkSamplerCreateInfo SamplerCreateInfo(const void* next = nullptr) {
    VkSamplerCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkCopyDescriptorSet CopyDescriptorSet(const void* next = nullptr) {
    VkCopyDescriptorSet info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    info.pNext = next;
    return info;
}

inline VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(const void* next = nullptr) {
    VkDescriptorPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo(const void* next = nullptr) {
    VkDescriptorSetAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(const void* next = nullptr) {
    VkDescriptorSetLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkWriteDescriptorSet WriteDescriptorSet(const void* next = nullptr) {
    VkWriteDescriptorSet info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    info.pNext = next;
    return info;
}

inline VkFramebufferCreateInfo FramebufferCreateInfo(const void* next = nullptr) {
    VkFramebufferCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkRenderPassCreateInfo RenderPassCreateInfo(const void* next = nullptr) {
    VkRenderPassCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkCommandPoolCreateInfo CommandPoolCreateInfo(const void* next = nullptr) {
    VkCommandPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkCommandBufferAllocateInfo CommandBufferAllocateInfo(const void* next = nullptr) {
    VkCommandBufferAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo(const void* next = nullptr) {
    VkCommandBufferInheritanceInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
    info.pNext = next;
    return info;
}

inline VkCommandBufferBeginInfo CommandBufferBeginInfo(const void* next = nullptr) {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = next;
    return info;
}

inline VkRenderPassBeginInfo RenderPassBeginInfo(const void* next = nullptr) {
    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSubgroupProperties PhysicalDeviceSubgroupProperties(void* next = nullptr) {
    VkPhysicalDeviceSubgroupProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkBindBufferMemoryInfo BindBufferMemoryInfo(const void* next = nullptr) {
    VkBindBufferMemoryInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO;
    info.pNext = next;
    return info;
}

inline VkBindImageMemoryInfo BindImageMemoryInfo(const void* next = nullptr) {
    VkBindImageMemoryInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevice16BitStorageFeatures PhysicalDevice16BitStorageFeatures(void* next = nullptr) {
    VkPhysicalDevice16BitStorageFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
    info.pNext = next;
    return info;
}

inline VkMemoryDedicatedRequirements MemoryDedicatedRequirements(void* next = nullptr) {
    VkMemoryDedicatedRequirements info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
    info.pNext = next;
    return info;
}

inline VkMemoryDedicatedAllocateInfo MemoryDedicatedAllocateInfo(const void* next = nullptr) {
    VkMemoryDedicatedAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkMemoryAllocateFlagsInfo MemoryAllocateFlagsInfo(const void* next = nullptr) {
    VkMemoryAllocateFlagsInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupRenderPassBeginInfo DeviceGroupRenderPassBeginInfo(const void* next = nullptr) {
    VkDeviceGroupRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupCommandBufferBeginInfo DeviceGroupCommandBufferBeginInfo(const void* next = nullptr) {
    VkDeviceGroupCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupSubmitInfo DeviceGroupSubmitInfo(const void* next = nullptr) {
    VkDeviceGroupSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupBindSparseInfo DeviceGroupBindSparseInfo(const void* next = nullptr) {
    VkDeviceGroupBindSparseInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO;
    info.pNext = next;
    return info;
}

inline VkBindBufferMemoryDeviceGroupInfo BindBufferMemoryDeviceGroupInfo(const void* next = nullptr) {
    VkBindBufferMemoryDeviceGroupInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO;
    info.pNext = next;
    return info;
}

inline VkBindImageMemoryDeviceGroupInfo BindImageMemoryDeviceGroupInfo(const void* next = nullptr) {
    VkBindImageMemoryDeviceGroupInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceGroupProperties PhysicalDeviceGroupProperties(void* next = nullptr) {
    VkPhysicalDeviceGroupProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupDeviceCreateInfo DeviceGroupDeviceCreateInfo(const void* next = nullptr) {
    VkDeviceGroupDeviceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkBufferMemoryRequirementsInfo2 BufferMemoryRequirementsInfo2(const void* next = nullptr) {
    VkBufferMemoryRequirementsInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
    info.pNext = next;
    return info;
}

inline VkImageMemoryRequirementsInfo2 ImageMemoryRequirementsInfo2(const void* next = nullptr) {
    VkImageMemoryRequirementsInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
    info.pNext = next;
    return info;
}

inline VkImageSparseMemoryRequirementsInfo2 ImageSparseMemoryRequirementsInfo2(const void* next = nullptr) {
    VkImageSparseMemoryRequirementsInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2;
    info.pNext = next;
    return info;
}

inline VkMemoryRequirements2 MemoryRequirements2(void* next = nullptr) {
    VkMemoryRequirements2 info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
    info.pNext = next;
    return info;
}

inline VkSparseImageMemoryRequirements2 SparseImageMemoryRequirements2(void* next = nullptr) {
    VkSparseImageMemoryRequirements2 info{};
    info.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFeatures2 PhysicalDeviceFeatures2(void* next = nullptr) {
    VkPhysicalDeviceFeatures2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceProperties2 PhysicalDeviceProperties2(void* next = nullptr) {
    VkPhysicalDeviceProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    info.pNext = next;
    return info;
}

inline VkFormatProperties2 FormatProperties2(void* next = nullptr) {
    VkFormatProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
    info.pNext = next;
    return info;
}

inline VkImageFormatProperties2 ImageFormatProperties2(void* next = nullptr) {
    VkImageFormatProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageFormatInfo2 PhysicalDeviceImageFormatInfo2(const void* next = nullptr) {
    VkPhysicalDeviceImageFormatInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
    info.pNext = next;
    return info;
}

inline VkQueueFamilyProperties2 QueueFamilyProperties2(void* next = nullptr) {
    VkQueueFamilyProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMemoryProperties2 PhysicalDeviceMemoryProperties2(void* next = nullptr) {
    VkPhysicalDeviceMemoryProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
    info.pNext = next;
    return info;
}

inline VkSparseImageFormatProperties2 SparseImageFormatProperties2(void* next = nullptr) {
    VkSparseImageFormatProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSparseImageFormatInfo2 PhysicalDeviceSparseImageFormatInfo2(const void* next = nullptr) {
    VkPhysicalDeviceSparseImageFormatInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePointClippingProperties PhysicalDevicePointClippingProperties(void* next = nullptr) {
    VkPhysicalDevicePointClippingProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkRenderPassInputAttachmentAspectCreateInfo RenderPassInputAttachmentAspectCreateInfo(const void* next = nullptr) {
    VkRenderPassInputAttachmentAspectCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkImageViewUsageCreateInfo ImageViewUsageCreateInfo(const void* next = nullptr) {
    VkImageViewUsageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineTessellationDomainOriginStateCreateInfo PipelineTessellationDomainOriginStateCreateInfo(
    const void* next = nullptr) {
    VkPipelineTessellationDomainOriginStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkRenderPassMultiviewCreateInfo RenderPassMultiviewCreateInfo(const void* next = nullptr) {
    VkRenderPassMultiviewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiviewFeatures PhysicalDeviceMultiviewFeatures(void* next = nullptr) {
    VkPhysicalDeviceMultiviewFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiviewProperties PhysicalDeviceMultiviewProperties(void* next = nullptr) {
    VkPhysicalDeviceMultiviewProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVariablePointersFeatures PhysicalDeviceVariablePointersFeatures(void* next = nullptr) {
    VkPhysicalDeviceVariablePointersFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceProtectedMemoryFeatures PhysicalDeviceProtectedMemoryFeatures(void* next = nullptr) {
    VkPhysicalDeviceProtectedMemoryFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceProtectedMemoryProperties PhysicalDeviceProtectedMemoryProperties(void* next = nullptr) {
    VkPhysicalDeviceProtectedMemoryProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDeviceQueueInfo2 DeviceQueueInfo2(const void* next = nullptr) {
    VkDeviceQueueInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
    info.pNext = next;
    return info;
}

inline VkProtectedSubmitInfo ProtectedSubmitInfo(const void* next = nullptr) {
    VkProtectedSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
    info.pNext = next;
    return info;
}

inline VkSamplerYcbcrConversionCreateInfo SamplerYcbcrConversionCreateInfo(const void* next = nullptr) {
    VkSamplerYcbcrConversionCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkSamplerYcbcrConversionInfo SamplerYcbcrConversionInfo(const void* next = nullptr) {
    VkSamplerYcbcrConversionInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
    info.pNext = next;
    return info;
}

inline VkBindImagePlaneMemoryInfo BindImagePlaneMemoryInfo(const void* next = nullptr) {
    VkBindImagePlaneMemoryInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
    info.pNext = next;
    return info;
}

inline VkImagePlaneMemoryRequirementsInfo ImagePlaneMemoryRequirementsInfo(const void* next = nullptr) {
    VkImagePlaneMemoryRequirementsInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSamplerYcbcrConversionFeatures PhysicalDeviceSamplerYcbcrConversionFeatures(void* next = nullptr) {
    VkPhysicalDeviceSamplerYcbcrConversionFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
    info.pNext = next;
    return info;
}

inline VkSamplerYcbcrConversionImageFormatProperties SamplerYcbcrConversionImageFormatProperties(void* next = nullptr) {
    VkSamplerYcbcrConversionImageFormatProperties info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDescriptorUpdateTemplateCreateInfo DescriptorUpdateTemplateCreateInfo(const void* next = nullptr) {
    VkDescriptorUpdateTemplateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalImageFormatInfo PhysicalDeviceExternalImageFormatInfo(const void* next = nullptr) {
    VkPhysicalDeviceExternalImageFormatInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO;
    info.pNext = next;
    return info;
}

inline VkExternalImageFormatProperties ExternalImageFormatProperties(void* next = nullptr) {
    VkExternalImageFormatProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalBufferInfo PhysicalDeviceExternalBufferInfo(const void* next = nullptr) {
    VkPhysicalDeviceExternalBufferInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO;
    info.pNext = next;
    return info;
}

inline VkExternalBufferProperties ExternalBufferProperties(void* next = nullptr) {
    VkExternalBufferProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceIDProperties PhysicalDeviceIDProperties(void* next = nullptr) {
    VkPhysicalDeviceIDProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkExternalMemoryImageCreateInfo ExternalMemoryImageCreateInfo(const void* next = nullptr) {
    VkExternalMemoryImageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkExternalMemoryBufferCreateInfo ExternalMemoryBufferCreateInfo(const void* next = nullptr) {
    VkExternalMemoryBufferCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkExportMemoryAllocateInfo ExportMemoryAllocateInfo(const void* next = nullptr) {
    VkExportMemoryAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalFenceInfo PhysicalDeviceExternalFenceInfo(const void* next = nullptr) {
    VkPhysicalDeviceExternalFenceInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO;
    info.pNext = next;
    return info;
}

inline VkExternalFenceProperties ExternalFenceProperties(void* next = nullptr) {
    VkExternalFenceProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkExportFenceCreateInfo ExportFenceCreateInfo(const void* next = nullptr) {
    VkExportFenceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkExportSemaphoreCreateInfo ExportSemaphoreCreateInfo(const void* next = nullptr) {
    VkExportSemaphoreCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalSemaphoreInfo PhysicalDeviceExternalSemaphoreInfo(const void* next = nullptr) {
    VkPhysicalDeviceExternalSemaphoreInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO;
    info.pNext = next;
    return info;
}

inline VkExternalSemaphoreProperties ExternalSemaphoreProperties(void* next = nullptr) {
    VkExternalSemaphoreProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance3Properties PhysicalDeviceMaintenance3Properties(void* next = nullptr) {
    VkPhysicalDeviceMaintenance3Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetLayoutSupport DescriptorSetLayoutSupport(void* next = nullptr) {
    VkDescriptorSetLayoutSupport info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderDrawParametersFeatures PhysicalDeviceShaderDrawParametersFeatures(void* next = nullptr) {
    VkPhysicalDeviceShaderDrawParametersFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkan11Features PhysicalDeviceVulkan11Features(void* next = nullptr) {
    VkPhysicalDeviceVulkan11Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkan11Properties PhysicalDeviceVulkan11Properties(void* next = nullptr) {
    VkPhysicalDeviceVulkan11Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkan12Features PhysicalDeviceVulkan12Features(void* next = nullptr) {
    VkPhysicalDeviceVulkan12Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkan12Properties PhysicalDeviceVulkan12Properties(void* next = nullptr) {
    VkPhysicalDeviceVulkan12Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkImageFormatListCreateInfo ImageFormatListCreateInfo(const void* next = nullptr) {
    VkImageFormatListCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkAttachmentDescription2 AttachmentDescription2(const void* next = nullptr) {
    VkAttachmentDescription2 info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
    info.pNext = next;
    return info;
}

inline VkAttachmentReference2 AttachmentReference2(const void* next = nullptr) {
    VkAttachmentReference2 info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
    info.pNext = next;
    return info;
}

inline VkSubpassDescription2 SubpassDescription2(const void* next = nullptr) {
    VkSubpassDescription2 info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
    info.pNext = next;
    return info;
}

inline VkSubpassDependency2 SubpassDependency2(const void* next = nullptr) {
    VkSubpassDependency2 info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
    info.pNext = next;
    return info;
}

inline VkRenderPassCreateInfo2 RenderPassCreateInfo2(const void* next = nullptr) {
    VkRenderPassCreateInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
    info.pNext = next;
    return info;
}

inline VkSubpassBeginInfo SubpassBeginInfo(const void* next = nullptr) {
    VkSubpassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO;
    info.pNext = next;
    return info;
}

inline VkSubpassEndInfo SubpassEndInfo(const void* next = nullptr) {
    VkSubpassEndInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_END_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevice8BitStorageFeatures PhysicalDevice8BitStorageFeatures(void* next = nullptr) {
    VkPhysicalDevice8BitStorageFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDriverProperties PhysicalDeviceDriverProperties(void* next = nullptr) {
    VkPhysicalDeviceDriverProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderAtomicInt64Features PhysicalDeviceShaderAtomicInt64Features(void* next = nullptr) {
    VkPhysicalDeviceShaderAtomicInt64Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderFloat16Int8Features PhysicalDeviceShaderFloat16Int8Features(void* next = nullptr) {
    VkPhysicalDeviceShaderFloat16Int8Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFloatControlsProperties PhysicalDeviceFloatControlsProperties(void* next = nullptr) {
    VkPhysicalDeviceFloatControlsProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetLayoutBindingFlagsCreateInfo DescriptorSetLayoutBindingFlagsCreateInfo(const void* next = nullptr) {
    VkDescriptorSetLayoutBindingFlagsCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDescriptorIndexingFeatures PhysicalDeviceDescriptorIndexingFeatures(void* next = nullptr) {
    VkPhysicalDeviceDescriptorIndexingFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDescriptorIndexingProperties PhysicalDeviceDescriptorIndexingProperties(void* next = nullptr) {
    VkPhysicalDeviceDescriptorIndexingProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetVariableDescriptorCountAllocateInfo DescriptorSetVariableDescriptorCountAllocateInfo(
    const void* next = nullptr) {
    VkDescriptorSetVariableDescriptorCountAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetVariableDescriptorCountLayoutSupport DescriptorSetVariableDescriptorCountLayoutSupport(
    void* next = nullptr) {
    VkDescriptorSetVariableDescriptorCountLayoutSupport info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT;
    info.pNext = next;
    return info;
}

inline VkSubpassDescriptionDepthStencilResolve SubpassDescriptionDepthStencilResolve(const void* next = nullptr) {
    VkSubpassDescriptionDepthStencilResolve info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDepthStencilResolveProperties PhysicalDeviceDepthStencilResolveProperties(void* next = nullptr) {
    VkPhysicalDeviceDepthStencilResolveProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceScalarBlockLayoutFeatures PhysicalDeviceScalarBlockLayoutFeatures(void* next = nullptr) {
    VkPhysicalDeviceScalarBlockLayoutFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES;
    info.pNext = next;
    return info;
}

inline VkImageStencilUsageCreateInfo ImageStencilUsageCreateInfo(const void* next = nullptr) {
    VkImageStencilUsageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkSamplerReductionModeCreateInfo SamplerReductionModeCreateInfo(const void* next = nullptr) {
    VkSamplerReductionModeCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSamplerFilterMinmaxProperties PhysicalDeviceSamplerFilterMinmaxProperties(void* next = nullptr) {
    VkPhysicalDeviceSamplerFilterMinmaxProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkanMemoryModelFeatures PhysicalDeviceVulkanMemoryModelFeatures(void* next = nullptr) {
    VkPhysicalDeviceVulkanMemoryModelFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImagelessFramebufferFeatures PhysicalDeviceImagelessFramebufferFeatures(void* next = nullptr) {
    VkPhysicalDeviceImagelessFramebufferFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES;
    info.pNext = next;
    return info;
}

inline VkFramebufferAttachmentImageInfo FramebufferAttachmentImageInfo(const void* next = nullptr) {
    VkFramebufferAttachmentImageInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO;
    info.pNext = next;
    return info;
}

inline VkFramebufferAttachmentsCreateInfo FramebufferAttachmentsCreateInfo(const void* next = nullptr) {
    VkFramebufferAttachmentsCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkRenderPassAttachmentBeginInfo RenderPassAttachmentBeginInfo(const void* next = nullptr) {
    VkRenderPassAttachmentBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceUniformBufferStandardLayoutFeatures PhysicalDeviceUniformBufferStandardLayoutFeatures(
    void* next = nullptr) {
    VkPhysicalDeviceUniformBufferStandardLayoutFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures PhysicalDeviceShaderSubgroupExtendedTypesFeatures(
    void* next = nullptr) {
    VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures PhysicalDeviceSeparateDepthStencilLayoutsFeatures(
    void* next = nullptr) {
    VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES;
    info.pNext = next;
    return info;
}

inline VkAttachmentReferenceStencilLayout AttachmentReferenceStencilLayout(void* next = nullptr) {
    VkAttachmentReferenceStencilLayout info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT;
    info.pNext = next;
    return info;
}

inline VkAttachmentDescriptionStencilLayout AttachmentDescriptionStencilLayout(void* next = nullptr) {
    VkAttachmentDescriptionStencilLayout info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceHostQueryResetFeatures PhysicalDeviceHostQueryResetFeatures(void* next = nullptr) {
    VkPhysicalDeviceHostQueryResetFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTimelineSemaphoreFeatures PhysicalDeviceTimelineSemaphoreFeatures(void* next = nullptr) {
    VkPhysicalDeviceTimelineSemaphoreFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTimelineSemaphoreProperties PhysicalDeviceTimelineSemaphoreProperties(void* next = nullptr) {
    VkPhysicalDeviceTimelineSemaphoreProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkSemaphoreTypeCreateInfo SemaphoreTypeCreateInfo(const void* next = nullptr) {
    VkSemaphoreTypeCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkTimelineSemaphoreSubmitInfo TimelineSemaphoreSubmitInfo(const void* next = nullptr) {
    VkTimelineSemaphoreSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
    info.pNext = next;
    return info;
}

inline VkSemaphoreWaitInfo SemaphoreWaitInfo(const void* next = nullptr) {
    VkSemaphoreWaitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
    info.pNext = next;
    return info;
}

inline VkSemaphoreSignalInfo SemaphoreSignalInfo(const void* next = nullptr) {
    VkSemaphoreSignalInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceBufferDeviceAddressFeatures PhysicalDeviceBufferDeviceAddressFeatures(void* next = nullptr) {
    VkPhysicalDeviceBufferDeviceAddressFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
    info.pNext = next;
    return info;
}

inline VkBufferDeviceAddressInfo BufferDeviceAddressInfo(const void* next = nullptr) {
    VkBufferDeviceAddressInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
    info.pNext = next;
    return info;
}

inline VkBufferOpaqueCaptureAddressCreateInfo BufferOpaqueCaptureAddressCreateInfo(const void* next = nullptr) {
    VkBufferOpaqueCaptureAddressCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkMemoryOpaqueCaptureAddressAllocateInfo MemoryOpaqueCaptureAddressAllocateInfo(const void* next = nullptr) {
    VkMemoryOpaqueCaptureAddressAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO;
    info.pNext = next;
    return info;
}

inline VkDeviceMemoryOpaqueCaptureAddressInfo DeviceMemoryOpaqueCaptureAddressInfo(const void* next = nullptr) {
    VkDeviceMemoryOpaqueCaptureAddressInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkan13Features PhysicalDeviceVulkan13Features(void* next = nullptr) {
    VkPhysicalDeviceVulkan13Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVulkan13Properties PhysicalDeviceVulkan13Properties(void* next = nullptr) {
    VkPhysicalDeviceVulkan13Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPipelineCreationFeedbackCreateInfo PipelineCreationFeedbackCreateInfo(const void* next = nullptr) {
    VkPipelineCreationFeedbackCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderTerminateInvocationFeatures PhysicalDeviceShaderTerminateInvocationFeatures(void* next = nullptr) {
    VkPhysicalDeviceShaderTerminateInvocationFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceToolProperties PhysicalDeviceToolProperties(void* next = nullptr) {
    VkPhysicalDeviceToolProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures PhysicalDeviceShaderDemoteToHelperInvocationFeatures(
    void* next = nullptr) {
    VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePrivateDataFeatures PhysicalDevicePrivateDataFeatures(void* next = nullptr) {
    VkPhysicalDevicePrivateDataFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES;
    info.pNext = next;
    return info;
}

inline VkDevicePrivateDataCreateInfo DevicePrivateDataCreateInfo(const void* next = nullptr) {
    VkDevicePrivateDataCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPrivateDataSlotCreateInfo PrivateDataSlotCreateInfo(const void* next = nullptr) {
    VkPrivateDataSlotCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelineCreationCacheControlFeatures PhysicalDevicePipelineCreationCacheControlFeatures(
    void* next = nullptr) {
    VkPhysicalDevicePipelineCreationCacheControlFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES;
    info.pNext = next;
    return info;
}

inline VkMemoryBarrier2 MemoryBarrier2(const void* next = nullptr) {
    VkMemoryBarrier2 info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2;
    info.pNext = next;
    return info;
}

inline VkBufferMemoryBarrier2 BufferMemoryBarrier2(const void* next = nullptr) {
    VkBufferMemoryBarrier2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2;
    info.pNext = next;
    return info;
}

inline VkImageMemoryBarrier2 ImageMemoryBarrier2(const void* next = nullptr) {
    VkImageMemoryBarrier2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    info.pNext = next;
    return info;
}

inline VkDependencyInfo DependencyInfo(const void* next = nullptr) {
    VkDependencyInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    info.pNext = next;
    return info;
}

inline VkSemaphoreSubmitInfo SemaphoreSubmitInfo(const void* next = nullptr) {
    VkSemaphoreSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    info.pNext = next;
    return info;
}

inline VkCommandBufferSubmitInfo CommandBufferSubmitInfo(const void* next = nullptr) {
    VkCommandBufferSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
    info.pNext = next;
    return info;
}

inline VkSubmitInfo2 SubmitInfo2(const void* next = nullptr) {
    VkSubmitInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSynchronization2Features PhysicalDeviceSynchronization2Features(void* next = nullptr) {
    VkPhysicalDeviceSynchronization2Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures(
    void* next = nullptr) {
    VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageRobustnessFeatures PhysicalDeviceImageRobustnessFeatures(void* next = nullptr) {
    VkPhysicalDeviceImageRobustnessFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES;
    info.pNext = next;
    return info;
}

inline VkBufferCopy2 BufferCopy2(const void* next = nullptr) {
    VkBufferCopy2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COPY_2;
    info.pNext = next;
    return info;
}

inline VkCopyBufferInfo2 CopyBufferInfo2(const void* next = nullptr) {
    VkCopyBufferInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2;
    info.pNext = next;
    return info;
}

inline VkImageCopy2 ImageCopy2(const void* next = nullptr) {
    VkImageCopy2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_COPY_2;
    info.pNext = next;
    return info;
}

inline VkCopyImageInfo2 CopyImageInfo2(const void* next = nullptr) {
    VkCopyImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2;
    info.pNext = next;
    return info;
}

inline VkBufferImageCopy2 BufferImageCopy2(const void* next = nullptr) {
    VkBufferImageCopy2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2;
    info.pNext = next;
    return info;
}

inline VkCopyBufferToImageInfo2 CopyBufferToImageInfo2(const void* next = nullptr) {
    VkCopyBufferToImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2;
    info.pNext = next;
    return info;
}

inline VkCopyImageToBufferInfo2 CopyImageToBufferInfo2(const void* next = nullptr) {
    VkCopyImageToBufferInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2;
    info.pNext = next;
    return info;
}

inline VkImageBlit2 ImageBlit2(const void* next = nullptr) {
    VkImageBlit2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_BLIT_2;
    info.pNext = next;
    return info;
}

inline VkBlitImageInfo2 BlitImageInfo2(const void* next = nullptr) {
    VkBlitImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2;
    info.pNext = next;
    return info;
}

inline VkImageResolve2 ImageResolve2(const void* next = nullptr) {
    VkImageResolve2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2;
    info.pNext = next;
    return info;
}

inline VkResolveImageInfo2 ResolveImageInfo2(const void* next = nullptr) {
    VkResolveImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSubgroupSizeControlFeatures PhysicalDeviceSubgroupSizeControlFeatures(void* next = nullptr) {
    VkPhysicalDeviceSubgroupSizeControlFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSubgroupSizeControlProperties PhysicalDeviceSubgroupSizeControlProperties(void* next = nullptr) {
    VkPhysicalDeviceSubgroupSizeControlProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPipelineShaderStageRequiredSubgroupSizeCreateInfo PipelineShaderStageRequiredSubgroupSizeCreateInfo(
    void* next = nullptr) {
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceInlineUniformBlockFeatures PhysicalDeviceInlineUniformBlockFeatures(void* next = nullptr) {
    VkPhysicalDeviceInlineUniformBlockFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceInlineUniformBlockProperties PhysicalDeviceInlineUniformBlockProperties(void* next = nullptr) {
    VkPhysicalDeviceInlineUniformBlockProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkWriteDescriptorSetInlineUniformBlock WriteDescriptorSetInlineUniformBlock(const void* next = nullptr) {
    VkWriteDescriptorSetInlineUniformBlock info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK;
    info.pNext = next;
    return info;
}

inline VkDescriptorPoolInlineUniformBlockCreateInfo DescriptorPoolInlineUniformBlockCreateInfo(const void* next = nullptr) {
    VkDescriptorPoolInlineUniformBlockCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTextureCompressionASTCHDRFeatures PhysicalDeviceTextureCompressionASTCHDRFeatures(void* next = nullptr) {
    VkPhysicalDeviceTextureCompressionASTCHDRFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES;
    info.pNext = next;
    return info;
}

inline VkRenderingAttachmentInfo RenderingAttachmentInfo(const void* next = nullptr) {
    VkRenderingAttachmentInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    info.pNext = next;
    return info;
}

inline VkRenderingInfo RenderingInfo(const void* next = nullptr) {
    VkRenderingInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    info.pNext = next;
    return info;
}

inline VkPipelineRenderingCreateInfo PipelineRenderingCreateInfo(const void* next = nullptr) {
    VkPipelineRenderingCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDynamicRenderingFeatures PhysicalDeviceDynamicRenderingFeatures(void* next = nullptr) {
    VkPhysicalDeviceDynamicRenderingFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
    info.pNext = next;
    return info;
}

inline VkCommandBufferInheritanceRenderingInfo CommandBufferInheritanceRenderingInfo(const void* next = nullptr) {
    VkCommandBufferInheritanceRenderingInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderIntegerDotProductFeatures PhysicalDeviceShaderIntegerDotProductFeatures(void* next = nullptr) {
    VkPhysicalDeviceShaderIntegerDotProductFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderIntegerDotProductProperties PhysicalDeviceShaderIntegerDotProductProperties(void* next = nullptr) {
    VkPhysicalDeviceShaderIntegerDotProductProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTexelBufferAlignmentProperties PhysicalDeviceTexelBufferAlignmentProperties(void* next = nullptr) {
    VkPhysicalDeviceTexelBufferAlignmentProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkFormatProperties3 FormatProperties3(void* next = nullptr) {
    VkFormatProperties3 info{};
    info.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance4Features PhysicalDeviceMaintenance4Features(void* next = nullptr) {
    VkPhysicalDeviceMaintenance4Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance4Properties PhysicalDeviceMaintenance4Properties(void* next = nullptr) {
    VkPhysicalDeviceMaintenance4Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES;
    info.pNext = next;
    return info;
}

inline VkDeviceBufferMemoryRequirements DeviceBufferMemoryRequirements(const void* next = nullptr) {
    VkDeviceBufferMemoryRequirements info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS;
    info.pNext = next;
    return info;
}

inline VkDeviceImageMemoryRequirements DeviceImageMemoryRequirements(const void* next = nullptr) {
    VkDeviceImageMemoryRequirements info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS;
    info.pNext = next;
    return info;
}

inline VkSwapchainCreateInfoKHR SwapchainCreateInfoKHR(const void* next = nullptr) {
    VkSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPresentInfoKHR PresentInfoKHR(const void* next = nullptr) {
    VkPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkImageSwapchainCreateInfoKHR ImageSwapchainCreateInfoKHR(const void* next = nullptr) {
    VkImageSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkBindImageMemorySwapchainInfoKHR BindImageMemorySwapchainInfoKHR(const void* next = nullptr) {
    VkBindImageMemorySwapchainInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkAcquireNextImageInfoKHR AcquireNextImageInfoKHR(const void* next = nullptr) {
    VkAcquireNextImageInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupPresentCapabilitiesKHR DeviceGroupPresentCapabilitiesKHR(void* next = nullptr) {
    VkDeviceGroupPresentCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupPresentInfoKHR DeviceGroupPresentInfoKHR(const void* next = nullptr) {
    VkDeviceGroupPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkDeviceGroupSwapchainCreateInfoKHR DeviceGroupSwapchainCreateInfoKHR(const void* next = nullptr) {
    VkDeviceGroupSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayModeCreateInfoKHR DisplayModeCreateInfoKHR(const void* next = nullptr) {
    VkDisplayModeCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplaySurfaceCreateInfoKHR DisplaySurfaceCreateInfoKHR(const void* next = nullptr) {
    VkDisplaySurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayPresentInfoKHR DisplayPresentInfoKHR(const void* next = nullptr) {
    VkDisplayPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_XLIB_KHR
inline VkXlibSurfaceCreateInfoKHR XlibSurfaceCreateInfoKHR(const void* next = nullptr) {
    VkXlibSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_XLIB_KHR

#ifdef VK_USE_PLATFORM_XCB_KHR
inline VkXcbSurfaceCreateInfoKHR XcbSurfaceCreateInfoKHR(const void* next = nullptr) {
    VkXcbSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_XCB_KHR

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
inline VkWaylandSurfaceCreateInfoKHR WaylandSurfaceCreateInfoKHR(const void* next = nullptr) {
    VkWaylandSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WAYLAND_KHR

#ifdef VK_USE_PLATFORM_ANDROID_KHR
inline VkAndroidSurfaceCreateInfoKHR AndroidSurfaceCreateInfoKHR(const void* next = nullptr) {
    VkAndroidSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_ANDROID_KHR

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkWin32SurfaceCreateInfoKHR Win32SurfaceCreateInfoKHR(const void* next = nullptr) {
    VkWin32SurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkQueueFamilyQueryResultStatusPropertiesKHR QueueFamilyQueryResultStatusPropertiesKHR(void* next = nullptr) {
    VkQueueFamilyQueryResultStatusPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkQueueFamilyVideoPropertiesKHR QueueFamilyVideoPropertiesKHR(void* next = nullptr) {
    VkQueueFamilyVideoPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoProfileInfoKHR VideoProfileInfoKHR(const void* next = nullptr) {
    VkVideoProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoProfileListInfoKHR VideoProfileListInfoKHR(const void* next = nullptr) {
    VkVideoProfileListInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoCapabilitiesKHR VideoCapabilitiesKHR(void* next = nullptr) {
    VkVideoCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVideoFormatInfoKHR PhysicalDeviceVideoFormatInfoKHR(const void* next = nullptr) {
    VkPhysicalDeviceVideoFormatInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoFormatPropertiesKHR VideoFormatPropertiesKHR(void* next = nullptr) {
    VkVideoFormatPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoPictureResourceInfoKHR VideoPictureResourceInfoKHR(const void* next = nullptr) {
    VkVideoPictureResourceInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoReferenceSlotInfoKHR VideoReferenceSlotInfoKHR(const void* next = nullptr) {
    VkVideoReferenceSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoSessionMemoryRequirementsKHR VideoSessionMemoryRequirementsKHR(void* next = nullptr) {
    VkVideoSessionMemoryRequirementsKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
    info.pNext = next;
    return info;
}

inline VkBindVideoSessionMemoryInfoKHR BindVideoSessionMemoryInfoKHR(const void* next = nullptr) {
    VkBindVideoSessionMemoryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoSessionCreateInfoKHR VideoSessionCreateInfoKHR(const void* next = nullptr) {
    VkVideoSessionCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoSessionParametersCreateInfoKHR VideoSessionParametersCreateInfoKHR(const void* next = nullptr) {
    VkVideoSessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoSessionParametersUpdateInfoKHR VideoSessionParametersUpdateInfoKHR(const void* next = nullptr) {
    VkVideoSessionParametersUpdateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoBeginCodingInfoKHR VideoBeginCodingInfoKHR(const void* next = nullptr) {
    VkVideoBeginCodingInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEndCodingInfoKHR VideoEndCodingInfoKHR(const void* next = nullptr) {
    VkVideoEndCodingInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoCodingControlInfoKHR VideoCodingControlInfoKHR(const void* next = nullptr) {
    VkVideoCodingControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeCapabilitiesKHR VideoDecodeCapabilitiesKHR(void* next = nullptr) {
    VkVideoDecodeCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeUsageInfoKHR VideoDecodeUsageInfoKHR(const void* next = nullptr) {
    VkVideoDecodeUsageInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeInfoKHR VideoDecodeInfoKHR(const void* next = nullptr) {
    VkVideoDecodeInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264CapabilitiesKHR VideoEncodeH264CapabilitiesKHR(void* next = nullptr) {
    VkVideoEncodeH264CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264QualityLevelPropertiesKHR VideoEncodeH264QualityLevelPropertiesKHR(void* next = nullptr) {
    VkVideoEncodeH264QualityLevelPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_QUALITY_LEVEL_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264SessionCreateInfoKHR VideoEncodeH264SessionCreateInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264SessionCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264SessionParametersAddInfoKHR VideoEncodeH264SessionParametersAddInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264SessionParametersCreateInfoKHR VideoEncodeH264SessionParametersCreateInfoKHR(
    const void* next = nullptr) {
    VkVideoEncodeH264SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264SessionParametersGetInfoKHR VideoEncodeH264SessionParametersGetInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264SessionParametersGetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_GET_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264SessionParametersFeedbackInfoKHR VideoEncodeH264SessionParametersFeedbackInfoKHR(void* next = nullptr) {
    VkVideoEncodeH264SessionParametersFeedbackInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_FEEDBACK_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264NaluSliceInfoKHR VideoEncodeH264NaluSliceInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264NaluSliceInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_NALU_SLICE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264PictureInfoKHR VideoEncodeH264PictureInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PICTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264DpbSlotInfoKHR VideoEncodeH264DpbSlotInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_DPB_SLOT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264ProfileInfoKHR VideoEncodeH264ProfileInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264RateControlInfoKHR VideoEncodeH264RateControlInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264RateControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264RateControlLayerInfoKHR VideoEncodeH264RateControlLayerInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264RateControlLayerInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_LAYER_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH264GopRemainingFrameInfoKHR VideoEncodeH264GopRemainingFrameInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH264GopRemainingFrameInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_GOP_REMAINING_FRAME_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265CapabilitiesKHR VideoEncodeH265CapabilitiesKHR(void* next = nullptr) {
    VkVideoEncodeH265CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265SessionCreateInfoKHR VideoEncodeH265SessionCreateInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265SessionCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265QualityLevelPropertiesKHR VideoEncodeH265QualityLevelPropertiesKHR(void* next = nullptr) {
    VkVideoEncodeH265QualityLevelPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_QUALITY_LEVEL_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265SessionParametersAddInfoKHR VideoEncodeH265SessionParametersAddInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265SessionParametersCreateInfoKHR VideoEncodeH265SessionParametersCreateInfoKHR(
    const void* next = nullptr) {
    VkVideoEncodeH265SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265SessionParametersGetInfoKHR VideoEncodeH265SessionParametersGetInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265SessionParametersGetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_GET_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265SessionParametersFeedbackInfoKHR VideoEncodeH265SessionParametersFeedbackInfoKHR(void* next = nullptr) {
    VkVideoEncodeH265SessionParametersFeedbackInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_FEEDBACK_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265NaluSliceSegmentInfoKHR VideoEncodeH265NaluSliceSegmentInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265NaluSliceSegmentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_NALU_SLICE_SEGMENT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265PictureInfoKHR VideoEncodeH265PictureInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PICTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265DpbSlotInfoKHR VideoEncodeH265DpbSlotInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_DPB_SLOT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265ProfileInfoKHR VideoEncodeH265ProfileInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PROFILE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265RateControlInfoKHR VideoEncodeH265RateControlInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265RateControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265RateControlLayerInfoKHR VideoEncodeH265RateControlLayerInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265RateControlLayerInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_LAYER_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeH265GopRemainingFrameInfoKHR VideoEncodeH265GopRemainingFrameInfoKHR(const void* next = nullptr) {
    VkVideoEncodeH265GopRemainingFrameInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_GOP_REMAINING_FRAME_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH264ProfileInfoKHR VideoDecodeH264ProfileInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH264ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH264CapabilitiesKHR VideoDecodeH264CapabilitiesKHR(void* next = nullptr) {
    VkVideoDecodeH264CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH264SessionParametersAddInfoKHR VideoDecodeH264SessionParametersAddInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH264SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH264SessionParametersCreateInfoKHR VideoDecodeH264SessionParametersCreateInfoKHR(
    const void* next = nullptr) {
    VkVideoDecodeH264SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH264PictureInfoKHR VideoDecodeH264PictureInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH264PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH264DpbSlotInfoKHR VideoDecodeH264DpbSlotInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH264DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkRenderingFragmentShadingRateAttachmentInfoKHR RenderingFragmentShadingRateAttachmentInfoKHR(
    const void* next = nullptr) {
    VkRenderingFragmentShadingRateAttachmentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkRenderingFragmentDensityMapAttachmentInfoEXT RenderingFragmentDensityMapAttachmentInfoEXT(const void* next = nullptr) {
    VkRenderingFragmentDensityMapAttachmentInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkAttachmentSampleCountInfoAMD AttachmentSampleCountInfoAMD(const void* next = nullptr) {
    VkAttachmentSampleCountInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD;
    info.pNext = next;
    return info;
}

inline VkMultiviewPerViewAttributesInfoNVX MultiviewPerViewAttributesInfoNVX(const void* next = nullptr) {
    VkMultiviewPerViewAttributesInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkImportMemoryWin32HandleInfoKHR ImportMemoryWin32HandleInfoKHR(const void* next = nullptr) {
    VkImportMemoryWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkExportMemoryWin32HandleInfoKHR ExportMemoryWin32HandleInfoKHR(const void* next = nullptr) {
    VkExportMemoryWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkMemoryWin32HandlePropertiesKHR MemoryWin32HandlePropertiesKHR(void* next = nullptr) {
    VkMemoryWin32HandlePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkMemoryGetWin32HandleInfoKHR MemoryGetWin32HandleInfoKHR(const void* next = nullptr) {
    VkMemoryGetWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkImportMemoryFdInfoKHR ImportMemoryFdInfoKHR(const void* next = nullptr) {
    VkImportMemoryFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkMemoryFdPropertiesKHR MemoryFdPropertiesKHR(void* next = nullptr) {
    VkMemoryFdPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkMemoryGetFdInfoKHR MemoryGetFdInfoKHR(const void* next = nullptr) {
    VkMemoryGetFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkWin32KeyedMutexAcquireReleaseInfoKHR Win32KeyedMutexAcquireReleaseInfoKHR(const void* next = nullptr) {
    VkWin32KeyedMutexAcquireReleaseInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkImportSemaphoreWin32HandleInfoKHR ImportSemaphoreWin32HandleInfoKHR(const void* next = nullptr) {
    VkImportSemaphoreWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkExportSemaphoreWin32HandleInfoKHR ExportSemaphoreWin32HandleInfoKHR(const void* next = nullptr) {
    VkExportSemaphoreWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkD3D12FenceSubmitInfoKHR D3D12FenceSubmitInfoKHR(const void* next = nullptr) {
    VkD3D12FenceSubmitInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkSemaphoreGetWin32HandleInfoKHR SemaphoreGetWin32HandleInfoKHR(const void* next = nullptr) {
    VkSemaphoreGetWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkImportSemaphoreFdInfoKHR ImportSemaphoreFdInfoKHR(const void* next = nullptr) {
    VkImportSemaphoreFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkSemaphoreGetFdInfoKHR SemaphoreGetFdInfoKHR(const void* next = nullptr) {
    VkSemaphoreGetFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePushDescriptorPropertiesKHR PhysicalDevicePushDescriptorPropertiesKHR(void* next = nullptr) {
    VkPhysicalDevicePushDescriptorPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPresentRegionsKHR PresentRegionsKHR(const void* next = nullptr) {
    VkPresentRegionsKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR;
    info.pNext = next;
    return info;
}

inline VkSharedPresentSurfaceCapabilitiesKHR SharedPresentSurfaceCapabilitiesKHR(void* next = nullptr) {
    VkSharedPresentSurfaceCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkImportFenceWin32HandleInfoKHR ImportFenceWin32HandleInfoKHR(const void* next = nullptr) {
    VkImportFenceWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkExportFenceWin32HandleInfoKHR ExportFenceWin32HandleInfoKHR(const void* next = nullptr) {
    VkExportFenceWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkFenceGetWin32HandleInfoKHR FenceGetWin32HandleInfoKHR(const void* next = nullptr) {
    VkFenceGetWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkImportFenceFdInfoKHR ImportFenceFdInfoKHR(const void* next = nullptr) {
    VkImportFenceFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkFenceGetFdInfoKHR FenceGetFdInfoKHR(const void* next = nullptr) {
    VkFenceGetFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePerformanceQueryFeaturesKHR PhysicalDevicePerformanceQueryFeaturesKHR(void* next = nullptr) {
    VkPhysicalDevicePerformanceQueryFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePerformanceQueryPropertiesKHR PhysicalDevicePerformanceQueryPropertiesKHR(void* next = nullptr) {
    VkPhysicalDevicePerformanceQueryPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPerformanceCounterKHR PerformanceCounterKHR(void* next = nullptr) {
    VkPerformanceCounterKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR;
    info.pNext = next;
    return info;
}

inline VkPerformanceCounterDescriptionKHR PerformanceCounterDescriptionKHR(void* next = nullptr) {
    VkPerformanceCounterDescriptionKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR;
    info.pNext = next;
    return info;
}

inline VkQueryPoolPerformanceCreateInfoKHR QueryPoolPerformanceCreateInfoKHR(const void* next = nullptr) {
    VkQueryPoolPerformanceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkAcquireProfilingLockInfoKHR AcquireProfilingLockInfoKHR(const void* next = nullptr) {
    VkAcquireProfilingLockInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPerformanceQuerySubmitInfoKHR PerformanceQuerySubmitInfoKHR(const void* next = nullptr) {
    VkPerformanceQuerySubmitInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSurfaceInfo2KHR PhysicalDeviceSurfaceInfo2KHR(const void* next = nullptr) {
    VkPhysicalDeviceSurfaceInfo2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
    info.pNext = next;
    return info;
}

inline VkSurfaceCapabilities2KHR SurfaceCapabilities2KHR(void* next = nullptr) {
    VkSurfaceCapabilities2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
    info.pNext = next;
    return info;
}

inline VkSurfaceFormat2KHR SurfaceFormat2KHR(void* next = nullptr) {
    VkSurfaceFormat2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayProperties2KHR DisplayProperties2KHR(void* next = nullptr) {
    VkDisplayProperties2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayPlaneProperties2KHR DisplayPlaneProperties2KHR(void* next = nullptr) {
    VkDisplayPlaneProperties2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayModeProperties2KHR DisplayModeProperties2KHR(void* next = nullptr) {
    VkDisplayModeProperties2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayPlaneInfo2KHR DisplayPlaneInfo2KHR(const void* next = nullptr) {
    VkDisplayPlaneInfo2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR;
    info.pNext = next;
    return info;
}

inline VkDisplayPlaneCapabilities2KHR DisplayPlaneCapabilities2KHR(void* next = nullptr) {
    VkDisplayPlaneCapabilities2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR;
    info.pNext = next;
    return info;
}

#ifdef VK_ENABLE_BETA_EXTENSIONS
inline VkPhysicalDevicePortabilitySubsetFeaturesKHR PhysicalDevicePortabilitySubsetFeaturesKHR(void* next = nullptr) {
    VkPhysicalDevicePortabilitySubsetFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePortabilitySubsetPropertiesKHR PhysicalDevicePortabilitySubsetPropertiesKHR(void* next = nullptr) {
    VkPhysicalDevicePortabilitySubsetPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}
#endif // VK_ENABLE_BETA_EXTENSIONS

inline VkPhysicalDeviceShaderClockFeaturesKHR PhysicalDeviceShaderClockFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceShaderClockFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH265ProfileInfoKHR VideoDecodeH265ProfileInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH265ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH265CapabilitiesKHR VideoDecodeH265CapabilitiesKHR(void* next = nullptr) {
    VkVideoDecodeH265CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH265SessionParametersAddInfoKHR VideoDecodeH265SessionParametersAddInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH265SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH265SessionParametersCreateInfoKHR VideoDecodeH265SessionParametersCreateInfoKHR(
    const void* next = nullptr) {
    VkVideoDecodeH265SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH265PictureInfoKHR VideoDecodeH265PictureInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH265PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeH265DpbSlotInfoKHR VideoDecodeH265DpbSlotInfoKHR(const void* next = nullptr) {
    VkVideoDecodeH265DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkDeviceQueueGlobalPriorityCreateInfoKHR DeviceQueueGlobalPriorityCreateInfoKHR(const void* next = nullptr) {
    VkDeviceQueueGlobalPriorityCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR PhysicalDeviceGlobalPriorityQueryFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkQueueFamilyGlobalPriorityPropertiesKHR QueueFamilyGlobalPriorityPropertiesKHR(void* next = nullptr) {
    VkQueueFamilyGlobalPriorityPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_GLOBAL_PRIORITY_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkFragmentShadingRateAttachmentInfoKHR FragmentShadingRateAttachmentInfoKHR(const void* next = nullptr) {
    VkFragmentShadingRateAttachmentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineFragmentShadingRateStateCreateInfoKHR PipelineFragmentShadingRateStateCreateInfoKHR(
    const void* next = nullptr) {
    VkPipelineFragmentShadingRateStateCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateFeaturesKHR PhysicalDeviceFragmentShadingRateFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceFragmentShadingRateFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRatePropertiesKHR PhysicalDeviceFragmentShadingRatePropertiesKHR(void* next = nullptr) {
    VkPhysicalDeviceFragmentShadingRatePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateKHR PhysicalDeviceFragmentShadingRateKHR(void* next = nullptr) {
    VkPhysicalDeviceFragmentShadingRateKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDynamicRenderingLocalReadFeaturesKHR PhysicalDeviceDynamicRenderingLocalReadFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceDynamicRenderingLocalReadFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_LOCAL_READ_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkRenderingAttachmentLocationInfoKHR RenderingAttachmentLocationInfoKHR(const void* next = nullptr) {
    VkRenderingAttachmentLocationInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_LOCATION_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkRenderingInputAttachmentIndexInfoKHR RenderingInputAttachmentIndexInfoKHR(const void* next = nullptr) {
    VkRenderingInputAttachmentIndexInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INPUT_ATTACHMENT_INDEX_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderQuadControlFeaturesKHR PhysicalDeviceShaderQuadControlFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceShaderQuadControlFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_QUAD_CONTROL_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkSurfaceProtectedCapabilitiesKHR SurfaceProtectedCapabilitiesKHR(const void* next = nullptr) {
    VkSurfaceProtectedCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePresentWaitFeaturesKHR PhysicalDevicePresentWaitFeaturesKHR(void* next = nullptr) {
    VkPhysicalDevicePresentWaitFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR PhysicalDevicePipelineExecutablePropertiesFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineInfoKHR PipelineInfoKHR(const void* next = nullptr) {
    VkPipelineInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineExecutablePropertiesKHR PipelineExecutablePropertiesKHR(void* next = nullptr) {
    VkPipelineExecutablePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineExecutableInfoKHR PipelineExecutableInfoKHR(const void* next = nullptr) {
    VkPipelineExecutableInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineExecutableStatisticKHR PipelineExecutableStatisticKHR(void* next = nullptr) {
    VkPipelineExecutableStatisticKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineExecutableInternalRepresentationKHR PipelineExecutableInternalRepresentationKHR(void* next = nullptr) {
    VkPipelineExecutableInternalRepresentationKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR;
    info.pNext = next;
    return info;
}

inline VkMemoryMapInfoKHR MemoryMapInfoKHR(const void* next = nullptr) {
    VkMemoryMapInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_MAP_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkMemoryUnmapInfoKHR MemoryUnmapInfoKHR(const void* next = nullptr) {
    VkMemoryUnmapInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_UNMAP_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineLibraryCreateInfoKHR PipelineLibraryCreateInfoKHR(const void* next = nullptr) {
    VkPipelineLibraryCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPresentIdKHR PresentIdKHR(const void* next = nullptr) {
    VkPresentIdKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_ID_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePresentIdFeaturesKHR PhysicalDevicePresentIdFeaturesKHR(void* next = nullptr) {
    VkPhysicalDevicePresentIdFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeInfoKHR VideoEncodeInfoKHR(const void* next = nullptr) {
    VkVideoEncodeInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeCapabilitiesKHR VideoEncodeCapabilitiesKHR(void* next = nullptr) {
    VkVideoEncodeCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkQueryPoolVideoEncodeFeedbackCreateInfoKHR QueryPoolVideoEncodeFeedbackCreateInfoKHR(const void* next = nullptr) {
    VkQueryPoolVideoEncodeFeedbackCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeUsageInfoKHR VideoEncodeUsageInfoKHR(const void* next = nullptr) {
    VkVideoEncodeUsageInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_USAGE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeRateControlLayerInfoKHR VideoEncodeRateControlLayerInfoKHR(const void* next = nullptr) {
    VkVideoEncodeRateControlLayerInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_LAYER_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeRateControlInfoKHR VideoEncodeRateControlInfoKHR(const void* next = nullptr) {
    VkVideoEncodeRateControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR PhysicalDeviceVideoEncodeQualityLevelInfoKHR(const void* next = nullptr) {
    VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_QUALITY_LEVEL_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeQualityLevelPropertiesKHR VideoEncodeQualityLevelPropertiesKHR(void* next = nullptr) {
    VkVideoEncodeQualityLevelPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUALITY_LEVEL_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeQualityLevelInfoKHR VideoEncodeQualityLevelInfoKHR(const void* next = nullptr) {
    VkVideoEncodeQualityLevelInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUALITY_LEVEL_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeSessionParametersGetInfoKHR VideoEncodeSessionParametersGetInfoKHR(const void* next = nullptr) {
    VkVideoEncodeSessionParametersGetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_PARAMETERS_GET_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoEncodeSessionParametersFeedbackInfoKHR VideoEncodeSessionParametersFeedbackInfoKHR(void* next = nullptr) {
    VkVideoEncodeSessionParametersFeedbackInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_PARAMETERS_FEEDBACK_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkQueueFamilyCheckpointProperties2NV QueueFamilyCheckpointProperties2NV(void* next = nullptr) {
    VkQueueFamilyCheckpointProperties2NV info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV;
    info.pNext = next;
    return info;
}

inline VkCheckpointData2NV CheckpointData2NV(void* next = nullptr) {
    VkCheckpointData2NV info{};
    info.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR PhysicalDeviceFragmentShaderBarycentricFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR PhysicalDeviceFragmentShaderBarycentricPropertiesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR PhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR PhysicalDeviceRayTracingMaintenance1FeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR PhysicalDeviceShaderSubgroupRotateFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_ROTATE_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR PhysicalDeviceShaderMaximalReconvergenceFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance5FeaturesKHR PhysicalDeviceMaintenance5FeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceMaintenance5FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance5PropertiesKHR PhysicalDeviceMaintenance5PropertiesKHR(void* next = nullptr) {
    VkPhysicalDeviceMaintenance5PropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkRenderingAreaInfoKHR RenderingAreaInfoKHR(const void* next = nullptr) {
    VkRenderingAreaInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_AREA_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkImageSubresource2KHR ImageSubresource2KHR(void* next = nullptr) {
    VkImageSubresource2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_SUBRESOURCE_2_KHR;
    info.pNext = next;
    return info;
}

inline VkDeviceImageSubresourceInfoKHR DeviceImageSubresourceInfoKHR(const void* next = nullptr) {
    VkDeviceImageSubresourceInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_SUBRESOURCE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkSubresourceLayout2KHR SubresourceLayout2KHR(void* next = nullptr) {
    VkSubresourceLayout2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_LAYOUT_2_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineCreateFlags2CreateInfoKHR PipelineCreateFlags2CreateInfoKHR(const void* next = nullptr) {
    VkPipelineCreateFlags2CreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkBufferUsageFlags2CreateInfoKHR BufferUsageFlags2CreateInfoKHR(const void* next = nullptr) {
    VkBufferUsageFlags2CreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_USAGE_FLAGS_2_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR PhysicalDeviceRayTracingPositionFetchFeaturesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_POSITION_FETCH_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkCooperativeMatrixPropertiesKHR CooperativeMatrixPropertiesKHR(void* next = nullptr) {
    VkCooperativeMatrixPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixFeaturesKHR PhysicalDeviceCooperativeMatrixFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixPropertiesKHR PhysicalDeviceCooperativeMatrixPropertiesKHR(void* next = nullptr) {
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeAV1ProfileInfoKHR VideoDecodeAV1ProfileInfoKHR(const void* next = nullptr) {
    VkVideoDecodeAV1ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PROFILE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeAV1CapabilitiesKHR VideoDecodeAV1CapabilitiesKHR(void* next = nullptr) {
    VkVideoDecodeAV1CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_CAPABILITIES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeAV1SessionParametersCreateInfoKHR VideoDecodeAV1SessionParametersCreateInfoKHR(const void* next = nullptr) {
    VkVideoDecodeAV1SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_SESSION_PARAMETERS_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeAV1PictureInfoKHR VideoDecodeAV1PictureInfoKHR(const void* next = nullptr) {
    VkVideoDecodeAV1PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PICTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoDecodeAV1DpbSlotInfoKHR VideoDecodeAV1DpbSlotInfoKHR(const void* next = nullptr) {
    VkVideoDecodeAV1DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_DPB_SLOT_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVideoMaintenance1FeaturesKHR PhysicalDeviceVideoMaintenance1FeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceVideoMaintenance1FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkVideoInlineQueryInfoKHR VideoInlineQueryInfoKHR(const void* next = nullptr) {
    VkVideoInlineQueryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_INLINE_QUERY_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR PhysicalDeviceVertexAttributeDivisorPropertiesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineVertexInputDivisorStateCreateInfoKHR PipelineVertexInputDivisorStateCreateInfoKHR(const void* next = nullptr) {
    VkPipelineVertexInputDivisorStateCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR PhysicalDeviceVertexAttributeDivisorFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderFloatControls2FeaturesKHR PhysicalDeviceShaderFloatControls2FeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceShaderFloatControls2FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT_CONTROLS_2_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceIndexTypeUint8FeaturesKHR PhysicalDeviceIndexTypeUint8FeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceIndexTypeUint8FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceLineRasterizationFeaturesKHR PhysicalDeviceLineRasterizationFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceLineRasterizationFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceLineRasterizationPropertiesKHR PhysicalDeviceLineRasterizationPropertiesKHR(void* next = nullptr) {
    VkPhysicalDeviceLineRasterizationPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationLineStateCreateInfoKHR PipelineRasterizationLineStateCreateInfoKHR(const void* next = nullptr) {
    VkPipelineRasterizationLineStateCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkCalibratedTimestampInfoKHR CalibratedTimestampInfoKHR(const void* next = nullptr) {
    VkCalibratedTimestampInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderExpectAssumeFeaturesKHR PhysicalDeviceShaderExpectAssumeFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance6FeaturesKHR PhysicalDeviceMaintenance6FeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceMaintenance6FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_6_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMaintenance6PropertiesKHR PhysicalDeviceMaintenance6PropertiesKHR(void* next = nullptr) {
    VkPhysicalDeviceMaintenance6PropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_6_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkBindMemoryStatusKHR BindMemoryStatusKHR(const void* next = nullptr) {
    VkBindMemoryStatusKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_MEMORY_STATUS_KHR;
    info.pNext = next;
    return info;
}

inline VkBindDescriptorSetsInfoKHR BindDescriptorSetsInfoKHR(const void* next = nullptr) {
    VkBindDescriptorSetsInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_DESCRIPTOR_SETS_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPushConstantsInfoKHR PushConstantsInfoKHR(const void* next = nullptr) {
    VkPushConstantsInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PUSH_CONSTANTS_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPushDescriptorSetInfoKHR PushDescriptorSetInfoKHR(const void* next = nullptr) {
    VkPushDescriptorSetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PUSH_DESCRIPTOR_SET_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPushDescriptorSetWithTemplateInfoKHR PushDescriptorSetWithTemplateInfoKHR(const void* next = nullptr) {
    VkPushDescriptorSetWithTemplateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PUSH_DESCRIPTOR_SET_WITH_TEMPLATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkSetDescriptorBufferOffsetsInfoEXT SetDescriptorBufferOffsetsInfoEXT(const void* next = nullptr) {
    VkSetDescriptorBufferOffsetsInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SET_DESCRIPTOR_BUFFER_OFFSETS_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkBindDescriptorBufferEmbeddedSamplersInfoEXT BindDescriptorBufferEmbeddedSamplersInfoEXT(const void* next = nullptr) {
    VkBindDescriptorBufferEmbeddedSamplersInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_DESCRIPTOR_BUFFER_EMBEDDED_SAMPLERS_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCreateInfoEXT(const void* next = nullptr) {
    VkDebugReportCallbackCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationStateRasterizationOrderAMD PipelineRasterizationStateRasterizationOrderAMD(
    const void* next = nullptr) {
    VkPipelineRasterizationStateRasterizationOrderAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD;
    info.pNext = next;
    return info;
}

inline VkDebugMarkerObjectNameInfoEXT DebugMarkerObjectNameInfoEXT(const void* next = nullptr) {
    VkDebugMarkerObjectNameInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugMarkerObjectTagInfoEXT DebugMarkerObjectTagInfoEXT(const void* next = nullptr) {
    VkDebugMarkerObjectTagInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugMarkerMarkerInfoEXT DebugMarkerMarkerInfoEXT(const void* next = nullptr) {
    VkDebugMarkerMarkerInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDedicatedAllocationImageCreateInfoNV DedicatedAllocationImageCreateInfoNV(const void* next = nullptr) {
    VkDedicatedAllocationImageCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkDedicatedAllocationBufferCreateInfoNV DedicatedAllocationBufferCreateInfoNV(const void* next = nullptr) {
    VkDedicatedAllocationBufferCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkDedicatedAllocationMemoryAllocateInfoNV DedicatedAllocationMemoryAllocateInfoNV(const void* next = nullptr) {
    VkDedicatedAllocationMemoryAllocateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTransformFeedbackFeaturesEXT PhysicalDeviceTransformFeedbackFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceTransformFeedbackFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTransformFeedbackPropertiesEXT PhysicalDeviceTransformFeedbackPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceTransformFeedbackPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationStateStreamCreateInfoEXT PipelineRasterizationStateStreamCreateInfoEXT(
    const void* next = nullptr) {
    VkPipelineRasterizationStateStreamCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkCuModuleCreateInfoNVX CuModuleCreateInfoNVX(const void* next = nullptr) {
    VkCuModuleCreateInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_CU_MODULE_CREATE_INFO_NVX;
    info.pNext = next;
    return info;
}

inline VkCuFunctionCreateInfoNVX CuFunctionCreateInfoNVX(const void* next = nullptr) {
    VkCuFunctionCreateInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_CU_FUNCTION_CREATE_INFO_NVX;
    info.pNext = next;
    return info;
}

inline VkCuLaunchInfoNVX CuLaunchInfoNVX(const void* next = nullptr) {
    VkCuLaunchInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_CU_LAUNCH_INFO_NVX;
    info.pNext = next;
    return info;
}

inline VkImageViewHandleInfoNVX ImageViewHandleInfoNVX(const void* next = nullptr) {
    VkImageViewHandleInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX;
    info.pNext = next;
    return info;
}

inline VkImageViewAddressPropertiesNVX ImageViewAddressPropertiesNVX(void* next = nullptr) {
    VkImageViewAddressPropertiesNVX info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX;
    info.pNext = next;
    return info;
}

inline VkTextureLODGatherFormatPropertiesAMD TextureLODGatherFormatPropertiesAMD(void* next = nullptr) {
    VkTextureLODGatherFormatPropertiesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_GGP
inline VkStreamDescriptorSurfaceCreateInfoGGP StreamDescriptorSurfaceCreateInfoGGP(const void* next = nullptr) {
    VkStreamDescriptorSurfaceCreateInfoGGP info{};
    info.sType = VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_GGP

inline VkPhysicalDeviceCornerSampledImageFeaturesNV PhysicalDeviceCornerSampledImageFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceCornerSampledImageFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkExternalMemoryImageCreateInfoNV ExternalMemoryImageCreateInfoNV(const void* next = nullptr) {
    VkExternalMemoryImageCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkExportMemoryAllocateInfoNV ExportMemoryAllocateInfoNV(const void* next = nullptr) {
    VkExportMemoryAllocateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkImportMemoryWin32HandleInfoNV ImportMemoryWin32HandleInfoNV(const void* next = nullptr) {
    VkImportMemoryWin32HandleInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkExportMemoryWin32HandleInfoNV ExportMemoryWin32HandleInfoNV(const void* next = nullptr) {
    VkExportMemoryWin32HandleInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkWin32KeyedMutexAcquireReleaseInfoNV Win32KeyedMutexAcquireReleaseInfoNV(const void* next = nullptr) {
    VkWin32KeyedMutexAcquireReleaseInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkValidationFlagsEXT ValidationFlagsEXT(const void* next = nullptr) {
    VkValidationFlagsEXT info{};
    info.sType = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_VI_NN
inline VkViSurfaceCreateInfoNN ViSurfaceCreateInfoNN(const void* next = nullptr) {
    VkViSurfaceCreateInfoNN info{};
    info.sType = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_VI_NN

inline VkImageViewASTCDecodeModeEXT ImageViewASTCDecodeModeEXT(const void* next = nullptr) {
    VkImageViewASTCDecodeModeEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceASTCDecodeFeaturesEXT PhysicalDeviceASTCDecodeFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceASTCDecodeFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelineRobustnessFeaturesEXT PhysicalDevicePipelineRobustnessFeaturesEXT(void* next = nullptr) {
    VkPhysicalDevicePipelineRobustnessFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelineRobustnessPropertiesEXT PhysicalDevicePipelineRobustnessPropertiesEXT(void* next = nullptr) {
    VkPhysicalDevicePipelineRobustnessPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineRobustnessCreateInfoEXT PipelineRobustnessCreateInfoEXT(const void* next = nullptr) {
    VkPipelineRobustnessCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkConditionalRenderingBeginInfoEXT ConditionalRenderingBeginInfoEXT(const void* next = nullptr) {
    VkConditionalRenderingBeginInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceConditionalRenderingFeaturesEXT PhysicalDeviceConditionalRenderingFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceConditionalRenderingFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkCommandBufferInheritanceConditionalRenderingInfoEXT CommandBufferInheritanceConditionalRenderingInfoEXT(
    const void* next = nullptr) {
    VkCommandBufferInheritanceConditionalRenderingInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportWScalingStateCreateInfoNV PipelineViewportWScalingStateCreateInfoNV(const void* next = nullptr) {
    VkPipelineViewportWScalingStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkSurfaceCapabilities2EXT SurfaceCapabilities2EXT(void* next = nullptr) {
    VkSurfaceCapabilities2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT;
    info.pNext = next;
    return info;
}

inline VkDisplayPowerInfoEXT DisplayPowerInfoEXT(const void* next = nullptr) {
    VkDisplayPowerInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDeviceEventInfoEXT DeviceEventInfoEXT(const void* next = nullptr) {
    VkDeviceEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDisplayEventInfoEXT DisplayEventInfoEXT(const void* next = nullptr) {
    VkDisplayEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSwapchainCounterCreateInfoEXT SwapchainCounterCreateInfoEXT(const void* next = nullptr) {
    VkSwapchainCounterCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPresentTimesInfoGOOGLE PresentTimesInfoGOOGLE(const void* next = nullptr) {
    VkPresentTimesInfoGOOGLE info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX(
    void* next = nullptr) {
    VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportSwizzleStateCreateInfoNV PipelineViewportSwizzleStateCreateInfoNV(const void* next = nullptr) {
    VkPipelineViewportSwizzleStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDiscardRectanglePropertiesEXT PhysicalDeviceDiscardRectanglePropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceDiscardRectanglePropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineDiscardRectangleStateCreateInfoEXT PipelineDiscardRectangleStateCreateInfoEXT(const void* next = nullptr) {
    VkPipelineDiscardRectangleStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceConservativeRasterizationPropertiesEXT PhysicalDeviceConservativeRasterizationPropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceConservativeRasterizationPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationConservativeStateCreateInfoEXT PipelineRasterizationConservativeStateCreateInfoEXT(
    const void* next = nullptr) {
    VkPipelineRasterizationConservativeStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDepthClipEnableFeaturesEXT PhysicalDeviceDepthClipEnableFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceDepthClipEnableFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationDepthClipStateCreateInfoEXT PipelineRasterizationDepthClipStateCreateInfoEXT(
    const void* next = nullptr) {
    VkPipelineRasterizationDepthClipStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkHdrMetadataEXT HdrMetadataEXT(const void* next = nullptr) {
    VkHdrMetadataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG PhysicalDeviceRelaxedLineRasterizationFeaturesIMG(
    void* next = nullptr) {
    VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RELAXED_LINE_RASTERIZATION_FEATURES_IMG;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_IOS_MVK
inline VkIOSSurfaceCreateInfoMVK IOSSurfaceCreateInfoMVK(const void* next = nullptr) {
    VkIOSSurfaceCreateInfoMVK info{};
    info.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_IOS_MVK

#ifdef VK_USE_PLATFORM_MACOS_MVK
inline VkMacOSSurfaceCreateInfoMVK MacOSSurfaceCreateInfoMVK(const void* next = nullptr) {
    VkMacOSSurfaceCreateInfoMVK info{};
    info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_MACOS_MVK

inline VkDebugUtilsLabelEXT DebugUtilsLabelEXT(const void* next = nullptr) {
    VkDebugUtilsLabelEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugUtilsObjectNameInfoEXT DebugUtilsObjectNameInfoEXT(const void* next = nullptr) {
    VkDebugUtilsObjectNameInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugUtilsMessengerCallbackDataEXT DebugUtilsMessengerCallbackDataEXT(const void* next = nullptr) {
    VkDebugUtilsMessengerCallbackDataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugUtilsMessengerCreateInfoEXT DebugUtilsMessengerCreateInfoEXT(const void* next = nullptr) {
    VkDebugUtilsMessengerCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDebugUtilsObjectTagInfoEXT DebugUtilsObjectTagInfoEXT(const void* next = nullptr) {
    VkDebugUtilsObjectTagInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_ANDROID_KHR
inline VkAndroidHardwareBufferUsageANDROID AndroidHardwareBufferUsageANDROID(void* next = nullptr) {
    VkAndroidHardwareBufferUsageANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID;
    info.pNext = next;
    return info;
}

inline VkAndroidHardwareBufferPropertiesANDROID AndroidHardwareBufferPropertiesANDROID(void* next = nullptr) {
    VkAndroidHardwareBufferPropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID;
    info.pNext = next;
    return info;
}

inline VkAndroidHardwareBufferFormatPropertiesANDROID AndroidHardwareBufferFormatPropertiesANDROID(void* next = nullptr) {
    VkAndroidHardwareBufferFormatPropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID;
    info.pNext = next;
    return info;
}

inline VkImportAndroidHardwareBufferInfoANDROID ImportAndroidHardwareBufferInfoANDROID(const void* next = nullptr) {
    VkImportAndroidHardwareBufferInfoANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
    info.pNext = next;
    return info;
}

inline VkMemoryGetAndroidHardwareBufferInfoANDROID MemoryGetAndroidHardwareBufferInfoANDROID(const void* next = nullptr) {
    VkMemoryGetAndroidHardwareBufferInfoANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
    info.pNext = next;
    return info;
}

inline VkExternalFormatANDROID ExternalFormatANDROID(void* next = nullptr) {
    VkExternalFormatANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID;
    info.pNext = next;
    return info;
}

inline VkAndroidHardwareBufferFormatProperties2ANDROID AndroidHardwareBufferFormatProperties2ANDROID(void* next = nullptr) {
    VkAndroidHardwareBufferFormatProperties2ANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_ANDROID_KHR

#ifdef VK_ENABLE_BETA_EXTENSIONS
inline VkPhysicalDeviceShaderEnqueueFeaturesAMDX PhysicalDeviceShaderEnqueueFeaturesAMDX(void* next = nullptr) {
    VkPhysicalDeviceShaderEnqueueFeaturesAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ENQUEUE_FEATURES_AMDX;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderEnqueuePropertiesAMDX PhysicalDeviceShaderEnqueuePropertiesAMDX(void* next = nullptr) {
    VkPhysicalDeviceShaderEnqueuePropertiesAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ENQUEUE_PROPERTIES_AMDX;
    info.pNext = next;
    return info;
}

inline VkExecutionGraphPipelineScratchSizeAMDX ExecutionGraphPipelineScratchSizeAMDX(void* next = nullptr) {
    VkExecutionGraphPipelineScratchSizeAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_EXECUTION_GRAPH_PIPELINE_SCRATCH_SIZE_AMDX;
    info.pNext = next;
    return info;
}

inline VkExecutionGraphPipelineCreateInfoAMDX ExecutionGraphPipelineCreateInfoAMDX(const void* next = nullptr) {
    VkExecutionGraphPipelineCreateInfoAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_EXECUTION_GRAPH_PIPELINE_CREATE_INFO_AMDX;
    info.pNext = next;
    return info;
}

inline VkPipelineShaderStageNodeCreateInfoAMDX PipelineShaderStageNodeCreateInfoAMDX(const void* next = nullptr) {
    VkPipelineShaderStageNodeCreateInfoAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_NODE_CREATE_INFO_AMDX;
    info.pNext = next;
    return info;
}
#endif // VK_ENABLE_BETA_EXTENSIONS

inline VkSampleLocationsInfoEXT SampleLocationsInfoEXT(const void* next = nullptr) {
    VkSampleLocationsInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkRenderPassSampleLocationsBeginInfoEXT RenderPassSampleLocationsBeginInfoEXT(const void* next = nullptr) {
    VkRenderPassSampleLocationsBeginInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineSampleLocationsStateCreateInfoEXT PipelineSampleLocationsStateCreateInfoEXT(const void* next = nullptr) {
    VkPipelineSampleLocationsStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSampleLocationsPropertiesEXT PhysicalDeviceSampleLocationsPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceSampleLocationsPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkMultisamplePropertiesEXT MultisamplePropertiesEXT(void* next = nullptr) {
    VkMultisamplePropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT PhysicalDeviceBlendOperationAdvancedFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT PhysicalDeviceBlendOperationAdvancedPropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineColorBlendAdvancedStateCreateInfoEXT PipelineColorBlendAdvancedStateCreateInfoEXT(const void* next = nullptr) {
    VkPipelineColorBlendAdvancedStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineCoverageToColorStateCreateInfoNV PipelineCoverageToColorStateCreateInfoNV(const void* next = nullptr) {
    VkPipelineCoverageToColorStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineCoverageModulationStateCreateInfoNV PipelineCoverageModulationStateCreateInfoNV(const void* next = nullptr) {
    VkPipelineCoverageModulationStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderSMBuiltinsPropertiesNV PhysicalDeviceShaderSMBuiltinsPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceShaderSMBuiltinsPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderSMBuiltinsFeaturesNV PhysicalDeviceShaderSMBuiltinsFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceShaderSMBuiltinsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkDrmFormatModifierPropertiesListEXT DrmFormatModifierPropertiesListEXT(void* next = nullptr) {
    VkDrmFormatModifierPropertiesListEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageDrmFormatModifierInfoEXT PhysicalDeviceImageDrmFormatModifierInfoEXT(const void* next = nullptr) {
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImageDrmFormatModifierListCreateInfoEXT ImageDrmFormatModifierListCreateInfoEXT(const void* next = nullptr) {
    VkImageDrmFormatModifierListCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImageDrmFormatModifierExplicitCreateInfoEXT ImageDrmFormatModifierExplicitCreateInfoEXT(const void* next = nullptr) {
    VkImageDrmFormatModifierExplicitCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImageDrmFormatModifierPropertiesEXT ImageDrmFormatModifierPropertiesEXT(void* next = nullptr) {
    VkImageDrmFormatModifierPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkDrmFormatModifierPropertiesList2EXT DrmFormatModifierPropertiesList2EXT(void* next = nullptr) {
    VkDrmFormatModifierPropertiesList2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_2_EXT;
    info.pNext = next;
    return info;
}

inline VkValidationCacheCreateInfoEXT ValidationCacheCreateInfoEXT(const void* next = nullptr) {
    VkValidationCacheCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkShaderModuleValidationCacheCreateInfoEXT ShaderModuleValidationCacheCreateInfoEXT(const void* next = nullptr) {
    VkShaderModuleValidationCacheCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportShadingRateImageStateCreateInfoNV PipelineViewportShadingRateImageStateCreateInfoNV(
    const void* next = nullptr) {
    VkPipelineViewportShadingRateImageStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShadingRateImageFeaturesNV PhysicalDeviceShadingRateImageFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceShadingRateImageFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShadingRateImagePropertiesNV PhysicalDeviceShadingRateImagePropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceShadingRateImagePropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportCoarseSampleOrderStateCreateInfoNV PipelineViewportCoarseSampleOrderStateCreateInfoNV(
    const void* next = nullptr) {
    VkPipelineViewportCoarseSampleOrderStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkRayTracingShaderGroupCreateInfoNV RayTracingShaderGroupCreateInfoNV(const void* next = nullptr) {
    VkRayTracingShaderGroupCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkRayTracingPipelineCreateInfoNV RayTracingPipelineCreateInfoNV(const void* next = nullptr) {
    VkRayTracingPipelineCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkGeometryTrianglesNV GeometryTrianglesNV(const void* next = nullptr) {
    VkGeometryTrianglesNV info{};
    info.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
    info.pNext = next;
    return info;
}

inline VkGeometryAABBNV GeometryAABBNV(const void* next = nullptr) {
    VkGeometryAABBNV info{};
    info.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
    info.pNext = next;
    return info;
}

inline VkGeometryNV GeometryNV(const void* next = nullptr) {
    VkGeometryNV info{};
    info.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureInfoNV AccelerationStructureInfoNV(const void* next = nullptr) {
    VkAccelerationStructureInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureCreateInfoNV AccelerationStructureCreateInfoNV(const void* next = nullptr) {
    VkAccelerationStructureCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkBindAccelerationStructureMemoryInfoNV BindAccelerationStructureMemoryInfoNV(const void* next = nullptr) {
    VkBindAccelerationStructureMemoryInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkWriteDescriptorSetAccelerationStructureNV WriteDescriptorSetAccelerationStructureNV(const void* next = nullptr) {
    VkWriteDescriptorSetAccelerationStructureNV info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureMemoryRequirementsInfoNV AccelerationStructureMemoryRequirementsInfoNV(
    const void* next = nullptr) {
    VkAccelerationStructureMemoryRequirementsInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingPropertiesNV PhysicalDeviceRayTracingPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceRayTracingPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV PhysicalDeviceRepresentativeFragmentTestFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineRepresentativeFragmentTestStateCreateInfoNV PipelineRepresentativeFragmentTestStateCreateInfoNV(
    const void* next = nullptr) {
    VkPipelineRepresentativeFragmentTestStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageViewImageFormatInfoEXT PhysicalDeviceImageViewImageFormatInfoEXT(void* next = nullptr) {
    VkPhysicalDeviceImageViewImageFormatInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkFilterCubicImageViewImageFormatPropertiesEXT FilterCubicImageViewImageFormatPropertiesEXT(void* next = nullptr) {
    VkFilterCubicImageViewImageFormatPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkImportMemoryHostPointerInfoEXT ImportMemoryHostPointerInfoEXT(const void* next = nullptr) {
    VkImportMemoryHostPointerInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkMemoryHostPointerPropertiesEXT MemoryHostPointerPropertiesEXT(void* next = nullptr) {
    VkMemoryHostPointerPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalMemoryHostPropertiesEXT PhysicalDeviceExternalMemoryHostPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineCompilerControlCreateInfoAMD PipelineCompilerControlCreateInfoAMD(const void* next = nullptr) {
    VkPipelineCompilerControlCreateInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderCorePropertiesAMD PhysicalDeviceShaderCorePropertiesAMD(void* next = nullptr) {
    VkPhysicalDeviceShaderCorePropertiesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
    info.pNext = next;
    return info;
}

inline VkDeviceMemoryOverallocationCreateInfoAMD DeviceMemoryOverallocationCreateInfoAMD(const void* next = nullptr) {
    VkDeviceMemoryOverallocationCreateInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT PhysicalDeviceVertexAttributeDivisorPropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_GGP
inline VkPresentFrameTokenGGP PresentFrameTokenGGP(const void* next = nullptr) {
    VkPresentFrameTokenGGP info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_GGP

inline VkPhysicalDeviceComputeShaderDerivativesFeaturesNV PhysicalDeviceComputeShaderDerivativesFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceComputeShaderDerivativesFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMeshShaderFeaturesNV PhysicalDeviceMeshShaderFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceMeshShaderFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMeshShaderPropertiesNV PhysicalDeviceMeshShaderPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceMeshShaderPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderImageFootprintFeaturesNV PhysicalDeviceShaderImageFootprintFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceShaderImageFootprintFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportExclusiveScissorStateCreateInfoNV PipelineViewportExclusiveScissorStateCreateInfoNV(
    const void* next = nullptr) {
    VkPipelineViewportExclusiveScissorStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExclusiveScissorFeaturesNV PhysicalDeviceExclusiveScissorFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceExclusiveScissorFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkQueueFamilyCheckpointPropertiesNV QueueFamilyCheckpointPropertiesNV(void* next = nullptr) {
    VkQueueFamilyCheckpointPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkCheckpointDataNV CheckpointDataNV(void* next = nullptr) {
    VkCheckpointDataNV info{};
    info.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL(
    void* next = nullptr) {
    VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL;
    info.pNext = next;
    return info;
}

inline VkInitializePerformanceApiInfoINTEL InitializePerformanceApiInfoINTEL(const void* next = nullptr) {
    VkInitializePerformanceApiInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL;
    info.pNext = next;
    return info;
}

inline VkQueryPoolPerformanceQueryCreateInfoINTEL QueryPoolPerformanceQueryCreateInfoINTEL(const void* next = nullptr) {
    VkQueryPoolPerformanceQueryCreateInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL;
    info.pNext = next;
    return info;
}

inline VkPerformanceMarkerInfoINTEL PerformanceMarkerInfoINTEL(const void* next = nullptr) {
    VkPerformanceMarkerInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL;
    info.pNext = next;
    return info;
}

inline VkPerformanceStreamMarkerInfoINTEL PerformanceStreamMarkerInfoINTEL(const void* next = nullptr) {
    VkPerformanceStreamMarkerInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL;
    info.pNext = next;
    return info;
}

inline VkPerformanceOverrideInfoINTEL PerformanceOverrideInfoINTEL(const void* next = nullptr) {
    VkPerformanceOverrideInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL;
    info.pNext = next;
    return info;
}

inline VkPerformanceConfigurationAcquireInfoINTEL PerformanceConfigurationAcquireInfoINTEL(const void* next = nullptr) {
    VkPerformanceConfigurationAcquireInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePCIBusInfoPropertiesEXT PhysicalDevicePCIBusInfoPropertiesEXT(void* next = nullptr) {
    VkPhysicalDevicePCIBusInfoPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkDisplayNativeHdrSurfaceCapabilitiesAMD DisplayNativeHdrSurfaceCapabilitiesAMD(void* next = nullptr) {
    VkDisplayNativeHdrSurfaceCapabilitiesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD;
    info.pNext = next;
    return info;
}

inline VkSwapchainDisplayNativeHdrCreateInfoAMD SwapchainDisplayNativeHdrCreateInfoAMD(const void* next = nullptr) {
    VkSwapchainDisplayNativeHdrCreateInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_FUCHSIA
inline VkImagePipeSurfaceCreateInfoFUCHSIA ImagePipeSurfaceCreateInfoFUCHSIA(const void* next = nullptr) {
    VkImagePipeSurfaceCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_FUCHSIA

#ifdef VK_USE_PLATFORM_METAL_EXT
inline VkMetalSurfaceCreateInfoEXT MetalSurfaceCreateInfoEXT(const void* next = nullptr) {
    VkMetalSurfaceCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_METAL_EXT

inline VkPhysicalDeviceFragmentDensityMapFeaturesEXT PhysicalDeviceFragmentDensityMapFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceFragmentDensityMapFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMapPropertiesEXT PhysicalDeviceFragmentDensityMapPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceFragmentDensityMapPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkRenderPassFragmentDensityMapCreateInfoEXT RenderPassFragmentDensityMapCreateInfoEXT(const void* next = nullptr) {
    VkRenderPassFragmentDensityMapCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderCoreProperties2AMD PhysicalDeviceShaderCoreProperties2AMD(void* next = nullptr) {
    VkPhysicalDeviceShaderCoreProperties2AMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCoherentMemoryFeaturesAMD PhysicalDeviceCoherentMemoryFeaturesAMD(void* next = nullptr) {
    VkPhysicalDeviceCoherentMemoryFeaturesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT PhysicalDeviceShaderImageAtomicInt64FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMemoryBudgetPropertiesEXT PhysicalDeviceMemoryBudgetPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceMemoryBudgetPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMemoryPriorityFeaturesEXT PhysicalDeviceMemoryPriorityFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceMemoryPriorityFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkMemoryPriorityAllocateInfoEXT MemoryPriorityAllocateInfoEXT(const void* next = nullptr) {
    VkMemoryPriorityAllocateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceBufferDeviceAddressFeaturesEXT PhysicalDeviceBufferDeviceAddressFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceBufferDeviceAddressFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkBufferDeviceAddressCreateInfoEXT BufferDeviceAddressCreateInfoEXT(const void* next = nullptr) {
    VkBufferDeviceAddressCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkValidationFeaturesEXT ValidationFeaturesEXT(const void* next = nullptr) {
    VkValidationFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkCooperativeMatrixPropertiesNV CooperativeMatrixPropertiesNV(void* next = nullptr) {
    VkCooperativeMatrixPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixFeaturesNV PhysicalDeviceCooperativeMatrixFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceCooperativeMatrixFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixPropertiesNV PhysicalDeviceCooperativeMatrixPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceCooperativeMatrixPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCoverageReductionModeFeaturesNV PhysicalDeviceCoverageReductionModeFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceCoverageReductionModeFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineCoverageReductionStateCreateInfoNV PipelineCoverageReductionStateCreateInfoNV(const void* next = nullptr) {
    VkPipelineCoverageReductionStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkFramebufferMixedSamplesCombinationNV FramebufferMixedSamplesCombinationNV(void* next = nullptr) {
    VkFramebufferMixedSamplesCombinationNV info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT PhysicalDeviceFragmentShaderInterlockFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceYcbcrImageArraysFeaturesEXT PhysicalDeviceYcbcrImageArraysFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceYcbcrImageArraysFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceProvokingVertexFeaturesEXT PhysicalDeviceProvokingVertexFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceProvokingVertexFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceProvokingVertexPropertiesEXT PhysicalDeviceProvokingVertexPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceProvokingVertexPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineRasterizationProvokingVertexStateCreateInfoEXT PipelineRasterizationProvokingVertexStateCreateInfoEXT(
    const void* next = nullptr) {
    VkPipelineRasterizationProvokingVertexStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkSurfaceFullScreenExclusiveInfoEXT SurfaceFullScreenExclusiveInfoEXT(void* next = nullptr) {
    VkSurfaceFullScreenExclusiveInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSurfaceCapabilitiesFullScreenExclusiveEXT SurfaceCapabilitiesFullScreenExclusiveEXT(void* next = nullptr) {
    VkSurfaceCapabilitiesFullScreenExclusiveEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT;
    info.pNext = next;
    return info;
}

inline VkSurfaceFullScreenExclusiveWin32InfoEXT SurfaceFullScreenExclusiveWin32InfoEXT(const void* next = nullptr) {
    VkSurfaceFullScreenExclusiveWin32InfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkHeadlessSurfaceCreateInfoEXT HeadlessSurfaceCreateInfoEXT(const void* next = nullptr) {
    VkHeadlessSurfaceCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderAtomicFloatFeaturesEXT PhysicalDeviceShaderAtomicFloatFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicStateFeaturesEXT PhysicalDeviceExtendedDynamicStateFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceExtendedDynamicStateFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceHostImageCopyFeaturesEXT PhysicalDeviceHostImageCopyFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceHostImageCopyFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceHostImageCopyPropertiesEXT PhysicalDeviceHostImageCopyPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceHostImageCopyPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkMemoryToImageCopyEXT MemoryToImageCopyEXT(const void* next = nullptr) {
    VkMemoryToImageCopyEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT;
    info.pNext = next;
    return info;
}

inline VkImageToMemoryCopyEXT ImageToMemoryCopyEXT(const void* next = nullptr) {
    VkImageToMemoryCopyEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyMemoryToImageInfoEXT CopyMemoryToImageInfoEXT(const void* next = nullptr) {
    VkCopyMemoryToImageInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyImageToMemoryInfoEXT CopyImageToMemoryInfoEXT(const void* next = nullptr) {
    VkCopyImageToMemoryInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyImageToImageInfoEXT CopyImageToImageInfoEXT(const void* next = nullptr) {
    VkCopyImageToImageInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_IMAGE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkHostImageLayoutTransitionInfoEXT HostImageLayoutTransitionInfoEXT(const void* next = nullptr) {
    VkHostImageLayoutTransitionInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSubresourceHostMemcpySizeEXT SubresourceHostMemcpySizeEXT(void* next = nullptr) {
    VkSubresourceHostMemcpySizeEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_HOST_MEMCPY_SIZE_EXT;
    info.pNext = next;
    return info;
}

inline VkHostImageCopyDevicePerformanceQueryEXT HostImageCopyDevicePerformanceQueryEXT(void* next = nullptr) {
    VkHostImageCopyDevicePerformanceQueryEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMapMemoryPlacedFeaturesEXT PhysicalDeviceMapMemoryPlacedFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceMapMemoryPlacedFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAP_MEMORY_PLACED_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMapMemoryPlacedPropertiesEXT PhysicalDeviceMapMemoryPlacedPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceMapMemoryPlacedPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAP_MEMORY_PLACED_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkMemoryMapPlacedInfoEXT MemoryMapPlacedInfoEXT(const void* next = nullptr) {
    VkMemoryMapPlacedInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_MAP_PLACED_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT PhysicalDeviceShaderAtomicFloat2FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkSurfacePresentModeEXT SurfacePresentModeEXT(void* next = nullptr) {
    VkSurfacePresentModeEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_EXT;
    info.pNext = next;
    return info;
}

inline VkSurfacePresentScalingCapabilitiesEXT SurfacePresentScalingCapabilitiesEXT(void* next = nullptr) {
    VkSurfacePresentScalingCapabilitiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_EXT;
    info.pNext = next;
    return info;
}

inline VkSurfacePresentModeCompatibilityEXT SurfacePresentModeCompatibilityEXT(void* next = nullptr) {
    VkSurfacePresentModeCompatibilityEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_COMPATIBILITY_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT PhysicalDeviceSwapchainMaintenance1FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SWAPCHAIN_MAINTENANCE_1_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkSwapchainPresentFenceInfoEXT SwapchainPresentFenceInfoEXT(const void* next = nullptr) {
    VkSwapchainPresentFenceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_FENCE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSwapchainPresentModesCreateInfoEXT SwapchainPresentModesCreateInfoEXT(const void* next = nullptr) {
    VkSwapchainPresentModesCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODES_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSwapchainPresentModeInfoEXT SwapchainPresentModeInfoEXT(const void* next = nullptr) {
    VkSwapchainPresentModeInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSwapchainPresentScalingCreateInfoEXT SwapchainPresentScalingCreateInfoEXT(const void* next = nullptr) {
    VkSwapchainPresentScalingCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_SCALING_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkReleaseSwapchainImagesInfoEXT ReleaseSwapchainImagesInfoEXT(const void* next = nullptr) {
    VkReleaseSwapchainImagesInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RELEASE_SWAPCHAIN_IMAGES_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV PhysicalDeviceDeviceGeneratedCommandsPropertiesNV(
    void* next = nullptr) {
    VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV PhysicalDeviceDeviceGeneratedCommandsFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkGraphicsShaderGroupCreateInfoNV GraphicsShaderGroupCreateInfoNV(const void* next = nullptr) {
    VkGraphicsShaderGroupCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_SHADER_GROUP_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkGraphicsPipelineShaderGroupsCreateInfoNV GraphicsPipelineShaderGroupsCreateInfoNV(const void* next = nullptr) {
    VkGraphicsPipelineShaderGroupsCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkIndirectCommandsLayoutTokenNV IndirectCommandsLayoutTokenNV(const void* next = nullptr) {
    VkIndirectCommandsLayoutTokenNV info{};
    info.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV;
    info.pNext = next;
    return info;
}

inline VkIndirectCommandsLayoutCreateInfoNV IndirectCommandsLayoutCreateInfoNV(const void* next = nullptr) {
    VkIndirectCommandsLayoutCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkGeneratedCommandsInfoNV GeneratedCommandsInfoNV(const void* next = nullptr) {
    VkGeneratedCommandsInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkGeneratedCommandsMemoryRequirementsInfoNV GeneratedCommandsMemoryRequirementsInfoNV(const void* next = nullptr) {
    VkGeneratedCommandsMemoryRequirementsInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceInheritedViewportScissorFeaturesNV PhysicalDeviceInheritedViewportScissorFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceInheritedViewportScissorFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkCommandBufferInheritanceViewportScissorInfoNV CommandBufferInheritanceViewportScissorInfoNV(
    const void* next = nullptr) {
    VkCommandBufferInheritanceViewportScissorInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT PhysicalDeviceTexelBufferAlignmentFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkRenderPassTransformBeginInfoQCOM RenderPassTransformBeginInfoQCOM(void* next = nullptr) {
    VkRenderPassTransformBeginInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkCommandBufferInheritanceRenderPassTransformInfoQCOM CommandBufferInheritanceRenderPassTransformInfoQCOM(
    void* next = nullptr) {
    VkCommandBufferInheritanceRenderPassTransformInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDepthBiasControlFeaturesEXT PhysicalDeviceDepthBiasControlFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceDepthBiasControlFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_BIAS_CONTROL_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkDepthBiasInfoEXT DepthBiasInfoEXT(const void* next = nullptr) {
    VkDepthBiasInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEPTH_BIAS_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDepthBiasRepresentationInfoEXT DepthBiasRepresentationInfoEXT(const void* next = nullptr) {
    VkDepthBiasRepresentationInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEPTH_BIAS_REPRESENTATION_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDeviceMemoryReportFeaturesEXT PhysicalDeviceDeviceMemoryReportFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceDeviceMemoryReportFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkDeviceMemoryReportCallbackDataEXT DeviceMemoryReportCallbackDataEXT(void* next = nullptr) {
    VkDeviceMemoryReportCallbackDataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_REPORT_CALLBACK_DATA_EXT;
    info.pNext = next;
    return info;
}

inline VkDeviceDeviceMemoryReportCreateInfoEXT DeviceDeviceMemoryReportCreateInfoEXT(const void* next = nullptr) {
    VkDeviceDeviceMemoryReportCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRobustness2FeaturesEXT PhysicalDeviceRobustness2FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceRobustness2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRobustness2PropertiesEXT PhysicalDeviceRobustness2PropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceRobustness2PropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkSamplerCustomBorderColorCreateInfoEXT SamplerCustomBorderColorCreateInfoEXT(const void* next = nullptr) {
    VkSamplerCustomBorderColorCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCustomBorderColorPropertiesEXT PhysicalDeviceCustomBorderColorPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceCustomBorderColorPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCustomBorderColorFeaturesEXT PhysicalDeviceCustomBorderColorFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceCustomBorderColorFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePresentBarrierFeaturesNV PhysicalDevicePresentBarrierFeaturesNV(void* next = nullptr) {
    VkPhysicalDevicePresentBarrierFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_BARRIER_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkSurfaceCapabilitiesPresentBarrierNV SurfaceCapabilitiesPresentBarrierNV(void* next = nullptr) {
    VkSurfaceCapabilitiesPresentBarrierNV info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_PRESENT_BARRIER_NV;
    info.pNext = next;
    return info;
}

inline VkSwapchainPresentBarrierCreateInfoNV SwapchainPresentBarrierCreateInfoNV(void* next = nullptr) {
    VkSwapchainPresentBarrierCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_BARRIER_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDiagnosticsConfigFeaturesNV PhysicalDeviceDiagnosticsConfigFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceDiagnosticsConfigFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkDeviceDiagnosticsConfigCreateInfoNV DeviceDiagnosticsConfigCreateInfoNV(const void* next = nullptr) {
    VkDeviceDiagnosticsConfigCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkCudaModuleCreateInfoNV CudaModuleCreateInfoNV(const void* next = nullptr) {
    VkCudaModuleCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_CUDA_MODULE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkCudaFunctionCreateInfoNV CudaFunctionCreateInfoNV(const void* next = nullptr) {
    VkCudaFunctionCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_CUDA_FUNCTION_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkCudaLaunchInfoNV CudaLaunchInfoNV(const void* next = nullptr) {
    VkCudaLaunchInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_CUDA_LAUNCH_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCudaKernelLaunchFeaturesNV PhysicalDeviceCudaKernelLaunchFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceCudaKernelLaunchFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUDA_KERNEL_LAUNCH_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCudaKernelLaunchPropertiesNV PhysicalDeviceCudaKernelLaunchPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceCudaKernelLaunchPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUDA_KERNEL_LAUNCH_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkQueryLowLatencySupportNV QueryLowLatencySupportNV(const void* next = nullptr) {
    VkQueryLowLatencySupportNV info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_LOW_LATENCY_SUPPORT_NV;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_METAL_EXT
inline VkExportMetalObjectCreateInfoEXT ExportMetalObjectCreateInfoEXT(const void* next = nullptr) {
    VkExportMetalObjectCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECT_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalObjectsInfoEXT ExportMetalObjectsInfoEXT(const void* next = nullptr) {
    VkExportMetalObjectsInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECTS_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalDeviceInfoEXT ExportMetalDeviceInfoEXT(const void* next = nullptr) {
    VkExportMetalDeviceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_DEVICE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalCommandQueueInfoEXT ExportMetalCommandQueueInfoEXT(const void* next = nullptr) {
    VkExportMetalCommandQueueInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_COMMAND_QUEUE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalBufferInfoEXT ExportMetalBufferInfoEXT(const void* next = nullptr) {
    VkExportMetalBufferInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_BUFFER_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImportMetalBufferInfoEXT ImportMetalBufferInfoEXT(const void* next = nullptr) {
    VkImportMetalBufferInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_BUFFER_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalTextureInfoEXT ExportMetalTextureInfoEXT(const void* next = nullptr) {
    VkExportMetalTextureInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_TEXTURE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImportMetalTextureInfoEXT ImportMetalTextureInfoEXT(const void* next = nullptr) {
    VkImportMetalTextureInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_TEXTURE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalIOSurfaceInfoEXT ExportMetalIOSurfaceInfoEXT(const void* next = nullptr) {
    VkExportMetalIOSurfaceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_IO_SURFACE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImportMetalIOSurfaceInfoEXT ImportMetalIOSurfaceInfoEXT(const void* next = nullptr) {
    VkImportMetalIOSurfaceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_IO_SURFACE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkExportMetalSharedEventInfoEXT ExportMetalSharedEventInfoEXT(const void* next = nullptr) {
    VkExportMetalSharedEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_SHARED_EVENT_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImportMetalSharedEventInfoEXT ImportMetalSharedEventInfoEXT(const void* next = nullptr) {
    VkImportMetalSharedEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_SHARED_EVENT_INFO_EXT;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_METAL_EXT

inline VkPhysicalDeviceDescriptorBufferPropertiesEXT PhysicalDeviceDescriptorBufferPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceDescriptorBufferPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT PhysicalDeviceDescriptorBufferDensityMapPropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_DENSITY_MAP_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDescriptorBufferFeaturesEXT PhysicalDeviceDescriptorBufferFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceDescriptorBufferFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkDescriptorAddressInfoEXT DescriptorAddressInfoEXT(void* next = nullptr) {
    VkDescriptorAddressInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_ADDRESS_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDescriptorBufferBindingInfoEXT DescriptorBufferBindingInfoEXT(void* next = nullptr) {
    VkDescriptorBufferBindingInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDescriptorBufferBindingPushDescriptorBufferHandleEXT DescriptorBufferBindingPushDescriptorBufferHandleEXT(
    void* next = nullptr) {
    VkDescriptorBufferBindingPushDescriptorBufferHandleEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_PUSH_DESCRIPTOR_BUFFER_HANDLE_EXT;
    info.pNext = next;
    return info;
}

inline VkDescriptorGetInfoEXT DescriptorGetInfoEXT(const void* next = nullptr) {
    VkDescriptorGetInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkBufferCaptureDescriptorDataInfoEXT BufferCaptureDescriptorDataInfoEXT(const void* next = nullptr) {
    VkBufferCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImageCaptureDescriptorDataInfoEXT ImageCaptureDescriptorDataInfoEXT(const void* next = nullptr) {
    VkImageCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkImageViewCaptureDescriptorDataInfoEXT ImageViewCaptureDescriptorDataInfoEXT(const void* next = nullptr) {
    VkImageViewCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkSamplerCaptureDescriptorDataInfoEXT SamplerCaptureDescriptorDataInfoEXT(const void* next = nullptr) {
    VkSamplerCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkOpaqueCaptureDescriptorDataCreateInfoEXT OpaqueCaptureDescriptorDataCreateInfoEXT(const void* next = nullptr) {
    VkOpaqueCaptureDescriptorDataCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureCaptureDescriptorDataInfoEXT AccelerationStructureCaptureDescriptorDataInfoEXT(
    const void* next = nullptr) {
    VkAccelerationStructureCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT PhysicalDeviceGraphicsPipelineLibraryFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT PhysicalDeviceGraphicsPipelineLibraryPropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkGraphicsPipelineLibraryCreateInfoEXT GraphicsPipelineLibraryCreateInfoEXT(const void* next = nullptr) {
    VkGraphicsPipelineLibraryCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_LIBRARY_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD PhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD(
    void* next = nullptr) {
    VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_FEATURES_AMD;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV PhysicalDeviceFragmentShadingRateEnumsFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV PhysicalDeviceFragmentShadingRateEnumsPropertiesNV(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineFragmentShadingRateEnumStateCreateInfoNV PipelineFragmentShadingRateEnumStateCreateInfoNV(
    const void* next = nullptr) {
    VkPipelineFragmentShadingRateEnumStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureGeometryMotionTrianglesDataNV AccelerationStructureGeometryMotionTrianglesDataNV(
    const void* next = nullptr) {
    VkAccelerationStructureGeometryMotionTrianglesDataNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureMotionInfoNV AccelerationStructureMotionInfoNV(const void* next = nullptr) {
    VkAccelerationStructureMotionInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingMotionBlurFeaturesNV PhysicalDeviceRayTracingMotionBlurFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceRayTracingMotionBlurFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMap2FeaturesEXT PhysicalDeviceFragmentDensityMap2FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceFragmentDensityMap2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMap2PropertiesEXT PhysicalDeviceFragmentDensityMap2PropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceFragmentDensityMap2PropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyCommandTransformInfoQCOM CopyCommandTransformInfoQCOM(const void* next = nullptr) {
    VkCopyCommandTransformInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageCompressionControlFeaturesEXT PhysicalDeviceImageCompressionControlFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceImageCompressionControlFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkImageCompressionControlEXT ImageCompressionControlEXT(const void* next = nullptr) {
    VkImageCompressionControlEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
    info.pNext = next;
    return info;
}

inline VkImageCompressionPropertiesEXT ImageCompressionPropertiesEXT(void* next = nullptr) {
    VkImageCompressionPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT PhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevice4444FormatsFeaturesEXT PhysicalDevice4444FormatsFeaturesEXT(void* next = nullptr) {
    VkPhysicalDevice4444FormatsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFaultFeaturesEXT PhysicalDeviceFaultFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceFaultFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkDeviceFaultCountsEXT DeviceFaultCountsEXT(void* next = nullptr) {
    VkDeviceFaultCountsEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;
    info.pNext = next;
    return info;
}

inline VkDeviceFaultInfoEXT DeviceFaultInfoEXT(void* next = nullptr) {
    VkDeviceFaultInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT
PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT PhysicalDeviceRGBA10X6FormatsFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
inline VkDirectFBSurfaceCreateInfoEXT DirectFBSurfaceCreateInfoEXT(const void* next = nullptr) {
    VkDirectFBSurfaceCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

inline VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT PhysicalDeviceMutableDescriptorTypeFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkMutableDescriptorTypeCreateInfoEXT MutableDescriptorTypeCreateInfoEXT(const void* next = nullptr) {
    VkMutableDescriptorTypeCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT PhysicalDeviceVertexInputDynamicStateFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkVertexInputBindingDescription2EXT VertexInputBindingDescription2EXT(void* next = nullptr) {
    VkVertexInputBindingDescription2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT;
    info.pNext = next;
    return info;
}

inline VkVertexInputAttributeDescription2EXT VertexInputAttributeDescription2EXT(void* next = nullptr) {
    VkVertexInputAttributeDescription2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDrmPropertiesEXT PhysicalDeviceDrmPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceDrmPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceAddressBindingReportFeaturesEXT PhysicalDeviceAddressBindingReportFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceAddressBindingReportFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ADDRESS_BINDING_REPORT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkDeviceAddressBindingCallbackDataEXT DeviceAddressBindingCallbackDataEXT(void* next = nullptr) {
    VkDeviceAddressBindingCallbackDataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_ADDRESS_BINDING_CALLBACK_DATA_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDepthClipControlFeaturesEXT PhysicalDeviceDepthClipControlFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceDepthClipControlFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineViewportDepthClipControlCreateInfoEXT PipelineViewportDepthClipControlCreateInfoEXT(
    const void* next = nullptr) {
    VkPipelineViewportDepthClipControlCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT PhysicalDevicePrimitiveTopologyListRestartFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_FUCHSIA
inline VkImportMemoryZirconHandleInfoFUCHSIA ImportMemoryZirconHandleInfoFUCHSIA(const void* next = nullptr) {
    VkImportMemoryZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkMemoryZirconHandlePropertiesFUCHSIA MemoryZirconHandlePropertiesFUCHSIA(void* next = nullptr) {
    VkMemoryZirconHandlePropertiesFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkMemoryGetZirconHandleInfoFUCHSIA MemoryGetZirconHandleInfoFUCHSIA(const void* next = nullptr) {
    VkMemoryGetZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkImportSemaphoreZirconHandleInfoFUCHSIA ImportSemaphoreZirconHandleInfoFUCHSIA(const void* next = nullptr) {
    VkImportSemaphoreZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkSemaphoreGetZirconHandleInfoFUCHSIA SemaphoreGetZirconHandleInfoFUCHSIA(const void* next = nullptr) {
    VkSemaphoreGetZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkBufferCollectionCreateInfoFUCHSIA BufferCollectionCreateInfoFUCHSIA(const void* next = nullptr) {
    VkBufferCollectionCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CREATE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkImportMemoryBufferCollectionFUCHSIA ImportMemoryBufferCollectionFUCHSIA(const void* next = nullptr) {
    VkImportMemoryBufferCollectionFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkBufferCollectionImageCreateInfoFUCHSIA BufferCollectionImageCreateInfoFUCHSIA(const void* next = nullptr) {
    VkBufferCollectionImageCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_IMAGE_CREATE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkBufferCollectionConstraintsInfoFUCHSIA BufferCollectionConstraintsInfoFUCHSIA(const void* next = nullptr) {
    VkBufferCollectionConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CONSTRAINTS_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkBufferConstraintsInfoFUCHSIA BufferConstraintsInfoFUCHSIA(const void* next = nullptr) {
    VkBufferConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CONSTRAINTS_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkBufferCollectionBufferCreateInfoFUCHSIA BufferCollectionBufferCreateInfoFUCHSIA(const void* next = nullptr) {
    VkBufferCollectionBufferCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_BUFFER_CREATE_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkSysmemColorSpaceFUCHSIA SysmemColorSpaceFUCHSIA(const void* next = nullptr) {
    VkSysmemColorSpaceFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_SYSMEM_COLOR_SPACE_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkBufferCollectionPropertiesFUCHSIA BufferCollectionPropertiesFUCHSIA(void* next = nullptr) {
    VkBufferCollectionPropertiesFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_PROPERTIES_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkImageFormatConstraintsInfoFUCHSIA ImageFormatConstraintsInfoFUCHSIA(const void* next = nullptr) {
    VkImageFormatConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_CONSTRAINTS_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}

inline VkImageConstraintsInfoFUCHSIA ImageConstraintsInfoFUCHSIA(const void* next = nullptr) {
    VkImageConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CONSTRAINTS_INFO_FUCHSIA;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_FUCHSIA

inline VkSubpassShadingPipelineCreateInfoHUAWEI SubpassShadingPipelineCreateInfoHUAWEI(void* next = nullptr) {
    VkSubpassShadingPipelineCreateInfoHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_SHADING_PIPELINE_CREATE_INFO_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSubpassShadingFeaturesHUAWEI PhysicalDeviceSubpassShadingFeaturesHUAWEI(void* next = nullptr) {
    VkPhysicalDeviceSubpassShadingFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_FEATURES_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSubpassShadingPropertiesHUAWEI PhysicalDeviceSubpassShadingPropertiesHUAWEI(void* next = nullptr) {
    VkPhysicalDeviceSubpassShadingPropertiesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_PROPERTIES_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceInvocationMaskFeaturesHUAWEI PhysicalDeviceInvocationMaskFeaturesHUAWEI(void* next = nullptr) {
    VkPhysicalDeviceInvocationMaskFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkMemoryGetRemoteAddressInfoNV MemoryGetRemoteAddressInfoNV(const void* next = nullptr) {
    VkMemoryGetRemoteAddressInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalMemoryRDMAFeaturesNV PhysicalDeviceExternalMemoryRDMAFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceExternalMemoryRDMAFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPipelinePropertiesIdentifierEXT PipelinePropertiesIdentifierEXT(void* next = nullptr) {
    VkPipelinePropertiesIdentifierEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_PROPERTIES_IDENTIFIER_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelinePropertiesFeaturesEXT PhysicalDevicePipelinePropertiesFeaturesEXT(void* next = nullptr) {
    VkPhysicalDevicePipelinePropertiesFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROPERTIES_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFrameBoundaryFeaturesEXT PhysicalDeviceFrameBoundaryFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceFrameBoundaryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAME_BOUNDARY_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkFrameBoundaryEXT FrameBoundaryEXT(const void* next = nullptr) {
    VkFrameBoundaryEXT info{};
    info.sType = VK_STRUCTURE_TYPE_FRAME_BOUNDARY_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT PhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkSubpassResolvePerformanceQueryEXT SubpassResolvePerformanceQueryEXT(void* next = nullptr) {
    VkSubpassResolvePerformanceQueryEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_RESOLVE_PERFORMANCE_QUERY_EXT;
    info.pNext = next;
    return info;
}

inline VkMultisampledRenderToSingleSampledInfoEXT MultisampledRenderToSingleSampledInfoEXT(const void* next = nullptr) {
    VkMultisampledRenderToSingleSampledInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicState2FeaturesEXT PhysicalDeviceExtendedDynamicState2FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceExtendedDynamicState2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_SCREEN_QNX
inline VkScreenSurfaceCreateInfoQNX ScreenSurfaceCreateInfoQNX(const void* next = nullptr) {
    VkScreenSurfaceCreateInfoQNX info{};
    info.sType = VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_SCREEN_QNX

inline VkPhysicalDeviceColorWriteEnableFeaturesEXT PhysicalDeviceColorWriteEnableFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceColorWriteEnableFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineColorWriteCreateInfoEXT PipelineColorWriteCreateInfoEXT(const void* next = nullptr) {
    VkPipelineColorWriteCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT PhysicalDevicePrimitivesGeneratedQueryFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVES_GENERATED_QUERY_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageViewMinLodFeaturesEXT PhysicalDeviceImageViewMinLodFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceImageViewMinLodFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkImageViewMinLodCreateInfoEXT ImageViewMinLodCreateInfoEXT(const void* next = nullptr) {
    VkImageViewMinLodCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_MIN_LOD_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiDrawFeaturesEXT PhysicalDeviceMultiDrawFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceMultiDrawFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiDrawPropertiesEXT PhysicalDeviceMultiDrawPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceMultiDrawPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImage2DViewOf3DFeaturesEXT PhysicalDeviceImage2DViewOf3DFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceImage2DViewOf3DFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_2D_VIEW_OF_3D_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderTileImageFeaturesEXT PhysicalDeviceShaderTileImageFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderTileImageFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderTileImagePropertiesEXT PhysicalDeviceShaderTileImagePropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderTileImagePropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkMicromapBuildInfoEXT MicromapBuildInfoEXT(const void* next = nullptr) {
    VkMicromapBuildInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkMicromapCreateInfoEXT MicromapCreateInfoEXT(const void* next = nullptr) {
    VkMicromapCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceOpacityMicromapFeaturesEXT PhysicalDeviceOpacityMicromapFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceOpacityMicromapFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceOpacityMicromapPropertiesEXT PhysicalDeviceOpacityMicromapPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceOpacityMicromapPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkMicromapVersionInfoEXT MicromapVersionInfoEXT(const void* next = nullptr) {
    VkMicromapVersionInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_VERSION_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyMicromapToMemoryInfoEXT CopyMicromapToMemoryInfoEXT(const void* next = nullptr) {
    VkCopyMicromapToMemoryInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_TO_MEMORY_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyMemoryToMicromapInfoEXT CopyMemoryToMicromapInfoEXT(const void* next = nullptr) {
    VkCopyMemoryToMicromapInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_MICROMAP_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkCopyMicromapInfoEXT CopyMicromapInfoEXT(const void* next = nullptr) {
    VkCopyMicromapInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkMicromapBuildSizesInfoEXT MicromapBuildSizesInfoEXT(const void* next = nullptr) {
    VkMicromapBuildSizesInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_SIZES_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureTrianglesOpacityMicromapEXT AccelerationStructureTrianglesOpacityMicromapEXT(
    void* next = nullptr) {
    VkAccelerationStructureTrianglesOpacityMicromapEXT info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_OPACITY_MICROMAP_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_ENABLE_BETA_EXTENSIONS
inline VkPhysicalDeviceDisplacementMicromapFeaturesNV PhysicalDeviceDisplacementMicromapFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceDisplacementMicromapFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISPLACEMENT_MICROMAP_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDisplacementMicromapPropertiesNV PhysicalDeviceDisplacementMicromapPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceDisplacementMicromapPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISPLACEMENT_MICROMAP_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureTrianglesDisplacementMicromapNV AccelerationStructureTrianglesDisplacementMicromapNV(
    void* next = nullptr) {
    VkAccelerationStructureTrianglesDisplacementMicromapNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_DISPLACEMENT_MICROMAP_NV;
    info.pNext = next;
    return info;
}
#endif // VK_ENABLE_BETA_EXTENSIONS

inline VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI PhysicalDeviceClusterCullingShaderFeaturesHUAWEI(
    void* next = nullptr) {
    VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_FEATURES_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI PhysicalDeviceClusterCullingShaderPropertiesHUAWEI(
    void* next = nullptr) {
    VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_PROPERTIES_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI PhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI(
    void* next = nullptr) {
    VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_VRS_FEATURES_HUAWEI;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceBorderColorSwizzleFeaturesEXT PhysicalDeviceBorderColorSwizzleFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceBorderColorSwizzleFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkSamplerBorderColorComponentMappingCreateInfoEXT SamplerBorderColorComponentMappingCreateInfoEXT(
    const void* next = nullptr) {
    VkSamplerBorderColorComponentMappingCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT PhysicalDevicePageableDeviceLocalMemoryFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderCorePropertiesARM PhysicalDeviceShaderCorePropertiesARM(void* next = nullptr) {
    VkPhysicalDeviceShaderCorePropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_ARM;
    info.pNext = next;
    return info;
}

inline VkDeviceQueueShaderCoreControlCreateInfoARM DeviceQueueShaderCoreControlCreateInfoARM(void* next = nullptr) {
    VkDeviceQueueShaderCoreControlCreateInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_SHADER_CORE_CONTROL_CREATE_INFO_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSchedulingControlsFeaturesARM PhysicalDeviceSchedulingControlsFeaturesARM(void* next = nullptr) {
    VkPhysicalDeviceSchedulingControlsFeaturesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_FEATURES_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSchedulingControlsPropertiesARM PhysicalDeviceSchedulingControlsPropertiesARM(void* next = nullptr) {
    VkPhysicalDeviceSchedulingControlsPropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_PROPERTIES_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT PhysicalDeviceImageSlicedViewOf3DFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_SLICED_VIEW_OF_3D_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkImageViewSlicedCreateInfoEXT ImageViewSlicedCreateInfoEXT(const void* next = nullptr) {
    VkImageViewSlicedCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_SLICED_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE PhysicalDeviceDescriptorSetHostMappingFeaturesVALVE(
    void* next = nullptr) {
    VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_SET_HOST_MAPPING_FEATURES_VALVE;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetBindingReferenceVALVE DescriptorSetBindingReferenceVALVE(const void* next = nullptr) {
    VkDescriptorSetBindingReferenceVALVE info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_BINDING_REFERENCE_VALVE;
    info.pNext = next;
    return info;
}

inline VkDescriptorSetLayoutHostMappingInfoVALVE DescriptorSetLayoutHostMappingInfoVALVE(void* next = nullptr) {
    VkDescriptorSetLayoutHostMappingInfoVALVE info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_HOST_MAPPING_INFO_VALVE;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDepthClampZeroOneFeaturesEXT PhysicalDeviceDepthClampZeroOneFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceDepthClampZeroOneFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLAMP_ZERO_ONE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT PhysicalDeviceNonSeamlessCubeMapFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NON_SEAMLESS_CUBE_MAP_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRenderPassStripedFeaturesARM PhysicalDeviceRenderPassStripedFeaturesARM(void* next = nullptr) {
    VkPhysicalDeviceRenderPassStripedFeaturesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RENDER_PASS_STRIPED_FEATURES_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRenderPassStripedPropertiesARM PhysicalDeviceRenderPassStripedPropertiesARM(void* next = nullptr) {
    VkPhysicalDeviceRenderPassStripedPropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RENDER_PASS_STRIPED_PROPERTIES_ARM;
    info.pNext = next;
    return info;
}

inline VkRenderPassStripeInfoARM RenderPassStripeInfoARM(const void* next = nullptr) {
    VkRenderPassStripeInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_INFO_ARM;
    info.pNext = next;
    return info;
}

inline VkRenderPassStripeBeginInfoARM RenderPassStripeBeginInfoARM(const void* next = nullptr) {
    VkRenderPassStripeBeginInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_BEGIN_INFO_ARM;
    info.pNext = next;
    return info;
}

inline VkRenderPassStripeSubmitInfoARM RenderPassStripeSubmitInfoARM(const void* next = nullptr) {
    VkRenderPassStripeSubmitInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_SUBMIT_INFO_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM PhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM PhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM(
    void* next = nullptr) {
    VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM;
    info.pNext = next;
    return info;
}

inline VkSubpassFragmentDensityMapOffsetEndInfoQCOM SubpassFragmentDensityMapOffsetEndInfoQCOM(const void* next = nullptr) {
    VkSubpassFragmentDensityMapOffsetEndInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCopyMemoryIndirectFeaturesNV PhysicalDeviceCopyMemoryIndirectFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceCopyMemoryIndirectFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCopyMemoryIndirectPropertiesNV PhysicalDeviceCopyMemoryIndirectPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceCopyMemoryIndirectPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMemoryDecompressionFeaturesNV PhysicalDeviceMemoryDecompressionFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceMemoryDecompressionFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMemoryDecompressionPropertiesNV PhysicalDeviceMemoryDecompressionPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceMemoryDecompressionPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV PhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_COMPUTE_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkComputePipelineIndirectBufferInfoNV ComputePipelineIndirectBufferInfoNV(const void* next = nullptr) {
    VkComputePipelineIndirectBufferInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_INDIRECT_BUFFER_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPipelineIndirectDeviceAddressInfoNV PipelineIndirectDeviceAddressInfoNV(const void* next = nullptr) {
    VkPipelineIndirectDeviceAddressInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_INDIRECT_DEVICE_ADDRESS_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceLinearColorAttachmentFeaturesNV PhysicalDeviceLinearColorAttachmentFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceLinearColorAttachmentFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT PhysicalDeviceImageCompressionControlSwapchainFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkImageViewSampleWeightCreateInfoQCOM ImageViewSampleWeightCreateInfoQCOM(const void* next = nullptr) {
    VkImageViewSampleWeightCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_SAMPLE_WEIGHT_CREATE_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageProcessingFeaturesQCOM PhysicalDeviceImageProcessingFeaturesQCOM(void* next = nullptr) {
    VkPhysicalDeviceImageProcessingFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageProcessingPropertiesQCOM PhysicalDeviceImageProcessingPropertiesQCOM(void* next = nullptr) {
    VkPhysicalDeviceImageProcessingPropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_PROPERTIES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceNestedCommandBufferFeaturesEXT PhysicalDeviceNestedCommandBufferFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceNestedCommandBufferFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceNestedCommandBufferPropertiesEXT PhysicalDeviceNestedCommandBufferPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceNestedCommandBufferPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkExternalMemoryAcquireUnmodifiedEXT ExternalMemoryAcquireUnmodifiedEXT(const void* next = nullptr) {
    VkExternalMemoryAcquireUnmodifiedEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicState3FeaturesEXT PhysicalDeviceExtendedDynamicState3FeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceExtendedDynamicState3FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicState3PropertiesEXT PhysicalDeviceExtendedDynamicState3PropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceExtendedDynamicState3PropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT PhysicalDeviceSubpassMergeFeedbackFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_MERGE_FEEDBACK_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkRenderPassCreationControlEXT RenderPassCreationControlEXT(const void* next = nullptr) {
    VkRenderPassCreationControlEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_CONTROL_EXT;
    info.pNext = next;
    return info;
}

inline VkRenderPassCreationFeedbackCreateInfoEXT RenderPassCreationFeedbackCreateInfoEXT(const void* next = nullptr) {
    VkRenderPassCreationFeedbackCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_FEEDBACK_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkRenderPassSubpassFeedbackCreateInfoEXT RenderPassSubpassFeedbackCreateInfoEXT(const void* next = nullptr) {
    VkRenderPassSubpassFeedbackCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SUBPASS_FEEDBACK_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkDirectDriverLoadingInfoLUNARG DirectDriverLoadingInfoLUNARG(void* next = nullptr) {
    VkDirectDriverLoadingInfoLUNARG info{};
    info.sType = VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_INFO_LUNARG;
    info.pNext = next;
    return info;
}

inline VkDirectDriverLoadingListLUNARG DirectDriverLoadingListLUNARG(const void* next = nullptr) {
    VkDirectDriverLoadingListLUNARG info{};
    info.sType = VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_LIST_LUNARG;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT PhysicalDeviceShaderModuleIdentifierFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT PhysicalDeviceShaderModuleIdentifierPropertiesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkPipelineShaderStageModuleIdentifierCreateInfoEXT PipelineShaderStageModuleIdentifierCreateInfoEXT(
    const void* next = nullptr) {
    VkPipelineShaderStageModuleIdentifierCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_MODULE_IDENTIFIER_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkShaderModuleIdentifierEXT ShaderModuleIdentifierEXT(void* next = nullptr) {
    VkShaderModuleIdentifierEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_IDENTIFIER_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceOpticalFlowFeaturesNV PhysicalDeviceOpticalFlowFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceOpticalFlowFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceOpticalFlowPropertiesNV PhysicalDeviceOpticalFlowPropertiesNV(void* next = nullptr) {
    VkPhysicalDeviceOpticalFlowPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkOpticalFlowImageFormatInfoNV OpticalFlowImageFormatInfoNV(const void* next = nullptr) {
    VkOpticalFlowImageFormatInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkOpticalFlowImageFormatPropertiesNV OpticalFlowImageFormatPropertiesNV(const void* next = nullptr) {
    VkOpticalFlowImageFormatPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkOpticalFlowSessionCreateInfoNV OpticalFlowSessionCreateInfoNV(void* next = nullptr) {
    VkOpticalFlowSessionCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkOpticalFlowSessionCreatePrivateDataInfoNV OpticalFlowSessionCreatePrivateDataInfoNV(void* next = nullptr) {
    VkOpticalFlowSessionCreatePrivateDataInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_PRIVATE_DATA_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkOpticalFlowExecuteInfoNV OpticalFlowExecuteInfoNV(void* next = nullptr) {
    VkOpticalFlowExecuteInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceLegacyDitheringFeaturesEXT PhysicalDeviceLegacyDitheringFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceLegacyDitheringFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LEGACY_DITHERING_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelineProtectedAccessFeaturesEXT PhysicalDevicePipelineProtectedAccessFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDevicePipelineProtectedAccessFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROTECTED_ACCESS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_ANDROID_KHR
inline VkPhysicalDeviceExternalFormatResolveFeaturesANDROID PhysicalDeviceExternalFormatResolveFeaturesANDROID(
    void* next = nullptr) {
    VkPhysicalDeviceExternalFormatResolveFeaturesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FORMAT_RESOLVE_FEATURES_ANDROID;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalFormatResolvePropertiesANDROID PhysicalDeviceExternalFormatResolvePropertiesANDROID(
    void* next = nullptr) {
    VkPhysicalDeviceExternalFormatResolvePropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FORMAT_RESOLVE_PROPERTIES_ANDROID;
    info.pNext = next;
    return info;
}

inline VkAndroidHardwareBufferFormatResolvePropertiesANDROID AndroidHardwareBufferFormatResolvePropertiesANDROID(
    void* next = nullptr) {
    VkAndroidHardwareBufferFormatResolvePropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_RESOLVE_PROPERTIES_ANDROID;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_ANDROID_KHR

inline VkPhysicalDeviceShaderObjectFeaturesEXT PhysicalDeviceShaderObjectFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderObjectFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderObjectPropertiesEXT PhysicalDeviceShaderObjectPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceShaderObjectPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

inline VkShaderCreateInfoEXT ShaderCreateInfoEXT(const void* next = nullptr) {
    VkShaderCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceTilePropertiesFeaturesQCOM PhysicalDeviceTilePropertiesFeaturesQCOM(void* next = nullptr) {
    VkPhysicalDeviceTilePropertiesFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_PROPERTIES_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkTilePropertiesQCOM TilePropertiesQCOM(void* next = nullptr) {
    VkTilePropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_TILE_PROPERTIES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceAmigoProfilingFeaturesSEC PhysicalDeviceAmigoProfilingFeaturesSEC(void* next = nullptr) {
    VkPhysicalDeviceAmigoProfilingFeaturesSEC info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_AMIGO_PROFILING_FEATURES_SEC;
    info.pNext = next;
    return info;
}

inline VkAmigoProfilingSubmitInfoSEC AmigoProfilingSubmitInfoSEC(const void* next = nullptr) {
    VkAmigoProfilingSubmitInfoSEC info{};
    info.sType = VK_STRUCTURE_TYPE_AMIGO_PROFILING_SUBMIT_INFO_SEC;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM PhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM(
    void* next = nullptr) {
    VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_VIEWPORTS_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV PhysicalDeviceRayTracingInvocationReorderPropertiesNV(
    void* next = nullptr) {
    VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV PhysicalDeviceRayTracingInvocationReorderFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV PhysicalDeviceExtendedSparseAddressSpaceFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_SPARSE_ADDRESS_SPACE_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV PhysicalDeviceExtendedSparseAddressSpacePropertiesNV(
    void* next = nullptr) {
    VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_SPARSE_ADDRESS_SPACE_PROPERTIES_NV;
    info.pNext = next;
    return info;
}

inline VkLayerSettingsCreateInfoEXT LayerSettingsCreateInfoEXT(const void* next = nullptr) {
    VkLayerSettingsCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM PhysicalDeviceShaderCoreBuiltinsFeaturesARM(void* next = nullptr) {
    VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_FEATURES_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM PhysicalDeviceShaderCoreBuiltinsPropertiesARM(void* next = nullptr) {
    VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_PROPERTIES_ARM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT PhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_LIBRARY_GROUP_HANDLES_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT PhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT(
    void* next = nullptr) {
    VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkLatencySleepModeInfoNV LatencySleepModeInfoNV(const void* next = nullptr) {
    VkLatencySleepModeInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_MODE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkLatencySleepInfoNV LatencySleepInfoNV(const void* next = nullptr) {
    VkLatencySleepInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkSetLatencyMarkerInfoNV SetLatencyMarkerInfoNV(const void* next = nullptr) {
    VkSetLatencyMarkerInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_SET_LATENCY_MARKER_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkLatencyTimingsFrameReportNV LatencyTimingsFrameReportNV(const void* next = nullptr) {
    VkLatencyTimingsFrameReportNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_TIMINGS_FRAME_REPORT_NV;
    info.pNext = next;
    return info;
}

inline VkGetLatencyMarkerInfoNV GetLatencyMarkerInfoNV(const void* next = nullptr) {
    VkGetLatencyMarkerInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GET_LATENCY_MARKER_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkLatencySubmissionPresentIdNV LatencySubmissionPresentIdNV(const void* next = nullptr) {
    VkLatencySubmissionPresentIdNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SUBMISSION_PRESENT_ID_NV;
    info.pNext = next;
    return info;
}

inline VkSwapchainLatencyCreateInfoNV SwapchainLatencyCreateInfoNV(const void* next = nullptr) {
    VkSwapchainLatencyCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_LATENCY_CREATE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkOutOfBandQueueTypeInfoNV OutOfBandQueueTypeInfoNV(const void* next = nullptr) {
    VkOutOfBandQueueTypeInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OUT_OF_BAND_QUEUE_TYPE_INFO_NV;
    info.pNext = next;
    return info;
}

inline VkLatencySurfaceCapabilitiesNV LatencySurfaceCapabilitiesNV(const void* next = nullptr) {
    VkLatencySurfaceCapabilitiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SURFACE_CAPABILITIES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM PhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM(
    void* next = nullptr) {
    VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_RENDER_AREAS_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM(
    const void* next = nullptr) {
    VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_RENDER_AREAS_RENDER_PASS_BEGIN_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDevicePerStageDescriptorSetFeaturesNV PhysicalDevicePerStageDescriptorSetFeaturesNV(void* next = nullptr) {
    VkPhysicalDevicePerStageDescriptorSetFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PER_STAGE_DESCRIPTOR_SET_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageProcessing2FeaturesQCOM PhysicalDeviceImageProcessing2FeaturesQCOM(void* next = nullptr) {
    VkPhysicalDeviceImageProcessing2FeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_2_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceImageProcessing2PropertiesQCOM PhysicalDeviceImageProcessing2PropertiesQCOM(void* next = nullptr) {
    VkPhysicalDeviceImageProcessing2PropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_2_PROPERTIES_QCOM;
    info.pNext = next;
    return info;
}

inline VkSamplerBlockMatchWindowCreateInfoQCOM SamplerBlockMatchWindowCreateInfoQCOM(const void* next = nullptr) {
    VkSamplerBlockMatchWindowCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_BLOCK_MATCH_WINDOW_CREATE_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCubicWeightsFeaturesQCOM PhysicalDeviceCubicWeightsFeaturesQCOM(void* next = nullptr) {
    VkPhysicalDeviceCubicWeightsFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUBIC_WEIGHTS_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkSamplerCubicWeightsCreateInfoQCOM SamplerCubicWeightsCreateInfoQCOM(const void* next = nullptr) {
    VkSamplerCubicWeightsCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CUBIC_WEIGHTS_CREATE_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkBlitImageCubicWeightsInfoQCOM BlitImageCubicWeightsInfoQCOM(const void* next = nullptr) {
    VkBlitImageCubicWeightsInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_CUBIC_WEIGHTS_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceYcbcrDegammaFeaturesQCOM PhysicalDeviceYcbcrDegammaFeaturesQCOM(void* next = nullptr) {
    VkPhysicalDeviceYcbcrDegammaFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_DEGAMMA_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM SamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM(
    void* next = nullptr) {
    VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_YCBCR_DEGAMMA_CREATE_INFO_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceCubicClampFeaturesQCOM PhysicalDeviceCubicClampFeaturesQCOM(void* next = nullptr) {
    VkPhysicalDeviceCubicClampFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUBIC_CLAMP_FEATURES_QCOM;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT
PhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_FEATURES_EXT;
    info.pNext = next;
    return info;
}

#ifdef VK_USE_PLATFORM_SCREEN_QNX
inline VkScreenBufferPropertiesQNX ScreenBufferPropertiesQNX(void* next = nullptr) {
    VkScreenBufferPropertiesQNX info{};
    info.sType = VK_STRUCTURE_TYPE_SCREEN_BUFFER_PROPERTIES_QNX;
    info.pNext = next;
    return info;
}

inline VkScreenBufferFormatPropertiesQNX ScreenBufferFormatPropertiesQNX(void* next = nullptr) {
    VkScreenBufferFormatPropertiesQNX info{};
    info.sType = VK_STRUCTURE_TYPE_SCREEN_BUFFER_FORMAT_PROPERTIES_QNX;
    info.pNext = next;
    return info;
}

inline VkImportScreenBufferInfoQNX ImportScreenBufferInfoQNX(const void* next = nullptr) {
    VkImportScreenBufferInfoQNX info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SCREEN_BUFFER_INFO_QNX;
    info.pNext = next;
    return info;
}

inline VkExternalFormatQNX ExternalFormatQNX(void* next = nullptr) {
    VkExternalFormatQNX info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_QNX;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX PhysicalDeviceExternalMemoryScreenBufferFeaturesQNX(
    void* next = nullptr) {
    VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_SCREEN_BUFFER_FEATURES_QNX;
    info.pNext = next;
    return info;
}
#endif // VK_USE_PLATFORM_SCREEN_QNX

inline VkPhysicalDeviceLayeredDriverPropertiesMSFT PhysicalDeviceLayeredDriverPropertiesMSFT(void* next = nullptr) {
    VkPhysicalDeviceLayeredDriverPropertiesMSFT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LAYERED_DRIVER_PROPERTIES_MSFT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV PhysicalDeviceDescriptorPoolOverallocationFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_POOL_OVERALLOCATION_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRawAccessChainsFeaturesNV PhysicalDeviceRawAccessChainsFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceRawAccessChainsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAW_ACCESS_CHAINS_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV PhysicalDeviceShaderAtomicFloat16VectorFeaturesNV(
    void* next = nullptr) {
    VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT16_VECTOR_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingValidationFeaturesNV PhysicalDeviceRayTracingValidationFeaturesNV(void* next = nullptr) {
    VkPhysicalDeviceRayTracingValidationFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_VALIDATION_FEATURES_NV;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureGeometryTrianglesDataKHR AccelerationStructureGeometryTrianglesDataKHR(
    const void* next = nullptr) {
    VkAccelerationStructureGeometryTrianglesDataKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureGeometryAabbsDataKHR AccelerationStructureGeometryAabbsDataKHR(const void* next = nullptr) {
    VkAccelerationStructureGeometryAabbsDataKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureGeometryInstancesDataKHR AccelerationStructureGeometryInstancesDataKHR(
    const void* next = nullptr) {
    VkAccelerationStructureGeometryInstancesDataKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureGeometryKHR AccelerationStructureGeometryKHR(const void* next = nullptr) {
    VkAccelerationStructureGeometryKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureBuildGeometryInfoKHR AccelerationStructureBuildGeometryInfoKHR(const void* next = nullptr) {
    VkAccelerationStructureBuildGeometryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureCreateInfoKHR AccelerationStructureCreateInfoKHR(const void* next = nullptr) {
    VkAccelerationStructureCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkWriteDescriptorSetAccelerationStructureKHR WriteDescriptorSetAccelerationStructureKHR(const void* next = nullptr) {
    VkWriteDescriptorSetAccelerationStructureKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceAccelerationStructureFeaturesKHR PhysicalDeviceAccelerationStructureFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceAccelerationStructureFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceAccelerationStructurePropertiesKHR PhysicalDeviceAccelerationStructurePropertiesKHR(
    void* next = nullptr) {
    VkPhysicalDeviceAccelerationStructurePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureDeviceAddressInfoKHR AccelerationStructureDeviceAddressInfoKHR(const void* next = nullptr) {
    VkAccelerationStructureDeviceAddressInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureVersionInfoKHR AccelerationStructureVersionInfoKHR(const void* next = nullptr) {
    VkAccelerationStructureVersionInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkCopyAccelerationStructureToMemoryInfoKHR CopyAccelerationStructureToMemoryInfoKHR(const void* next = nullptr) {
    VkCopyAccelerationStructureToMemoryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkCopyMemoryToAccelerationStructureInfoKHR CopyMemoryToAccelerationStructureInfoKHR(const void* next = nullptr) {
    VkCopyMemoryToAccelerationStructureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkCopyAccelerationStructureInfoKHR CopyAccelerationStructureInfoKHR(const void* next = nullptr) {
    VkCopyAccelerationStructureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkAccelerationStructureBuildSizesInfoKHR AccelerationStructureBuildSizesInfoKHR(const void* next = nullptr) {
    VkAccelerationStructureBuildSizesInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkRayTracingShaderGroupCreateInfoKHR RayTracingShaderGroupCreateInfoKHR(const void* next = nullptr) {
    VkRayTracingShaderGroupCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkRayTracingPipelineInterfaceCreateInfoKHR RayTracingPipelineInterfaceCreateInfoKHR(const void* next = nullptr) {
    VkRayTracingPipelineInterfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkRayTracingPipelineCreateInfoKHR RayTracingPipelineCreateInfoKHR(const void* next = nullptr) {
    VkRayTracingPipelineCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingPipelineFeaturesKHR PhysicalDeviceRayTracingPipelineFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayTracingPipelinePropertiesKHR PhysicalDeviceRayTracingPipelinePropertiesKHR(void* next = nullptr) {
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceRayQueryFeaturesKHR PhysicalDeviceRayQueryFeaturesKHR(void* next = nullptr) {
    VkPhysicalDeviceRayQueryFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMeshShaderFeaturesEXT PhysicalDeviceMeshShaderFeaturesEXT(void* next = nullptr) {
    VkPhysicalDeviceMeshShaderFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
    info.pNext = next;
    return info;
}

inline VkPhysicalDeviceMeshShaderPropertiesEXT PhysicalDeviceMeshShaderPropertiesEXT(void* next = nullptr) {
    VkPhysicalDeviceMeshShaderPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
    info.pNext = next;
    return info;
}

} // namespace Itor
} // namespace vkt
