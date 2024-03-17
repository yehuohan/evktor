#include "app.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define EN_VALIDATION_LAYER 0

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

static const int MAX_FRAMES_IN_FLIGHT = 2;
static bool framebuffer_resized = false;

static std::vector<const char*> getRequiredInstanceExtensions(bool validation_layer) {
    // Extensions required by glfw
    uint32_t glfw_exts_cnt = 0;
    const char** glfw_exts;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_exts_cnt);

    std::vector<const char*> exts(glfw_exts, glfw_exts + glfw_exts_cnt);

    return exts;
}

static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription dsr{
        // Specify the index
        .binding = 0,
        .stride = sizeof(MeshData::Vertex),
        // Specify moving to the next data in-vertex entry after each vertex or instance
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
    };

    return dsr;
}

static std::vector<VkVertexInputAttributeDescription> getAttributeDescription() {
    // location, binding, format, offset
    std::vector<VkVertexInputAttributeDescription> attrs{};
    attrs.push_back(VkVertexInputAttributeDescription{
        0,
        0,
        VK_FORMAT_R32G32B32_SFLOAT,
        offsetof(MeshData::Vertex, pos),
    });
    attrs.push_back(VkVertexInputAttributeDescription{
        1,
        0,
        VK_FORMAT_R32G32B32_SFLOAT,
        offsetof(MeshData::Vertex, color),
    });
    attrs.push_back(VkVertexInputAttributeDescription{
        2,
        0,
        VK_FORMAT_R32G32B32_SFLOAT,
        offsetof(MeshData::Vertex, normal),
    });
    attrs.push_back(VkVertexInputAttributeDescription{
        3,
        0,
        VK_FORMAT_R32G32_SFLOAT,
        offsetof(MeshData::Vertex, texcoord),
    });

    return attrs;
}

App::App(int width, int height) : XWin(width, height) {
    this->setCameraType(ICamera::Arcball);
    this->setCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));

    // Initialize glfw
    if (!glfwInit()) {
        throw ErrorFormat("Failed to init GLFW");
    };
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->window = glfwCreateWindow(wid, hei, "evktor", nullptr, nullptr);
    if (NULL == this->window) {
        glfwTerminate();
        throw ErrorFormat("Failed to create GLFW window");
    }
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，并Capture光标
    glfwSetScrollCallback(window, [](GLFWwindow*, double xoffset, double yoffset) {
        camera.get()->processMouseScroll(yoffset);
    });
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int wid, int hei) {
        framebuffer_resized = true;
    });

    glfwMakeContextCurrent(this->window); // 设置当前上下文为win，有了win才能加载volk
}

void App::run() {
    initVulkan();

    float last_time = 0.0f;
    while (!glfwWindowShouldClose(this->window)) {
        double timeout = -1.0;
        if (last_time > 0.0 && fps > 0.0) {
            timeout = 1.0 / fps - (glfwGetTime() - last_time);
        }
        if (timeout > 0.0) {
            glfwWaitEventsTimeout(timeout);
        } else {
            glfwPollEvents();
        }

        float cur_time = glfwGetTime();
        float delta_time = cur_time - last_time;
        last_time = cur_time;

        processKeys(window, delta_time);
        processCursorPos(window, wid, hei);
        view_matrices.view = camera.get()->getView();
        view_matrices.proj = camera.get()->getProj(this->vkt.render_context->getSwapchain().image_extent.width,
                                                   this->vkt.render_context->getSwapchain().image_extent.height);

        this->tick(cur_time, delta_time);
    }

    vkDeviceWaitIdle(vkt.api);

    cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
}

/*!
 * @brief Draw frame for presentation
 *
 * With the following operations:
 * - Acquire an image from the swap chain
 * - Execute the command buffer with that image as attachment in the framebuffer
 * - Return the image to the swap chain for presentaion
 *
 * For Gpu-Gpu synchronization:
 *  - `sems_image_available`: image was acquired from swap chain and can be drawn to
 *  - `sems_render_finished`: image render has been finished and can be pensent
 *
 * For Cpu-Gpu synchronization:
 *  - `fences_flight`: command buffer of drawing image has been finished
 *  - `fences_images`: images being using by another frame is finished
 *
 * Frames for flight : number of sync objects (对应同步量的数量，即MAX_FRAMES_IN_FLIGHT)
 * Frames for images : number of images in swap chain (对应swap chain中的images数组，即swapchain.images.size())
 *
 * If MAX_FRAMES_IN_FLIGHT > swapchain.images.size() or `vkAcquireNextImageKHR`
 * returns images out-of-order, it's possible that render to a swap chain image
 * that is already in flight (可能出现同步量用在一个已经在使用的swap chain image上)
 *
 */
void App::tick(float cur_time, float delta_time) {
    VkResult ret;

    // Wait fence to be signaled means that the next frame(`current_frame` has
    // increased at end of last function call) has been ready
    fences_flight[current_frame].wait();

    // Variable to store the index of the available image from swap chain
    uint32_t img_idx;
    // Get signal when the presentation is finished using the image and
    // the image can be drawing to
    ret = vkAcquireNextImageKHR(vkt.api,
                                *vkt.render_context,
                                UINT64_MAX,
                                this->sems_image_available[current_frame],
                                VK_NULL_HANDLE,
                                &img_idx);
    // VK_ERROR_OUT_OF_DATE_KHR: The swap chains has become incompatible with the
    //                           surface and can no longer be used for rendering.
    // VK_SUBOPTIMAL_KHR: The swap chain can still be used to successfully present
    //                    to the surface, buf the surface properties are no longer
    //                    matched exactly.
    if (ret == VK_ERROR_OUT_OF_DATE_KHR) {
        // recreateSwapchain();
        return;
    } else if (ret != VK_SUCCESS && ret != VK_SUBOPTIMAL_KHR) {
        throw ErrorFormat("failed to acquire swap chain image: {}", (int)ret);
    }

    // Wait image if previous frame uses image[`img_idx`]
    if (this->fences_images[img_idx] != VK_NULL_HANDLE) {
        vkWaitForFences(vkt.api, 1, &this->fences_images[img_idx], VK_TRUE, UINT64_MAX);
    }
    // Mark image[`img_idx`] in flight means that image is being used by `current_frame`
    this->fences_images[img_idx] = fences_flight[current_frame];

    vkt.render_context->activateRenderFrame(img_idx);
    auto& render_frame = vkt.render_context->getRenderFrame().unwrap().get();
    render_frame.reset();
    auto& cmdbuf = render_frame.requestCommandBuffer(vkt.api.graphicsQueue().unwrap().get()).unwrap().get();

    updateUniformBuffers(img_idx);
    recordCommandBuffers(cmdbuf, img_idx);

    // Submit command buffer
    VkSemaphore wait_semaphores[] = {this->sems_image_available[current_frame]};
    VkSemaphore signal_semaphores[] = {this->sems_render_finished[current_frame]};
    VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSubmitInfo submit_info = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        // Specify which semaphores to wait on before execution begins
        // and in which states of the pipeline to wait
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = wait_semaphores,
        .pWaitDstStageMask = wait_stages,
        // Specify which command buffers to actually for execution
        .commandBufferCount = 1,
        .pCommandBuffers = &cmdbuf.handle,
        // Specify which semaphores to signal once the command buffers have finished execution
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = signal_semaphores,
    };

    fences_flight[current_frame].reset();
    // Fence will be signaled when command buffer finishes executing
    ret = vkQueueSubmit(vkt.api.graphicsQueue().unwrap().get(), 1, &submit_info, fences_flight[current_frame]);
    if (ret != VK_SUCCESS) {
        throw ErrorFormat("failed to submit draw command buffer: {}", (int)ret);
    }

    // Present drawing result
    VkSwapchainKHR swapchains[] = {*vkt.render_context};
    VkPresentInfoKHR present_info = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        // Specify which semaphores to wait on before presentation can happen
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = signal_semaphores,
        // Specify the swap chains to present images and the index of the image
        // for each swap chain
        .swapchainCount = 1,
        .pSwapchains = swapchains,
        .pImageIndices = &img_idx,
        // Get array of `VkResult` values of every individual swap chain
        .pResults = nullptr,
    };
    ret = vkQueuePresentKHR(vkt.api.presentQueue().unwrap().get(), &present_info);
    if (ret == VK_ERROR_OUT_OF_DATE_KHR || ret == VK_SUBOPTIMAL_KHR || framebuffer_resized) {
        // recreateSwapchain();
    } else if (ret != VK_SUCCESS) {
        throw ErrorFormat("failed to present swap chain image: {}", (int)ret);
    }

    // Advance to the next frame
    current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void App::createInstance() {
    auto& api = vkt.api;

    api.init(InstanceState()
                 .setAppName("evktor")
                 .setAppVerion(VK_MAKE_VERSION(1, 0, 0))
                 .setEngineName("vktor")
                 .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                 .setApiVerion(VK_API_VERSION_1_2)
                 .addExtensions(getRequiredInstanceExtensions((bool)EN_VALIDATION_LAYER))
                 .enableValidationLayers((bool)EN_VALIDATION_LAYER)
                 .enableDebugUtils()
                 .setVerbose(false))
        .unwrap();

    VkResult ret = glfwCreateWindowSurface(api, this->window, nullptr, &surface);
    if (ret != VK_SUCCESS) {
        throw ErrorFormat("failed to create window surface: {}", (int)ret);
    }

    api.init(PhysicalDeviceState()
                 // .preferIntegratedGPU()
                 .requirePresentQueue(surface)
                 .requireGraphicsQueue()
                 .requireTransferQueue()
                 .addRequiredExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME)
                 .setVerbose(false))
        .unwrap();

    api.init(DeviceState().setVerbose(false)).unwrap();
}

void App::createSwapchain() {
    vkt.addRenderContext();

    int width, height;
    glfwGetFramebufferSize(this->window, &width, &height);
    VkExtent2D extent2d = {
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height),
    };

    vkt.render_context
        ->add(SwapchainState(surface)
                  // .addDesiredPresentMode(VK_PRESENT_MODE_MAILBOX_KHR)
                  .addDesiredPresentMode(VK_PRESENT_MODE_FIFO_KHR)
                  .setDesiredExtent(extent2d))
        .unwrap();
}

void App::recreateSwapchain() {
    // Handle minimization by pausing until the window is in the foreground again
    int w = 0, h = 0;
    glfwGetFramebufferSize(this->window, &w, &h);
    while (w == 0 || h == 0) {
        glfwGetFramebufferSize(this->window, &w, &h);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(vkt.api);

    cleanupSwapchain();
    createSwapchain();

    createBasePass();
}

void App::createBasePass() {
    base = newBox<RenderPipeline>(vkt.api);
    {
        auto vert = Shader::load("glsl/mesh_data.vert").unwrap();
        auto frag = Shader::load("glsl/mesh_data.frag").unwrap();
        vert.addDescriptor(ShaderDescriptor::BufferUniform, 0);
        frag.addDescriptor(ShaderDescriptor::ImageSampler, 1);

        RenderSubpass subpass{std::move(vert), std::move(frag)};
        subpass.setColorAttachments({0});
        base->addSubpass(std::move(subpass));
    }

    auto& rctx = *vkt.render_context;
    for (int k = 0; k < vkt.render_context->getSwapchain().image_count; k++) {
        RenderTarget rt(rctx.getSwapchain().createImageView(k).unwrap());
        rt.set(AttachmentOps::color()).set(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR).set({0.0f, 0.0f, 0.0f, 1.0f});
        rt_presents.push_back(RenderTargetTable::build({&rt}).unwrap());
    }

    desc_info.bufs[0] = VkDescriptorBufferInfo{VK_NULL_HANDLE, 0, sizeof(UniformBufferObject)};
    desc_info.imgs[1] = VkDescriptorImageInfo{VK_NULL_HANDLE, VK_NULL_HANDLE, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
    {
        int w, h, c;
        stbi_uc* pixels = stbi_load(Assets::getTex("box.png").c_str(), &w, &h, &c, STBI_rgb_alpha);
        VkDeviceSize pixels_size = w * h * 4;
        Buffer buffer_staging = BufferState()
                                    .setSize(pixels_size)
                                    .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                    .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                    // .build_native(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT).unwrap();
                                    .into(vkt.api)
                                    .unwrap();
        buffer_staging.copyFrom(pixels);
        uint32_t mip_levels = static_cast<uint32_t>(std::floor(std::log2(std::max(w, h)))) + 1;
        mesh_tex = newBox<Image>(ImageState()
                                     .setFormat(VK_FORMAT_R8G8B8A8_SRGB)
                                     .setExtent(w, h)
                                     .setMipLevels(mip_levels)
                                     // .setTiling(VK_IMAGE_TILING_LINEAR)
                                     .setUsage(VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT)
                                     // .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                     .into(vkt.api)
                                     .unwrap());
        // mesh_tex->copyFrom(pixels, pixels_size);
        stbi_image_free(pixels);

        auto& frm = vkt.render_context->getRenderFrame().unwrap().get();
        auto& cmdbuf = frm.requestCommandBuffer(vkt.api.transferQueue().unwrap().get()).unwrap().get();

        buffer_staging.copyTo(cmdbuf, *mesh_tex);
        mesh_tex->genMipmaps(cmdbuf);

        mesh_tex_view = newBox<ImageView>(ImageViewState(*mesh_tex).into().unwrap());
        mesh_spl = newBox<Sampler>(SamplerState().setNearest().into(vkt.api).unwrap());
    }
    desc_info.imgs[1].sampler = *mesh_spl;
    desc_info.imgs[1].imageView = *mesh_tex_view;

    for (size_t k = 0; k < vkt.render_context->getSwapchain().image_count; k++) {
        buffer_uniform.push_back(newBox<Buffer>(BufferState()
                                                    .setSize(sizeof(UniformBufferObject))
                                                    .setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                                                    .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                                    // .build_native(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT).unwrap()));
                                                    .into(vkt.api)
                                                    .unwrap()));
    }
}

void App::recordCommandBuffers(CommandBuffer& cmdbuf, uint32_t img_idx) {
    // Record command buffers for every image in the swap chain
    uint32_t k = img_idx;

    const auto& swc = vkt.render_context->getSwapchain();
    auto& render_frame = vkt.render_context->getRenderFrame().unwrap().get();
    auto& rtt = rt_presents[k];

    auto& subpass = base->getSubpasses()[0];
    auto& vert = subpass.vertShader();
    auto& frag = subpass.fragShader();
    const auto& shaders = Vector<const Shader*>{&vert, &frag};

    auto& shader_vert = vkt.requestShaderModule(vert).unwrap().get();
    auto& shader_frag = vkt.requestShaderModule(frag).unwrap().get();
    auto& desc_setlayout = vkt.requestDescriptorSetLayout(0, shaders).unwrap().get();
    auto& pipeline_layout = vkt.requestPipelineLayout(shaders).unwrap().get();
    auto& render_pass = vkt.requestRenderPass(rtt, *base).unwrap().get();
    GraphicsPipelineState pso{};
    pso.addShader(std::move(shader_vert))
        .addShader(std::move(shader_frag))
        .setRenderPass(render_pass)
        .setPipelineLayout(pipeline_layout)
        .addVertexInputBinding(getBindingDescription())
        .addVertexInputAttributes(getAttributeDescription())
        .addViewport(0.0, 0.0, swc.image_extent.width, swc.image_extent.height)
        .addScissor(0, 0, swc.image_extent.width, swc.image_extent.height);
        // .addDynamic(VK_DYNAMIC_STATE_VIEWPORT)
        // .addDynamic(VK_DYNAMIC_STATE_SCISSOR)
    VkPipelineColorBlendAttachmentState color_blend_attm{};
    color_blend_attm.blendEnable = VK_FALSE;
    color_blend_attm.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    color_blend_attm.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_blend_attm.colorBlendOp = VK_BLEND_OP_ADD;
    color_blend_attm.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    color_blend_attm.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_blend_attm.alphaBlendOp = VK_BLEND_OP_ADD;
    color_blend_attm.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                                      VK_COLOR_COMPONENT_A_BIT;
    pso.addColorBlendAttachment(color_blend_attm);

    auto& pipeline = vkt.requestGraphicsPipeline(pso).unwrap().get();
    auto& framebuffer = vkt.requestFramebuffer(rtt, render_pass).unwrap().get();

    VkResult ret = cmdbuf.begin();
    if (ret != VK_SUCCESS) {
        throw ErrorFormat("failed to begin recording command buffer[{}]: {}", k, (int)ret);
    }

    // Start a render pass
    VkClearValue clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
    auto render_pass_bi = Itor::RenderPassBeginInfo();
    // Specify the render pass and the attachments to bind
    render_pass_bi.renderPass = render_pass;
    render_pass_bi.framebuffer = framebuffer;
    // Define the size of the render area
    render_pass_bi.renderArea = VkRect2D{
        .offset = {0, 0},
        .extent = rtt.getExtent(),
    };
    // Define the clear values for `VK_ATTACHMENT_LOAD_OP_CLEAR`
    render_pass_bi.clearValueCount = 1;
    render_pass_bi.pClearValues = &clear_color;
    vkCmdBeginRenderPass(cmdbuf, &render_pass_bi, VK_SUBPASS_CONTENTS_INLINE);

    // Record drawing commands
    vkCmdBindPipeline(cmdbuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    // Bind uniform buffer

    desc_info.bufs[0].buffer = *buffer_uniform[k];
    auto& desc_set = render_frame.requestDescriptorSet(desc_setlayout, desc_info).unwrap().get();

    vkCmdBindDescriptorSets(cmdbuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout, 0, 1, desc_set, 0, nullptr);
    // Bind vertex buffer
    VkBuffer vert_bufs[] = {*this->buffer_vertex};
    VkDeviceSize vert_offsets[] = {0};
    vkCmdBindVertexBuffers(cmdbuf, 0, 1, vert_bufs, vert_offsets);
    // vkCmdDraw(cmdbuf,
    //         3, // Number tf vertices to draw
    //         1, // For instanced rendering or not
    //         0, // The start value ot gl_VertexIndex
    //         0); // The start value of gl_InstanceIndex

    // Bind vertex index buffer
    vkCmdBindIndexBuffer(cmdbuf, *this->buffer_index, 0, VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(cmdbuf, static_cast<uint32_t>(MESH_DATA_Frustum.indices.size()), 1, 0, 0, 0);

    vkCmdEndRenderPass(cmdbuf);

    ret = cmdbuf.end();
    if (ret != VK_SUCCESS) {
        throw ErrorFormat("failed to end recording command buffer[{}]: {}", k, (int)ret);
    }
}

void App::updateUniformBuffers(uint32_t img_idx) {
    UniformBufferObject ubo;
    ubo.model = glm::mat4(1.0);
    ubo.view = this->view_matrices.view;
    ubo.proj = this->view_matrices.proj;
    // Attention: Vulkan use top-left as original (0, 0), so invert the Y axis of projection
    ubo.proj[1][1] *= -1;

    buffer_uniform.at(img_idx)->copyFrom(&ubo);
}

void App::createIndexBuffer() {
    VkDeviceSize buffer_size = sizeof(MeshData::Vertex) * MESH_DATA_Frustum.indices.size();
    auto bso = BufferState();
    Buffer buffer_staging = BufferState()
                                .setSize(buffer_size)
                                .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                // .build_native(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT).unwrap();
                                .into(vkt.api)
                                .unwrap();
    buffer_index = newBox<Buffer>(BufferState()
                                      .setSize(buffer_size)
                                      .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                                      .into(vkt.api)
                                      .unwrap());

    auto& render_frame = vkt.render_context->getRenderFrame().unwrap().get();
    auto& cmdbuf = render_frame.requestCommandBuffer(vkt.api.transferQueue().unwrap().get()).unwrap().get();
    buffer_staging.copyFrom(MESH_DATA_Frustum.indices.data());
    buffer_staging.copyTo(cmdbuf, *buffer_index);
}

void App::createVertexBuffer() {
    VkDeviceSize buffer_size = sizeof(MeshData::Vertex) * MESH_DATA_Frustum.vertices.size();
    // Use a host visible buffer as temporary buffer to store vertices data
    Buffer buffer_staging = BufferState()
                                .setSize(buffer_size)
                                .setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                                // Memory can be map for access by Cpu,
                                // and indicated with COHERENT for consistent memory access
                                .setMemoryFlags(VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT)
                                // .build_native(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT).unwrap();
                                .into(vkt.api)
                                .unwrap();
    // Use device local buffer as actual vertex buffer and copy the vertices data from stage buffer to vertex buffer
    buffer_vertex = newBox<Buffer>(BufferState()
                                       .setSize(buffer_size)
                                       .setUsage(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
                                       // Use most optimal memory for Gpu access
                                       .into(vkt.api)
                                       .unwrap());

    auto& render_frame = vkt.render_context->getRenderFrame().unwrap().get();
    auto& cmdbuf = render_frame.requestCommandBuffer(vkt.api.transferQueue().unwrap().get()).unwrap().get();
    buffer_staging.copyFrom(MESH_DATA_Frustum.vertices.data());
    // Copy buffer from SRC_BIT to DST_BIT
    buffer_staging.copyTo(cmdbuf, *buffer_vertex);
}

void App::initVulkan() {
    createInstance();
    createSwapchain();

    createBasePass();
    createIndexBuffer();
    createVertexBuffer();

    // - Fence: to synchronize application with rendering operation
    // - Semaphore: to synchronize operations within or across command queues
    fences_images.resize(vkt.render_context->getSwapchain().image_count, VK_NULL_HANDLE);
    for (int k = 0; k < MAX_FRAMES_IN_FLIGHT; k++) {
        sems_image_available.push_back(vkt.api.create(SemaphoreState()).unwrap());
        sems_render_finished.push_back(vkt.api.create(SemaphoreState()).unwrap());
        fences_flight.push_back(vkt.api.create(FenceState().setFlags(VK_FENCE_CREATE_SIGNALED_BIT)).unwrap());
    }
}

void App::cleanupSwapchain() {
    vkt.render_context.reset();
    buffer_uniform.clear();
}

void App::cleanup() {
    auto& api = vkt.api;
    cleanupSwapchain();

    buffer_index.reset();
    buffer_vertex.reset();

    sems_image_available.clear();
    sems_render_finished.clear();
    fences_flight.clear();
    vkDestroySurfaceKHR(api, surface, nullptr);

    glfwDestroyWindow(this->window);
    glfwTerminate();
}
