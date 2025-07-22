#pragma once
#include <volk.h>

#include "generated/vk_initializer.hpp"
#include "generated/vk_string.hpp"
#include "share/defines.hpp"
#include "share/helpers.hpp"
#include "share/result.hpp"
#include "share/share.hpp"
#include "share/traits.hpp"

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

/**
 * @brief Conversion constructor
 *
 * This is mainly for the Vulkan handle
 */
#define OnType(Type, Var)   \
    OnConstType(Type, Var); \
    operator Type*() {      \
        return &Var;        \
    }

/**
 * @brief Const conversion constructor
 *
 * This is mainly for the const Vulkan handle
 */
#define OnConstType(Type, Var)     \
    operator const Type() const {  \
        return Var;                \
    }                              \
    operator const Type*() const { \
        return &Var;               \
    }

/**
 * @brief Vulkan core handle type
 *
 * Derived struct need to process `handle` at copy/move/assign constructor
 */
template <typename T>
struct CoreHandle : private NonCopyable {
protected:
    /** Vulkan handle is borrowed or not
     *
     * A borrowed CoreHandle doesn't have ownership and must not destory the handle.
     */
    bool __borrowed = false;

public:
    /** Vulkan handle */
    T handle = VK_NULL_HANDLE;

    virtual ~CoreHandle() {}
    OnType(T, this->handle);
};

/**
 * @brief State info for Vulkan core type
 *
 * Example code:
 * ```cpp
 *      class TypeState : public CoreStater {
 *          friend struct Type;
 *          Self set() { ...; return *this; };
 *          Self add() { ...; return *this; };
 *          Res<Type> into() const {}
 *      };
 *      struct Type : public CoreHandle<VkXXX> {
 *          static Res<Type> from(const TypeState& info) {}
 *      };
 *
 *      auto tso = TypeState();
 *      tso.set().add();
 *      auto ty1 = Type::from(tso).unwrap();
 *      tso = TypeState();
 *      auto ty2 = tso.set().add().info().unwrap();
 * ```
 */
template <typename S>
class CoreStater : private NonCopyable {
protected:
    explicit CoreStater(String&& name) {
        __name = std::move(name);
    }

public:
    using Self = S&;

    String __name = "";           /**< Debug name */
    bool __verbose = VKT_CORE_VERBOSE;

    inline Self setDebugName(String&& name) {
        __name = std::move(name);
        return static_cast<Self>(*this);
    }
    inline Self setVerbose(bool verbose = true) {
        __verbose = verbose;
        return static_cast<Self>(*this);
    }
};

/**
 * @brief Enumerate template for Vulkan
 *
 * Function 'F' should return VkResult
 */
template <typename T, typename F, typename... Ts>
auto enumerate(Vector<T>& out, F&& f, Ts&&... ts) -> VkResult {
    uint32_t count = 0;
    VkResult res;
    do {
        res = f(ts..., &count, nullptr);
        if (res != VK_SUCCESS) {
            return res;
        }
        out.resize(count);
        res = f(ts..., &count, out.data());
        out.resize(count);
    } while (res == VK_INCOMPLETE);
    return res;
}

/**
 * @brief Enumerate template for Vulkan
 *
 * Function 'F' should return void
 */
template <typename T, typename F, typename... Ts>
auto enumerate(F&& f, Ts&&... ts) -> Vector<T> {
    uint32_t count = 0;
    Vector<T> vec;
    f(ts..., &count, nullptr);
    vec.resize(count);
    f(ts..., &count, vec.data());
    vec.resize(count);
    return std::move(vec);
}

/**
 * @brief Traverse vulkan next chain
 *
 * @param next The `.pNext` chain
 * @retval true Exit traverse early when function 'F' returns true
 * @retval false Exit traverse until catch null next
 */
template <typename F>
auto traverse(const void* next, F&& f) -> bool {
    const void* n = next;
    while (n) {
        const VkBaseInStructure& base = *static_cast<const VkBaseInStructure*>(n);
        if (f(base)) {
            return true;
        }
        n = base.pNext;
    }
    return false;
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
