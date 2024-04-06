#include "queue.hpp"
#include "command_buffer.hpp"
#include "swapchain.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

Queue::Queue(Queue&& rhs) : family_index(rhs.family_index), index(rhs.index) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
}

Queue::~Queue() {
    handle = VK_NULL_HANDLE;
}

VkResult Queue::submit(const std::vector<VkSubmitInfo>& submits, VkFence fence) const {
    return vkQueueSubmit(handle, u32(submits.size()), submits.data(), fence);
}

VkResult Queue::submit(const CommandBuffer& cmdbuf, VkFence fence) const {
    auto submit_info = Itor::SubmitInfo();
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = cmdbuf;
    return vkQueueSubmit(handle, 1, &submit_info, fence);
}

VkResult Queue::present(const Swapchain& swapchain, uint32_t image_index, VkSemaphore wait_semaphore) const {
    auto present_info = Itor::PresentInfoKHR();
    present_info.waitSemaphoreCount = wait_semaphore ? 1 : 0;
    present_info.pWaitSemaphores = &wait_semaphore;
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapchain;
    present_info.pImageIndices = &image_index;
    return vkQueuePresentKHR(handle, &present_info);
}

VkResult Queue::waitIdle() const {
    return vkQueueWaitIdle(handle);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
