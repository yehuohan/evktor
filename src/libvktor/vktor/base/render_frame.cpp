#include "render_frame.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderFrame::RenderFrame(const BaseApi& base_api, size_t thread_count) : api(base_api), thread_count(thread_count) {
    cmd_pools.resize(thread_count);
    desc_poolers.resize(thread_count);
    desc_sets.resize(thread_count);
}

RenderFrame::RenderFrame(RenderFrame&& rhs) : api(rhs.api), thread_count(rhs.thread_count) {
    cmd_pools = std::move(rhs.cmd_pools);
    desc_poolers = std::move(rhs.desc_poolers);
    desc_sets = std::move(rhs.desc_sets);
}

void RenderFrame::reset() {
    for (auto& cmdpools : cmd_pools) {
        for (auto& cmdpool : cmdpools) {
            cmdpool.second.resetCommandPool();
        }
    }
}

void RenderFrame::freeDescriptorSets(size_t thread_index) {
    if (thread_index < desc_poolers.size()) {
        desc_poolers[thread_index].clear();
    } else {
        LogW("The thread index to free is out of descriptor pooler array");
    }
    if (thread_index < desc_sets.size()) {
        desc_sets[thread_index].clear();
    } else {
        LogW("The thread index to free is out of descriptor set array");
    }
}

Res<Ref<CommandBuffer>> RenderFrame::requestCommandBuffer(const Queue& queue, size_t thread_index) {
    if (thread_index >= cmd_pools.size()) {
        return Er("Thread index is out of command pool array");
    }
    CommandPool* pool = nullptr;

    auto& cmdpools = cmd_pools[thread_index];
    auto item = cmdpools.find(queue.family_index);
    if (item != cmdpools.end()) {
        pool = &item->second;
    } else {
        auto res = CommandPoolBuilder(api)
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueIndex(queue.family_index)
                       .build();
        if (res.isErr()) {
            return Err(res.unwrapErr());
        }
        auto cmdpool = cmdpools.insert({queue.family_index, res.unwrap()}).first;
        pool = &cmdpool->second;
    }

    return pool->requestCommandBuffer(CommandBuffer::Level::Primary);
}

Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          const DescriptorInfo& desc_info,
                                                          size_t thread_index) {
    auto res_pool = requestDescriptorPool(desc_setlayout, thread_index);
    if (res_pool.isErr()) {
        return Err(res_pool.unwrapErr());
    }
    auto& pool = res_pool.unwrap().get();

    return requestDescriptorSet(desc_setlayout, desc_info, pool, thread_index);
}

Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          const DescriptorArrayInfo& desc_info,
                                                          size_t thread_index) {
    auto res_pool = requestDescriptorPool(desc_setlayout, thread_index);
    if (res_pool.isErr()) {
        return Err(res_pool.unwrapErr());
    }
    auto& pool = res_pool.unwrap().get();

    return requestDescriptorSet(desc_setlayout, desc_info, pool, thread_index);
}

Res<Ref<DescriptorPool>> RenderFrame::requestDescriptorPool(const DescriptorSetLayout& desc_setlayout, size_t thread_index) {
    if (thread_index >= desc_poolers.size()) {
        return Er("Thread index is out of descriptor pooler array");
    }

    // Get descriptor pooler
    DescriptorPooler* pooler = nullptr;
    {
        auto& descpoolers = desc_poolers[thread_index];
        size_t key = hash(desc_setlayout);
        auto item = descpoolers.find(key);
        if (item != descpoolers.end()) {
            pooler = &item->second;
        } else {
            auto descpooler = descpoolers.insert({key, DescriptorPooler(desc_setlayout)}).first;
            pooler = &descpooler->second;
        }
    }

    // Get available descriptor pool from pooler
    return pooler->get();
}

template <typename T>
Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          const T& desc_info,
                                                          DescriptorPool& desc_pool,
                                                          size_t thread_index) {
    if (thread_index >= desc_sets.size()) {
        return Er("Thread index is out of descriptor set array");
    }

    // Get descriptor set from pool
    DescriptorSet* set = nullptr;
    {
        auto& descsets = desc_sets[thread_index];
        size_t key = hash(desc_setlayout, desc_pool, desc_info);
        auto item = descsets.find(key);
        if (item != descsets.end()) {
            set = &item->second;
        } else {
            auto res = desc_pool.allocate();
            if (res.isErr()) {
                return Err(res.unwrapErr());
            }
            auto descset = descsets.insert({key, res.unwrap()}).first;
            set = &descset->second;
            // Update descriptor for the first allocation time
            set->update(desc_info);
        }
    }

    return Ok(newRef(*set));
}

NAMESPACE_END(vkt)
