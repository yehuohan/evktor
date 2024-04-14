#pragma once
#include "api/api.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

#define OnName(r, n) OnRet(r.setDebugName(n), "Failed to set debug name: {}", n)

/**
 * @brief Vulkan core resource type
 *
 * CoreResource's default move assignment operator is deleted, as there's a
 * non-static data member of a reference type (const A& api).
 * CoreResource should better not define move assignment operator because:
 *  - the reference member can not be updated in move assignment operator
 *  - need destruct CoreHandle mannual (move assignment operator won't call destructor)
 *  - need check `this != &rhs` (otherwise move assignment operator doesn't make sense and may destruct the CoreHandle)
 */
template <typename T, VkObjectType OBJECT_TYPE>
struct CoreResource : public CoreHandle<T> {
    const CoreApi& api;

    explicit CoreResource(const CoreApi& api) : api(api) {}
    virtual ~CoreResource() {}

    inline VkResult setDebugName(const Name& name) const {
        return api.setDebugName(OBJECT_TYPE, u64(reinterpret_cast<uint64_t>(this->handle)), name.c_str());
    }
};

/**
 * @brief CoreResource argument with extra data
 */
template <typename T>
struct Arg : private NonCopyable {
    const T& a; /**< CoreResource argument */

    explicit Arg(const T& a) : a(a) {}
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
