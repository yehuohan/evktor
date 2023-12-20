#include "render_frame.hpp"

NAMESPACE_BEGIN(vkt)

using namespace core;

RenderFrame::RenderFrame(const BaseApi& base_api, size_t thread_count) : api(base_api), thread_count(thread_count) {
    cmd_pools.resize(thread_count);
    desc_poolers.resize(thread_count);
    desc_sets.resize(thread_count);
}

void RenderFrame::reset() {
    for (auto& cmdpools : cmd_pools) {
        for (auto& cmdpool : cmdpools) {
            cmdpool.second.resetCommandPool();
        }
    }
}

void RenderFrame::freeDescriptorSets(uint32_t thread_index) {
    assert(thread_index < desc_poolers.size() && "Thread index is out of descriptor pooler array");
    assert(thread_index < desc_sets.size() && "Thread index is out of descriptor set array");
    desc_poolers[thread_index].clear();
    desc_sets[thread_index].clear();
}

Res<Ref<CommandBuffer>> RenderFrame::requestCommandBuffer(uint32_t queue_family_index, uint32_t thread_index) {
    assert(thread_index < cmd_pools.size() && "Thread index is out of command pool array");
    CommandPool* pool = nullptr;

    auto& cmdpools = cmd_pools[thread_index];
    auto item = cmdpools.find(queue_family_index);
    if (item != cmdpools.end()) {
        pool = &item->second;
    } else {
        auto res = CommandPoolBuilder(api)
                       .setFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                       .setQueueIndex(api.graphicsIndex())
                       .build();
        if (res.isErr()) {
            return Err(res.unwrapErr());
        }
        auto cmdpool = cmdpools.insert({queue_family_index, res.unwrap()}).first;
        pool = &cmdpool->second;
    }

    return pool->requestCommandBuffer(CommandBuffer::Level::Primary);
}

Res<Ref<DescriptorSet>> RenderFrame::requestDescriptorSet(const DescriptorSetLayout& desc_setlayout,
                                                          const DescriptorInfo& desc_info,
                                                          uint32_t thread_index) {
    assert(thread_index < desc_poolers.size() && "Thread index is out of descriptor pooler array");
    assert(thread_index < desc_sets.size() && "Thread index is out of descriptor set array");

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
    auto res_pool = pooler->get();
    if (res_pool.isErr()) {
        return Err(res_pool.unwrapErr());
    }
    auto& pool = res_pool.unwrap().get();

    // Get descriptor set from pool
    DescriptorSet* set = nullptr;
    {
        auto& descsets = desc_sets[thread_index];
        size_t key = hash(desc_setlayout, pool, desc_info);
        auto item = descsets.find(key);
        if (item != descsets.end()) {
            set = &item->second;
        } else {
            auto res = pool.allocate();
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
