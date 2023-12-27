#pragma once

#include <string>
#include <vulkan/vulkan.h>

#define VkStr(Type, Var) vkt::On_Str_##Type(Var)

namespace vkt {
// Enums
std::string On_Str_VkResult(VkResult e);
std::string On_Str_VkStructureType(VkStructureType e);
std::string On_Str_VkPipelineCacheHeaderVersion(VkPipelineCacheHeaderVersion e);
std::string On_Str_VkImageLayout(VkImageLayout e);
std::string On_Str_VkObjectType(VkObjectType e);
std::string On_Str_VkVendorId(VkVendorId e);
std::string On_Str_VkSystemAllocationScope(VkSystemAllocationScope e);
std::string On_Str_VkInternalAllocationType(VkInternalAllocationType e);
std::string On_Str_VkFormat(VkFormat e);
std::string On_Str_VkImageTiling(VkImageTiling e);
std::string On_Str_VkImageType(VkImageType e);
std::string On_Str_VkPhysicalDeviceType(VkPhysicalDeviceType e);
std::string On_Str_VkQueryType(VkQueryType e);
std::string On_Str_VkSharingMode(VkSharingMode e);
std::string On_Str_VkComponentSwizzle(VkComponentSwizzle e);
std::string On_Str_VkImageViewType(VkImageViewType e);
std::string On_Str_VkBlendFactor(VkBlendFactor e);
std::string On_Str_VkBlendOp(VkBlendOp e);
std::string On_Str_VkCompareOp(VkCompareOp e);
std::string On_Str_VkDynamicState(VkDynamicState e);
std::string On_Str_VkFrontFace(VkFrontFace e);
std::string On_Str_VkVertexInputRate(VkVertexInputRate e);
std::string On_Str_VkPrimitiveTopology(VkPrimitiveTopology e);
std::string On_Str_VkPolygonMode(VkPolygonMode e);
std::string On_Str_VkStencilOp(VkStencilOp e);
std::string On_Str_VkLogicOp(VkLogicOp e);
std::string On_Str_VkBorderColor(VkBorderColor e);
std::string On_Str_VkFilter(VkFilter e);
std::string On_Str_VkSamplerAddressMode(VkSamplerAddressMode e);
std::string On_Str_VkSamplerMipmapMode(VkSamplerMipmapMode e);
std::string On_Str_VkDescriptorType(VkDescriptorType e);
std::string On_Str_VkAttachmentLoadOp(VkAttachmentLoadOp e);
std::string On_Str_VkAttachmentStoreOp(VkAttachmentStoreOp e);
std::string On_Str_VkPipelineBindPoint(VkPipelineBindPoint e);
std::string On_Str_VkCommandBufferLevel(VkCommandBufferLevel e);
std::string On_Str_VkIndexType(VkIndexType e);
std::string On_Str_VkSubpassContents(VkSubpassContents e);
std::string On_Str_VkPointClippingBehavior(VkPointClippingBehavior e);
std::string On_Str_VkTessellationDomainOrigin(VkTessellationDomainOrigin e);
std::string On_Str_VkSamplerYcbcrModelConversion(VkSamplerYcbcrModelConversion e);
std::string On_Str_VkSamplerYcbcrRange(VkSamplerYcbcrRange e);
std::string On_Str_VkChromaLocation(VkChromaLocation e);
std::string On_Str_VkDescriptorUpdateTemplateType(VkDescriptorUpdateTemplateType e);
std::string On_Str_VkDriverId(VkDriverId e);
std::string On_Str_VkShaderFloatControlsIndependence(VkShaderFloatControlsIndependence e);
std::string On_Str_VkSamplerReductionMode(VkSamplerReductionMode e);
std::string On_Str_VkSemaphoreType(VkSemaphoreType e);
std::string On_Str_VkPresentModeKHR(VkPresentModeKHR e);
std::string On_Str_VkColorSpaceKHR(VkColorSpaceKHR e);
std::string On_Str_VkQueryResultStatusKHR(VkQueryResultStatusKHR e);
std::string On_Str_VkPerformanceCounterUnitKHR(VkPerformanceCounterUnitKHR e);
std::string On_Str_VkPerformanceCounterScopeKHR(VkPerformanceCounterScopeKHR e);
std::string On_Str_VkPerformanceCounterStorageKHR(VkPerformanceCounterStorageKHR e);
std::string On_Str_VkQueueGlobalPriorityKHR(VkQueueGlobalPriorityKHR e);
std::string On_Str_VkFragmentShadingRateCombinerOpKHR(VkFragmentShadingRateCombinerOpKHR e);
std::string On_Str_VkPipelineExecutableStatisticFormatKHR(VkPipelineExecutableStatisticFormatKHR e);
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeTuningModeKHR(VkVideoEncodeTuningModeKHR e);
#endif // VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkComponentTypeKHR(VkComponentTypeKHR e);
std::string On_Str_VkScopeKHR(VkScopeKHR e);
std::string On_Str_VkDebugReportObjectTypeEXT(VkDebugReportObjectTypeEXT e);
std::string On_Str_VkRasterizationOrderAMD(VkRasterizationOrderAMD e);
std::string On_Str_VkShaderInfoTypeAMD(VkShaderInfoTypeAMD e);
std::string On_Str_VkValidationCheckEXT(VkValidationCheckEXT e);
std::string On_Str_VkPipelineRobustnessBufferBehaviorEXT(VkPipelineRobustnessBufferBehaviorEXT e);
std::string On_Str_VkPipelineRobustnessImageBehaviorEXT(VkPipelineRobustnessImageBehaviorEXT e);
std::string On_Str_VkDisplayPowerStateEXT(VkDisplayPowerStateEXT e);
std::string On_Str_VkDeviceEventTypeEXT(VkDeviceEventTypeEXT e);
std::string On_Str_VkDisplayEventTypeEXT(VkDisplayEventTypeEXT e);
std::string On_Str_VkViewportCoordinateSwizzleNV(VkViewportCoordinateSwizzleNV e);
std::string On_Str_VkDiscardRectangleModeEXT(VkDiscardRectangleModeEXT e);
std::string On_Str_VkConservativeRasterizationModeEXT(VkConservativeRasterizationModeEXT e);
std::string On_Str_VkBlendOverlapEXT(VkBlendOverlapEXT e);
std::string On_Str_VkCoverageModulationModeNV(VkCoverageModulationModeNV e);
std::string On_Str_VkValidationCacheHeaderVersionEXT(VkValidationCacheHeaderVersionEXT e);
std::string On_Str_VkShadingRatePaletteEntryNV(VkShadingRatePaletteEntryNV e);
std::string On_Str_VkCoarseSampleOrderTypeNV(VkCoarseSampleOrderTypeNV e);
std::string On_Str_VkRayTracingShaderGroupTypeKHR(VkRayTracingShaderGroupTypeKHR e);
std::string On_Str_VkGeometryTypeKHR(VkGeometryTypeKHR e);
std::string On_Str_VkAccelerationStructureTypeKHR(VkAccelerationStructureTypeKHR e);
std::string On_Str_VkCopyAccelerationStructureModeKHR(VkCopyAccelerationStructureModeKHR e);
std::string On_Str_VkAccelerationStructureMemoryRequirementsTypeNV(VkAccelerationStructureMemoryRequirementsTypeNV e);
std::string On_Str_VkTimeDomainEXT(VkTimeDomainEXT e);
std::string On_Str_VkMemoryOverallocationBehaviorAMD(VkMemoryOverallocationBehaviorAMD e);
std::string On_Str_VkPerformanceConfigurationTypeINTEL(VkPerformanceConfigurationTypeINTEL e);
std::string On_Str_VkQueryPoolSamplingModeINTEL(VkQueryPoolSamplingModeINTEL e);
std::string On_Str_VkPerformanceOverrideTypeINTEL(VkPerformanceOverrideTypeINTEL e);
std::string On_Str_VkPerformanceParameterTypeINTEL(VkPerformanceParameterTypeINTEL e);
std::string On_Str_VkPerformanceValueTypeINTEL(VkPerformanceValueTypeINTEL e);
std::string On_Str_VkValidationFeatureEnableEXT(VkValidationFeatureEnableEXT e);
std::string On_Str_VkValidationFeatureDisableEXT(VkValidationFeatureDisableEXT e);
std::string On_Str_VkCoverageReductionModeNV(VkCoverageReductionModeNV e);
std::string On_Str_VkProvokingVertexModeEXT(VkProvokingVertexModeEXT e);
#ifdef VK_USE_PLATFORM_WIN32_KHR
std::string On_Str_VkFullScreenExclusiveEXT(VkFullScreenExclusiveEXT e);
#endif // VK_USE_PLATFORM_WIN32_KHR
std::string On_Str_VkLineRasterizationModeEXT(VkLineRasterizationModeEXT e);
std::string On_Str_VkIndirectCommandsTokenTypeNV(VkIndirectCommandsTokenTypeNV e);
std::string On_Str_VkDepthBiasRepresentationEXT(VkDepthBiasRepresentationEXT e);
std::string On_Str_VkDeviceMemoryReportEventTypeEXT(VkDeviceMemoryReportEventTypeEXT e);
std::string On_Str_VkFragmentShadingRateTypeNV(VkFragmentShadingRateTypeNV e);
std::string On_Str_VkFragmentShadingRateNV(VkFragmentShadingRateNV e);
std::string On_Str_VkAccelerationStructureMotionInstanceTypeNV(VkAccelerationStructureMotionInstanceTypeNV e);
std::string On_Str_VkDeviceFaultAddressTypeEXT(VkDeviceFaultAddressTypeEXT e);
std::string On_Str_VkDeviceFaultVendorBinaryHeaderVersionEXT(VkDeviceFaultVendorBinaryHeaderVersionEXT e);
std::string On_Str_VkDeviceAddressBindingTypeEXT(VkDeviceAddressBindingTypeEXT e);
std::string On_Str_VkMicromapTypeEXT(VkMicromapTypeEXT e);
std::string On_Str_VkBuildMicromapModeEXT(VkBuildMicromapModeEXT e);
std::string On_Str_VkCopyMicromapModeEXT(VkCopyMicromapModeEXT e);
std::string On_Str_VkOpacityMicromapFormatEXT(VkOpacityMicromapFormatEXT e);
std::string On_Str_VkOpacityMicromapSpecialIndexEXT(VkOpacityMicromapSpecialIndexEXT e);
std::string On_Str_VkAccelerationStructureCompatibilityKHR(VkAccelerationStructureCompatibilityKHR e);
std::string On_Str_VkAccelerationStructureBuildTypeKHR(VkAccelerationStructureBuildTypeKHR e);
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkDisplacementMicromapFormatNV(VkDisplacementMicromapFormatNV e);
#endif // VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkSubpassMergeStatusEXT(VkSubpassMergeStatusEXT e);
std::string On_Str_VkDirectDriverLoadingModeLUNARG(VkDirectDriverLoadingModeLUNARG e);
std::string On_Str_VkOpticalFlowPerformanceLevelNV(VkOpticalFlowPerformanceLevelNV e);
std::string On_Str_VkOpticalFlowSessionBindingPointNV(VkOpticalFlowSessionBindingPointNV e);
std::string On_Str_VkShaderCodeTypeEXT(VkShaderCodeTypeEXT e);
std::string On_Str_VkRayTracingInvocationReorderModeNV(VkRayTracingInvocationReorderModeNV e);
std::string On_Str_VkBuildAccelerationStructureModeKHR(VkBuildAccelerationStructureModeKHR e);
std::string On_Str_VkShaderGroupShaderKHR(VkShaderGroupShaderKHR e);

// Flags
std::string On_Str_VkAccessFlags(VkAccessFlags f);
std::string On_Str_VkImageAspectFlags(VkImageAspectFlags f);
std::string On_Str_VkFormatFeatureFlags(VkFormatFeatureFlags f);
std::string On_Str_VkImageCreateFlags(VkImageCreateFlags f);
std::string On_Str_VkSampleCountFlags(VkSampleCountFlags f);
std::string On_Str_VkImageUsageFlags(VkImageUsageFlags f);
std::string On_Str_VkInstanceCreateFlags(VkInstanceCreateFlags f);
std::string On_Str_VkMemoryHeapFlags(VkMemoryHeapFlags f);
std::string On_Str_VkMemoryPropertyFlags(VkMemoryPropertyFlags f);
std::string On_Str_VkQueueFlags(VkQueueFlags f);
std::string On_Str_VkDeviceQueueCreateFlags(VkDeviceQueueCreateFlags f);
std::string On_Str_VkPipelineStageFlags(VkPipelineStageFlags f);
std::string On_Str_VkSparseMemoryBindFlags(VkSparseMemoryBindFlags f);
std::string On_Str_VkSparseImageFormatFlags(VkSparseImageFormatFlags f);
std::string On_Str_VkFenceCreateFlags(VkFenceCreateFlags f);
std::string On_Str_VkEventCreateFlags(VkEventCreateFlags f);
std::string On_Str_VkQueryPipelineStatisticFlags(VkQueryPipelineStatisticFlags f);
std::string On_Str_VkQueryResultFlags(VkQueryResultFlags f);
std::string On_Str_VkBufferCreateFlags(VkBufferCreateFlags f);
std::string On_Str_VkBufferUsageFlags(VkBufferUsageFlags f);
std::string On_Str_VkImageViewCreateFlags(VkImageViewCreateFlags f);
std::string On_Str_VkPipelineCacheCreateFlags(VkPipelineCacheCreateFlags f);
std::string On_Str_VkColorComponentFlags(VkColorComponentFlags f);
std::string On_Str_VkPipelineCreateFlags(VkPipelineCreateFlags f);
std::string On_Str_VkPipelineShaderStageCreateFlags(VkPipelineShaderStageCreateFlags f);
std::string On_Str_VkShaderStageFlags(VkShaderStageFlags f);
std::string On_Str_VkCullModeFlags(VkCullModeFlags f);
std::string On_Str_VkPipelineDepthStencilStateCreateFlags(VkPipelineDepthStencilStateCreateFlags f);
std::string On_Str_VkPipelineColorBlendStateCreateFlags(VkPipelineColorBlendStateCreateFlags f);
std::string On_Str_VkPipelineLayoutCreateFlags(VkPipelineLayoutCreateFlags f);
std::string On_Str_VkSamplerCreateFlags(VkSamplerCreateFlags f);
std::string On_Str_VkDescriptorPoolCreateFlags(VkDescriptorPoolCreateFlags f);
std::string On_Str_VkDescriptorSetLayoutCreateFlags(VkDescriptorSetLayoutCreateFlags f);
std::string On_Str_VkAttachmentDescriptionFlags(VkAttachmentDescriptionFlags f);
std::string On_Str_VkDependencyFlags(VkDependencyFlags f);
std::string On_Str_VkFramebufferCreateFlags(VkFramebufferCreateFlags f);
std::string On_Str_VkRenderPassCreateFlags(VkRenderPassCreateFlags f);
std::string On_Str_VkSubpassDescriptionFlags(VkSubpassDescriptionFlags f);
std::string On_Str_VkCommandPoolCreateFlags(VkCommandPoolCreateFlags f);
std::string On_Str_VkCommandPoolResetFlags(VkCommandPoolResetFlags f);
std::string On_Str_VkCommandBufferUsageFlags(VkCommandBufferUsageFlags f);
std::string On_Str_VkQueryControlFlags(VkQueryControlFlags f);
std::string On_Str_VkCommandBufferResetFlags(VkCommandBufferResetFlags f);
std::string On_Str_VkStencilFaceFlags(VkStencilFaceFlags f);
std::string On_Str_VkSubgroupFeatureFlags(VkSubgroupFeatureFlags f);
std::string On_Str_VkPeerMemoryFeatureFlags(VkPeerMemoryFeatureFlags f);
std::string On_Str_VkMemoryAllocateFlags(VkMemoryAllocateFlags f);
std::string On_Str_VkExternalMemoryHandleTypeFlags(VkExternalMemoryHandleTypeFlags f);
std::string On_Str_VkExternalMemoryFeatureFlags(VkExternalMemoryFeatureFlags f);
std::string On_Str_VkExternalFenceHandleTypeFlags(VkExternalFenceHandleTypeFlags f);
std::string On_Str_VkExternalFenceFeatureFlags(VkExternalFenceFeatureFlags f);
std::string On_Str_VkFenceImportFlags(VkFenceImportFlags f);
std::string On_Str_VkSemaphoreImportFlags(VkSemaphoreImportFlags f);
std::string On_Str_VkExternalSemaphoreHandleTypeFlags(VkExternalSemaphoreHandleTypeFlags f);
std::string On_Str_VkExternalSemaphoreFeatureFlags(VkExternalSemaphoreFeatureFlags f);
std::string On_Str_VkResolveModeFlags(VkResolveModeFlags f);
std::string On_Str_VkDescriptorBindingFlags(VkDescriptorBindingFlags f);
std::string On_Str_VkSemaphoreWaitFlags(VkSemaphoreWaitFlags f);
std::string On_Str_VkPipelineCreationFeedbackFlags(VkPipelineCreationFeedbackFlags f);
std::string On_Str_VkToolPurposeFlags(VkToolPurposeFlags f);
std::string On_Str_VkPipelineStageFlags2(VkPipelineStageFlags2 f);
std::string On_Str_VkAccessFlags2(VkAccessFlags2 f);
std::string On_Str_VkSubmitFlags(VkSubmitFlags f);
std::string On_Str_VkRenderingFlags(VkRenderingFlags f);
std::string On_Str_VkFormatFeatureFlags2(VkFormatFeatureFlags2 f);
std::string On_Str_VkSurfaceTransformFlagsKHR(VkSurfaceTransformFlagsKHR f);
std::string On_Str_VkCompositeAlphaFlagsKHR(VkCompositeAlphaFlagsKHR f);
std::string On_Str_VkSwapchainCreateFlagsKHR(VkSwapchainCreateFlagsKHR f);
std::string On_Str_VkDeviceGroupPresentModeFlagsKHR(VkDeviceGroupPresentModeFlagsKHR f);
std::string On_Str_VkDisplayPlaneAlphaFlagsKHR(VkDisplayPlaneAlphaFlagsKHR f);
std::string On_Str_VkVideoCodecOperationFlagsKHR(VkVideoCodecOperationFlagsKHR f);
std::string On_Str_VkVideoChromaSubsamplingFlagsKHR(VkVideoChromaSubsamplingFlagsKHR f);
std::string On_Str_VkVideoComponentBitDepthFlagsKHR(VkVideoComponentBitDepthFlagsKHR f);
std::string On_Str_VkVideoCapabilityFlagsKHR(VkVideoCapabilityFlagsKHR f);
std::string On_Str_VkVideoSessionCreateFlagsKHR(VkVideoSessionCreateFlagsKHR f);
std::string On_Str_VkVideoCodingControlFlagsKHR(VkVideoCodingControlFlagsKHR f);
std::string On_Str_VkVideoDecodeCapabilityFlagsKHR(VkVideoDecodeCapabilityFlagsKHR f);
std::string On_Str_VkVideoDecodeUsageFlagsKHR(VkVideoDecodeUsageFlagsKHR f);
std::string On_Str_VkVideoDecodeH264PictureLayoutFlagsKHR(VkVideoDecodeH264PictureLayoutFlagsKHR f);
std::string On_Str_VkPerformanceCounterDescriptionFlagsKHR(VkPerformanceCounterDescriptionFlagsKHR f);
std::string On_Str_VkAcquireProfilingLockFlagsKHR(VkAcquireProfilingLockFlagsKHR f);
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeCapabilityFlagsKHR(VkVideoEncodeCapabilityFlagsKHR f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeRateControlModeFlagsKHR(VkVideoEncodeRateControlModeFlagsKHR f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeFeedbackFlagsKHR(VkVideoEncodeFeedbackFlagsKHR f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeUsageFlagsKHR(VkVideoEncodeUsageFlagsKHR f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeContentFlagsKHR(VkVideoEncodeContentFlagsKHR f);
#endif // VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkPipelineCreateFlags2KHR(VkPipelineCreateFlags2KHR f);
std::string On_Str_VkBufferUsageFlags2KHR(VkBufferUsageFlags2KHR f);
std::string On_Str_VkDebugReportFlagsEXT(VkDebugReportFlagsEXT f);
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH264CapabilityFlagsEXT(VkVideoEncodeH264CapabilityFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH264StdFlagsEXT(VkVideoEncodeH264StdFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH264RateControlFlagsEXT(VkVideoEncodeH264RateControlFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH265CapabilityFlagsEXT(VkVideoEncodeH265CapabilityFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH265StdFlagsEXT(VkVideoEncodeH265StdFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH265CtbSizeFlagsEXT(VkVideoEncodeH265CtbSizeFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH265TransformBlockSizeFlagsEXT(VkVideoEncodeH265TransformBlockSizeFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
#ifdef VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkVideoEncodeH265RateControlFlagsEXT(VkVideoEncodeH265RateControlFlagsEXT f);
#endif // VK_ENABLE_BETA_EXTENSIONS
std::string On_Str_VkExternalMemoryHandleTypeFlagsNV(VkExternalMemoryHandleTypeFlagsNV f);
std::string On_Str_VkExternalMemoryFeatureFlagsNV(VkExternalMemoryFeatureFlagsNV f);
std::string On_Str_VkConditionalRenderingFlagsEXT(VkConditionalRenderingFlagsEXT f);
std::string On_Str_VkSurfaceCounterFlagsEXT(VkSurfaceCounterFlagsEXT f);
std::string On_Str_VkDebugUtilsMessageSeverityFlagsEXT(VkDebugUtilsMessageSeverityFlagsEXT f);
std::string On_Str_VkDebugUtilsMessageTypeFlagsEXT(VkDebugUtilsMessageTypeFlagsEXT f);
std::string On_Str_VkGeometryFlagsKHR(VkGeometryFlagsKHR f);
std::string On_Str_VkGeometryInstanceFlagsKHR(VkGeometryInstanceFlagsKHR f);
std::string On_Str_VkBuildAccelerationStructureFlagsKHR(VkBuildAccelerationStructureFlagsKHR f);
std::string On_Str_VkPipelineCompilerControlFlagsAMD(VkPipelineCompilerControlFlagsAMD f);
std::string On_Str_VkShaderCorePropertiesFlagsAMD(VkShaderCorePropertiesFlagsAMD f);
std::string On_Str_VkHostImageCopyFlagsEXT(VkHostImageCopyFlagsEXT f);
std::string On_Str_VkPresentScalingFlagsEXT(VkPresentScalingFlagsEXT f);
std::string On_Str_VkPresentGravityFlagsEXT(VkPresentGravityFlagsEXT f);
std::string On_Str_VkIndirectStateFlagsNV(VkIndirectStateFlagsNV f);
std::string On_Str_VkIndirectCommandsLayoutUsageFlagsNV(VkIndirectCommandsLayoutUsageFlagsNV f);
std::string On_Str_VkDeviceDiagnosticsConfigFlagsNV(VkDeviceDiagnosticsConfigFlagsNV f);
#ifdef VK_USE_PLATFORM_METAL_EXT
std::string On_Str_VkExportMetalObjectTypeFlagsEXT(VkExportMetalObjectTypeFlagsEXT f);
#endif // VK_USE_PLATFORM_METAL_EXT
std::string On_Str_VkGraphicsPipelineLibraryFlagsEXT(VkGraphicsPipelineLibraryFlagsEXT f);
std::string On_Str_VkImageCompressionFlagsEXT(VkImageCompressionFlagsEXT f);
std::string On_Str_VkImageCompressionFixedRateFlagsEXT(VkImageCompressionFixedRateFlagsEXT f);
std::string On_Str_VkDeviceAddressBindingFlagsEXT(VkDeviceAddressBindingFlagsEXT f);
#ifdef VK_USE_PLATFORM_FUCHSIA
std::string On_Str_VkImageConstraintsInfoFlagsFUCHSIA(VkImageConstraintsInfoFlagsFUCHSIA f);
#endif // VK_USE_PLATFORM_FUCHSIA
std::string On_Str_VkBuildMicromapFlagsEXT(VkBuildMicromapFlagsEXT f);
std::string On_Str_VkMicromapCreateFlagsEXT(VkMicromapCreateFlagsEXT f);
std::string On_Str_VkMemoryDecompressionMethodFlagsNV(VkMemoryDecompressionMethodFlagsNV f);
std::string On_Str_VkOpticalFlowGridSizeFlagsNV(VkOpticalFlowGridSizeFlagsNV f);
std::string On_Str_VkOpticalFlowUsageFlagsNV(VkOpticalFlowUsageFlagsNV f);
std::string On_Str_VkOpticalFlowSessionCreateFlagsNV(VkOpticalFlowSessionCreateFlagsNV f);
std::string On_Str_VkOpticalFlowExecuteFlagsNV(VkOpticalFlowExecuteFlagsNV f);
std::string On_Str_VkShaderCreateFlagsEXT(VkShaderCreateFlagsEXT f);
std::string On_Str_VkAccelerationStructureCreateFlagsKHR(VkAccelerationStructureCreateFlagsKHR f);
} // namespace vkt
