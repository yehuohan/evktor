#include "render_frame.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderFrame::RenderFrame(const CoreApi& api, size_t thread_count)
    : api(api)
    , fence_pool(api)
    , semaphore_pool(api)
    , event_pool(api)
    , thread_count(thread_count) {
    cmd_pools.resize(thread_count);
    desc_poolers.resize(thread_count);
    desc_sets.resize(thread_count);
}

RenderFrame::RenderFrame(RenderFrame&& rhs)
    : api(rhs.api)
    , fence_pool(std::move(rhs.fence_pool))
    , semaphore_pool(std::move(rhs.semaphore_pool))
    , event_pool(std::move(rhs.event_pool))
    , thread_count(rhs.thread_count) {
    swapchain_rtt = std::move(rhs.swapchain_rtt);
    cmd_pools = std::move(rhs.cmd_pools);
    desc_poolers = std::move(rhs.desc_poolers);
    desc_sets = std::move(rhs.desc_sets);
}

void RenderFrame::setSwapchainRTT(Box<RenderTargetTable>&& rtt) {
    swapchain_rtt = std::move(rtt);
}

Res<CRef<RenderTargetTable>> RenderFrame::getSwapchainRTT() const {
    if (swapchain_rtt) {
        return Ok(newCRef(*swapchain_rtt));
    }
    return Er("No valid render target table in this render frame");
}

Res<Void> RenderFrame::resetFrame() {
    bool okay = true;
    for (auto& cmdpools : cmd_pools) {
        for (auto& iter : cmdpools) {
            iter.second.resetPool();
        }
    }
    event_pool.resetPool();
    semaphore_pool.resetPool();
    OnRet(fence_pool.waitPool(), "Failed to wait fence pool");
    OnRet(fence_pool.resetPool(), "Failed to reset fence pool");
    return Ok(Void{});
}

void RenderFrame::resetDescriptorSets(size_t thread_index) {
    if (thread_index < desc_sets.size()) {
        desc_sets[thread_index].clear();
    } else {
        vktLogW("The thread index to free is out of descriptor set array");
    }
    if (thread_index < desc_poolers.size()) {
        desc_poolers[thread_index].clear();
    } else {
        vktLogW("The thread index to free is out of descriptor pooler array");
    }
}

Res<Ref<CommandBuffer>> RenderFrame::requestCommandBuffer(const Queue& queue, size_t thread_index) {
    if (thread_index >= cmd_pools.size()) {
        return Er("Thread index is out of command pool array");
    }

    // Get command pool
    CommandPool* cmdpool = nullptr;
    {
        auto& cmdpools = cmd_pools[thread_index];
        auto item = cmdpools.find(queue.family_index);
        if (item != cmdpools.end()) {
            cmdpool = &item->second;
        } else {
            auto res = CommandPoolState()
                           .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                           .setQueueIndex(queue.family_index)
                           .into(api);
            OnErr(res);
            auto iter = cmdpools.insert({queue.family_index, res.unwrap()}).first;
            cmdpool = &iter->second;
        }
    }

    return cmdpool->allocate(CommandBuffer::Level::Primary);
}

Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          const DescriptorInfo& desc_info,
                                                          size_t thread_index) {
    auto res = requestDescriptorPool(desc_setlayout, thread_index);
    OnErr(res);
    auto& desc_pool = res.unwrap().get();

    return requestDescriptorSet(desc_setlayout, desc_pool, desc_info, thread_index);
}

Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          const DescriptorArrayInfo& desc_info,
                                                          size_t thread_index) {
    auto res = requestDescriptorPool(desc_setlayout, thread_index);
    OnErr(res);
    auto& desc_pool = res.unwrap().get();

    return requestDescriptorSet(desc_setlayout, desc_pool, desc_info, thread_index);
}

Res<Ref<DescriptorPool>> RenderFrame::requestDescriptorPool(const DescriptorSetLayout& desc_setlayout, size_t thread_index) {
    if (thread_index >= desc_poolers.size()) {
        return Er("Thread index is out of descriptor pooler array");
    }

    // Get descriptor pooler
    DescriptorPooler* descpooler = nullptr;
    {
        auto& descpoolers = desc_poolers[thread_index];
        size_t key = hash(desc_setlayout);
        auto item = descpoolers.find(key);
        if (item != descpoolers.end()) {
            descpooler = &item->second;
        } else {
            auto iter = descpoolers.insert({key, DescriptorPooler(desc_setlayout)}).first;
            descpooler = &iter->second;
        }
    }

    // Get available descriptor pool from pooler
    return descpooler->request();
}

template <typename T>
Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          DescriptorPool& desc_pool,
                                                          const T& desc_info,
                                                          size_t thread_index) {
    if (thread_index >= desc_sets.size()) {
        return Er("Thread index is out of descriptor set array");
    }

    // Get descriptor set from pool
    DescriptorSet* descset = nullptr;
    {
        auto& descsets = desc_sets[thread_index];
        size_t key = hash(desc_setlayout, desc_pool, desc_info);
        auto item = descsets.find(key);
        if (item != descsets.end()) {
            descset = &item->second;
        } else {
            auto res = desc_pool.allocate();
            OnErr(res);
            auto iter = descsets.insert({key, res.unwrap()}).first;
            descset = &iter->second;
            // Update descriptor for the first allocation time
            descset->update(desc_info);
        }
    }

    return Ok(newRef(*descset));
}

NAMESPACE_END(vkt)
