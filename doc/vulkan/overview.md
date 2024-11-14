
## Concepts

- Instance & Physical device

A vulkan app use `Vulkan-API` through a `VkInstance`.
We can query for vulkan supported hardware with their properties, and select one or more `VkPhysicalDevice` to use.

- Logical device & Queue families

Upon `VkPhysicalDevice`, We need to create VkDevice(logical device) with specific `VkPhysicalFeatures` to use.
We also need to specify the queue families to use such as `graphics queue families`, `compute queue families` and `transfer queue families`. Each queue family supports a specific set of operations in its queues.

- Window surface & Swap chain

A window surface(`VkSurfaceKHR`) is a cross-platform abstraction to present rendered images.
The swap chain is a collection of render targets.

- Image views & Framebuffers

To draw to an image acquired from the swap chain, we have to wrap it into a `VkImageView` and `VkFrameBuffer`. There could be many different images in the swap chain, we'll create `VkImageView` and `VkFrameBuffer` for each image.
A `VkImageView` references a specific part of an image.
A `VkFramebuffer` references image views that are to be used for color, depth and stencil targets.

- Render passes

Render passes describe the type of images that are used during rendering, how they will be used, and how their contents should be treated.

- Graphics pipeline

`VkPipeline` describes the configurable state of the graphics card（图形管线定义了显卡的可配置状态）, such as viewport size, and the programmable state using `VkShaderModule`.

- Command pools & Command buffers

`VkCommandPool` is associated with a specific queue family.
`VkCommandBuffer` is allocated from a `VkCommandPool`.
Operations in vulkan to execute, like drawing operations, need to be recorded in to `VkCommandBuffer`.
So operations in vulkan need to be submitted to a queue to execute.
