#pragma once
#include "vktor.hpp"
#define GLFW_INCLUDE_NONE
#include "assets.h"
#include "mesh.h"
#include "mesh_data.h"
#include "xwin.h"
#include <cstdint>
#include <string>
#include <vector>

using namespace vkt;

struct __Pass {
    DescriptorInfo desc_info{};
    Ptr<core::DescriptorSetLayout> desc_setlayout;
    Ptr<core::RenderPass> render_pass;
    Ptr<PipelineLayout> graphics_pipeline_layout;
    Box<core::GraphicsPipeline> graphics_pipeline;
    // Vector<core::Framebuffer> swapchain_framebuffers;

    void setup(Vktor& vkt) {
        render_pass = newPtr<RenderPass>(RenderPassState()
                                             .addPresentAttachment(vkt.render_context->getSwapchain().image_format)
                                             .addSubpass({}, {0})
                                             .into(vkt.api)
                                             .unwrap());
        // this->swapchain_framebuffers.push_back(
        //     vkt.Framebuffer(*render_pass).addAttachments(rt.getImageViews()).setExtent(rt.getExtent()).build().unwrap());
        // render_pass_bi.renderArea.extent = vkt.render_context->getSwapchain().image_extent;
        // desc_setlayout = newPtr<DescriptorSetLayout>(vkt.DescriptorSetLayout()
        //                                                  .addVertBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
        //                                                  .addFragBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
        //                                                  .build()
        //                                                  .unwrap());
    }
};

class App : public XWin {
public:
    App(int width, int height);
    virtual ~App() {}

    virtual void run() override;
    void tick(float cur_time, float delta_time);

private:
    void createInstance();
    void createSwapchain();
    void recreateSwapchain();

    void createBasePass();
    void createIndexBuffer();
    void createVertexBuffer();

    void updateUniformBuffers(uint32_t img_idx);
    void recordCommandBuffers(CommandBuffer& cmdbuf, uint32_t img_idx);

    void initVulkan();
    void cleanupSwapchain();
    void cleanup();

private:
    Vktor vkt;
    VkSurfaceKHR surface;

    Box<RenderPipeline> base;
    Vector<RenderTargetTable> rt_presents;

    std::vector<Box<core::Buffer>> buffer_uniform;
    Box<core::Buffer> buffer_index;
    Box<core::Buffer> buffer_vertex;

    Box<core::Image> mesh_tex;
    Box<core::ImageView> mesh_tex_view;
    Box<core::Sampler> mesh_spl;
    DescriptorInfo desc_info{};

    std::vector<Semaphore> sems_image_available;
    std::vector<Semaphore> sems_render_finished;
    std::vector<Fence> fences_flight;
    std::vector<bool> fences_flight_used;
    std::vector<VkFence> fences_images;
    int current_frame = 0;
};
