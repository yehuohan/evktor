#pragma once
#include "api/__api.hpp"

NAMESPACE_BEGIN(std)

template <>
struct hash<VkDescriptorBufferInfo> {
    inline size_t operator()(const VkDescriptorBufferInfo& desc_buf) const {
        size_t res = 0;
        hashCombine(res, desc_buf.buffer);
        hashCombine(res, desc_buf.offset);
        hashCombine(res, desc_buf.range);
        return res;
    }
};

template <>
struct hash<VkDescriptorImageInfo> {
    inline size_t operator()(const VkDescriptorImageInfo& desc_img) const {
        size_t res = 0;
        hashCombine(res, desc_img.sampler);
        hashCombine(res, desc_img.imageView);
        hashCombine(res, desc_img.imageLayout);
        return res;
    }
};

template <>
struct hash<VkVertexInputBindingDescription> {
    inline size_t operator()(const VkVertexInputBindingDescription& binding) const {
        size_t res = 0;
        hashCombine(res, binding.binding);
        hashCombine(res, binding.stride);
        hashCombine(res, binding.inputRate);
        return res;
    }
};

template <>
struct hash<VkVertexInputAttributeDescription> {
    inline size_t operator()(const VkVertexInputAttributeDescription& attribute) const {
        size_t res = 0;
        hashCombine(res, attribute.location);
        hashCombine(res, attribute.binding);
        hashCombine(res, attribute.format);
        hashCombine(res, attribute.offset);
        return res;
    }
};

template <>
struct hash<VkPipelineInputAssemblyStateCreateInfo> {
    inline size_t operator()(const VkPipelineInputAssemblyStateCreateInfo& input_assembly) const {
        size_t res = 0;
        hashCombine(res, input_assembly.topology);
        hashCombine(res, input_assembly.primitiveRestartEnable);
        return res;
    }
};

template <>
struct hash<VkViewport> {
    inline size_t operator()(const VkViewport& viewport) const {
        size_t res = 0;
        hashCombine(res, viewport.x);
        hashCombine(res, viewport.y);
        hashCombine(res, viewport.width);
        hashCombine(res, viewport.height);
        hashCombine(res, viewport.minDepth);
        hashCombine(res, viewport.maxDepth);
        return res;
    }
};

template <>
struct hash<VkRect2D> {
    inline size_t operator()(const VkRect2D& scissor) const {
        size_t res = 0;
        hashCombine(res, scissor.extent.width);
        hashCombine(res, scissor.extent.height);
        hashCombine(res, scissor.offset.x);
        hashCombine(res, scissor.offset.y);
        return res;
    }
};

template <>
struct hash<VkPipelineRasterizationStateCreateInfo> {
    inline size_t operator()(const VkPipelineRasterizationStateCreateInfo& rasterization) const {
        size_t res = 0;
        hashCombine(res, rasterization.depthClampEnable);
        hashCombine(res, rasterization.rasterizerDiscardEnable);
        hashCombine(res, rasterization.polygonMode);
        hashCombine(res, rasterization.cullMode);
        hashCombine(res, rasterization.frontFace);
        hashCombine(res, rasterization.depthBiasEnable);
        hashCombine(res, rasterization.depthBiasConstantFactor);
        hashCombine(res, rasterization.depthBiasClamp);
        hashCombine(res, rasterization.depthBiasSlopeFactor);
        hashCombine(res, rasterization.lineWidth);
        return res;
    }
};

template <>
struct hash<VkPipelineMultisampleStateCreateInfo> {
    inline size_t operator()(const VkPipelineMultisampleStateCreateInfo& multisample) const {
        size_t res = 0;
        hashCombine(res, multisample.rasterizationSamples);
        hashCombine(res, multisample.sampleShadingEnable);
        hashCombine(res, multisample.minSampleShading);
        if (multisample.pSampleMask) {
            for (size_t k = 0; k < static_cast<size_t>(multisample.rasterizationSamples) / 32; k++) {
                hashCombine(res, multisample.pSampleMask[k]);
            }
        }
        hashCombine(res, multisample.alphaToCoverageEnable);
        hashCombine(res, multisample.alphaToOneEnable);
        return res;
    }
};

template <>
struct hash<VkStencilOpState> {
    inline size_t operator()(const VkStencilOpState& stencil_op) const {
        size_t res = 0;
        hashCombine(res, stencil_op.failOp);
        hashCombine(res, stencil_op.passOp);
        hashCombine(res, stencil_op.depthFailOp);
        hashCombine(res, stencil_op.compareOp);
        hashCombine(res, stencil_op.compareMask);
        hashCombine(res, stencil_op.writeMask);
        hashCombine(res, stencil_op.reference);
        return res;
    }
};

template <>
struct hash<VkPipelineDepthStencilStateCreateInfo> {
    inline size_t operator()(const VkPipelineDepthStencilStateCreateInfo& depth_stencil) const {
        size_t res = 0;
        hashCombine(res, depth_stencil.depthTestEnable);
        hashCombine(res, depth_stencil.depthWriteEnable);
        hashCombine(res, depth_stencil.depthCompareOp);
        hashCombine(res, depth_stencil.depthBoundsTestEnable);
        hashCombine(res, depth_stencil.stencilTestEnable);
        hashCombine(res, depth_stencil.front);
        hashCombine(res, depth_stencil.back);
        hashCombine(res, depth_stencil.minDepthBounds);
        hashCombine(res, depth_stencil.maxDepthBounds);
        return res;
    }
};

template <>
struct hash<VkPipelineColorBlendAttachmentState> {
    inline size_t operator()(const VkPipelineColorBlendAttachmentState& color_blend_attm) const {
        size_t res = 0;
        hashCombine(res, color_blend_attm.blendEnable);
        hashCombine(res, color_blend_attm.srcColorBlendFactor);
        hashCombine(res, color_blend_attm.dstColorBlendFactor);
        hashCombine(res, color_blend_attm.colorBlendOp);
        hashCombine(res, color_blend_attm.srcAlphaBlendFactor);
        hashCombine(res, color_blend_attm.dstAlphaBlendFactor);
        hashCombine(res, color_blend_attm.alphaBlendOp);
        hashCombine(res, color_blend_attm.colorWriteMask);
        return res;
    }
};

NAMESPACE_END(std)
