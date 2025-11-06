#include "pipeline_cache.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

using Self = PipelineCacheState::Self;

Self PipelineCacheState::setFlags(VkPipelineCacheCreateFlags flags) {
    cache_ci.flags = flags;
    return *this;
}

Self PipelineCacheState::setInitialData(const void* data, size_t data_size) {
    cache_ci.initialDataSize = data_size;
    cache_ci.pInitialData = data;
    return *this;
}

Self PipelineCacheState::setInitialData(const Vector<uint8_t>& data) {
    cache_ci.initialDataSize = data.size();
    cache_ci.pInitialData = data.data();
    return *this;
}

Res<PipelineCache> PipelineCacheState::into(const CoreApi& api) const {
    return PipelineCache::from(api, *this);
}

PipelineCache::PipelineCache(PipelineCache&& rhs) : CoreResource(rhs.api) {
    handle = rhs.handle;
    rhs.handle = VK_NULL_HANDLE;
    __borrowed = rhs.__borrowed;
}

PipelineCache::~PipelineCache() {
    if (!__borrowed && handle) {
        vkDestroyPipelineCache(api, handle, api);
    }
    handle = VK_NULL_HANDLE;
}

Res<PipelineCache> PipelineCache::from(const CoreApi& api, const PipelineCacheState& info) {
    PipelineCache pipeline_cache(api);

    info.cache_ci.pNext = info.__next;
    OnRet(vkCreatePipelineCache(api, &info.cache_ci, api, pipeline_cache), "Failed to create pipeline cache");
    OnName(pipeline_cache, info.__name);

    return Ok(std::move(pipeline_cache));
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
