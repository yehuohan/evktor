#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct QueryPool;

class QueryPoolState : public CoreState<QueryPoolState> {
    friend struct QueryPool;

private:
    mutable VkQueryPoolCreateInfo query_pool_ci = Itor::QueryPoolCreateInfo();

public:
    explicit QueryPoolState(String&& name = "QueryPool") : CoreState(std::move(name)) {}

    Self setFlags(VkQueryPoolCreateFlags flags);
    Self setType(VkQueryType type);
    Self setCount(uint32_t count);
    Self setPipelineStatisticFlags(VkQueryPipelineStatisticFlags flags);

    Res<QueryPool> into(const CoreApi& api) const;
};

struct QueryPool : public CoreResource<VkQueryPool, VK_OBJECT_TYPE_QUERY_POOL> {
    uint32_t query_count = 0;

protected:
    explicit QueryPool(const CoreApi& api) : CoreResource(api) {}

public:
    QueryPool(QueryPool&&);
    ~QueryPool();

    VkResult getResults(uint32_t first,
                        uint32_t count,
                        size_t data_size,
                        void* data,
                        VkDeviceSize stride,
                        VkQueryResultFlags flags = 0) const;
    VkResult getAllResults(size_t data_size, void* data, VkDeviceSize stride, VkQueryResultFlags flags = 0) const;

    static Res<QueryPool> from(const CoreApi& api, const QueryPoolState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
