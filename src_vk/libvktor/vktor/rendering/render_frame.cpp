#include "render_frame.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderFrame::RenderFrame(const CoreApi& api, size_t thread_count)
    : api(api)
    , thread_count(thread_count)
    , fence_pool(api)
    , semaphore_pool(api)
    , event_pool(api) {
    cmd_pools.resize(thread_count);
    desc_poolers.resize(thread_count);
    desc_sets.resize(thread_count);
}

RenderFrame::RenderFrame(RenderFrame&& rhs)
    : api(rhs.api)
    , thread_count(rhs.thread_count)
    , fence_pool(std::move(rhs.fence_pool))
    , semaphore_pool(std::move(rhs.semaphore_pool))
    , event_pool(std::move(rhs.event_pool)) {
    cmd_pools = std::move(rhs.cmd_pools);
    desc_poolers = std::move(rhs.desc_poolers);
    desc_sets = std::move(rhs.desc_sets);
}

Res<Void> RenderFrame::resetFrame() {
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

Res<CRef<CommandBuffer>> RenderFrame::requestCommandBuffer(const Queue& queue, const String& cmd_name, size_t thread_index) {
    if (thread_index >= cmd_pools.size()) {
        return Er("Thread index is out of command pool array");
    }

    // Get command pool
    CommandPool* cmdpool = nullptr;
    {
        auto& cmdpools = cmd_pools[thread_index];
        if (auto it = cmdpools.find(queue.family_index); it != cmdpools.end()) {
            cmdpool = &it->second;
        } else {
            auto res = CommandPoolState(vktFmt("{}#Pool", cmd_name))
                           .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                           .setQueueFamilyIndex(queue.family_index)
                           .into(api);
            OnErr(res);
            auto iter = cmdpools.insert({queue.family_index, res.unwrap()}).first;
            cmdpool = &iter->second;
        }
    }

    return cmdpool->allocate(CommandPool::Level::Primary, vktFmt("{}#Buffer", cmd_name));
}

Res<CRef<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                           const DescriptorInfo& desc_info,
                                                           const String& desc_name,
                                                           size_t thread_index) {
    if (thread_index >= desc_sets.size()) {
        return Er("Thread index is out of descriptor set array");
    }

    // Get descriptor set from descriptor pool
    DescriptorSet* descset = nullptr;
    {
        auto& descsets = desc_sets[thread_index];
        // The DescriptorPooler.request() always return the last DescriptorPool.
        // If DescriptorPool's allocated DescriptorSet is more than maxsets, a new DescriptorPool will be created.
        // So compute hash on DescriptorPool will result different key with same DescriptorSetLayout.
        // So must hash DescriptorSetLayout and DescriptorInfo only.
        size_t key = hash(desc_setlayout, desc_info);
        if (auto it = descsets.find(key); it != descsets.end()) {
            descset = &*it->second;
        } else {
            // Get descriptor pool
            auto res_pool = requestDescriptorPool(desc_setlayout, vktFmt("{}#Pool", desc_name), thread_index);
            OnErr(res_pool);
            auto& desc_pool = res_pool.unwrap().get();

            auto res = desc_pool.allocate(desc_setlayout, nullptr, vktFmt("{}#Set", desc_name));
            OnErr(res);
            auto iter = descsets.insert({key, newBox<DescriptorSet>(res.unwrap())}).first;
            descset = &*iter->second;
            // Update descriptor for the first allocation time
            descset->update(desc_info, desc_setlayout);
        }
    }

    return Ok(newCRef(*descset));
}

Res<Ref<DescriptorPool>> RenderFrame::requestDescriptorPool(const DescriptorSetLayout& desc_setlayout,
                                                            String&& name,
                                                            size_t thread_index) {
    if (thread_index >= desc_poolers.size()) {
        return Er("Thread index is out of descriptor pooler array");
    }

    // Get descriptor pooler
    DescriptorPooler* descpooler = nullptr;
    {
        auto& descpoolers = desc_poolers[thread_index];
        size_t key = hash(desc_setlayout);
        if (auto it = descpoolers.find(key); it != descpoolers.end()) {
            descpooler = &it->second;
        } else {
            auto iter = descpoolers.insert({key, DescriptorPooler()}).first;
            descpooler = &iter->second;
        }
    }

    // Get available descriptor pool from pooler
    return descpooler->request(desc_setlayout, std::move(name));
}

void RenderFrame::watchStatus() const {
    for (size_t k = 0; k < thread_count; k++) {
        vktOut("RenderFrame[{}] {{\n"
               "\tCommand pools      : {}\n"
               "\tDescriptor poolers : {}\n"
               "\tDescriptor sets    : {}\n"
               "\tFence pool         : {} + {}\n"
               "\tSemaphore pool     : {} + {}\n"
               "\tEvent pool         : {} + {}\n"
               "}}",
               k,
               cmd_pools[k].size(),
               desc_poolers[k].size(),
               desc_sets[k].size(),
               fence_pool.getCount(),
               fence_pool.getCacheCount(),
               semaphore_pool.getCount(),
               semaphore_pool.getCacheCount(),
               event_pool.getCount(),
               event_pool.getCacheCount());
    }
}

NAMESPACE_END(vkt)
