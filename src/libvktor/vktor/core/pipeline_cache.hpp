#pragma once
#include "__core.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

struct PipelineCache;

class PipelineCacheState : public CoreStater<PipelineCacheState> {
    friend struct PipelineCache;

private:
    mutable VkPipelineCacheCreateInfo cache_ci = Itor::PipelineCacheCreateInfo();

public:
    explicit PipelineCacheState(String&& name = "PipelineCache") : CoreStater(std::move(name)) {}

    Self setFlags(VkPipelineCacheCreateFlags flags);
    Self setInitialData(const void* data, size_t data_size);
    Self setInitialData(const Vector<uint8_t>& data);

    Res<PipelineCache> into(const CoreApi& api) const;
};

struct PipelineCache : public CoreResource<VkPipelineCache, VK_OBJECT_TYPE_PIPELINE_CACHE> {
protected:
    explicit PipelineCache(const CoreApi& api) : CoreResource(api) {}

public:
    PipelineCache(PipelineCache&&);
    ~PipelineCache();

public:
    static Res<PipelineCache> from(const CoreApi& api, const PipelineCacheState& info);
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
