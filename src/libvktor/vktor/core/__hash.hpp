#pragma once
#include "api/__api.hpp"

NAMESPACE_BEGIN(std)

template <>
struct hash<VkDescriptorBufferInfo> {
    inline size_t operator()(const VkDescriptorBufferInfo& desc_buf) const {
        size_t res = 0;
        vkt::hashCombine(res, desc_buf.buffer);
        vkt::hashCombine(res, desc_buf.offset);
        vkt::hashCombine(res, desc_buf.range);
        return res;
    }
};

template <>
struct hash<VkDescriptorImageInfo> {
    inline size_t operator()(const VkDescriptorImageInfo& desc_img) const {
        size_t res = 0;
        vkt::hashCombine(res, desc_img.sampler);
        vkt::hashCombine(res, desc_img.imageView);
        vkt::hashCombine(res, desc_img.imageLayout);
        return res;
    }
};

template <>
struct hash<VkVertexInputBindingDescription> {
    inline size_t operator()(const VkVertexInputBindingDescription& binding) const {
        size_t res = 0;
        vkt::hashCombine(res, binding.binding);
        vkt::hashCombine(res, binding.stride);
        vkt::hashCombine(res, binding.inputRate);
        return res;
    }
};

template <>
struct hash<VkVertexInputAttributeDescription> {
    inline size_t operator()(const VkVertexInputAttributeDescription& attribute) const {
        size_t res = 0;
        vkt::hashCombine(res, attribute.location);
        vkt::hashCombine(res, attribute.binding);
        vkt::hashCombine(res, attribute.format);
        vkt::hashCombine(res, attribute.offset);
        return res;
    }
};

template <>
struct hash<VkPipelineInputAssemblyStateCreateInfo> {
    inline size_t operator()(const VkPipelineInputAssemblyStateCreateInfo& input_assembly) const {
        size_t res = 0;
        vkt::hashCombine(res, input_assembly.topology);
        vkt::hashCombine(res, input_assembly.primitiveRestartEnable);
        return res;
    }
};

template <>
struct hash<VkViewport> {
    inline size_t operator()(const VkViewport& viewport) const {
        size_t res = 0;
        vkt::hashCombine(res, viewport.x);
        vkt::hashCombine(res, viewport.y);
        vkt::hashCombine(res, viewport.width);
        vkt::hashCombine(res, viewport.height);
        vkt::hashCombine(res, viewport.minDepth);
        vkt::hashCombine(res, viewport.maxDepth);
        return res;
    }
};

template <>
struct hash<VkRect2D> {
    inline size_t operator()(const VkRect2D& scissor) const {
        size_t res = 0;
        vkt::hashCombine(res, scissor.extent.width);
        vkt::hashCombine(res, scissor.extent.height);
        vkt::hashCombine(res, scissor.offset.x);
        vkt::hashCombine(res, scissor.offset.y);
        return res;
    }
};

template <>
struct hash<VkPipelineRasterizationStateCreateInfo> {
    inline size_t operator()(const VkPipelineRasterizationStateCreateInfo& rasterization) const {
        size_t res = 0;
        vkt::hashCombine(res, rasterization.depthClampEnable);
        vkt::hashCombine(res, rasterization.rasterizerDiscardEnable);
        vkt::hashCombine(res, rasterization.polygonMode);
        vkt::hashCombine(res, rasterization.cullMode);
        vkt::hashCombine(res, rasterization.frontFace);
        vkt::hashCombine(res, rasterization.depthBiasEnable);
        vkt::hashCombine(res, rasterization.depthBiasConstantFactor);
        vkt::hashCombine(res, rasterization.depthBiasClamp);
        vkt::hashCombine(res, rasterization.depthBiasSlopeFactor);
        vkt::hashCombine(res, rasterization.lineWidth);
        return res;
    }
};

template <>
struct hash<VkPipelineMultisampleStateCreateInfo> {
    inline size_t operator()(const VkPipelineMultisampleStateCreateInfo& multisample) const {
        size_t res = 0;
        vkt::hashCombine(res, multisample.rasterizationSamples);
        vkt::hashCombine(res, multisample.sampleShadingEnable);
        vkt::hashCombine(res, multisample.minSampleShading);
        if (multisample.pSampleMask) {
            for (size_t k = 0; k < multisample.rasterizationSamples / 32; k++) {
                vkt::hashCombine(res, multisample.pSampleMask[k]);
            }
        }
        vkt::hashCombine(res, multisample.alphaToCoverageEnable);
        vkt::hashCombine(res, multisample.alphaToOneEnable);
        return res;
    }
};

template <>
struct hash<VkStencilOpState> {
    inline size_t operator()(const VkStencilOpState& stencil_op) const {
        size_t res = 0;
        vkt::hashCombine(res, stencil_op.failOp);
        vkt::hashCombine(res, stencil_op.passOp);
        vkt::hashCombine(res, stencil_op.depthFailOp);
        vkt::hashCombine(res, stencil_op.compareOp);
        vkt::hashCombine(res, stencil_op.compareMask);
        vkt::hashCombine(res, stencil_op.writeMask);
        vkt::hashCombine(res, stencil_op.reference);
        return res;
    }
};

template <>
struct hash<VkPipelineDepthStencilStateCreateInfo> {
    inline size_t operator()(const VkPipelineDepthStencilStateCreateInfo& depth_stencil) const {
        size_t res = 0;
        vkt::hashCombine(res, depth_stencil.depthTestEnable);
        vkt::hashCombine(res, depth_stencil.depthWriteEnable);
        vkt::hashCombine(res, depth_stencil.depthCompareOp);
        vkt::hashCombine(res, depth_stencil.depthBoundsTestEnable);
        vkt::hashCombine(res, depth_stencil.stencilTestEnable);
        vkt::hashCombine(res, depth_stencil.front);
        vkt::hashCombine(res, depth_stencil.back);
        vkt::hashCombine(res, depth_stencil.minDepthBounds);
        vkt::hashCombine(res, depth_stencil.maxDepthBounds);
        return res;
    }
};

template <>
struct hash<VkPipelineColorBlendAttachmentState> {
    inline size_t operator()(const VkPipelineColorBlendAttachmentState& color_blend_attm) const {
        size_t res = 0;
        vkt::hashCombine(res, color_blend_attm.blendEnable);
        vkt::hashCombine(res, color_blend_attm.srcColorBlendFactor);
        vkt::hashCombine(res, color_blend_attm.dstColorBlendFactor);
        vkt::hashCombine(res, color_blend_attm.colorBlendOp);
        vkt::hashCombine(res, color_blend_attm.srcAlphaBlendFactor);
        vkt::hashCombine(res, color_blend_attm.dstAlphaBlendFactor);
        vkt::hashCombine(res, color_blend_attm.alphaBlendOp);
        vkt::hashCombine(res, color_blend_attm.colorWriteMask);
        return res;
    }
};

NAMESPACE_END(std)
