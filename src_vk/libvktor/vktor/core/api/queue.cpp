#include "queue.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

VkResult VkHandle<VkQueue>::submit(const VkSubmitInfo& submit, VkFence fence) const {
    return vkQueueSubmit(__handle, 1, &submit, fence);
}

VkResult VkHandle<VkQueue>::submit(VkCommandBuffer cmdbuf, VkFence fence) const {
    auto submit_info = Itor::SubmitInfo();
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &cmdbuf;
    return vkQueueSubmit(__handle, 1, &submit_info, fence);
}

VkResult VkHandle<VkQueue>::present(VkSwapchainKHR swapchain, uint32_t image_index, VkSemaphore wait_semaphore) const {
    auto present_info = Itor::PresentInfoKHR();
    present_info.waitSemaphoreCount = wait_semaphore ? 1 : 0;
    present_info.pWaitSemaphores = &wait_semaphore;
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &swapchain;
    present_info.pImageIndices = &image_index;
    return vkQueuePresentKHR(__handle, &present_info);
}

VkResult VkHandle<VkQueue>::waitIdle() const {
    return vkQueueWaitIdle(__handle);
}

Queue Queue::from(VkDevice device, uint32_t family_index, uint32_t index) {
    Queue queue(family_index, index);
    queue.__parent = device;
    vkGetDeviceQueue(device, queue.family_index, queue.index, queue);
    return queue;
}

QueueSubmitter& QueueSubmitter::wait(uint32_t count, const VkSemaphore* semaphores, const VkPipelineStageFlags* stages) {
    info.waitSemaphoreCount = count;
    info.pWaitSemaphores = semaphores;
    info.pWaitDstStageMask = stages;
    return *this;
}

QueueSubmitter& QueueSubmitter::signal(uint32_t count, const VkSemaphore* semaphores) {
    info.signalSemaphoreCount = count;
    info.pSignalSemaphores = semaphores;
    return *this;
}

VkResult QueueSubmitter::submit(VkCommandBuffer cmdbuf, VkFence fence) {
    info.commandBufferCount = 1;
    info.pCommandBuffers = &cmdbuf;
    return queue.submit(info, fence);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
