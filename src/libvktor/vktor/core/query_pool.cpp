#include "query_pool.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = QueryPoolState::Self;

Self QueryPoolState::setFlags(VkQueryPoolCreateFlags flags) {
    query_pool_ci.flags = flags;
    return *this;
}

Self QueryPoolState::setType(VkQueryType type) {
    query_pool_ci.queryType = type;
    return *this;
}

Self QueryPoolState::setCount(uint32_t count) {
    query_pool_ci.queryCount = count;
    return *this;
}

Self QueryPoolState::setPipelineStatisticFlags(VkQueryPipelineStatisticFlags flags) {
    query_pool_ci.pipelineStatistics = flags;
    return *this;
}

Res<QueryPool> QueryPoolState::into(const CoreApi& api) const {
    return QueryPool::from(api, *this);
}

QueryPool::QueryPool(QueryPool&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
    query_count = rhs.query_count;
}

QueryPool::~QueryPool() {
    if (!__borrowed && handle) {
        vkDestroyQueryPool(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

VkResult QueryPool::getResults(uint32_t first,
                               uint32_t count,
                               size_t data_size,
                               void* data,
                               VkDeviceSize stride,
                               VkQueryResultFlags flags) const {
    return vkGetQueryPoolResults(api, handle, first, count, data_size, data, stride, flags);
}

VkResult QueryPool::getAllResults(size_t data_size, void* data, VkDeviceSize stride, VkQueryResultFlags flags) const {
    return vkGetQueryPoolResults(api, handle, 0, query_count, data_size, data, stride, flags);
}

Res<QueryPool> QueryPool::from(const CoreApi& api, const QueryPoolState& info) {
    QueryPool query_pool(api);

    info.query_pool_ci.pNext = info.__next;
    OnRet(vkCreateQueryPool(api, &info.query_pool_ci, api, query_pool), "Failed to create query pool");
    OnName(query_pool, info.__name);
    query_pool.query_count = info.query_pool_ci.queryCount;

    return Ok(std::move(query_pool));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
