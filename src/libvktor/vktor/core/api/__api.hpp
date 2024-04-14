#pragma once
#include "__defs.hpp"
#include <string>

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

/** A lite string as name */
typedef std::string Name;

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
    explicit CoreStater(Name&& name) {
        __name = std::move(name);
    }

public:
    using Self = S&;

    Name __name = ""; /**< Debug name */
    bool __verbose = VKT_CORE_VERBOSE;

    // TODO: support next chain
    // virtual Self setNext(void* next) = 0;
    inline Self setDebugName(Name&& name) {
        __name = std::move(name);
        return static_cast<Self>(*this);
    }
    inline Self setVerbose(bool verbose = true) {
        __verbose = verbose;
        return static_cast<Self>(*this);
    }
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
