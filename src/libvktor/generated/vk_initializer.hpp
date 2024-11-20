#pragma once

#include <vulkan/vulkan.h>

namespace vkt {
namespace Itor {

inline VkBufferMemoryBarrier BufferMemoryBarrier() {
    VkBufferMemoryBarrier info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    return info;
}

inline VkImageMemoryBarrier ImageMemoryBarrier() {
    VkImageMemoryBarrier info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    return info;
}

inline VkMemoryBarrier MemoryBarrier() {
    VkMemoryBarrier info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    return info;
}

inline VkApplicationInfo ApplicationInfo() {
    VkApplicationInfo info{};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    return info;
}

inline VkInstanceCreateInfo InstanceCreateInfo() {
    VkInstanceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return info;
}

inline VkDeviceQueueCreateInfo DeviceQueueCreateInfo() {
    VkDeviceQueueCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    return info;
}

inline VkDeviceCreateInfo DeviceCreateInfo() {
    VkDeviceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    return info;
}

inline VkSubmitInfo SubmitInfo() {
    VkSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    return info;
}

inline VkMappedMemoryRange MappedMemoryRange() {
    VkMappedMemoryRange info{};
    info.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    return info;
}

inline VkMemoryAllocateInfo MemoryAllocateInfo() {
    VkMemoryAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    return info;
}

inline VkBindSparseInfo BindSparseInfo() {
    VkBindSparseInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
    return info;
}

inline VkFenceCreateInfo FenceCreateInfo() {
    VkFenceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return info;
}

inline VkSemaphoreCreateInfo SemaphoreCreateInfo() {
    VkSemaphoreCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return info;
}

inline VkEventCreateInfo EventCreateInfo() {
    VkEventCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    return info;
}

inline VkQueryPoolCreateInfo QueryPoolCreateInfo() {
    VkQueryPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    return info;
}

inline VkBufferCreateInfo BufferCreateInfo() {
    VkBufferCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    return info;
}

inline VkBufferViewCreateInfo BufferViewCreateInfo() {
    VkBufferViewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    return info;
}

inline VkImageCreateInfo ImageCreateInfo() {
    VkImageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    return info;
}

inline VkImageViewCreateInfo ImageViewCreateInfo() {
    VkImageViewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    return info;
}

inline VkShaderModuleCreateInfo ShaderModuleCreateInfo() {
    VkShaderModuleCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    return info;
}

inline VkPipelineCacheCreateInfo PipelineCacheCreateInfo() {
    VkPipelineCacheCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    return info;
}

inline VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo() {
    VkPipelineShaderStageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    return info;
}

inline VkComputePipelineCreateInfo ComputePipelineCreateInfo() {
    VkComputePipelineCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    return info;
}

inline VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo() {
    VkPipelineVertexInputStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo() {
    VkPipelineInputAssemblyStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo() {
    VkPipelineTessellationStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo() {
    VkPipelineViewportStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo() {
    VkPipelineRasterizationStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo() {
    VkPipelineMultisampleStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo() {
    VkPipelineDepthStencilStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo() {
    VkPipelineColorBlendStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    return info;
}

inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo() {
    VkPipelineDynamicStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    return info;
}

inline VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo() {
    VkGraphicsPipelineCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    return info;
}

inline VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo() {
    VkPipelineLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    return info;
}

inline VkSamplerCreateInfo SamplerCreateInfo() {
    VkSamplerCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    return info;
}

inline VkCopyDescriptorSet CopyDescriptorSet() {
    VkCopyDescriptorSet info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    return info;
}

inline VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo() {
    VkDescriptorPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    return info;
}

inline VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo() {
    VkDescriptorSetAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    return info;
}

inline VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo() {
    VkDescriptorSetLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    return info;
}

inline VkWriteDescriptorSet WriteDescriptorSet() {
    VkWriteDescriptorSet info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    return info;
}

inline VkFramebufferCreateInfo FramebufferCreateInfo() {
    VkFramebufferCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    return info;
}

inline VkRenderPassCreateInfo RenderPassCreateInfo() {
    VkRenderPassCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    return info;
}

inline VkCommandPoolCreateInfo CommandPoolCreateInfo() {
    VkCommandPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    return info;
}

inline VkCommandBufferAllocateInfo CommandBufferAllocateInfo() {
    VkCommandBufferAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    return info;
}

inline VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo() {
    VkCommandBufferInheritanceInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
    return info;
}

inline VkCommandBufferBeginInfo CommandBufferBeginInfo() {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    return info;
}

inline VkRenderPassBeginInfo RenderPassBeginInfo() {
    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    return info;
}

inline VkPhysicalDeviceSubgroupProperties PhysicalDeviceSubgroupProperties() {
    VkPhysicalDeviceSubgroupProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
    return info;
}

inline VkBindBufferMemoryInfo BindBufferMemoryInfo() {
    VkBindBufferMemoryInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO;
    return info;
}

inline VkBindImageMemoryInfo BindImageMemoryInfo() {
    VkBindImageMemoryInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
    return info;
}

inline VkPhysicalDevice16BitStorageFeatures PhysicalDevice16BitStorageFeatures() {
    VkPhysicalDevice16BitStorageFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
    return info;
}

inline VkMemoryDedicatedRequirements MemoryDedicatedRequirements() {
    VkMemoryDedicatedRequirements info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
    return info;
}

inline VkMemoryDedicatedAllocateInfo MemoryDedicatedAllocateInfo() {
    VkMemoryDedicatedAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
    return info;
}

inline VkMemoryAllocateFlagsInfo MemoryAllocateFlagsInfo() {
    VkMemoryAllocateFlagsInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
    return info;
}

inline VkDeviceGroupRenderPassBeginInfo DeviceGroupRenderPassBeginInfo() {
    VkDeviceGroupRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO;
    return info;
}

inline VkDeviceGroupCommandBufferBeginInfo DeviceGroupCommandBufferBeginInfo() {
    VkDeviceGroupCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO;
    return info;
}

inline VkDeviceGroupSubmitInfo DeviceGroupSubmitInfo() {
    VkDeviceGroupSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
    return info;
}

inline VkDeviceGroupBindSparseInfo DeviceGroupBindSparseInfo() {
    VkDeviceGroupBindSparseInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO;
    return info;
}

inline VkBindBufferMemoryDeviceGroupInfo BindBufferMemoryDeviceGroupInfo() {
    VkBindBufferMemoryDeviceGroupInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO;
    return info;
}

inline VkBindImageMemoryDeviceGroupInfo BindImageMemoryDeviceGroupInfo() {
    VkBindImageMemoryDeviceGroupInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO;
    return info;
}

inline VkPhysicalDeviceGroupProperties PhysicalDeviceGroupProperties() {
    VkPhysicalDeviceGroupProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
    return info;
}

inline VkDeviceGroupDeviceCreateInfo DeviceGroupDeviceCreateInfo() {
    VkDeviceGroupDeviceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
    return info;
}

inline VkBufferMemoryRequirementsInfo2 BufferMemoryRequirementsInfo2() {
    VkBufferMemoryRequirementsInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
    return info;
}

inline VkImageMemoryRequirementsInfo2 ImageMemoryRequirementsInfo2() {
    VkImageMemoryRequirementsInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
    return info;
}

inline VkImageSparseMemoryRequirementsInfo2 ImageSparseMemoryRequirementsInfo2() {
    VkImageSparseMemoryRequirementsInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2;
    return info;
}

inline VkMemoryRequirements2 MemoryRequirements2() {
    VkMemoryRequirements2 info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
    return info;
}

inline VkSparseImageMemoryRequirements2 SparseImageMemoryRequirements2() {
    VkSparseImageMemoryRequirements2 info{};
    info.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2;
    return info;
}

inline VkPhysicalDeviceFeatures2 PhysicalDeviceFeatures2() {
    VkPhysicalDeviceFeatures2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    return info;
}

inline VkPhysicalDeviceProperties2 PhysicalDeviceProperties2() {
    VkPhysicalDeviceProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    return info;
}

inline VkFormatProperties2 FormatProperties2() {
    VkFormatProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
    return info;
}

inline VkImageFormatProperties2 ImageFormatProperties2() {
    VkImageFormatProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
    return info;
}

inline VkPhysicalDeviceImageFormatInfo2 PhysicalDeviceImageFormatInfo2() {
    VkPhysicalDeviceImageFormatInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
    return info;
}

inline VkQueueFamilyProperties2 QueueFamilyProperties2() {
    VkQueueFamilyProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
    return info;
}

inline VkPhysicalDeviceMemoryProperties2 PhysicalDeviceMemoryProperties2() {
    VkPhysicalDeviceMemoryProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
    return info;
}

inline VkSparseImageFormatProperties2 SparseImageFormatProperties2() {
    VkSparseImageFormatProperties2 info{};
    info.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2;
    return info;
}

inline VkPhysicalDeviceSparseImageFormatInfo2 PhysicalDeviceSparseImageFormatInfo2() {
    VkPhysicalDeviceSparseImageFormatInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2;
    return info;
}

inline VkPhysicalDevicePointClippingProperties PhysicalDevicePointClippingProperties() {
    VkPhysicalDevicePointClippingProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
    return info;
}

inline VkRenderPassInputAttachmentAspectCreateInfo RenderPassInputAttachmentAspectCreateInfo() {
    VkRenderPassInputAttachmentAspectCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
    return info;
}

inline VkImageViewUsageCreateInfo ImageViewUsageCreateInfo() {
    VkImageViewUsageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
    return info;
}

inline VkPipelineTessellationDomainOriginStateCreateInfo PipelineTessellationDomainOriginStateCreateInfo() {
    VkPipelineTessellationDomainOriginStateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO;
    return info;
}

inline VkRenderPassMultiviewCreateInfo RenderPassMultiviewCreateInfo() {
    VkRenderPassMultiviewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceMultiviewFeatures PhysicalDeviceMultiviewFeatures() {
    VkPhysicalDeviceMultiviewFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
    return info;
}

inline VkPhysicalDeviceMultiviewProperties PhysicalDeviceMultiviewProperties() {
    VkPhysicalDeviceMultiviewProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceVariablePointersFeatures PhysicalDeviceVariablePointersFeatures() {
    VkPhysicalDeviceVariablePointersFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES;
    return info;
}

inline VkPhysicalDeviceProtectedMemoryFeatures PhysicalDeviceProtectedMemoryFeatures() {
    VkPhysicalDeviceProtectedMemoryFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
    return info;
}

inline VkPhysicalDeviceProtectedMemoryProperties PhysicalDeviceProtectedMemoryProperties() {
    VkPhysicalDeviceProtectedMemoryProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES;
    return info;
}

inline VkDeviceQueueInfo2 DeviceQueueInfo2() {
    VkDeviceQueueInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
    return info;
}

inline VkProtectedSubmitInfo ProtectedSubmitInfo() {
    VkProtectedSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
    return info;
}

inline VkSamplerYcbcrConversionCreateInfo SamplerYcbcrConversionCreateInfo() {
    VkSamplerYcbcrConversionCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
    return info;
}

inline VkSamplerYcbcrConversionInfo SamplerYcbcrConversionInfo() {
    VkSamplerYcbcrConversionInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
    return info;
}

inline VkBindImagePlaneMemoryInfo BindImagePlaneMemoryInfo() {
    VkBindImagePlaneMemoryInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
    return info;
}

inline VkImagePlaneMemoryRequirementsInfo ImagePlaneMemoryRequirementsInfo() {
    VkImagePlaneMemoryRequirementsInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO;
    return info;
}

inline VkPhysicalDeviceSamplerYcbcrConversionFeatures PhysicalDeviceSamplerYcbcrConversionFeatures() {
    VkPhysicalDeviceSamplerYcbcrConversionFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
    return info;
}

inline VkSamplerYcbcrConversionImageFormatProperties SamplerYcbcrConversionImageFormatProperties() {
    VkSamplerYcbcrConversionImageFormatProperties info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES;
    return info;
}

inline VkDescriptorUpdateTemplateCreateInfo DescriptorUpdateTemplateCreateInfo() {
    VkDescriptorUpdateTemplateCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceExternalImageFormatInfo PhysicalDeviceExternalImageFormatInfo() {
    VkPhysicalDeviceExternalImageFormatInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO;
    return info;
}

inline VkExternalImageFormatProperties ExternalImageFormatProperties() {
    VkExternalImageFormatProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceExternalBufferInfo PhysicalDeviceExternalBufferInfo() {
    VkPhysicalDeviceExternalBufferInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO;
    return info;
}

inline VkExternalBufferProperties ExternalBufferProperties() {
    VkExternalBufferProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceIDProperties PhysicalDeviceIDProperties() {
    VkPhysicalDeviceIDProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
    return info;
}

inline VkExternalMemoryImageCreateInfo ExternalMemoryImageCreateInfo() {
    VkExternalMemoryImageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
    return info;
}

inline VkExternalMemoryBufferCreateInfo ExternalMemoryBufferCreateInfo() {
    VkExternalMemoryBufferCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO;
    return info;
}

inline VkExportMemoryAllocateInfo ExportMemoryAllocateInfo() {
    VkExportMemoryAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
    return info;
}

inline VkPhysicalDeviceExternalFenceInfo PhysicalDeviceExternalFenceInfo() {
    VkPhysicalDeviceExternalFenceInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO;
    return info;
}

inline VkExternalFenceProperties ExternalFenceProperties() {
    VkExternalFenceProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES;
    return info;
}

inline VkExportFenceCreateInfo ExportFenceCreateInfo() {
    VkExportFenceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO;
    return info;
}

inline VkExportSemaphoreCreateInfo ExportSemaphoreCreateInfo() {
    VkExportSemaphoreCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceExternalSemaphoreInfo PhysicalDeviceExternalSemaphoreInfo() {
    VkPhysicalDeviceExternalSemaphoreInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO;
    return info;
}

inline VkExternalSemaphoreProperties ExternalSemaphoreProperties() {
    VkExternalSemaphoreProperties info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceMaintenance3Properties PhysicalDeviceMaintenance3Properties() {
    VkPhysicalDeviceMaintenance3Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
    return info;
}

inline VkDescriptorSetLayoutSupport DescriptorSetLayoutSupport() {
    VkDescriptorSetLayoutSupport info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT;
    return info;
}

inline VkPhysicalDeviceShaderDrawParametersFeatures PhysicalDeviceShaderDrawParametersFeatures() {
    VkPhysicalDeviceShaderDrawParametersFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
    return info;
}

inline VkPhysicalDeviceVulkan11Features PhysicalDeviceVulkan11Features() {
    VkPhysicalDeviceVulkan11Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    return info;
}

inline VkPhysicalDeviceVulkan11Properties PhysicalDeviceVulkan11Properties() {
    VkPhysicalDeviceVulkan11Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceVulkan12Features PhysicalDeviceVulkan12Features() {
    VkPhysicalDeviceVulkan12Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    return info;
}

inline VkPhysicalDeviceVulkan12Properties PhysicalDeviceVulkan12Properties() {
    VkPhysicalDeviceVulkan12Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
    return info;
}

inline VkImageFormatListCreateInfo ImageFormatListCreateInfo() {
    VkImageFormatListCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO;
    return info;
}

inline VkAttachmentDescription2 AttachmentDescription2() {
    VkAttachmentDescription2 info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
    return info;
}

inline VkAttachmentReference2 AttachmentReference2() {
    VkAttachmentReference2 info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
    return info;
}

inline VkSubpassDescription2 SubpassDescription2() {
    VkSubpassDescription2 info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
    return info;
}

inline VkSubpassDependency2 SubpassDependency2() {
    VkSubpassDependency2 info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
    return info;
}

inline VkRenderPassCreateInfo2 RenderPassCreateInfo2() {
    VkRenderPassCreateInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
    return info;
}

inline VkSubpassBeginInfo SubpassBeginInfo() {
    VkSubpassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO;
    return info;
}

inline VkSubpassEndInfo SubpassEndInfo() {
    VkSubpassEndInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_END_INFO;
    return info;
}

inline VkPhysicalDevice8BitStorageFeatures PhysicalDevice8BitStorageFeatures() {
    VkPhysicalDevice8BitStorageFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES;
    return info;
}

inline VkPhysicalDeviceDriverProperties PhysicalDeviceDriverProperties() {
    VkPhysicalDeviceDriverProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceShaderAtomicInt64Features PhysicalDeviceShaderAtomicInt64Features() {
    VkPhysicalDeviceShaderAtomicInt64Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES;
    return info;
}

inline VkPhysicalDeviceShaderFloat16Int8Features PhysicalDeviceShaderFloat16Int8Features() {
    VkPhysicalDeviceShaderFloat16Int8Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES;
    return info;
}

inline VkPhysicalDeviceFloatControlsProperties PhysicalDeviceFloatControlsProperties() {
    VkPhysicalDeviceFloatControlsProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES;
    return info;
}

inline VkDescriptorSetLayoutBindingFlagsCreateInfo DescriptorSetLayoutBindingFlagsCreateInfo() {
    VkDescriptorSetLayoutBindingFlagsCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceDescriptorIndexingFeatures PhysicalDeviceDescriptorIndexingFeatures() {
    VkPhysicalDeviceDescriptorIndexingFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
    return info;
}

inline VkPhysicalDeviceDescriptorIndexingProperties PhysicalDeviceDescriptorIndexingProperties() {
    VkPhysicalDeviceDescriptorIndexingProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES;
    return info;
}

inline VkDescriptorSetVariableDescriptorCountAllocateInfo DescriptorSetVariableDescriptorCountAllocateInfo() {
    VkDescriptorSetVariableDescriptorCountAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO;
    return info;
}

inline VkDescriptorSetVariableDescriptorCountLayoutSupport DescriptorSetVariableDescriptorCountLayoutSupport() {
    VkDescriptorSetVariableDescriptorCountLayoutSupport info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT;
    return info;
}

inline VkSubpassDescriptionDepthStencilResolve SubpassDescriptionDepthStencilResolve() {
    VkSubpassDescriptionDepthStencilResolve info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
    return info;
}

inline VkPhysicalDeviceDepthStencilResolveProperties PhysicalDeviceDepthStencilResolveProperties() {
    VkPhysicalDeviceDepthStencilResolveProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceScalarBlockLayoutFeatures PhysicalDeviceScalarBlockLayoutFeatures() {
    VkPhysicalDeviceScalarBlockLayoutFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES;
    return info;
}

inline VkImageStencilUsageCreateInfo ImageStencilUsageCreateInfo() {
    VkImageStencilUsageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO;
    return info;
}

inline VkSamplerReductionModeCreateInfo SamplerReductionModeCreateInfo() {
    VkSamplerReductionModeCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceSamplerFilterMinmaxProperties PhysicalDeviceSamplerFilterMinmaxProperties() {
    VkPhysicalDeviceSamplerFilterMinmaxProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceVulkanMemoryModelFeatures PhysicalDeviceVulkanMemoryModelFeatures() {
    VkPhysicalDeviceVulkanMemoryModelFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES;
    return info;
}

inline VkPhysicalDeviceImagelessFramebufferFeatures PhysicalDeviceImagelessFramebufferFeatures() {
    VkPhysicalDeviceImagelessFramebufferFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES;
    return info;
}

inline VkFramebufferAttachmentImageInfo FramebufferAttachmentImageInfo() {
    VkFramebufferAttachmentImageInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO;
    return info;
}

inline VkFramebufferAttachmentsCreateInfo FramebufferAttachmentsCreateInfo() {
    VkFramebufferAttachmentsCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO;
    return info;
}

inline VkRenderPassAttachmentBeginInfo RenderPassAttachmentBeginInfo() {
    VkRenderPassAttachmentBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO;
    return info;
}

inline VkPhysicalDeviceUniformBufferStandardLayoutFeatures PhysicalDeviceUniformBufferStandardLayoutFeatures() {
    VkPhysicalDeviceUniformBufferStandardLayoutFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES;
    return info;
}

inline VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures PhysicalDeviceShaderSubgroupExtendedTypesFeatures() {
    VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
    return info;
}

inline VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures PhysicalDeviceSeparateDepthStencilLayoutsFeatures() {
    VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES;
    return info;
}

inline VkAttachmentReferenceStencilLayout AttachmentReferenceStencilLayout() {
    VkAttachmentReferenceStencilLayout info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT;
    return info;
}

inline VkAttachmentDescriptionStencilLayout AttachmentDescriptionStencilLayout() {
    VkAttachmentDescriptionStencilLayout info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT;
    return info;
}

inline VkPhysicalDeviceHostQueryResetFeatures PhysicalDeviceHostQueryResetFeatures() {
    VkPhysicalDeviceHostQueryResetFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES;
    return info;
}

inline VkPhysicalDeviceTimelineSemaphoreFeatures PhysicalDeviceTimelineSemaphoreFeatures() {
    VkPhysicalDeviceTimelineSemaphoreFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
    return info;
}

inline VkPhysicalDeviceTimelineSemaphoreProperties PhysicalDeviceTimelineSemaphoreProperties() {
    VkPhysicalDeviceTimelineSemaphoreProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES;
    return info;
}

inline VkSemaphoreTypeCreateInfo SemaphoreTypeCreateInfo() {
    VkSemaphoreTypeCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
    return info;
}

inline VkTimelineSemaphoreSubmitInfo TimelineSemaphoreSubmitInfo() {
    VkTimelineSemaphoreSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
    return info;
}

inline VkSemaphoreWaitInfo SemaphoreWaitInfo() {
    VkSemaphoreWaitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
    return info;
}

inline VkSemaphoreSignalInfo SemaphoreSignalInfo() {
    VkSemaphoreSignalInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
    return info;
}

inline VkPhysicalDeviceBufferDeviceAddressFeatures PhysicalDeviceBufferDeviceAddressFeatures() {
    VkPhysicalDeviceBufferDeviceAddressFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
    return info;
}

inline VkBufferDeviceAddressInfo BufferDeviceAddressInfo() {
    VkBufferDeviceAddressInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
    return info;
}

inline VkBufferOpaqueCaptureAddressCreateInfo BufferOpaqueCaptureAddressCreateInfo() {
    VkBufferOpaqueCaptureAddressCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO;
    return info;
}

inline VkMemoryOpaqueCaptureAddressAllocateInfo MemoryOpaqueCaptureAddressAllocateInfo() {
    VkMemoryOpaqueCaptureAddressAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO;
    return info;
}

inline VkDeviceMemoryOpaqueCaptureAddressInfo DeviceMemoryOpaqueCaptureAddressInfo() {
    VkDeviceMemoryOpaqueCaptureAddressInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO;
    return info;
}

inline VkPhysicalDeviceVulkan13Features PhysicalDeviceVulkan13Features() {
    VkPhysicalDeviceVulkan13Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    return info;
}

inline VkPhysicalDeviceVulkan13Properties PhysicalDeviceVulkan13Properties() {
    VkPhysicalDeviceVulkan13Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
    return info;
}

inline VkPipelineCreationFeedbackCreateInfo PipelineCreationFeedbackCreateInfo() {
    VkPipelineCreationFeedbackCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceShaderTerminateInvocationFeatures PhysicalDeviceShaderTerminateInvocationFeatures() {
    VkPhysicalDeviceShaderTerminateInvocationFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES;
    return info;
}

inline VkPhysicalDeviceToolProperties PhysicalDeviceToolProperties() {
    VkPhysicalDeviceToolProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures PhysicalDeviceShaderDemoteToHelperInvocationFeatures() {
    VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES;
    return info;
}

inline VkPhysicalDevicePrivateDataFeatures PhysicalDevicePrivateDataFeatures() {
    VkPhysicalDevicePrivateDataFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES;
    return info;
}

inline VkDevicePrivateDataCreateInfo DevicePrivateDataCreateInfo() {
    VkDevicePrivateDataCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO;
    return info;
}

inline VkPrivateDataSlotCreateInfo PrivateDataSlotCreateInfo() {
    VkPrivateDataSlotCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO;
    return info;
}

inline VkPhysicalDevicePipelineCreationCacheControlFeatures PhysicalDevicePipelineCreationCacheControlFeatures() {
    VkPhysicalDevicePipelineCreationCacheControlFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES;
    return info;
}

inline VkMemoryBarrier2 MemoryBarrier2() {
    VkMemoryBarrier2 info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2;
    return info;
}

inline VkBufferMemoryBarrier2 BufferMemoryBarrier2() {
    VkBufferMemoryBarrier2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2;
    return info;
}

inline VkImageMemoryBarrier2 ImageMemoryBarrier2() {
    VkImageMemoryBarrier2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    return info;
}

inline VkDependencyInfo DependencyInfo() {
    VkDependencyInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    return info;
}

inline VkSemaphoreSubmitInfo SemaphoreSubmitInfo() {
    VkSemaphoreSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    return info;
}

inline VkCommandBufferSubmitInfo CommandBufferSubmitInfo() {
    VkCommandBufferSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
    return info;
}

inline VkSubmitInfo2 SubmitInfo2() {
    VkSubmitInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
    return info;
}

inline VkPhysicalDeviceSynchronization2Features PhysicalDeviceSynchronization2Features() {
    VkPhysicalDeviceSynchronization2Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES;
    return info;
}

inline VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures() {
    VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES;
    return info;
}

inline VkPhysicalDeviceImageRobustnessFeatures PhysicalDeviceImageRobustnessFeatures() {
    VkPhysicalDeviceImageRobustnessFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES;
    return info;
}

inline VkBufferCopy2 BufferCopy2() {
    VkBufferCopy2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COPY_2;
    return info;
}

inline VkCopyBufferInfo2 CopyBufferInfo2() {
    VkCopyBufferInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2;
    return info;
}

inline VkImageCopy2 ImageCopy2() {
    VkImageCopy2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_COPY_2;
    return info;
}

inline VkCopyImageInfo2 CopyImageInfo2() {
    VkCopyImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2;
    return info;
}

inline VkBufferImageCopy2 BufferImageCopy2() {
    VkBufferImageCopy2 info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2;
    return info;
}

inline VkCopyBufferToImageInfo2 CopyBufferToImageInfo2() {
    VkCopyBufferToImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2;
    return info;
}

inline VkCopyImageToBufferInfo2 CopyImageToBufferInfo2() {
    VkCopyImageToBufferInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2;
    return info;
}

inline VkImageBlit2 ImageBlit2() {
    VkImageBlit2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_BLIT_2;
    return info;
}

inline VkBlitImageInfo2 BlitImageInfo2() {
    VkBlitImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2;
    return info;
}

inline VkImageResolve2 ImageResolve2() {
    VkImageResolve2 info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2;
    return info;
}

inline VkResolveImageInfo2 ResolveImageInfo2() {
    VkResolveImageInfo2 info{};
    info.sType = VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2;
    return info;
}

inline VkPhysicalDeviceSubgroupSizeControlFeatures PhysicalDeviceSubgroupSizeControlFeatures() {
    VkPhysicalDeviceSubgroupSizeControlFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES;
    return info;
}

inline VkPhysicalDeviceSubgroupSizeControlProperties PhysicalDeviceSubgroupSizeControlProperties() {
    VkPhysicalDeviceSubgroupSizeControlProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES;
    return info;
}

inline VkPipelineShaderStageRequiredSubgroupSizeCreateInfo PipelineShaderStageRequiredSubgroupSizeCreateInfo() {
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceInlineUniformBlockFeatures PhysicalDeviceInlineUniformBlockFeatures() {
    VkPhysicalDeviceInlineUniformBlockFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES;
    return info;
}

inline VkPhysicalDeviceInlineUniformBlockProperties PhysicalDeviceInlineUniformBlockProperties() {
    VkPhysicalDeviceInlineUniformBlockProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES;
    return info;
}

inline VkWriteDescriptorSetInlineUniformBlock WriteDescriptorSetInlineUniformBlock() {
    VkWriteDescriptorSetInlineUniformBlock info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK;
    return info;
}

inline VkDescriptorPoolInlineUniformBlockCreateInfo DescriptorPoolInlineUniformBlockCreateInfo() {
    VkDescriptorPoolInlineUniformBlockCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceTextureCompressionASTCHDRFeatures PhysicalDeviceTextureCompressionASTCHDRFeatures() {
    VkPhysicalDeviceTextureCompressionASTCHDRFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES;
    return info;
}

inline VkRenderingAttachmentInfo RenderingAttachmentInfo() {
    VkRenderingAttachmentInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    return info;
}

inline VkRenderingInfo RenderingInfo() {
    VkRenderingInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    return info;
}

inline VkPipelineRenderingCreateInfo PipelineRenderingCreateInfo() {
    VkPipelineRenderingCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
    return info;
}

inline VkPhysicalDeviceDynamicRenderingFeatures PhysicalDeviceDynamicRenderingFeatures() {
    VkPhysicalDeviceDynamicRenderingFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
    return info;
}

inline VkCommandBufferInheritanceRenderingInfo CommandBufferInheritanceRenderingInfo() {
    VkCommandBufferInheritanceRenderingInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO;
    return info;
}

inline VkPhysicalDeviceShaderIntegerDotProductFeatures PhysicalDeviceShaderIntegerDotProductFeatures() {
    VkPhysicalDeviceShaderIntegerDotProductFeatures info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES;
    return info;
}

inline VkPhysicalDeviceShaderIntegerDotProductProperties PhysicalDeviceShaderIntegerDotProductProperties() {
    VkPhysicalDeviceShaderIntegerDotProductProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES;
    return info;
}

inline VkPhysicalDeviceTexelBufferAlignmentProperties PhysicalDeviceTexelBufferAlignmentProperties() {
    VkPhysicalDeviceTexelBufferAlignmentProperties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES;
    return info;
}

inline VkFormatProperties3 FormatProperties3() {
    VkFormatProperties3 info{};
    info.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3;
    return info;
}

inline VkPhysicalDeviceMaintenance4Features PhysicalDeviceMaintenance4Features() {
    VkPhysicalDeviceMaintenance4Features info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES;
    return info;
}

inline VkPhysicalDeviceMaintenance4Properties PhysicalDeviceMaintenance4Properties() {
    VkPhysicalDeviceMaintenance4Properties info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES;
    return info;
}

inline VkDeviceBufferMemoryRequirements DeviceBufferMemoryRequirements() {
    VkDeviceBufferMemoryRequirements info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS;
    return info;
}

inline VkDeviceImageMemoryRequirements DeviceImageMemoryRequirements() {
    VkDeviceImageMemoryRequirements info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS;
    return info;
}

inline VkSwapchainCreateInfoKHR SwapchainCreateInfoKHR() {
    VkSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    return info;
}

inline VkPresentInfoKHR PresentInfoKHR() {
    VkPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    return info;
}

inline VkImageSwapchainCreateInfoKHR ImageSwapchainCreateInfoKHR() {
    VkImageSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR;
    return info;
}

inline VkBindImageMemorySwapchainInfoKHR BindImageMemorySwapchainInfoKHR() {
    VkBindImageMemorySwapchainInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR;
    return info;
}

inline VkAcquireNextImageInfoKHR AcquireNextImageInfoKHR() {
    VkAcquireNextImageInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
    return info;
}

inline VkDeviceGroupPresentCapabilitiesKHR DeviceGroupPresentCapabilitiesKHR() {
    VkDeviceGroupPresentCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR;
    return info;
}

inline VkDeviceGroupPresentInfoKHR DeviceGroupPresentInfoKHR() {
    VkDeviceGroupPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR;
    return info;
}

inline VkDeviceGroupSwapchainCreateInfoKHR DeviceGroupSwapchainCreateInfoKHR() {
    VkDeviceGroupSwapchainCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
    return info;
}

inline VkDisplayModeCreateInfoKHR DisplayModeCreateInfoKHR() {
    VkDisplayModeCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
    return info;
}

inline VkDisplaySurfaceCreateInfoKHR DisplaySurfaceCreateInfoKHR() {
    VkDisplaySurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    return info;
}

inline VkDisplayPresentInfoKHR DisplayPresentInfoKHR() {
    VkDisplayPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR;
    return info;
}

#ifdef VK_USE_PLATFORM_XLIB_KHR
inline VkXlibSurfaceCreateInfoKHR XlibSurfaceCreateInfoKHR() {
    VkXlibSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_XLIB_KHR

#ifdef VK_USE_PLATFORM_XCB_KHR
inline VkXcbSurfaceCreateInfoKHR XcbSurfaceCreateInfoKHR() {
    VkXcbSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_XCB_KHR

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
inline VkWaylandSurfaceCreateInfoKHR WaylandSurfaceCreateInfoKHR() {
    VkWaylandSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_WAYLAND_KHR

#ifdef VK_USE_PLATFORM_ANDROID_KHR
inline VkAndroidSurfaceCreateInfoKHR AndroidSurfaceCreateInfoKHR() {
    VkAndroidSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_ANDROID_KHR

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkWin32SurfaceCreateInfoKHR Win32SurfaceCreateInfoKHR() {
    VkWin32SurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkQueueFamilyQueryResultStatusPropertiesKHR QueueFamilyQueryResultStatusPropertiesKHR() {
    VkQueueFamilyQueryResultStatusPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_KHR;
    return info;
}

inline VkQueueFamilyVideoPropertiesKHR QueueFamilyVideoPropertiesKHR() {
    VkQueueFamilyVideoPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR;
    return info;
}

inline VkVideoProfileInfoKHR VideoProfileInfoKHR() {
    VkVideoProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
    return info;
}

inline VkVideoProfileListInfoKHR VideoProfileListInfoKHR() {
    VkVideoProfileListInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
    return info;
}

inline VkVideoCapabilitiesKHR VideoCapabilitiesKHR() {
    VkVideoCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;
    return info;
}

inline VkPhysicalDeviceVideoFormatInfoKHR PhysicalDeviceVideoFormatInfoKHR() {
    VkPhysicalDeviceVideoFormatInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
    return info;
}

inline VkVideoFormatPropertiesKHR VideoFormatPropertiesKHR() {
    VkVideoFormatPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR;
    return info;
}

inline VkVideoPictureResourceInfoKHR VideoPictureResourceInfoKHR() {
    VkVideoPictureResourceInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
    return info;
}

inline VkVideoReferenceSlotInfoKHR VideoReferenceSlotInfoKHR() {
    VkVideoReferenceSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
    return info;
}

inline VkVideoSessionMemoryRequirementsKHR VideoSessionMemoryRequirementsKHR() {
    VkVideoSessionMemoryRequirementsKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
    return info;
}

inline VkBindVideoSessionMemoryInfoKHR BindVideoSessionMemoryInfoKHR() {
    VkBindVideoSessionMemoryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR;
    return info;
}

inline VkVideoSessionCreateInfoKHR VideoSessionCreateInfoKHR() {
    VkVideoSessionCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR;
    return info;
}

inline VkVideoSessionParametersCreateInfoKHR VideoSessionParametersCreateInfoKHR() {
    VkVideoSessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
    return info;
}

inline VkVideoSessionParametersUpdateInfoKHR VideoSessionParametersUpdateInfoKHR() {
    VkVideoSessionParametersUpdateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR;
    return info;
}

inline VkVideoBeginCodingInfoKHR VideoBeginCodingInfoKHR() {
    VkVideoBeginCodingInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR;
    return info;
}

inline VkVideoEndCodingInfoKHR VideoEndCodingInfoKHR() {
    VkVideoEndCodingInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;
    return info;
}

inline VkVideoCodingControlInfoKHR VideoCodingControlInfoKHR() {
    VkVideoCodingControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR;
    return info;
}

inline VkVideoDecodeCapabilitiesKHR VideoDecodeCapabilitiesKHR() {
    VkVideoDecodeCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
    return info;
}

inline VkVideoDecodeUsageInfoKHR VideoDecodeUsageInfoKHR() {
    VkVideoDecodeUsageInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR;
    return info;
}

inline VkVideoDecodeInfoKHR VideoDecodeInfoKHR() {
    VkVideoDecodeInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264CapabilitiesKHR VideoEncodeH264CapabilitiesKHR() {
    VkVideoEncodeH264CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_KHR;
    return info;
}

inline VkVideoEncodeH264QualityLevelPropertiesKHR VideoEncodeH264QualityLevelPropertiesKHR() {
    VkVideoEncodeH264QualityLevelPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_QUALITY_LEVEL_PROPERTIES_KHR;
    return info;
}

inline VkVideoEncodeH264SessionCreateInfoKHR VideoEncodeH264SessionCreateInfoKHR() {
    VkVideoEncodeH264SessionCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_CREATE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264SessionParametersAddInfoKHR VideoEncodeH264SessionParametersAddInfoKHR() {
    VkVideoEncodeH264SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264SessionParametersCreateInfoKHR VideoEncodeH264SessionParametersCreateInfoKHR() {
    VkVideoEncodeH264SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264SessionParametersGetInfoKHR VideoEncodeH264SessionParametersGetInfoKHR() {
    VkVideoEncodeH264SessionParametersGetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_GET_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264SessionParametersFeedbackInfoKHR VideoEncodeH264SessionParametersFeedbackInfoKHR() {
    VkVideoEncodeH264SessionParametersFeedbackInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_FEEDBACK_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264NaluSliceInfoKHR VideoEncodeH264NaluSliceInfoKHR() {
    VkVideoEncodeH264NaluSliceInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_NALU_SLICE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264PictureInfoKHR VideoEncodeH264PictureInfoKHR() {
    VkVideoEncodeH264PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PICTURE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264DpbSlotInfoKHR VideoEncodeH264DpbSlotInfoKHR() {
    VkVideoEncodeH264DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_DPB_SLOT_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264ProfileInfoKHR VideoEncodeH264ProfileInfoKHR() {
    VkVideoEncodeH264ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264RateControlInfoKHR VideoEncodeH264RateControlInfoKHR() {
    VkVideoEncodeH264RateControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264RateControlLayerInfoKHR VideoEncodeH264RateControlLayerInfoKHR() {
    VkVideoEncodeH264RateControlLayerInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_LAYER_INFO_KHR;
    return info;
}

inline VkVideoEncodeH264GopRemainingFrameInfoKHR VideoEncodeH264GopRemainingFrameInfoKHR() {
    VkVideoEncodeH264GopRemainingFrameInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_GOP_REMAINING_FRAME_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265CapabilitiesKHR VideoEncodeH265CapabilitiesKHR() {
    VkVideoEncodeH265CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_CAPABILITIES_KHR;
    return info;
}

inline VkVideoEncodeH265SessionCreateInfoKHR VideoEncodeH265SessionCreateInfoKHR() {
    VkVideoEncodeH265SessionCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_CREATE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265QualityLevelPropertiesKHR VideoEncodeH265QualityLevelPropertiesKHR() {
    VkVideoEncodeH265QualityLevelPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_QUALITY_LEVEL_PROPERTIES_KHR;
    return info;
}

inline VkVideoEncodeH265SessionParametersAddInfoKHR VideoEncodeH265SessionParametersAddInfoKHR() {
    VkVideoEncodeH265SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265SessionParametersCreateInfoKHR VideoEncodeH265SessionParametersCreateInfoKHR() {
    VkVideoEncodeH265SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265SessionParametersGetInfoKHR VideoEncodeH265SessionParametersGetInfoKHR() {
    VkVideoEncodeH265SessionParametersGetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_GET_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265SessionParametersFeedbackInfoKHR VideoEncodeH265SessionParametersFeedbackInfoKHR() {
    VkVideoEncodeH265SessionParametersFeedbackInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_FEEDBACK_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265NaluSliceSegmentInfoKHR VideoEncodeH265NaluSliceSegmentInfoKHR() {
    VkVideoEncodeH265NaluSliceSegmentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_NALU_SLICE_SEGMENT_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265PictureInfoKHR VideoEncodeH265PictureInfoKHR() {
    VkVideoEncodeH265PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PICTURE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265DpbSlotInfoKHR VideoEncodeH265DpbSlotInfoKHR() {
    VkVideoEncodeH265DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_DPB_SLOT_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265ProfileInfoKHR VideoEncodeH265ProfileInfoKHR() {
    VkVideoEncodeH265ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PROFILE_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265RateControlInfoKHR VideoEncodeH265RateControlInfoKHR() {
    VkVideoEncodeH265RateControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265RateControlLayerInfoKHR VideoEncodeH265RateControlLayerInfoKHR() {
    VkVideoEncodeH265RateControlLayerInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_LAYER_INFO_KHR;
    return info;
}

inline VkVideoEncodeH265GopRemainingFrameInfoKHR VideoEncodeH265GopRemainingFrameInfoKHR() {
    VkVideoEncodeH265GopRemainingFrameInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_GOP_REMAINING_FRAME_INFO_KHR;
    return info;
}

inline VkVideoDecodeH264ProfileInfoKHR VideoDecodeH264ProfileInfoKHR() {
    VkVideoDecodeH264ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR;
    return info;
}

inline VkVideoDecodeH264CapabilitiesKHR VideoDecodeH264CapabilitiesKHR() {
    VkVideoDecodeH264CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR;
    return info;
}

inline VkVideoDecodeH264SessionParametersAddInfoKHR VideoDecodeH264SessionParametersAddInfoKHR() {
    VkVideoDecodeH264SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
    return info;
}

inline VkVideoDecodeH264SessionParametersCreateInfoKHR VideoDecodeH264SessionParametersCreateInfoKHR() {
    VkVideoDecodeH264SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
    return info;
}

inline VkVideoDecodeH264PictureInfoKHR VideoDecodeH264PictureInfoKHR() {
    VkVideoDecodeH264PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;
    return info;
}

inline VkVideoDecodeH264DpbSlotInfoKHR VideoDecodeH264DpbSlotInfoKHR() {
    VkVideoDecodeH264DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
    return info;
}

inline VkRenderingFragmentShadingRateAttachmentInfoKHR RenderingFragmentShadingRateAttachmentInfoKHR() {
    VkRenderingFragmentShadingRateAttachmentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
    return info;
}

inline VkRenderingFragmentDensityMapAttachmentInfoEXT RenderingFragmentDensityMapAttachmentInfoEXT() {
    VkRenderingFragmentDensityMapAttachmentInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT;
    return info;
}

inline VkAttachmentSampleCountInfoAMD AttachmentSampleCountInfoAMD() {
    VkAttachmentSampleCountInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD;
    return info;
}

inline VkMultiviewPerViewAttributesInfoNVX MultiviewPerViewAttributesInfoNVX() {
    VkMultiviewPerViewAttributesInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkImportMemoryWin32HandleInfoKHR ImportMemoryWin32HandleInfoKHR() {
    VkImportMemoryWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
    return info;
}

inline VkExportMemoryWin32HandleInfoKHR ExportMemoryWin32HandleInfoKHR() {
    VkExportMemoryWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
    return info;
}

inline VkMemoryWin32HandlePropertiesKHR MemoryWin32HandlePropertiesKHR() {
    VkMemoryWin32HandlePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR;
    return info;
}

inline VkMemoryGetWin32HandleInfoKHR MemoryGetWin32HandleInfoKHR() {
    VkMemoryGetWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkImportMemoryFdInfoKHR ImportMemoryFdInfoKHR() {
    VkImportMemoryFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
    return info;
}

inline VkMemoryFdPropertiesKHR MemoryFdPropertiesKHR() {
    VkMemoryFdPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;
    return info;
}

inline VkMemoryGetFdInfoKHR MemoryGetFdInfoKHR() {
    VkMemoryGetFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkWin32KeyedMutexAcquireReleaseInfoKHR Win32KeyedMutexAcquireReleaseInfoKHR() {
    VkWin32KeyedMutexAcquireReleaseInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR;
    return info;
}

inline VkImportSemaphoreWin32HandleInfoKHR ImportSemaphoreWin32HandleInfoKHR() {
    VkImportSemaphoreWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    return info;
}

inline VkExportSemaphoreWin32HandleInfoKHR ExportSemaphoreWin32HandleInfoKHR() {
    VkExportSemaphoreWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    return info;
}

inline VkD3D12FenceSubmitInfoKHR D3D12FenceSubmitInfoKHR() {
    VkD3D12FenceSubmitInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR;
    return info;
}

inline VkSemaphoreGetWin32HandleInfoKHR SemaphoreGetWin32HandleInfoKHR() {
    VkSemaphoreGetWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkImportSemaphoreFdInfoKHR ImportSemaphoreFdInfoKHR() {
    VkImportSemaphoreFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR;
    return info;
}

inline VkSemaphoreGetFdInfoKHR SemaphoreGetFdInfoKHR() {
    VkSemaphoreGetFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR;
    return info;
}

inline VkPhysicalDevicePushDescriptorPropertiesKHR PhysicalDevicePushDescriptorPropertiesKHR() {
    VkPhysicalDevicePushDescriptorPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
    return info;
}

inline VkPresentRegionsKHR PresentRegionsKHR() {
    VkPresentRegionsKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR;
    return info;
}

inline VkSharedPresentSurfaceCapabilitiesKHR SharedPresentSurfaceCapabilitiesKHR() {
    VkSharedPresentSurfaceCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkImportFenceWin32HandleInfoKHR ImportFenceWin32HandleInfoKHR() {
    VkImportFenceWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR;
    return info;
}

inline VkExportFenceWin32HandleInfoKHR ExportFenceWin32HandleInfoKHR() {
    VkExportFenceWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR;
    return info;
}

inline VkFenceGetWin32HandleInfoKHR FenceGetWin32HandleInfoKHR() {
    VkFenceGetWin32HandleInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkImportFenceFdInfoKHR ImportFenceFdInfoKHR() {
    VkImportFenceFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR;
    return info;
}

inline VkFenceGetFdInfoKHR FenceGetFdInfoKHR() {
    VkFenceGetFdInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR;
    return info;
}

inline VkPhysicalDevicePerformanceQueryFeaturesKHR PhysicalDevicePerformanceQueryFeaturesKHR() {
    VkPhysicalDevicePerformanceQueryFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR;
    return info;
}

inline VkPhysicalDevicePerformanceQueryPropertiesKHR PhysicalDevicePerformanceQueryPropertiesKHR() {
    VkPhysicalDevicePerformanceQueryPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR;
    return info;
}

inline VkPerformanceCounterKHR PerformanceCounterKHR() {
    VkPerformanceCounterKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR;
    return info;
}

inline VkPerformanceCounterDescriptionKHR PerformanceCounterDescriptionKHR() {
    VkPerformanceCounterDescriptionKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR;
    return info;
}

inline VkQueryPoolPerformanceCreateInfoKHR QueryPoolPerformanceCreateInfoKHR() {
    VkQueryPoolPerformanceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR;
    return info;
}

inline VkAcquireProfilingLockInfoKHR AcquireProfilingLockInfoKHR() {
    VkAcquireProfilingLockInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR;
    return info;
}

inline VkPerformanceQuerySubmitInfoKHR PerformanceQuerySubmitInfoKHR() {
    VkPerformanceQuerySubmitInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceSurfaceInfo2KHR PhysicalDeviceSurfaceInfo2KHR() {
    VkPhysicalDeviceSurfaceInfo2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
    return info;
}

inline VkSurfaceCapabilities2KHR SurfaceCapabilities2KHR() {
    VkSurfaceCapabilities2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
    return info;
}

inline VkSurfaceFormat2KHR SurfaceFormat2KHR() {
    VkSurfaceFormat2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
    return info;
}

inline VkDisplayProperties2KHR DisplayProperties2KHR() {
    VkDisplayProperties2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR;
    return info;
}

inline VkDisplayPlaneProperties2KHR DisplayPlaneProperties2KHR() {
    VkDisplayPlaneProperties2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR;
    return info;
}

inline VkDisplayModeProperties2KHR DisplayModeProperties2KHR() {
    VkDisplayModeProperties2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR;
    return info;
}

inline VkDisplayPlaneInfo2KHR DisplayPlaneInfo2KHR() {
    VkDisplayPlaneInfo2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR;
    return info;
}

inline VkDisplayPlaneCapabilities2KHR DisplayPlaneCapabilities2KHR() {
    VkDisplayPlaneCapabilities2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR;
    return info;
}

#ifdef VK_ENABLE_BETA_EXTENSIONS
inline VkPhysicalDevicePortabilitySubsetFeaturesKHR PhysicalDevicePortabilitySubsetFeaturesKHR() {
    VkPhysicalDevicePortabilitySubsetFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR;
    return info;
}

inline VkPhysicalDevicePortabilitySubsetPropertiesKHR PhysicalDevicePortabilitySubsetPropertiesKHR() {
    VkPhysicalDevicePortabilitySubsetPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_PROPERTIES_KHR;
    return info;
}
#endif // VK_ENABLE_BETA_EXTENSIONS

inline VkPhysicalDeviceShaderClockFeaturesKHR PhysicalDeviceShaderClockFeaturesKHR() {
    VkPhysicalDeviceShaderClockFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR;
    return info;
}

inline VkVideoDecodeH265ProfileInfoKHR VideoDecodeH265ProfileInfoKHR() {
    VkVideoDecodeH265ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
    return info;
}

inline VkVideoDecodeH265CapabilitiesKHR VideoDecodeH265CapabilitiesKHR() {
    VkVideoDecodeH265CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
    return info;
}

inline VkVideoDecodeH265SessionParametersAddInfoKHR VideoDecodeH265SessionParametersAddInfoKHR() {
    VkVideoDecodeH265SessionParametersAddInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
    return info;
}

inline VkVideoDecodeH265SessionParametersCreateInfoKHR VideoDecodeH265SessionParametersCreateInfoKHR() {
    VkVideoDecodeH265SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
    return info;
}

inline VkVideoDecodeH265PictureInfoKHR VideoDecodeH265PictureInfoKHR() {
    VkVideoDecodeH265PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
    return info;
}

inline VkVideoDecodeH265DpbSlotInfoKHR VideoDecodeH265DpbSlotInfoKHR() {
    VkVideoDecodeH265DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
    return info;
}

inline VkDeviceQueueGlobalPriorityCreateInfoKHR DeviceQueueGlobalPriorityCreateInfoKHR() {
    VkDeviceQueueGlobalPriorityCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR PhysicalDeviceGlobalPriorityQueryFeaturesKHR() {
    VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES_KHR;
    return info;
}

inline VkQueueFamilyGlobalPriorityPropertiesKHR QueueFamilyGlobalPriorityPropertiesKHR() {
    VkQueueFamilyGlobalPriorityPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_GLOBAL_PRIORITY_PROPERTIES_KHR;
    return info;
}

inline VkFragmentShadingRateAttachmentInfoKHR FragmentShadingRateAttachmentInfoKHR() {
    VkFragmentShadingRateAttachmentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
    return info;
}

inline VkPipelineFragmentShadingRateStateCreateInfoKHR PipelineFragmentShadingRateStateCreateInfoKHR() {
    VkPipelineFragmentShadingRateStateCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateFeaturesKHR PhysicalDeviceFragmentShadingRateFeaturesKHR() {
    VkPhysicalDeviceFragmentShadingRateFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRatePropertiesKHR PhysicalDeviceFragmentShadingRatePropertiesKHR() {
    VkPhysicalDeviceFragmentShadingRatePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateKHR PhysicalDeviceFragmentShadingRateKHR() {
    VkPhysicalDeviceFragmentShadingRateKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR;
    return info;
}

inline VkPhysicalDeviceDynamicRenderingLocalReadFeaturesKHR PhysicalDeviceDynamicRenderingLocalReadFeaturesKHR() {
    VkPhysicalDeviceDynamicRenderingLocalReadFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_LOCAL_READ_FEATURES_KHR;
    return info;
}

inline VkRenderingAttachmentLocationInfoKHR RenderingAttachmentLocationInfoKHR() {
    VkRenderingAttachmentLocationInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_LOCATION_INFO_KHR;
    return info;
}

inline VkRenderingInputAttachmentIndexInfoKHR RenderingInputAttachmentIndexInfoKHR() {
    VkRenderingInputAttachmentIndexInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INPUT_ATTACHMENT_INDEX_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceShaderQuadControlFeaturesKHR PhysicalDeviceShaderQuadControlFeaturesKHR() {
    VkPhysicalDeviceShaderQuadControlFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_QUAD_CONTROL_FEATURES_KHR;
    return info;
}

inline VkSurfaceProtectedCapabilitiesKHR SurfaceProtectedCapabilitiesKHR() {
    VkSurfaceProtectedCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR;
    return info;
}

inline VkPhysicalDevicePresentWaitFeaturesKHR PhysicalDevicePresentWaitFeaturesKHR() {
    VkPhysicalDevicePresentWaitFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR;
    return info;
}

inline VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR PhysicalDevicePipelineExecutablePropertiesFeaturesKHR() {
    VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR;
    return info;
}

inline VkPipelineInfoKHR PipelineInfoKHR() {
    VkPipelineInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR;
    return info;
}

inline VkPipelineExecutablePropertiesKHR PipelineExecutablePropertiesKHR() {
    VkPipelineExecutablePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR;
    return info;
}

inline VkPipelineExecutableInfoKHR PipelineExecutableInfoKHR() {
    VkPipelineExecutableInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR;
    return info;
}

inline VkPipelineExecutableStatisticKHR PipelineExecutableStatisticKHR() {
    VkPipelineExecutableStatisticKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR;
    return info;
}

inline VkPipelineExecutableInternalRepresentationKHR PipelineExecutableInternalRepresentationKHR() {
    VkPipelineExecutableInternalRepresentationKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR;
    return info;
}

inline VkMemoryMapInfoKHR MemoryMapInfoKHR() {
    VkMemoryMapInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_MAP_INFO_KHR;
    return info;
}

inline VkMemoryUnmapInfoKHR MemoryUnmapInfoKHR() {
    VkMemoryUnmapInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_UNMAP_INFO_KHR;
    return info;
}

inline VkPipelineLibraryCreateInfoKHR PipelineLibraryCreateInfoKHR() {
    VkPipelineLibraryCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR;
    return info;
}

inline VkPresentIdKHR PresentIdKHR() {
    VkPresentIdKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_ID_KHR;
    return info;
}

inline VkPhysicalDevicePresentIdFeaturesKHR PhysicalDevicePresentIdFeaturesKHR() {
    VkPhysicalDevicePresentIdFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR;
    return info;
}

inline VkVideoEncodeInfoKHR VideoEncodeInfoKHR() {
    VkVideoEncodeInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_INFO_KHR;
    return info;
}

inline VkVideoEncodeCapabilitiesKHR VideoEncodeCapabilitiesKHR() {
    VkVideoEncodeCapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_CAPABILITIES_KHR;
    return info;
}

inline VkQueryPoolVideoEncodeFeedbackCreateInfoKHR QueryPoolVideoEncodeFeedbackCreateInfoKHR() {
    VkQueryPoolVideoEncodeFeedbackCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR;
    return info;
}

inline VkVideoEncodeUsageInfoKHR VideoEncodeUsageInfoKHR() {
    VkVideoEncodeUsageInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_USAGE_INFO_KHR;
    return info;
}

inline VkVideoEncodeRateControlLayerInfoKHR VideoEncodeRateControlLayerInfoKHR() {
    VkVideoEncodeRateControlLayerInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_LAYER_INFO_KHR;
    return info;
}

inline VkVideoEncodeRateControlInfoKHR VideoEncodeRateControlInfoKHR() {
    VkVideoEncodeRateControlInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR PhysicalDeviceVideoEncodeQualityLevelInfoKHR() {
    VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_QUALITY_LEVEL_INFO_KHR;
    return info;
}

inline VkVideoEncodeQualityLevelPropertiesKHR VideoEncodeQualityLevelPropertiesKHR() {
    VkVideoEncodeQualityLevelPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUALITY_LEVEL_PROPERTIES_KHR;
    return info;
}

inline VkVideoEncodeQualityLevelInfoKHR VideoEncodeQualityLevelInfoKHR() {
    VkVideoEncodeQualityLevelInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUALITY_LEVEL_INFO_KHR;
    return info;
}

inline VkVideoEncodeSessionParametersGetInfoKHR VideoEncodeSessionParametersGetInfoKHR() {
    VkVideoEncodeSessionParametersGetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_PARAMETERS_GET_INFO_KHR;
    return info;
}

inline VkVideoEncodeSessionParametersFeedbackInfoKHR VideoEncodeSessionParametersFeedbackInfoKHR() {
    VkVideoEncodeSessionParametersFeedbackInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_PARAMETERS_FEEDBACK_INFO_KHR;
    return info;
}

inline VkQueueFamilyCheckpointProperties2NV QueueFamilyCheckpointProperties2NV() {
    VkQueueFamilyCheckpointProperties2NV info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV;
    return info;
}

inline VkCheckpointData2NV CheckpointData2NV() {
    VkCheckpointData2NV info{};
    info.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV;
    return info;
}

inline VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR PhysicalDeviceFragmentShaderBarycentricFeaturesKHR() {
    VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR PhysicalDeviceFragmentShaderBarycentricPropertiesKHR() {
    VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_PROPERTIES_KHR;
    return info;
}

inline VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR PhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR() {
    VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR() {
    VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR PhysicalDeviceRayTracingMaintenance1FeaturesKHR() {
    VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR PhysicalDeviceShaderSubgroupRotateFeaturesKHR() {
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_ROTATE_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR PhysicalDeviceShaderMaximalReconvergenceFeaturesKHR() {
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceMaintenance5FeaturesKHR PhysicalDeviceMaintenance5FeaturesKHR() {
    VkPhysicalDeviceMaintenance5FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceMaintenance5PropertiesKHR PhysicalDeviceMaintenance5PropertiesKHR() {
    VkPhysicalDeviceMaintenance5PropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_PROPERTIES_KHR;
    return info;
}

inline VkRenderingAreaInfoKHR RenderingAreaInfoKHR() {
    VkRenderingAreaInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_AREA_INFO_KHR;
    return info;
}

inline VkImageSubresource2KHR ImageSubresource2KHR() {
    VkImageSubresource2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_SUBRESOURCE_2_KHR;
    return info;
}

inline VkDeviceImageSubresourceInfoKHR DeviceImageSubresourceInfoKHR() {
    VkDeviceImageSubresourceInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_SUBRESOURCE_INFO_KHR;
    return info;
}

inline VkSubresourceLayout2KHR SubresourceLayout2KHR() {
    VkSubresourceLayout2KHR info{};
    info.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_LAYOUT_2_KHR;
    return info;
}

inline VkPipelineCreateFlags2CreateInfoKHR PipelineCreateFlags2CreateInfoKHR() {
    VkPipelineCreateFlags2CreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR;
    return info;
}

inline VkBufferUsageFlags2CreateInfoKHR BufferUsageFlags2CreateInfoKHR() {
    VkBufferUsageFlags2CreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_USAGE_FLAGS_2_CREATE_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR PhysicalDeviceRayTracingPositionFetchFeaturesKHR() {
    VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_POSITION_FETCH_FEATURES_KHR;
    return info;
}

inline VkCooperativeMatrixPropertiesKHR CooperativeMatrixPropertiesKHR() {
    VkCooperativeMatrixPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixFeaturesKHR PhysicalDeviceCooperativeMatrixFeaturesKHR() {
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixPropertiesKHR PhysicalDeviceCooperativeMatrixPropertiesKHR() {
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR;
    return info;
}

inline VkVideoDecodeAV1ProfileInfoKHR VideoDecodeAV1ProfileInfoKHR() {
    VkVideoDecodeAV1ProfileInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PROFILE_INFO_KHR;
    return info;
}

inline VkVideoDecodeAV1CapabilitiesKHR VideoDecodeAV1CapabilitiesKHR() {
    VkVideoDecodeAV1CapabilitiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_CAPABILITIES_KHR;
    return info;
}

inline VkVideoDecodeAV1SessionParametersCreateInfoKHR VideoDecodeAV1SessionParametersCreateInfoKHR() {
    VkVideoDecodeAV1SessionParametersCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_SESSION_PARAMETERS_CREATE_INFO_KHR;
    return info;
}

inline VkVideoDecodeAV1PictureInfoKHR VideoDecodeAV1PictureInfoKHR() {
    VkVideoDecodeAV1PictureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PICTURE_INFO_KHR;
    return info;
}

inline VkVideoDecodeAV1DpbSlotInfoKHR VideoDecodeAV1DpbSlotInfoKHR() {
    VkVideoDecodeAV1DpbSlotInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_DPB_SLOT_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceVideoMaintenance1FeaturesKHR PhysicalDeviceVideoMaintenance1FeaturesKHR() {
    VkPhysicalDeviceVideoMaintenance1FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR;
    return info;
}

inline VkVideoInlineQueryInfoKHR VideoInlineQueryInfoKHR() {
    VkVideoInlineQueryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_VIDEO_INLINE_QUERY_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR PhysicalDeviceVertexAttributeDivisorPropertiesKHR() {
    VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_KHR;
    return info;
}

inline VkPipelineVertexInputDivisorStateCreateInfoKHR PipelineVertexInputDivisorStateCreateInfoKHR() {
    VkPipelineVertexInputDivisorStateCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR PhysicalDeviceVertexAttributeDivisorFeaturesKHR() {
    VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceShaderFloatControls2FeaturesKHR PhysicalDeviceShaderFloatControls2FeaturesKHR() {
    VkPhysicalDeviceShaderFloatControls2FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT_CONTROLS_2_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceIndexTypeUint8FeaturesKHR PhysicalDeviceIndexTypeUint8FeaturesKHR() {
    VkPhysicalDeviceIndexTypeUint8FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceLineRasterizationFeaturesKHR PhysicalDeviceLineRasterizationFeaturesKHR() {
    VkPhysicalDeviceLineRasterizationFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceLineRasterizationPropertiesKHR PhysicalDeviceLineRasterizationPropertiesKHR() {
    VkPhysicalDeviceLineRasterizationPropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES_KHR;
    return info;
}

inline VkPipelineRasterizationLineStateCreateInfoKHR PipelineRasterizationLineStateCreateInfoKHR() {
    VkPipelineRasterizationLineStateCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_KHR;
    return info;
}

inline VkCalibratedTimestampInfoKHR CalibratedTimestampInfoKHR() {
    VkCalibratedTimestampInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceShaderExpectAssumeFeaturesKHR PhysicalDeviceShaderExpectAssumeFeaturesKHR() {
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceMaintenance6FeaturesKHR PhysicalDeviceMaintenance6FeaturesKHR() {
    VkPhysicalDeviceMaintenance6FeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_6_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceMaintenance6PropertiesKHR PhysicalDeviceMaintenance6PropertiesKHR() {
    VkPhysicalDeviceMaintenance6PropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_6_PROPERTIES_KHR;
    return info;
}

inline VkBindMemoryStatusKHR BindMemoryStatusKHR() {
    VkBindMemoryStatusKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_MEMORY_STATUS_KHR;
    return info;
}

inline VkBindDescriptorSetsInfoKHR BindDescriptorSetsInfoKHR() {
    VkBindDescriptorSetsInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_DESCRIPTOR_SETS_INFO_KHR;
    return info;
}

inline VkPushConstantsInfoKHR PushConstantsInfoKHR() {
    VkPushConstantsInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PUSH_CONSTANTS_INFO_KHR;
    return info;
}

inline VkPushDescriptorSetInfoKHR PushDescriptorSetInfoKHR() {
    VkPushDescriptorSetInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PUSH_DESCRIPTOR_SET_INFO_KHR;
    return info;
}

inline VkPushDescriptorSetWithTemplateInfoKHR PushDescriptorSetWithTemplateInfoKHR() {
    VkPushDescriptorSetWithTemplateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PUSH_DESCRIPTOR_SET_WITH_TEMPLATE_INFO_KHR;
    return info;
}

inline VkSetDescriptorBufferOffsetsInfoEXT SetDescriptorBufferOffsetsInfoEXT() {
    VkSetDescriptorBufferOffsetsInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SET_DESCRIPTOR_BUFFER_OFFSETS_INFO_EXT;
    return info;
}

inline VkBindDescriptorBufferEmbeddedSamplersInfoEXT BindDescriptorBufferEmbeddedSamplersInfoEXT() {
    VkBindDescriptorBufferEmbeddedSamplersInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_DESCRIPTOR_BUFFER_EMBEDDED_SAMPLERS_INFO_EXT;
    return info;
}

inline VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCreateInfoEXT() {
    VkDebugReportCallbackCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    return info;
}

inline VkPipelineRasterizationStateRasterizationOrderAMD PipelineRasterizationStateRasterizationOrderAMD() {
    VkPipelineRasterizationStateRasterizationOrderAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD;
    return info;
}

inline VkDebugMarkerObjectNameInfoEXT DebugMarkerObjectNameInfoEXT() {
    VkDebugMarkerObjectNameInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
    return info;
}

inline VkDebugMarkerObjectTagInfoEXT DebugMarkerObjectTagInfoEXT() {
    VkDebugMarkerObjectTagInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
    return info;
}

inline VkDebugMarkerMarkerInfoEXT DebugMarkerMarkerInfoEXT() {
    VkDebugMarkerMarkerInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
    return info;
}

inline VkDedicatedAllocationImageCreateInfoNV DedicatedAllocationImageCreateInfoNV() {
    VkDedicatedAllocationImageCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV;
    return info;
}

inline VkDedicatedAllocationBufferCreateInfoNV DedicatedAllocationBufferCreateInfoNV() {
    VkDedicatedAllocationBufferCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV;
    return info;
}

inline VkDedicatedAllocationMemoryAllocateInfoNV DedicatedAllocationMemoryAllocateInfoNV() {
    VkDedicatedAllocationMemoryAllocateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceTransformFeedbackFeaturesEXT PhysicalDeviceTransformFeedbackFeaturesEXT() {
    VkPhysicalDeviceTransformFeedbackFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceTransformFeedbackPropertiesEXT PhysicalDeviceTransformFeedbackPropertiesEXT() {
    VkPhysicalDeviceTransformFeedbackPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT;
    return info;
}

inline VkPipelineRasterizationStateStreamCreateInfoEXT PipelineRasterizationStateStreamCreateInfoEXT() {
    VkPipelineRasterizationStateStreamCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT;
    return info;
}

inline VkCuModuleCreateInfoNVX CuModuleCreateInfoNVX() {
    VkCuModuleCreateInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_CU_MODULE_CREATE_INFO_NVX;
    return info;
}

inline VkCuFunctionCreateInfoNVX CuFunctionCreateInfoNVX() {
    VkCuFunctionCreateInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_CU_FUNCTION_CREATE_INFO_NVX;
    return info;
}

inline VkCuLaunchInfoNVX CuLaunchInfoNVX() {
    VkCuLaunchInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_CU_LAUNCH_INFO_NVX;
    return info;
}

inline VkImageViewHandleInfoNVX ImageViewHandleInfoNVX() {
    VkImageViewHandleInfoNVX info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX;
    return info;
}

inline VkImageViewAddressPropertiesNVX ImageViewAddressPropertiesNVX() {
    VkImageViewAddressPropertiesNVX info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX;
    return info;
}

inline VkTextureLODGatherFormatPropertiesAMD TextureLODGatherFormatPropertiesAMD() {
    VkTextureLODGatherFormatPropertiesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD;
    return info;
}

#ifdef VK_USE_PLATFORM_GGP
inline VkStreamDescriptorSurfaceCreateInfoGGP StreamDescriptorSurfaceCreateInfoGGP() {
    VkStreamDescriptorSurfaceCreateInfoGGP info{};
    info.sType = VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP;
    return info;
}
#endif // VK_USE_PLATFORM_GGP

inline VkPhysicalDeviceCornerSampledImageFeaturesNV PhysicalDeviceCornerSampledImageFeaturesNV() {
    VkPhysicalDeviceCornerSampledImageFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV;
    return info;
}

inline VkExternalMemoryImageCreateInfoNV ExternalMemoryImageCreateInfoNV() {
    VkExternalMemoryImageCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV;
    return info;
}

inline VkExportMemoryAllocateInfoNV ExportMemoryAllocateInfoNV() {
    VkExportMemoryAllocateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkImportMemoryWin32HandleInfoNV ImportMemoryWin32HandleInfoNV() {
    VkImportMemoryWin32HandleInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV;
    return info;
}

inline VkExportMemoryWin32HandleInfoNV ExportMemoryWin32HandleInfoNV() {
    VkExportMemoryWin32HandleInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV;
    return info;
}

inline VkWin32KeyedMutexAcquireReleaseInfoNV Win32KeyedMutexAcquireReleaseInfoNV() {
    VkWin32KeyedMutexAcquireReleaseInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkValidationFlagsEXT ValidationFlagsEXT() {
    VkValidationFlagsEXT info{};
    info.sType = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_VI_NN
inline VkViSurfaceCreateInfoNN ViSurfaceCreateInfoNN() {
    VkViSurfaceCreateInfoNN info{};
    info.sType = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
    return info;
}
#endif // VK_USE_PLATFORM_VI_NN

inline VkImageViewASTCDecodeModeEXT ImageViewASTCDecodeModeEXT() {
    VkImageViewASTCDecodeModeEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT;
    return info;
}

inline VkPhysicalDeviceASTCDecodeFeaturesEXT PhysicalDeviceASTCDecodeFeaturesEXT() {
    VkPhysicalDeviceASTCDecodeFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT;
    return info;
}

inline VkPhysicalDevicePipelineRobustnessFeaturesEXT PhysicalDevicePipelineRobustnessFeaturesEXT() {
    VkPhysicalDevicePipelineRobustnessFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_FEATURES_EXT;
    return info;
}

inline VkPhysicalDevicePipelineRobustnessPropertiesEXT PhysicalDevicePipelineRobustnessPropertiesEXT() {
    VkPhysicalDevicePipelineRobustnessPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_PROPERTIES_EXT;
    return info;
}

inline VkPipelineRobustnessCreateInfoEXT PipelineRobustnessCreateInfoEXT() {
    VkPipelineRobustnessCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO_EXT;
    return info;
}

inline VkConditionalRenderingBeginInfoEXT ConditionalRenderingBeginInfoEXT() {
    VkConditionalRenderingBeginInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceConditionalRenderingFeaturesEXT PhysicalDeviceConditionalRenderingFeaturesEXT() {
    VkPhysicalDeviceConditionalRenderingFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT;
    return info;
}

inline VkCommandBufferInheritanceConditionalRenderingInfoEXT CommandBufferInheritanceConditionalRenderingInfoEXT() {
    VkCommandBufferInheritanceConditionalRenderingInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT;
    return info;
}

inline VkPipelineViewportWScalingStateCreateInfoNV PipelineViewportWScalingStateCreateInfoNV() {
    VkPipelineViewportWScalingStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV;
    return info;
}

inline VkSurfaceCapabilities2EXT SurfaceCapabilities2EXT() {
    VkSurfaceCapabilities2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT;
    return info;
}

inline VkDisplayPowerInfoEXT DisplayPowerInfoEXT() {
    VkDisplayPowerInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT;
    return info;
}

inline VkDeviceEventInfoEXT DeviceEventInfoEXT() {
    VkDeviceEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT;
    return info;
}

inline VkDisplayEventInfoEXT DisplayEventInfoEXT() {
    VkDisplayEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT;
    return info;
}

inline VkSwapchainCounterCreateInfoEXT SwapchainCounterCreateInfoEXT() {
    VkSwapchainCounterCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT;
    return info;
}

inline VkPresentTimesInfoGOOGLE PresentTimesInfoGOOGLE() {
    VkPresentTimesInfoGOOGLE info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE;
    return info;
}

inline VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX() {
    VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
    return info;
}

inline VkPipelineViewportSwizzleStateCreateInfoNV PipelineViewportSwizzleStateCreateInfoNV() {
    VkPipelineViewportSwizzleStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceDiscardRectanglePropertiesEXT PhysicalDeviceDiscardRectanglePropertiesEXT() {
    VkPhysicalDeviceDiscardRectanglePropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
    return info;
}

inline VkPipelineDiscardRectangleStateCreateInfoEXT PipelineDiscardRectangleStateCreateInfoEXT() {
    VkPipelineDiscardRectangleStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceConservativeRasterizationPropertiesEXT PhysicalDeviceConservativeRasterizationPropertiesEXT() {
    VkPhysicalDeviceConservativeRasterizationPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
    return info;
}

inline VkPipelineRasterizationConservativeStateCreateInfoEXT PipelineRasterizationConservativeStateCreateInfoEXT() {
    VkPipelineRasterizationConservativeStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceDepthClipEnableFeaturesEXT PhysicalDeviceDepthClipEnableFeaturesEXT() {
    VkPhysicalDeviceDepthClipEnableFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT;
    return info;
}

inline VkPipelineRasterizationDepthClipStateCreateInfoEXT PipelineRasterizationDepthClipStateCreateInfoEXT() {
    VkPipelineRasterizationDepthClipStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT;
    return info;
}

inline VkHdrMetadataEXT HdrMetadataEXT() {
    VkHdrMetadataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
    return info;
}

inline VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG PhysicalDeviceRelaxedLineRasterizationFeaturesIMG() {
    VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RELAXED_LINE_RASTERIZATION_FEATURES_IMG;
    return info;
}

#ifdef VK_USE_PLATFORM_IOS_MVK
inline VkIOSSurfaceCreateInfoMVK IOSSurfaceCreateInfoMVK() {
    VkIOSSurfaceCreateInfoMVK info{};
    info.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    return info;
}
#endif // VK_USE_PLATFORM_IOS_MVK

#ifdef VK_USE_PLATFORM_MACOS_MVK
inline VkMacOSSurfaceCreateInfoMVK MacOSSurfaceCreateInfoMVK() {
    VkMacOSSurfaceCreateInfoMVK info{};
    info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    return info;
}
#endif // VK_USE_PLATFORM_MACOS_MVK

inline VkDebugUtilsLabelEXT DebugUtilsLabelEXT() {
    VkDebugUtilsLabelEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    return info;
}

inline VkDebugUtilsObjectNameInfoEXT DebugUtilsObjectNameInfoEXT() {
    VkDebugUtilsObjectNameInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
    return info;
}

inline VkDebugUtilsMessengerCallbackDataEXT DebugUtilsMessengerCallbackDataEXT() {
    VkDebugUtilsMessengerCallbackDataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
    return info;
}

inline VkDebugUtilsMessengerCreateInfoEXT DebugUtilsMessengerCreateInfoEXT() {
    VkDebugUtilsMessengerCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    return info;
}

inline VkDebugUtilsObjectTagInfoEXT DebugUtilsObjectTagInfoEXT() {
    VkDebugUtilsObjectTagInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_ANDROID_KHR
inline VkAndroidHardwareBufferUsageANDROID AndroidHardwareBufferUsageANDROID() {
    VkAndroidHardwareBufferUsageANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID;
    return info;
}

inline VkAndroidHardwareBufferPropertiesANDROID AndroidHardwareBufferPropertiesANDROID() {
    VkAndroidHardwareBufferPropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID;
    return info;
}

inline VkAndroidHardwareBufferFormatPropertiesANDROID AndroidHardwareBufferFormatPropertiesANDROID() {
    VkAndroidHardwareBufferFormatPropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID;
    return info;
}

inline VkImportAndroidHardwareBufferInfoANDROID ImportAndroidHardwareBufferInfoANDROID() {
    VkImportAndroidHardwareBufferInfoANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
    return info;
}

inline VkMemoryGetAndroidHardwareBufferInfoANDROID MemoryGetAndroidHardwareBufferInfoANDROID() {
    VkMemoryGetAndroidHardwareBufferInfoANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
    return info;
}

inline VkExternalFormatANDROID ExternalFormatANDROID() {
    VkExternalFormatANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID;
    return info;
}

inline VkAndroidHardwareBufferFormatProperties2ANDROID AndroidHardwareBufferFormatProperties2ANDROID() {
    VkAndroidHardwareBufferFormatProperties2ANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID;
    return info;
}
#endif // VK_USE_PLATFORM_ANDROID_KHR

#ifdef VK_ENABLE_BETA_EXTENSIONS
inline VkPhysicalDeviceShaderEnqueueFeaturesAMDX PhysicalDeviceShaderEnqueueFeaturesAMDX() {
    VkPhysicalDeviceShaderEnqueueFeaturesAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ENQUEUE_FEATURES_AMDX;
    return info;
}

inline VkPhysicalDeviceShaderEnqueuePropertiesAMDX PhysicalDeviceShaderEnqueuePropertiesAMDX() {
    VkPhysicalDeviceShaderEnqueuePropertiesAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ENQUEUE_PROPERTIES_AMDX;
    return info;
}

inline VkExecutionGraphPipelineScratchSizeAMDX ExecutionGraphPipelineScratchSizeAMDX() {
    VkExecutionGraphPipelineScratchSizeAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_EXECUTION_GRAPH_PIPELINE_SCRATCH_SIZE_AMDX;
    return info;
}

inline VkExecutionGraphPipelineCreateInfoAMDX ExecutionGraphPipelineCreateInfoAMDX() {
    VkExecutionGraphPipelineCreateInfoAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_EXECUTION_GRAPH_PIPELINE_CREATE_INFO_AMDX;
    return info;
}

inline VkPipelineShaderStageNodeCreateInfoAMDX PipelineShaderStageNodeCreateInfoAMDX() {
    VkPipelineShaderStageNodeCreateInfoAMDX info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_NODE_CREATE_INFO_AMDX;
    return info;
}
#endif // VK_ENABLE_BETA_EXTENSIONS

inline VkSampleLocationsInfoEXT SampleLocationsInfoEXT() {
    VkSampleLocationsInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
    return info;
}

inline VkRenderPassSampleLocationsBeginInfoEXT RenderPassSampleLocationsBeginInfoEXT() {
    VkRenderPassSampleLocationsBeginInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT;
    return info;
}

inline VkPipelineSampleLocationsStateCreateInfoEXT PipelineSampleLocationsStateCreateInfoEXT() {
    VkPipelineSampleLocationsStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceSampleLocationsPropertiesEXT PhysicalDeviceSampleLocationsPropertiesEXT() {
    VkPhysicalDeviceSampleLocationsPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
    return info;
}

inline VkMultisamplePropertiesEXT MultisamplePropertiesEXT() {
    VkMultisamplePropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT PhysicalDeviceBlendOperationAdvancedFeaturesEXT() {
    VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT PhysicalDeviceBlendOperationAdvancedPropertiesEXT() {
    VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
    return info;
}

inline VkPipelineColorBlendAdvancedStateCreateInfoEXT PipelineColorBlendAdvancedStateCreateInfoEXT() {
    VkPipelineColorBlendAdvancedStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT;
    return info;
}

inline VkPipelineCoverageToColorStateCreateInfoNV PipelineCoverageToColorStateCreateInfoNV() {
    VkPipelineCoverageToColorStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV;
    return info;
}

inline VkPipelineCoverageModulationStateCreateInfoNV PipelineCoverageModulationStateCreateInfoNV() {
    VkPipelineCoverageModulationStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceShaderSMBuiltinsPropertiesNV PhysicalDeviceShaderSMBuiltinsPropertiesNV() {
    VkPhysicalDeviceShaderSMBuiltinsPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceShaderSMBuiltinsFeaturesNV PhysicalDeviceShaderSMBuiltinsFeaturesNV() {
    VkPhysicalDeviceShaderSMBuiltinsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
    return info;
}

inline VkDrmFormatModifierPropertiesListEXT DrmFormatModifierPropertiesListEXT() {
    VkDrmFormatModifierPropertiesListEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT;
    return info;
}

inline VkPhysicalDeviceImageDrmFormatModifierInfoEXT PhysicalDeviceImageDrmFormatModifierInfoEXT() {
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT;
    return info;
}

inline VkImageDrmFormatModifierListCreateInfoEXT ImageDrmFormatModifierListCreateInfoEXT() {
    VkImageDrmFormatModifierListCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT;
    return info;
}

inline VkImageDrmFormatModifierExplicitCreateInfoEXT ImageDrmFormatModifierExplicitCreateInfoEXT() {
    VkImageDrmFormatModifierExplicitCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT;
    return info;
}

inline VkImageDrmFormatModifierPropertiesEXT ImageDrmFormatModifierPropertiesEXT() {
    VkImageDrmFormatModifierPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT;
    return info;
}

inline VkDrmFormatModifierPropertiesList2EXT DrmFormatModifierPropertiesList2EXT() {
    VkDrmFormatModifierPropertiesList2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_2_EXT;
    return info;
}

inline VkValidationCacheCreateInfoEXT ValidationCacheCreateInfoEXT() {
    VkValidationCacheCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT;
    return info;
}

inline VkShaderModuleValidationCacheCreateInfoEXT ShaderModuleValidationCacheCreateInfoEXT() {
    VkShaderModuleValidationCacheCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
    return info;
}

inline VkPipelineViewportShadingRateImageStateCreateInfoNV PipelineViewportShadingRateImageStateCreateInfoNV() {
    VkPipelineViewportShadingRateImageStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceShadingRateImageFeaturesNV PhysicalDeviceShadingRateImageFeaturesNV() {
    VkPhysicalDeviceShadingRateImageFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceShadingRateImagePropertiesNV PhysicalDeviceShadingRateImagePropertiesNV() {
    VkPhysicalDeviceShadingRateImagePropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV;
    return info;
}

inline VkPipelineViewportCoarseSampleOrderStateCreateInfoNV PipelineViewportCoarseSampleOrderStateCreateInfoNV() {
    VkPipelineViewportCoarseSampleOrderStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV;
    return info;
}

inline VkRayTracingShaderGroupCreateInfoNV RayTracingShaderGroupCreateInfoNV() {
    VkRayTracingShaderGroupCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV;
    return info;
}

inline VkRayTracingPipelineCreateInfoNV RayTracingPipelineCreateInfoNV() {
    VkRayTracingPipelineCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
    return info;
}

inline VkGeometryTrianglesNV GeometryTrianglesNV() {
    VkGeometryTrianglesNV info{};
    info.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
    return info;
}

inline VkGeometryAABBNV GeometryAABBNV() {
    VkGeometryAABBNV info{};
    info.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
    return info;
}

inline VkGeometryNV GeometryNV() {
    VkGeometryNV info{};
    info.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
    return info;
}

inline VkAccelerationStructureInfoNV AccelerationStructureInfoNV() {
    VkAccelerationStructureInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
    return info;
}

inline VkAccelerationStructureCreateInfoNV AccelerationStructureCreateInfoNV() {
    VkAccelerationStructureCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
    return info;
}

inline VkBindAccelerationStructureMemoryInfoNV BindAccelerationStructureMemoryInfoNV() {
    VkBindAccelerationStructureMemoryInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
    return info;
}

inline VkWriteDescriptorSetAccelerationStructureNV WriteDescriptorSetAccelerationStructureNV() {
    VkWriteDescriptorSetAccelerationStructureNV info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV;
    return info;
}

inline VkAccelerationStructureMemoryRequirementsInfoNV AccelerationStructureMemoryRequirementsInfoNV() {
    VkAccelerationStructureMemoryRequirementsInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
    return info;
}

inline VkPhysicalDeviceRayTracingPropertiesNV PhysicalDeviceRayTracingPropertiesNV() {
    VkPhysicalDeviceRayTracingPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV PhysicalDeviceRepresentativeFragmentTestFeaturesNV() {
    VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV;
    return info;
}

inline VkPipelineRepresentativeFragmentTestStateCreateInfoNV PipelineRepresentativeFragmentTestStateCreateInfoNV() {
    VkPipelineRepresentativeFragmentTestStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceImageViewImageFormatInfoEXT PhysicalDeviceImageViewImageFormatInfoEXT() {
    VkPhysicalDeviceImageViewImageFormatInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT;
    return info;
}

inline VkFilterCubicImageViewImageFormatPropertiesEXT FilterCubicImageViewImageFormatPropertiesEXT() {
    VkFilterCubicImageViewImageFormatPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT;
    return info;
}

inline VkImportMemoryHostPointerInfoEXT ImportMemoryHostPointerInfoEXT() {
    VkImportMemoryHostPointerInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT;
    return info;
}

inline VkMemoryHostPointerPropertiesEXT MemoryHostPointerPropertiesEXT() {
    VkMemoryHostPointerPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceExternalMemoryHostPropertiesEXT PhysicalDeviceExternalMemoryHostPropertiesEXT() {
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
    return info;
}

inline VkPipelineCompilerControlCreateInfoAMD PipelineCompilerControlCreateInfoAMD() {
    VkPipelineCompilerControlCreateInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
    return info;
}

inline VkPhysicalDeviceShaderCorePropertiesAMD PhysicalDeviceShaderCorePropertiesAMD() {
    VkPhysicalDeviceShaderCorePropertiesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
    return info;
}

inline VkDeviceMemoryOverallocationCreateInfoAMD DeviceMemoryOverallocationCreateInfoAMD() {
    VkDeviceMemoryOverallocationCreateInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD;
    return info;
}

inline VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT PhysicalDeviceVertexAttributeDivisorPropertiesEXT() {
    VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_GGP
inline VkPresentFrameTokenGGP PresentFrameTokenGGP() {
    VkPresentFrameTokenGGP info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP;
    return info;
}
#endif // VK_USE_PLATFORM_GGP

inline VkPhysicalDeviceComputeShaderDerivativesFeaturesNV PhysicalDeviceComputeShaderDerivativesFeaturesNV() {
    VkPhysicalDeviceComputeShaderDerivativesFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceMeshShaderFeaturesNV PhysicalDeviceMeshShaderFeaturesNV() {
    VkPhysicalDeviceMeshShaderFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceMeshShaderPropertiesNV PhysicalDeviceMeshShaderPropertiesNV() {
    VkPhysicalDeviceMeshShaderPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceShaderImageFootprintFeaturesNV PhysicalDeviceShaderImageFootprintFeaturesNV() {
    VkPhysicalDeviceShaderImageFootprintFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV;
    return info;
}

inline VkPipelineViewportExclusiveScissorStateCreateInfoNV PipelineViewportExclusiveScissorStateCreateInfoNV() {
    VkPipelineViewportExclusiveScissorStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceExclusiveScissorFeaturesNV PhysicalDeviceExclusiveScissorFeaturesNV() {
    VkPhysicalDeviceExclusiveScissorFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV;
    return info;
}

inline VkQueueFamilyCheckpointPropertiesNV QueueFamilyCheckpointPropertiesNV() {
    VkQueueFamilyCheckpointPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV;
    return info;
}

inline VkCheckpointDataNV CheckpointDataNV() {
    VkCheckpointDataNV info{};
    info.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV;
    return info;
}

inline VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL() {
    VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL;
    return info;
}

inline VkInitializePerformanceApiInfoINTEL InitializePerformanceApiInfoINTEL() {
    VkInitializePerformanceApiInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL;
    return info;
}

inline VkQueryPoolPerformanceQueryCreateInfoINTEL QueryPoolPerformanceQueryCreateInfoINTEL() {
    VkQueryPoolPerformanceQueryCreateInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL;
    return info;
}

inline VkPerformanceMarkerInfoINTEL PerformanceMarkerInfoINTEL() {
    VkPerformanceMarkerInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL;
    return info;
}

inline VkPerformanceStreamMarkerInfoINTEL PerformanceStreamMarkerInfoINTEL() {
    VkPerformanceStreamMarkerInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL;
    return info;
}

inline VkPerformanceOverrideInfoINTEL PerformanceOverrideInfoINTEL() {
    VkPerformanceOverrideInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL;
    return info;
}

inline VkPerformanceConfigurationAcquireInfoINTEL PerformanceConfigurationAcquireInfoINTEL() {
    VkPerformanceConfigurationAcquireInfoINTEL info{};
    info.sType = VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL;
    return info;
}

inline VkPhysicalDevicePCIBusInfoPropertiesEXT PhysicalDevicePCIBusInfoPropertiesEXT() {
    VkPhysicalDevicePCIBusInfoPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT;
    return info;
}

inline VkDisplayNativeHdrSurfaceCapabilitiesAMD DisplayNativeHdrSurfaceCapabilitiesAMD() {
    VkDisplayNativeHdrSurfaceCapabilitiesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD;
    return info;
}

inline VkSwapchainDisplayNativeHdrCreateInfoAMD SwapchainDisplayNativeHdrCreateInfoAMD() {
    VkSwapchainDisplayNativeHdrCreateInfoAMD info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD;
    return info;
}

#ifdef VK_USE_PLATFORM_FUCHSIA
inline VkImagePipeSurfaceCreateInfoFUCHSIA ImagePipeSurfaceCreateInfoFUCHSIA() {
    VkImagePipeSurfaceCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA;
    return info;
}
#endif // VK_USE_PLATFORM_FUCHSIA

#ifdef VK_USE_PLATFORM_METAL_EXT
inline VkMetalSurfaceCreateInfoEXT MetalSurfaceCreateInfoEXT() {
    VkMetalSurfaceCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    return info;
}
#endif // VK_USE_PLATFORM_METAL_EXT

inline VkPhysicalDeviceFragmentDensityMapFeaturesEXT PhysicalDeviceFragmentDensityMapFeaturesEXT() {
    VkPhysicalDeviceFragmentDensityMapFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMapPropertiesEXT PhysicalDeviceFragmentDensityMapPropertiesEXT() {
    VkPhysicalDeviceFragmentDensityMapPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT;
    return info;
}

inline VkRenderPassFragmentDensityMapCreateInfoEXT RenderPassFragmentDensityMapCreateInfoEXT() {
    VkRenderPassFragmentDensityMapCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceShaderCoreProperties2AMD PhysicalDeviceShaderCoreProperties2AMD() {
    VkPhysicalDeviceShaderCoreProperties2AMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;
    return info;
}

inline VkPhysicalDeviceCoherentMemoryFeaturesAMD PhysicalDeviceCoherentMemoryFeaturesAMD() {
    VkPhysicalDeviceCoherentMemoryFeaturesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
    return info;
}

inline VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT PhysicalDeviceShaderImageAtomicInt64FeaturesEXT() {
    VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceMemoryBudgetPropertiesEXT PhysicalDeviceMemoryBudgetPropertiesEXT() {
    VkPhysicalDeviceMemoryBudgetPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceMemoryPriorityFeaturesEXT PhysicalDeviceMemoryPriorityFeaturesEXT() {
    VkPhysicalDeviceMemoryPriorityFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
    return info;
}

inline VkMemoryPriorityAllocateInfoEXT MemoryPriorityAllocateInfoEXT() {
    VkMemoryPriorityAllocateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV() {
    VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceBufferDeviceAddressFeaturesEXT PhysicalDeviceBufferDeviceAddressFeaturesEXT() {
    VkPhysicalDeviceBufferDeviceAddressFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT;
    return info;
}

inline VkBufferDeviceAddressCreateInfoEXT BufferDeviceAddressCreateInfoEXT() {
    VkBufferDeviceAddressCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT;
    return info;
}

inline VkValidationFeaturesEXT ValidationFeaturesEXT() {
    VkValidationFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
    return info;
}

inline VkCooperativeMatrixPropertiesNV CooperativeMatrixPropertiesNV() {
    VkCooperativeMatrixPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixFeaturesNV PhysicalDeviceCooperativeMatrixFeaturesNV() {
    VkPhysicalDeviceCooperativeMatrixFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceCooperativeMatrixPropertiesNV PhysicalDeviceCooperativeMatrixPropertiesNV() {
    VkPhysicalDeviceCooperativeMatrixPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceCoverageReductionModeFeaturesNV PhysicalDeviceCoverageReductionModeFeaturesNV() {
    VkPhysicalDeviceCoverageReductionModeFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV;
    return info;
}

inline VkPipelineCoverageReductionStateCreateInfoNV PipelineCoverageReductionStateCreateInfoNV() {
    VkPipelineCoverageReductionStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV;
    return info;
}

inline VkFramebufferMixedSamplesCombinationNV FramebufferMixedSamplesCombinationNV() {
    VkFramebufferMixedSamplesCombinationNV info{};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV;
    return info;
}

inline VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT PhysicalDeviceFragmentShaderInterlockFeaturesEXT() {
    VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceYcbcrImageArraysFeaturesEXT PhysicalDeviceYcbcrImageArraysFeaturesEXT() {
    VkPhysicalDeviceYcbcrImageArraysFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceProvokingVertexFeaturesEXT PhysicalDeviceProvokingVertexFeaturesEXT() {
    VkPhysicalDeviceProvokingVertexFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceProvokingVertexPropertiesEXT PhysicalDeviceProvokingVertexPropertiesEXT() {
    VkPhysicalDeviceProvokingVertexPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT;
    return info;
}

inline VkPipelineRasterizationProvokingVertexStateCreateInfoEXT PipelineRasterizationProvokingVertexStateCreateInfoEXT() {
    VkPipelineRasterizationProvokingVertexStateCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR
inline VkSurfaceFullScreenExclusiveInfoEXT SurfaceFullScreenExclusiveInfoEXT() {
    VkSurfaceFullScreenExclusiveInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT;
    return info;
}

inline VkSurfaceCapabilitiesFullScreenExclusiveEXT SurfaceCapabilitiesFullScreenExclusiveEXT() {
    VkSurfaceCapabilitiesFullScreenExclusiveEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT;
    return info;
}

inline VkSurfaceFullScreenExclusiveWin32InfoEXT SurfaceFullScreenExclusiveWin32InfoEXT() {
    VkSurfaceFullScreenExclusiveWin32InfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT;
    return info;
}
#endif // VK_USE_PLATFORM_WIN32_KHR

inline VkHeadlessSurfaceCreateInfoEXT HeadlessSurfaceCreateInfoEXT() {
    VkHeadlessSurfaceCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceShaderAtomicFloatFeaturesEXT PhysicalDeviceShaderAtomicFloatFeaturesEXT() {
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicStateFeaturesEXT PhysicalDeviceExtendedDynamicStateFeaturesEXT() {
    VkPhysicalDeviceExtendedDynamicStateFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceHostImageCopyFeaturesEXT PhysicalDeviceHostImageCopyFeaturesEXT() {
    VkPhysicalDeviceHostImageCopyFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceHostImageCopyPropertiesEXT PhysicalDeviceHostImageCopyPropertiesEXT() {
    VkPhysicalDeviceHostImageCopyPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT;
    return info;
}

inline VkMemoryToImageCopyEXT MemoryToImageCopyEXT() {
    VkMemoryToImageCopyEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT;
    return info;
}

inline VkImageToMemoryCopyEXT ImageToMemoryCopyEXT() {
    VkImageToMemoryCopyEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT;
    return info;
}

inline VkCopyMemoryToImageInfoEXT CopyMemoryToImageInfoEXT() {
    VkCopyMemoryToImageInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT;
    return info;
}

inline VkCopyImageToMemoryInfoEXT CopyImageToMemoryInfoEXT() {
    VkCopyImageToMemoryInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT;
    return info;
}

inline VkCopyImageToImageInfoEXT CopyImageToImageInfoEXT() {
    VkCopyImageToImageInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_IMAGE_INFO_EXT;
    return info;
}

inline VkHostImageLayoutTransitionInfoEXT HostImageLayoutTransitionInfoEXT() {
    VkHostImageLayoutTransitionInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT;
    return info;
}

inline VkSubresourceHostMemcpySizeEXT SubresourceHostMemcpySizeEXT() {
    VkSubresourceHostMemcpySizeEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_HOST_MEMCPY_SIZE_EXT;
    return info;
}

inline VkHostImageCopyDevicePerformanceQueryEXT HostImageCopyDevicePerformanceQueryEXT() {
    VkHostImageCopyDevicePerformanceQueryEXT info{};
    info.sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT;
    return info;
}

inline VkPhysicalDeviceMapMemoryPlacedFeaturesEXT PhysicalDeviceMapMemoryPlacedFeaturesEXT() {
    VkPhysicalDeviceMapMemoryPlacedFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAP_MEMORY_PLACED_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceMapMemoryPlacedPropertiesEXT PhysicalDeviceMapMemoryPlacedPropertiesEXT() {
    VkPhysicalDeviceMapMemoryPlacedPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAP_MEMORY_PLACED_PROPERTIES_EXT;
    return info;
}

inline VkMemoryMapPlacedInfoEXT MemoryMapPlacedInfoEXT() {
    VkMemoryMapPlacedInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_MAP_PLACED_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT PhysicalDeviceShaderAtomicFloat2FeaturesEXT() {
    VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT;
    return info;
}

inline VkSurfacePresentModeEXT SurfacePresentModeEXT() {
    VkSurfacePresentModeEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_EXT;
    return info;
}

inline VkSurfacePresentScalingCapabilitiesEXT SurfacePresentScalingCapabilitiesEXT() {
    VkSurfacePresentScalingCapabilitiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_EXT;
    return info;
}

inline VkSurfacePresentModeCompatibilityEXT SurfacePresentModeCompatibilityEXT() {
    VkSurfacePresentModeCompatibilityEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_COMPATIBILITY_EXT;
    return info;
}

inline VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT PhysicalDeviceSwapchainMaintenance1FeaturesEXT() {
    VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SWAPCHAIN_MAINTENANCE_1_FEATURES_EXT;
    return info;
}

inline VkSwapchainPresentFenceInfoEXT SwapchainPresentFenceInfoEXT() {
    VkSwapchainPresentFenceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_FENCE_INFO_EXT;
    return info;
}

inline VkSwapchainPresentModesCreateInfoEXT SwapchainPresentModesCreateInfoEXT() {
    VkSwapchainPresentModesCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODES_CREATE_INFO_EXT;
    return info;
}

inline VkSwapchainPresentModeInfoEXT SwapchainPresentModeInfoEXT() {
    VkSwapchainPresentModeInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODE_INFO_EXT;
    return info;
}

inline VkSwapchainPresentScalingCreateInfoEXT SwapchainPresentScalingCreateInfoEXT() {
    VkSwapchainPresentScalingCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_SCALING_CREATE_INFO_EXT;
    return info;
}

inline VkReleaseSwapchainImagesInfoEXT ReleaseSwapchainImagesInfoEXT() {
    VkReleaseSwapchainImagesInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RELEASE_SWAPCHAIN_IMAGES_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV PhysicalDeviceDeviceGeneratedCommandsPropertiesNV() {
    VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV PhysicalDeviceDeviceGeneratedCommandsFeaturesNV() {
    VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV;
    return info;
}

inline VkGraphicsShaderGroupCreateInfoNV GraphicsShaderGroupCreateInfoNV() {
    VkGraphicsShaderGroupCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_SHADER_GROUP_CREATE_INFO_NV;
    return info;
}

inline VkGraphicsPipelineShaderGroupsCreateInfoNV GraphicsPipelineShaderGroupsCreateInfoNV() {
    VkGraphicsPipelineShaderGroupsCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV;
    return info;
}

inline VkIndirectCommandsLayoutTokenNV IndirectCommandsLayoutTokenNV() {
    VkIndirectCommandsLayoutTokenNV info{};
    info.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV;
    return info;
}

inline VkIndirectCommandsLayoutCreateInfoNV IndirectCommandsLayoutCreateInfoNV() {
    VkIndirectCommandsLayoutCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NV;
    return info;
}

inline VkGeneratedCommandsInfoNV GeneratedCommandsInfoNV() {
    VkGeneratedCommandsInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV;
    return info;
}

inline VkGeneratedCommandsMemoryRequirementsInfoNV GeneratedCommandsMemoryRequirementsInfoNV() {
    VkGeneratedCommandsMemoryRequirementsInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV;
    return info;
}

inline VkPhysicalDeviceInheritedViewportScissorFeaturesNV PhysicalDeviceInheritedViewportScissorFeaturesNV() {
    VkPhysicalDeviceInheritedViewportScissorFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV;
    return info;
}

inline VkCommandBufferInheritanceViewportScissorInfoNV CommandBufferInheritanceViewportScissorInfoNV() {
    VkCommandBufferInheritanceViewportScissorInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV;
    return info;
}

inline VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT PhysicalDeviceTexelBufferAlignmentFeaturesEXT() {
    VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
    return info;
}

inline VkRenderPassTransformBeginInfoQCOM RenderPassTransformBeginInfoQCOM() {
    VkRenderPassTransformBeginInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM;
    return info;
}

inline VkCommandBufferInheritanceRenderPassTransformInfoQCOM CommandBufferInheritanceRenderPassTransformInfoQCOM() {
    VkCommandBufferInheritanceRenderPassTransformInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceDepthBiasControlFeaturesEXT PhysicalDeviceDepthBiasControlFeaturesEXT() {
    VkPhysicalDeviceDepthBiasControlFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_BIAS_CONTROL_FEATURES_EXT;
    return info;
}

inline VkDepthBiasInfoEXT DepthBiasInfoEXT() {
    VkDepthBiasInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEPTH_BIAS_INFO_EXT;
    return info;
}

inline VkDepthBiasRepresentationInfoEXT DepthBiasRepresentationInfoEXT() {
    VkDepthBiasRepresentationInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEPTH_BIAS_REPRESENTATION_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceDeviceMemoryReportFeaturesEXT PhysicalDeviceDeviceMemoryReportFeaturesEXT() {
    VkPhysicalDeviceDeviceMemoryReportFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT;
    return info;
}

inline VkDeviceMemoryReportCallbackDataEXT DeviceMemoryReportCallbackDataEXT() {
    VkDeviceMemoryReportCallbackDataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_REPORT_CALLBACK_DATA_EXT;
    return info;
}

inline VkDeviceDeviceMemoryReportCreateInfoEXT DeviceDeviceMemoryReportCreateInfoEXT() {
    VkDeviceDeviceMemoryReportCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceRobustness2FeaturesEXT PhysicalDeviceRobustness2FeaturesEXT() {
    VkPhysicalDeviceRobustness2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceRobustness2PropertiesEXT PhysicalDeviceRobustness2PropertiesEXT() {
    VkPhysicalDeviceRobustness2PropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT;
    return info;
}

inline VkSamplerCustomBorderColorCreateInfoEXT SamplerCustomBorderColorCreateInfoEXT() {
    VkSamplerCustomBorderColorCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceCustomBorderColorPropertiesEXT PhysicalDeviceCustomBorderColorPropertiesEXT() {
    VkPhysicalDeviceCustomBorderColorPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceCustomBorderColorFeaturesEXT PhysicalDeviceCustomBorderColorFeaturesEXT() {
    VkPhysicalDeviceCustomBorderColorFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT;
    return info;
}

inline VkPhysicalDevicePresentBarrierFeaturesNV PhysicalDevicePresentBarrierFeaturesNV() {
    VkPhysicalDevicePresentBarrierFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_BARRIER_FEATURES_NV;
    return info;
}

inline VkSurfaceCapabilitiesPresentBarrierNV SurfaceCapabilitiesPresentBarrierNV() {
    VkSurfaceCapabilitiesPresentBarrierNV info{};
    info.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_PRESENT_BARRIER_NV;
    return info;
}

inline VkSwapchainPresentBarrierCreateInfoNV SwapchainPresentBarrierCreateInfoNV() {
    VkSwapchainPresentBarrierCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_BARRIER_CREATE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceDiagnosticsConfigFeaturesNV PhysicalDeviceDiagnosticsConfigFeaturesNV() {
    VkPhysicalDeviceDiagnosticsConfigFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV;
    return info;
}

inline VkDeviceDiagnosticsConfigCreateInfoNV DeviceDiagnosticsConfigCreateInfoNV() {
    VkDeviceDiagnosticsConfigCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV;
    return info;
}

inline VkCudaModuleCreateInfoNV CudaModuleCreateInfoNV() {
    VkCudaModuleCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_CUDA_MODULE_CREATE_INFO_NV;
    return info;
}

inline VkCudaFunctionCreateInfoNV CudaFunctionCreateInfoNV() {
    VkCudaFunctionCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_CUDA_FUNCTION_CREATE_INFO_NV;
    return info;
}

inline VkCudaLaunchInfoNV CudaLaunchInfoNV() {
    VkCudaLaunchInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_CUDA_LAUNCH_INFO_NV;
    return info;
}

inline VkPhysicalDeviceCudaKernelLaunchFeaturesNV PhysicalDeviceCudaKernelLaunchFeaturesNV() {
    VkPhysicalDeviceCudaKernelLaunchFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUDA_KERNEL_LAUNCH_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceCudaKernelLaunchPropertiesNV PhysicalDeviceCudaKernelLaunchPropertiesNV() {
    VkPhysicalDeviceCudaKernelLaunchPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUDA_KERNEL_LAUNCH_PROPERTIES_NV;
    return info;
}

inline VkQueryLowLatencySupportNV QueryLowLatencySupportNV() {
    VkQueryLowLatencySupportNV info{};
    info.sType = VK_STRUCTURE_TYPE_QUERY_LOW_LATENCY_SUPPORT_NV;
    return info;
}

#ifdef VK_USE_PLATFORM_METAL_EXT
inline VkExportMetalObjectCreateInfoEXT ExportMetalObjectCreateInfoEXT() {
    VkExportMetalObjectCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECT_CREATE_INFO_EXT;
    return info;
}

inline VkExportMetalObjectsInfoEXT ExportMetalObjectsInfoEXT() {
    VkExportMetalObjectsInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECTS_INFO_EXT;
    return info;
}

inline VkExportMetalDeviceInfoEXT ExportMetalDeviceInfoEXT() {
    VkExportMetalDeviceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_DEVICE_INFO_EXT;
    return info;
}

inline VkExportMetalCommandQueueInfoEXT ExportMetalCommandQueueInfoEXT() {
    VkExportMetalCommandQueueInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_COMMAND_QUEUE_INFO_EXT;
    return info;
}

inline VkExportMetalBufferInfoEXT ExportMetalBufferInfoEXT() {
    VkExportMetalBufferInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_BUFFER_INFO_EXT;
    return info;
}

inline VkImportMetalBufferInfoEXT ImportMetalBufferInfoEXT() {
    VkImportMetalBufferInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_BUFFER_INFO_EXT;
    return info;
}

inline VkExportMetalTextureInfoEXT ExportMetalTextureInfoEXT() {
    VkExportMetalTextureInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_TEXTURE_INFO_EXT;
    return info;
}

inline VkImportMetalTextureInfoEXT ImportMetalTextureInfoEXT() {
    VkImportMetalTextureInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_TEXTURE_INFO_EXT;
    return info;
}

inline VkExportMetalIOSurfaceInfoEXT ExportMetalIOSurfaceInfoEXT() {
    VkExportMetalIOSurfaceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_IO_SURFACE_INFO_EXT;
    return info;
}

inline VkImportMetalIOSurfaceInfoEXT ImportMetalIOSurfaceInfoEXT() {
    VkImportMetalIOSurfaceInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_IO_SURFACE_INFO_EXT;
    return info;
}

inline VkExportMetalSharedEventInfoEXT ExportMetalSharedEventInfoEXT() {
    VkExportMetalSharedEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_SHARED_EVENT_INFO_EXT;
    return info;
}

inline VkImportMetalSharedEventInfoEXT ImportMetalSharedEventInfoEXT() {
    VkImportMetalSharedEventInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_SHARED_EVENT_INFO_EXT;
    return info;
}
#endif // VK_USE_PLATFORM_METAL_EXT

inline VkPhysicalDeviceDescriptorBufferPropertiesEXT PhysicalDeviceDescriptorBufferPropertiesEXT() {
    VkPhysicalDeviceDescriptorBufferPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT PhysicalDeviceDescriptorBufferDensityMapPropertiesEXT() {
    VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_DENSITY_MAP_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceDescriptorBufferFeaturesEXT PhysicalDeviceDescriptorBufferFeaturesEXT() {
    VkPhysicalDeviceDescriptorBufferFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT;
    return info;
}

inline VkDescriptorAddressInfoEXT DescriptorAddressInfoEXT() {
    VkDescriptorAddressInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_ADDRESS_INFO_EXT;
    return info;
}

inline VkDescriptorBufferBindingInfoEXT DescriptorBufferBindingInfoEXT() {
    VkDescriptorBufferBindingInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_INFO_EXT;
    return info;
}

inline VkDescriptorBufferBindingPushDescriptorBufferHandleEXT DescriptorBufferBindingPushDescriptorBufferHandleEXT() {
    VkDescriptorBufferBindingPushDescriptorBufferHandleEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_PUSH_DESCRIPTOR_BUFFER_HANDLE_EXT;
    return info;
}

inline VkDescriptorGetInfoEXT DescriptorGetInfoEXT() {
    VkDescriptorGetInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT;
    return info;
}

inline VkBufferCaptureDescriptorDataInfoEXT BufferCaptureDescriptorDataInfoEXT() {
    VkBufferCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    return info;
}

inline VkImageCaptureDescriptorDataInfoEXT ImageCaptureDescriptorDataInfoEXT() {
    VkImageCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    return info;
}

inline VkImageViewCaptureDescriptorDataInfoEXT ImageViewCaptureDescriptorDataInfoEXT() {
    VkImageViewCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    return info;
}

inline VkSamplerCaptureDescriptorDataInfoEXT SamplerCaptureDescriptorDataInfoEXT() {
    VkSamplerCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    return info;
}

inline VkOpaqueCaptureDescriptorDataCreateInfoEXT OpaqueCaptureDescriptorDataCreateInfoEXT() {
    VkOpaqueCaptureDescriptorDataCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT;
    return info;
}

inline VkAccelerationStructureCaptureDescriptorDataInfoEXT AccelerationStructureCaptureDescriptorDataInfoEXT() {
    VkAccelerationStructureCaptureDescriptorDataInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CAPTURE_DESCRIPTOR_DATA_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT PhysicalDeviceGraphicsPipelineLibraryFeaturesEXT() {
    VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT PhysicalDeviceGraphicsPipelineLibraryPropertiesEXT() {
    VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_PROPERTIES_EXT;
    return info;
}

inline VkGraphicsPipelineLibraryCreateInfoEXT GraphicsPipelineLibraryCreateInfoEXT() {
    VkGraphicsPipelineLibraryCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_LIBRARY_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD PhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD() {
    VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_FEATURES_AMD;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV PhysicalDeviceFragmentShadingRateEnumsFeaturesNV() {
    VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV PhysicalDeviceFragmentShadingRateEnumsPropertiesNV() {
    VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV;
    return info;
}

inline VkPipelineFragmentShadingRateEnumStateCreateInfoNV PipelineFragmentShadingRateEnumStateCreateInfoNV() {
    VkPipelineFragmentShadingRateEnumStateCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV;
    return info;
}

inline VkAccelerationStructureGeometryMotionTrianglesDataNV AccelerationStructureGeometryMotionTrianglesDataNV() {
    VkAccelerationStructureGeometryMotionTrianglesDataNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV;
    return info;
}

inline VkAccelerationStructureMotionInfoNV AccelerationStructureMotionInfoNV() {
    VkAccelerationStructureMotionInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV;
    return info;
}

inline VkPhysicalDeviceRayTracingMotionBlurFeaturesNV PhysicalDeviceRayTracingMotionBlurFeaturesNV() {
    VkPhysicalDeviceRayTracingMotionBlurFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT() {
    VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMap2FeaturesEXT PhysicalDeviceFragmentDensityMap2FeaturesEXT() {
    VkPhysicalDeviceFragmentDensityMap2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMap2PropertiesEXT PhysicalDeviceFragmentDensityMap2PropertiesEXT() {
    VkPhysicalDeviceFragmentDensityMap2PropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT;
    return info;
}

inline VkCopyCommandTransformInfoQCOM CopyCommandTransformInfoQCOM() {
    VkCopyCommandTransformInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceImageCompressionControlFeaturesEXT PhysicalDeviceImageCompressionControlFeaturesEXT() {
    VkPhysicalDeviceImageCompressionControlFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_FEATURES_EXT;
    return info;
}

inline VkImageCompressionControlEXT ImageCompressionControlEXT() {
    VkImageCompressionControlEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
    return info;
}

inline VkImageCompressionPropertiesEXT ImageCompressionPropertiesEXT() {
    VkImageCompressionPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT PhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT() {
    VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_FEATURES_EXT;
    return info;
}

inline VkPhysicalDevice4444FormatsFeaturesEXT PhysicalDevice4444FormatsFeaturesEXT() {
    VkPhysicalDevice4444FormatsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceFaultFeaturesEXT PhysicalDeviceFaultFeaturesEXT() {
    VkPhysicalDeviceFaultFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT;
    return info;
}

inline VkDeviceFaultCountsEXT DeviceFaultCountsEXT() {
    VkDeviceFaultCountsEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;
    return info;
}

inline VkDeviceFaultInfoEXT DeviceFaultInfoEXT() {
    VkDeviceFaultInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT
PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT() {
    VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT PhysicalDeviceRGBA10X6FormatsFeaturesEXT() {
    VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
inline VkDirectFBSurfaceCreateInfoEXT DirectFBSurfaceCreateInfoEXT() {
    VkDirectFBSurfaceCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT;
    return info;
}
#endif // VK_USE_PLATFORM_DIRECTFB_EXT

inline VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT PhysicalDeviceMutableDescriptorTypeFeaturesEXT() {
    VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_EXT;
    return info;
}

inline VkMutableDescriptorTypeCreateInfoEXT MutableDescriptorTypeCreateInfoEXT() {
    VkMutableDescriptorTypeCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT PhysicalDeviceVertexInputDynamicStateFeaturesEXT() {
    VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT;
    return info;
}

inline VkVertexInputBindingDescription2EXT VertexInputBindingDescription2EXT() {
    VkVertexInputBindingDescription2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT;
    return info;
}

inline VkVertexInputAttributeDescription2EXT VertexInputAttributeDescription2EXT() {
    VkVertexInputAttributeDescription2EXT info{};
    info.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT;
    return info;
}

inline VkPhysicalDeviceDrmPropertiesEXT PhysicalDeviceDrmPropertiesEXT() {
    VkPhysicalDeviceDrmPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceAddressBindingReportFeaturesEXT PhysicalDeviceAddressBindingReportFeaturesEXT() {
    VkPhysicalDeviceAddressBindingReportFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ADDRESS_BINDING_REPORT_FEATURES_EXT;
    return info;
}

inline VkDeviceAddressBindingCallbackDataEXT DeviceAddressBindingCallbackDataEXT() {
    VkDeviceAddressBindingCallbackDataEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_ADDRESS_BINDING_CALLBACK_DATA_EXT;
    return info;
}

inline VkPhysicalDeviceDepthClipControlFeaturesEXT PhysicalDeviceDepthClipControlFeaturesEXT() {
    VkPhysicalDeviceDepthClipControlFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT;
    return info;
}

inline VkPipelineViewportDepthClipControlCreateInfoEXT PipelineViewportDepthClipControlCreateInfoEXT() {
    VkPipelineViewportDepthClipControlCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT PhysicalDevicePrimitiveTopologyListRestartFeaturesEXT() {
    VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_FUCHSIA
inline VkImportMemoryZirconHandleInfoFUCHSIA ImportMemoryZirconHandleInfoFUCHSIA() {
    VkImportMemoryZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA;
    return info;
}

inline VkMemoryZirconHandlePropertiesFUCHSIA MemoryZirconHandlePropertiesFUCHSIA() {
    VkMemoryZirconHandlePropertiesFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA;
    return info;
}

inline VkMemoryGetZirconHandleInfoFUCHSIA MemoryGetZirconHandleInfoFUCHSIA() {
    VkMemoryGetZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA;
    return info;
}

inline VkImportSemaphoreZirconHandleInfoFUCHSIA ImportSemaphoreZirconHandleInfoFUCHSIA() {
    VkImportSemaphoreZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA;
    return info;
}

inline VkSemaphoreGetZirconHandleInfoFUCHSIA SemaphoreGetZirconHandleInfoFUCHSIA() {
    VkSemaphoreGetZirconHandleInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA;
    return info;
}

inline VkBufferCollectionCreateInfoFUCHSIA BufferCollectionCreateInfoFUCHSIA() {
    VkBufferCollectionCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CREATE_INFO_FUCHSIA;
    return info;
}

inline VkImportMemoryBufferCollectionFUCHSIA ImportMemoryBufferCollectionFUCHSIA() {
    VkImportMemoryBufferCollectionFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA;
    return info;
}

inline VkBufferCollectionImageCreateInfoFUCHSIA BufferCollectionImageCreateInfoFUCHSIA() {
    VkBufferCollectionImageCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_IMAGE_CREATE_INFO_FUCHSIA;
    return info;
}

inline VkBufferCollectionConstraintsInfoFUCHSIA BufferCollectionConstraintsInfoFUCHSIA() {
    VkBufferCollectionConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CONSTRAINTS_INFO_FUCHSIA;
    return info;
}

inline VkBufferConstraintsInfoFUCHSIA BufferConstraintsInfoFUCHSIA() {
    VkBufferConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CONSTRAINTS_INFO_FUCHSIA;
    return info;
}

inline VkBufferCollectionBufferCreateInfoFUCHSIA BufferCollectionBufferCreateInfoFUCHSIA() {
    VkBufferCollectionBufferCreateInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_BUFFER_CREATE_INFO_FUCHSIA;
    return info;
}

inline VkSysmemColorSpaceFUCHSIA SysmemColorSpaceFUCHSIA() {
    VkSysmemColorSpaceFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_SYSMEM_COLOR_SPACE_FUCHSIA;
    return info;
}

inline VkBufferCollectionPropertiesFUCHSIA BufferCollectionPropertiesFUCHSIA() {
    VkBufferCollectionPropertiesFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_PROPERTIES_FUCHSIA;
    return info;
}

inline VkImageFormatConstraintsInfoFUCHSIA ImageFormatConstraintsInfoFUCHSIA() {
    VkImageFormatConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_CONSTRAINTS_INFO_FUCHSIA;
    return info;
}

inline VkImageConstraintsInfoFUCHSIA ImageConstraintsInfoFUCHSIA() {
    VkImageConstraintsInfoFUCHSIA info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CONSTRAINTS_INFO_FUCHSIA;
    return info;
}
#endif // VK_USE_PLATFORM_FUCHSIA

inline VkSubpassShadingPipelineCreateInfoHUAWEI SubpassShadingPipelineCreateInfoHUAWEI() {
    VkSubpassShadingPipelineCreateInfoHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_SHADING_PIPELINE_CREATE_INFO_HUAWEI;
    return info;
}

inline VkPhysicalDeviceSubpassShadingFeaturesHUAWEI PhysicalDeviceSubpassShadingFeaturesHUAWEI() {
    VkPhysicalDeviceSubpassShadingFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_FEATURES_HUAWEI;
    return info;
}

inline VkPhysicalDeviceSubpassShadingPropertiesHUAWEI PhysicalDeviceSubpassShadingPropertiesHUAWEI() {
    VkPhysicalDeviceSubpassShadingPropertiesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_PROPERTIES_HUAWEI;
    return info;
}

inline VkPhysicalDeviceInvocationMaskFeaturesHUAWEI PhysicalDeviceInvocationMaskFeaturesHUAWEI() {
    VkPhysicalDeviceInvocationMaskFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI;
    return info;
}

inline VkMemoryGetRemoteAddressInfoNV MemoryGetRemoteAddressInfoNV() {
    VkMemoryGetRemoteAddressInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV;
    return info;
}

inline VkPhysicalDeviceExternalMemoryRDMAFeaturesNV PhysicalDeviceExternalMemoryRDMAFeaturesNV() {
    VkPhysicalDeviceExternalMemoryRDMAFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV;
    return info;
}

inline VkPipelinePropertiesIdentifierEXT PipelinePropertiesIdentifierEXT() {
    VkPipelinePropertiesIdentifierEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_PROPERTIES_IDENTIFIER_EXT;
    return info;
}

inline VkPhysicalDevicePipelinePropertiesFeaturesEXT PhysicalDevicePipelinePropertiesFeaturesEXT() {
    VkPhysicalDevicePipelinePropertiesFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROPERTIES_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceFrameBoundaryFeaturesEXT PhysicalDeviceFrameBoundaryFeaturesEXT() {
    VkPhysicalDeviceFrameBoundaryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAME_BOUNDARY_FEATURES_EXT;
    return info;
}

inline VkFrameBoundaryEXT FrameBoundaryEXT() {
    VkFrameBoundaryEXT info{};
    info.sType = VK_STRUCTURE_TYPE_FRAME_BOUNDARY_EXT;
    return info;
}

inline VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT
PhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT() {
    VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_FEATURES_EXT;
    return info;
}

inline VkSubpassResolvePerformanceQueryEXT SubpassResolvePerformanceQueryEXT() {
    VkSubpassResolvePerformanceQueryEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_RESOLVE_PERFORMANCE_QUERY_EXT;
    return info;
}

inline VkMultisampledRenderToSingleSampledInfoEXT MultisampledRenderToSingleSampledInfoEXT() {
    VkMultisampledRenderToSingleSampledInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicState2FeaturesEXT PhysicalDeviceExtendedDynamicState2FeaturesEXT() {
    VkPhysicalDeviceExtendedDynamicState2FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_SCREEN_QNX
inline VkScreenSurfaceCreateInfoQNX ScreenSurfaceCreateInfoQNX() {
    VkScreenSurfaceCreateInfoQNX info{};
    info.sType = VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX;
    return info;
}
#endif // VK_USE_PLATFORM_SCREEN_QNX

inline VkPhysicalDeviceColorWriteEnableFeaturesEXT PhysicalDeviceColorWriteEnableFeaturesEXT() {
    VkPhysicalDeviceColorWriteEnableFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT;
    return info;
}

inline VkPipelineColorWriteCreateInfoEXT PipelineColorWriteCreateInfoEXT() {
    VkPipelineColorWriteCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT PhysicalDevicePrimitivesGeneratedQueryFeaturesEXT() {
    VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVES_GENERATED_QUERY_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceImageViewMinLodFeaturesEXT PhysicalDeviceImageViewMinLodFeaturesEXT() {
    VkPhysicalDeviceImageViewMinLodFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT;
    return info;
}

inline VkImageViewMinLodCreateInfoEXT ImageViewMinLodCreateInfoEXT() {
    VkImageViewMinLodCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_MIN_LOD_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceMultiDrawFeaturesEXT PhysicalDeviceMultiDrawFeaturesEXT() {
    VkPhysicalDeviceMultiDrawFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceMultiDrawPropertiesEXT PhysicalDeviceMultiDrawPropertiesEXT() {
    VkPhysicalDeviceMultiDrawPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceImage2DViewOf3DFeaturesEXT PhysicalDeviceImage2DViewOf3DFeaturesEXT() {
    VkPhysicalDeviceImage2DViewOf3DFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_2D_VIEW_OF_3D_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceShaderTileImageFeaturesEXT PhysicalDeviceShaderTileImageFeaturesEXT() {
    VkPhysicalDeviceShaderTileImageFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceShaderTileImagePropertiesEXT PhysicalDeviceShaderTileImagePropertiesEXT() {
    VkPhysicalDeviceShaderTileImagePropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_PROPERTIES_EXT;
    return info;
}

inline VkMicromapBuildInfoEXT MicromapBuildInfoEXT() {
    VkMicromapBuildInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT;
    return info;
}

inline VkMicromapCreateInfoEXT MicromapCreateInfoEXT() {
    VkMicromapCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceOpacityMicromapFeaturesEXT PhysicalDeviceOpacityMicromapFeaturesEXT() {
    VkPhysicalDeviceOpacityMicromapFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceOpacityMicromapPropertiesEXT PhysicalDeviceOpacityMicromapPropertiesEXT() {
    VkPhysicalDeviceOpacityMicromapPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_PROPERTIES_EXT;
    return info;
}

inline VkMicromapVersionInfoEXT MicromapVersionInfoEXT() {
    VkMicromapVersionInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_VERSION_INFO_EXT;
    return info;
}

inline VkCopyMicromapToMemoryInfoEXT CopyMicromapToMemoryInfoEXT() {
    VkCopyMicromapToMemoryInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_TO_MEMORY_INFO_EXT;
    return info;
}

inline VkCopyMemoryToMicromapInfoEXT CopyMemoryToMicromapInfoEXT() {
    VkCopyMemoryToMicromapInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_MICROMAP_INFO_EXT;
    return info;
}

inline VkCopyMicromapInfoEXT CopyMicromapInfoEXT() {
    VkCopyMicromapInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT;
    return info;
}

inline VkMicromapBuildSizesInfoEXT MicromapBuildSizesInfoEXT() {
    VkMicromapBuildSizesInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_SIZES_INFO_EXT;
    return info;
}

inline VkAccelerationStructureTrianglesOpacityMicromapEXT AccelerationStructureTrianglesOpacityMicromapEXT() {
    VkAccelerationStructureTrianglesOpacityMicromapEXT info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_OPACITY_MICROMAP_EXT;
    return info;
}

#ifdef VK_ENABLE_BETA_EXTENSIONS
inline VkPhysicalDeviceDisplacementMicromapFeaturesNV PhysicalDeviceDisplacementMicromapFeaturesNV() {
    VkPhysicalDeviceDisplacementMicromapFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISPLACEMENT_MICROMAP_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceDisplacementMicromapPropertiesNV PhysicalDeviceDisplacementMicromapPropertiesNV() {
    VkPhysicalDeviceDisplacementMicromapPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISPLACEMENT_MICROMAP_PROPERTIES_NV;
    return info;
}

inline VkAccelerationStructureTrianglesDisplacementMicromapNV AccelerationStructureTrianglesDisplacementMicromapNV() {
    VkAccelerationStructureTrianglesDisplacementMicromapNV info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_DISPLACEMENT_MICROMAP_NV;
    return info;
}
#endif // VK_ENABLE_BETA_EXTENSIONS

inline VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI PhysicalDeviceClusterCullingShaderFeaturesHUAWEI() {
    VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_FEATURES_HUAWEI;
    return info;
}

inline VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI PhysicalDeviceClusterCullingShaderPropertiesHUAWEI() {
    VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_PROPERTIES_HUAWEI;
    return info;
}

inline VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI PhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI() {
    VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_VRS_FEATURES_HUAWEI;
    return info;
}

inline VkPhysicalDeviceBorderColorSwizzleFeaturesEXT PhysicalDeviceBorderColorSwizzleFeaturesEXT() {
    VkPhysicalDeviceBorderColorSwizzleFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT;
    return info;
}

inline VkSamplerBorderColorComponentMappingCreateInfoEXT SamplerBorderColorComponentMappingCreateInfoEXT() {
    VkSamplerBorderColorComponentMappingCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT PhysicalDevicePageableDeviceLocalMemoryFeaturesEXT() {
    VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceShaderCorePropertiesARM PhysicalDeviceShaderCorePropertiesARM() {
    VkPhysicalDeviceShaderCorePropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_ARM;
    return info;
}

inline VkDeviceQueueShaderCoreControlCreateInfoARM DeviceQueueShaderCoreControlCreateInfoARM() {
    VkDeviceQueueShaderCoreControlCreateInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_SHADER_CORE_CONTROL_CREATE_INFO_ARM;
    return info;
}

inline VkPhysicalDeviceSchedulingControlsFeaturesARM PhysicalDeviceSchedulingControlsFeaturesARM() {
    VkPhysicalDeviceSchedulingControlsFeaturesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_FEATURES_ARM;
    return info;
}

inline VkPhysicalDeviceSchedulingControlsPropertiesARM PhysicalDeviceSchedulingControlsPropertiesARM() {
    VkPhysicalDeviceSchedulingControlsPropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_PROPERTIES_ARM;
    return info;
}

inline VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT PhysicalDeviceImageSlicedViewOf3DFeaturesEXT() {
    VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_SLICED_VIEW_OF_3D_FEATURES_EXT;
    return info;
}

inline VkImageViewSlicedCreateInfoEXT ImageViewSlicedCreateInfoEXT() {
    VkImageViewSlicedCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_SLICED_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE PhysicalDeviceDescriptorSetHostMappingFeaturesVALVE() {
    VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_SET_HOST_MAPPING_FEATURES_VALVE;
    return info;
}

inline VkDescriptorSetBindingReferenceVALVE DescriptorSetBindingReferenceVALVE() {
    VkDescriptorSetBindingReferenceVALVE info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_BINDING_REFERENCE_VALVE;
    return info;
}

inline VkDescriptorSetLayoutHostMappingInfoVALVE DescriptorSetLayoutHostMappingInfoVALVE() {
    VkDescriptorSetLayoutHostMappingInfoVALVE info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_HOST_MAPPING_INFO_VALVE;
    return info;
}

inline VkPhysicalDeviceDepthClampZeroOneFeaturesEXT PhysicalDeviceDepthClampZeroOneFeaturesEXT() {
    VkPhysicalDeviceDepthClampZeroOneFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLAMP_ZERO_ONE_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT PhysicalDeviceNonSeamlessCubeMapFeaturesEXT() {
    VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NON_SEAMLESS_CUBE_MAP_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceRenderPassStripedFeaturesARM PhysicalDeviceRenderPassStripedFeaturesARM() {
    VkPhysicalDeviceRenderPassStripedFeaturesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RENDER_PASS_STRIPED_FEATURES_ARM;
    return info;
}

inline VkPhysicalDeviceRenderPassStripedPropertiesARM PhysicalDeviceRenderPassStripedPropertiesARM() {
    VkPhysicalDeviceRenderPassStripedPropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RENDER_PASS_STRIPED_PROPERTIES_ARM;
    return info;
}

inline VkRenderPassStripeInfoARM RenderPassStripeInfoARM() {
    VkRenderPassStripeInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_INFO_ARM;
    return info;
}

inline VkRenderPassStripeBeginInfoARM RenderPassStripeBeginInfoARM() {
    VkRenderPassStripeBeginInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_BEGIN_INFO_ARM;
    return info;
}

inline VkRenderPassStripeSubmitInfoARM RenderPassStripeSubmitInfoARM() {
    VkRenderPassStripeSubmitInfoARM info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_SUBMIT_INFO_ARM;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM PhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM() {
    VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM;
    return info;
}

inline VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM PhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM() {
    VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM;
    return info;
}

inline VkSubpassFragmentDensityMapOffsetEndInfoQCOM SubpassFragmentDensityMapOffsetEndInfoQCOM() {
    VkSubpassFragmentDensityMapOffsetEndInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceCopyMemoryIndirectFeaturesNV PhysicalDeviceCopyMemoryIndirectFeaturesNV() {
    VkPhysicalDeviceCopyMemoryIndirectFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceCopyMemoryIndirectPropertiesNV PhysicalDeviceCopyMemoryIndirectPropertiesNV() {
    VkPhysicalDeviceCopyMemoryIndirectPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceMemoryDecompressionFeaturesNV PhysicalDeviceMemoryDecompressionFeaturesNV() {
    VkPhysicalDeviceMemoryDecompressionFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceMemoryDecompressionPropertiesNV PhysicalDeviceMemoryDecompressionPropertiesNV() {
    VkPhysicalDeviceMemoryDecompressionPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV PhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV() {
    VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_COMPUTE_FEATURES_NV;
    return info;
}

inline VkComputePipelineIndirectBufferInfoNV ComputePipelineIndirectBufferInfoNV() {
    VkComputePipelineIndirectBufferInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_INDIRECT_BUFFER_INFO_NV;
    return info;
}

inline VkPipelineIndirectDeviceAddressInfoNV PipelineIndirectDeviceAddressInfoNV() {
    VkPipelineIndirectDeviceAddressInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_INDIRECT_DEVICE_ADDRESS_INFO_NV;
    return info;
}

inline VkPhysicalDeviceLinearColorAttachmentFeaturesNV PhysicalDeviceLinearColorAttachmentFeaturesNV() {
    VkPhysicalDeviceLinearColorAttachmentFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT PhysicalDeviceImageCompressionControlSwapchainFeaturesEXT() {
    VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_FEATURES_EXT;
    return info;
}

inline VkImageViewSampleWeightCreateInfoQCOM ImageViewSampleWeightCreateInfoQCOM() {
    VkImageViewSampleWeightCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_SAMPLE_WEIGHT_CREATE_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceImageProcessingFeaturesQCOM PhysicalDeviceImageProcessingFeaturesQCOM() {
    VkPhysicalDeviceImageProcessingFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_FEATURES_QCOM;
    return info;
}

inline VkPhysicalDeviceImageProcessingPropertiesQCOM PhysicalDeviceImageProcessingPropertiesQCOM() {
    VkPhysicalDeviceImageProcessingPropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_PROPERTIES_QCOM;
    return info;
}

inline VkPhysicalDeviceNestedCommandBufferFeaturesEXT PhysicalDeviceNestedCommandBufferFeaturesEXT() {
    VkPhysicalDeviceNestedCommandBufferFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceNestedCommandBufferPropertiesEXT PhysicalDeviceNestedCommandBufferPropertiesEXT() {
    VkPhysicalDeviceNestedCommandBufferPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_PROPERTIES_EXT;
    return info;
}

inline VkExternalMemoryAcquireUnmodifiedEXT ExternalMemoryAcquireUnmodifiedEXT() {
    VkExternalMemoryAcquireUnmodifiedEXT info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_EXT;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicState3FeaturesEXT PhysicalDeviceExtendedDynamicState3FeaturesEXT() {
    VkPhysicalDeviceExtendedDynamicState3FeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceExtendedDynamicState3PropertiesEXT PhysicalDeviceExtendedDynamicState3PropertiesEXT() {
    VkPhysicalDeviceExtendedDynamicState3PropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_PROPERTIES_EXT;
    return info;
}

inline VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT PhysicalDeviceSubpassMergeFeedbackFeaturesEXT() {
    VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_MERGE_FEEDBACK_FEATURES_EXT;
    return info;
}

inline VkRenderPassCreationControlEXT RenderPassCreationControlEXT() {
    VkRenderPassCreationControlEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_CONTROL_EXT;
    return info;
}

inline VkRenderPassCreationFeedbackCreateInfoEXT RenderPassCreationFeedbackCreateInfoEXT() {
    VkRenderPassCreationFeedbackCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_FEEDBACK_CREATE_INFO_EXT;
    return info;
}

inline VkRenderPassSubpassFeedbackCreateInfoEXT RenderPassSubpassFeedbackCreateInfoEXT() {
    VkRenderPassSubpassFeedbackCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SUBPASS_FEEDBACK_CREATE_INFO_EXT;
    return info;
}

inline VkDirectDriverLoadingInfoLUNARG DirectDriverLoadingInfoLUNARG() {
    VkDirectDriverLoadingInfoLUNARG info{};
    info.sType = VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_INFO_LUNARG;
    return info;
}

inline VkDirectDriverLoadingListLUNARG DirectDriverLoadingListLUNARG() {
    VkDirectDriverLoadingListLUNARG info{};
    info.sType = VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_LIST_LUNARG;
    return info;
}

inline VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT PhysicalDeviceShaderModuleIdentifierFeaturesEXT() {
    VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT PhysicalDeviceShaderModuleIdentifierPropertiesEXT() {
    VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_PROPERTIES_EXT;
    return info;
}

inline VkPipelineShaderStageModuleIdentifierCreateInfoEXT PipelineShaderStageModuleIdentifierCreateInfoEXT() {
    VkPipelineShaderStageModuleIdentifierCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_MODULE_IDENTIFIER_CREATE_INFO_EXT;
    return info;
}

inline VkShaderModuleIdentifierEXT ShaderModuleIdentifierEXT() {
    VkShaderModuleIdentifierEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_IDENTIFIER_EXT;
    return info;
}

inline VkPhysicalDeviceOpticalFlowFeaturesNV PhysicalDeviceOpticalFlowFeaturesNV() {
    VkPhysicalDeviceOpticalFlowFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceOpticalFlowPropertiesNV PhysicalDeviceOpticalFlowPropertiesNV() {
    VkPhysicalDeviceOpticalFlowPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV;
    return info;
}

inline VkOpticalFlowImageFormatInfoNV OpticalFlowImageFormatInfoNV() {
    VkOpticalFlowImageFormatInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
    return info;
}

inline VkOpticalFlowImageFormatPropertiesNV OpticalFlowImageFormatPropertiesNV() {
    VkOpticalFlowImageFormatPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV;
    return info;
}

inline VkOpticalFlowSessionCreateInfoNV OpticalFlowSessionCreateInfoNV() {
    VkOpticalFlowSessionCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_INFO_NV;
    return info;
}

inline VkOpticalFlowSessionCreatePrivateDataInfoNV OpticalFlowSessionCreatePrivateDataInfoNV() {
    VkOpticalFlowSessionCreatePrivateDataInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_PRIVATE_DATA_INFO_NV;
    return info;
}

inline VkOpticalFlowExecuteInfoNV OpticalFlowExecuteInfoNV() {
    VkOpticalFlowExecuteInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV;
    return info;
}

inline VkPhysicalDeviceLegacyDitheringFeaturesEXT PhysicalDeviceLegacyDitheringFeaturesEXT() {
    VkPhysicalDeviceLegacyDitheringFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LEGACY_DITHERING_FEATURES_EXT;
    return info;
}

inline VkPhysicalDevicePipelineProtectedAccessFeaturesEXT PhysicalDevicePipelineProtectedAccessFeaturesEXT() {
    VkPhysicalDevicePipelineProtectedAccessFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROTECTED_ACCESS_FEATURES_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_ANDROID_KHR
inline VkPhysicalDeviceExternalFormatResolveFeaturesANDROID PhysicalDeviceExternalFormatResolveFeaturesANDROID() {
    VkPhysicalDeviceExternalFormatResolveFeaturesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FORMAT_RESOLVE_FEATURES_ANDROID;
    return info;
}

inline VkPhysicalDeviceExternalFormatResolvePropertiesANDROID PhysicalDeviceExternalFormatResolvePropertiesANDROID() {
    VkPhysicalDeviceExternalFormatResolvePropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FORMAT_RESOLVE_PROPERTIES_ANDROID;
    return info;
}

inline VkAndroidHardwareBufferFormatResolvePropertiesANDROID AndroidHardwareBufferFormatResolvePropertiesANDROID() {
    VkAndroidHardwareBufferFormatResolvePropertiesANDROID info{};
    info.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_RESOLVE_PROPERTIES_ANDROID;
    return info;
}
#endif // VK_USE_PLATFORM_ANDROID_KHR

inline VkPhysicalDeviceShaderObjectFeaturesEXT PhysicalDeviceShaderObjectFeaturesEXT() {
    VkPhysicalDeviceShaderObjectFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceShaderObjectPropertiesEXT PhysicalDeviceShaderObjectPropertiesEXT() {
    VkPhysicalDeviceShaderObjectPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_PROPERTIES_EXT;
    return info;
}

inline VkShaderCreateInfoEXT ShaderCreateInfoEXT() {
    VkShaderCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceTilePropertiesFeaturesQCOM PhysicalDeviceTilePropertiesFeaturesQCOM() {
    VkPhysicalDeviceTilePropertiesFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_PROPERTIES_FEATURES_QCOM;
    return info;
}

inline VkTilePropertiesQCOM TilePropertiesQCOM() {
    VkTilePropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_TILE_PROPERTIES_QCOM;
    return info;
}

inline VkPhysicalDeviceAmigoProfilingFeaturesSEC PhysicalDeviceAmigoProfilingFeaturesSEC() {
    VkPhysicalDeviceAmigoProfilingFeaturesSEC info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_AMIGO_PROFILING_FEATURES_SEC;
    return info;
}

inline VkAmigoProfilingSubmitInfoSEC AmigoProfilingSubmitInfoSEC() {
    VkAmigoProfilingSubmitInfoSEC info{};
    info.sType = VK_STRUCTURE_TYPE_AMIGO_PROFILING_SUBMIT_INFO_SEC;
    return info;
}

inline VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM PhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM() {
    VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_VIEWPORTS_FEATURES_QCOM;
    return info;
}

inline VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV PhysicalDeviceRayTracingInvocationReorderPropertiesNV() {
    VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_PROPERTIES_NV;
    return info;
}

inline VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV PhysicalDeviceRayTracingInvocationReorderFeaturesNV() {
    VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV PhysicalDeviceExtendedSparseAddressSpaceFeaturesNV() {
    VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_SPARSE_ADDRESS_SPACE_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV PhysicalDeviceExtendedSparseAddressSpacePropertiesNV() {
    VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_SPARSE_ADDRESS_SPACE_PROPERTIES_NV;
    return info;
}

inline VkLayerSettingsCreateInfoEXT LayerSettingsCreateInfoEXT() {
    VkLayerSettingsCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT;
    return info;
}

inline VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM PhysicalDeviceShaderCoreBuiltinsFeaturesARM() {
    VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_FEATURES_ARM;
    return info;
}

inline VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM PhysicalDeviceShaderCoreBuiltinsPropertiesARM() {
    VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_PROPERTIES_ARM;
    return info;
}

inline VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT PhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT() {
    VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_LIBRARY_GROUP_HANDLES_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT
PhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT() {
    VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_FEATURES_EXT;
    return info;
}

inline VkLatencySleepModeInfoNV LatencySleepModeInfoNV() {
    VkLatencySleepModeInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_MODE_INFO_NV;
    return info;
}

inline VkLatencySleepInfoNV LatencySleepInfoNV() {
    VkLatencySleepInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_INFO_NV;
    return info;
}

inline VkSetLatencyMarkerInfoNV SetLatencyMarkerInfoNV() {
    VkSetLatencyMarkerInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_SET_LATENCY_MARKER_INFO_NV;
    return info;
}

inline VkLatencyTimingsFrameReportNV LatencyTimingsFrameReportNV() {
    VkLatencyTimingsFrameReportNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_TIMINGS_FRAME_REPORT_NV;
    return info;
}

inline VkGetLatencyMarkerInfoNV GetLatencyMarkerInfoNV() {
    VkGetLatencyMarkerInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_GET_LATENCY_MARKER_INFO_NV;
    return info;
}

inline VkLatencySubmissionPresentIdNV LatencySubmissionPresentIdNV() {
    VkLatencySubmissionPresentIdNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SUBMISSION_PRESENT_ID_NV;
    return info;
}

inline VkSwapchainLatencyCreateInfoNV SwapchainLatencyCreateInfoNV() {
    VkSwapchainLatencyCreateInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_LATENCY_CREATE_INFO_NV;
    return info;
}

inline VkOutOfBandQueueTypeInfoNV OutOfBandQueueTypeInfoNV() {
    VkOutOfBandQueueTypeInfoNV info{};
    info.sType = VK_STRUCTURE_TYPE_OUT_OF_BAND_QUEUE_TYPE_INFO_NV;
    return info;
}

inline VkLatencySurfaceCapabilitiesNV LatencySurfaceCapabilitiesNV() {
    VkLatencySurfaceCapabilitiesNV info{};
    info.sType = VK_STRUCTURE_TYPE_LATENCY_SURFACE_CAPABILITIES_NV;
    return info;
}

inline VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM PhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM() {
    VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_RENDER_AREAS_FEATURES_QCOM;
    return info;
}

inline VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM() {
    VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_RENDER_AREAS_RENDER_PASS_BEGIN_INFO_QCOM;
    return info;
}

inline VkPhysicalDevicePerStageDescriptorSetFeaturesNV PhysicalDevicePerStageDescriptorSetFeaturesNV() {
    VkPhysicalDevicePerStageDescriptorSetFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PER_STAGE_DESCRIPTOR_SET_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceImageProcessing2FeaturesQCOM PhysicalDeviceImageProcessing2FeaturesQCOM() {
    VkPhysicalDeviceImageProcessing2FeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_2_FEATURES_QCOM;
    return info;
}

inline VkPhysicalDeviceImageProcessing2PropertiesQCOM PhysicalDeviceImageProcessing2PropertiesQCOM() {
    VkPhysicalDeviceImageProcessing2PropertiesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_2_PROPERTIES_QCOM;
    return info;
}

inline VkSamplerBlockMatchWindowCreateInfoQCOM SamplerBlockMatchWindowCreateInfoQCOM() {
    VkSamplerBlockMatchWindowCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_BLOCK_MATCH_WINDOW_CREATE_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceCubicWeightsFeaturesQCOM PhysicalDeviceCubicWeightsFeaturesQCOM() {
    VkPhysicalDeviceCubicWeightsFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUBIC_WEIGHTS_FEATURES_QCOM;
    return info;
}

inline VkSamplerCubicWeightsCreateInfoQCOM SamplerCubicWeightsCreateInfoQCOM() {
    VkSamplerCubicWeightsCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_CUBIC_WEIGHTS_CREATE_INFO_QCOM;
    return info;
}

inline VkBlitImageCubicWeightsInfoQCOM BlitImageCubicWeightsInfoQCOM() {
    VkBlitImageCubicWeightsInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_CUBIC_WEIGHTS_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceYcbcrDegammaFeaturesQCOM PhysicalDeviceYcbcrDegammaFeaturesQCOM() {
    VkPhysicalDeviceYcbcrDegammaFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_DEGAMMA_FEATURES_QCOM;
    return info;
}

inline VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM SamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM() {
    VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_YCBCR_DEGAMMA_CREATE_INFO_QCOM;
    return info;
}

inline VkPhysicalDeviceCubicClampFeaturesQCOM PhysicalDeviceCubicClampFeaturesQCOM() {
    VkPhysicalDeviceCubicClampFeaturesQCOM info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUBIC_CLAMP_FEATURES_QCOM;
    return info;
}

inline VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT
PhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT() {
    VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_FEATURES_EXT;
    return info;
}

#ifdef VK_USE_PLATFORM_SCREEN_QNX
inline VkScreenBufferPropertiesQNX ScreenBufferPropertiesQNX() {
    VkScreenBufferPropertiesQNX info{};
    info.sType = VK_STRUCTURE_TYPE_SCREEN_BUFFER_PROPERTIES_QNX;
    return info;
}

inline VkScreenBufferFormatPropertiesQNX ScreenBufferFormatPropertiesQNX() {
    VkScreenBufferFormatPropertiesQNX info{};
    info.sType = VK_STRUCTURE_TYPE_SCREEN_BUFFER_FORMAT_PROPERTIES_QNX;
    return info;
}

inline VkImportScreenBufferInfoQNX ImportScreenBufferInfoQNX() {
    VkImportScreenBufferInfoQNX info{};
    info.sType = VK_STRUCTURE_TYPE_IMPORT_SCREEN_BUFFER_INFO_QNX;
    return info;
}

inline VkExternalFormatQNX ExternalFormatQNX() {
    VkExternalFormatQNX info{};
    info.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_QNX;
    return info;
}

inline VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX PhysicalDeviceExternalMemoryScreenBufferFeaturesQNX() {
    VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_SCREEN_BUFFER_FEATURES_QNX;
    return info;
}
#endif // VK_USE_PLATFORM_SCREEN_QNX

inline VkPhysicalDeviceLayeredDriverPropertiesMSFT PhysicalDeviceLayeredDriverPropertiesMSFT() {
    VkPhysicalDeviceLayeredDriverPropertiesMSFT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LAYERED_DRIVER_PROPERTIES_MSFT;
    return info;
}

inline VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV PhysicalDeviceDescriptorPoolOverallocationFeaturesNV() {
    VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_POOL_OVERALLOCATION_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceRawAccessChainsFeaturesNV PhysicalDeviceRawAccessChainsFeaturesNV() {
    VkPhysicalDeviceRawAccessChainsFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAW_ACCESS_CHAINS_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV PhysicalDeviceShaderAtomicFloat16VectorFeaturesNV() {
    VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT16_VECTOR_FEATURES_NV;
    return info;
}

inline VkPhysicalDeviceRayTracingValidationFeaturesNV PhysicalDeviceRayTracingValidationFeaturesNV() {
    VkPhysicalDeviceRayTracingValidationFeaturesNV info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_VALIDATION_FEATURES_NV;
    return info;
}

inline VkAccelerationStructureGeometryTrianglesDataKHR AccelerationStructureGeometryTrianglesDataKHR() {
    VkAccelerationStructureGeometryTrianglesDataKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
    return info;
}

inline VkAccelerationStructureGeometryAabbsDataKHR AccelerationStructureGeometryAabbsDataKHR() {
    VkAccelerationStructureGeometryAabbsDataKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
    return info;
}

inline VkAccelerationStructureGeometryInstancesDataKHR AccelerationStructureGeometryInstancesDataKHR() {
    VkAccelerationStructureGeometryInstancesDataKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
    return info;
}

inline VkAccelerationStructureGeometryKHR AccelerationStructureGeometryKHR() {
    VkAccelerationStructureGeometryKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    return info;
}

inline VkAccelerationStructureBuildGeometryInfoKHR AccelerationStructureBuildGeometryInfoKHR() {
    VkAccelerationStructureBuildGeometryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    return info;
}

inline VkAccelerationStructureCreateInfoKHR AccelerationStructureCreateInfoKHR() {
    VkAccelerationStructureCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    return info;
}

inline VkWriteDescriptorSetAccelerationStructureKHR WriteDescriptorSetAccelerationStructureKHR() {
    VkWriteDescriptorSetAccelerationStructureKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
    return info;
}

inline VkPhysicalDeviceAccelerationStructureFeaturesKHR PhysicalDeviceAccelerationStructureFeaturesKHR() {
    VkPhysicalDeviceAccelerationStructureFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceAccelerationStructurePropertiesKHR PhysicalDeviceAccelerationStructurePropertiesKHR() {
    VkPhysicalDeviceAccelerationStructurePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
    return info;
}

inline VkAccelerationStructureDeviceAddressInfoKHR AccelerationStructureDeviceAddressInfoKHR() {
    VkAccelerationStructureDeviceAddressInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
    return info;
}

inline VkAccelerationStructureVersionInfoKHR AccelerationStructureVersionInfoKHR() {
    VkAccelerationStructureVersionInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR;
    return info;
}

inline VkCopyAccelerationStructureToMemoryInfoKHR CopyAccelerationStructureToMemoryInfoKHR() {
    VkCopyAccelerationStructureToMemoryInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR;
    return info;
}

inline VkCopyMemoryToAccelerationStructureInfoKHR CopyMemoryToAccelerationStructureInfoKHR() {
    VkCopyMemoryToAccelerationStructureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR;
    return info;
}

inline VkCopyAccelerationStructureInfoKHR CopyAccelerationStructureInfoKHR() {
    VkCopyAccelerationStructureInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR;
    return info;
}

inline VkAccelerationStructureBuildSizesInfoKHR AccelerationStructureBuildSizesInfoKHR() {
    VkAccelerationStructureBuildSizesInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
    return info;
}

inline VkRayTracingShaderGroupCreateInfoKHR RayTracingShaderGroupCreateInfoKHR() {
    VkRayTracingShaderGroupCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
    return info;
}

inline VkRayTracingPipelineInterfaceCreateInfoKHR RayTracingPipelineInterfaceCreateInfoKHR() {
    VkRayTracingPipelineInterfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR;
    return info;
}

inline VkRayTracingPipelineCreateInfoKHR RayTracingPipelineCreateInfoKHR() {
    VkRayTracingPipelineCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
    return info;
}

inline VkPhysicalDeviceRayTracingPipelineFeaturesKHR PhysicalDeviceRayTracingPipelineFeaturesKHR() {
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceRayTracingPipelinePropertiesKHR PhysicalDeviceRayTracingPipelinePropertiesKHR() {
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    return info;
}

inline VkPhysicalDeviceRayQueryFeaturesKHR PhysicalDeviceRayQueryFeaturesKHR() {
    VkPhysicalDeviceRayQueryFeaturesKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
    return info;
}

inline VkPhysicalDeviceMeshShaderFeaturesEXT PhysicalDeviceMeshShaderFeaturesEXT() {
    VkPhysicalDeviceMeshShaderFeaturesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
    return info;
}

inline VkPhysicalDeviceMeshShaderPropertiesEXT PhysicalDeviceMeshShaderPropertiesEXT() {
    VkPhysicalDeviceMeshShaderPropertiesEXT info{};
    info.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
    return info;
}

} // namespace Itor
} // namespace vkt
