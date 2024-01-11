#pragma once
#include "debug.hpp"
#include "vktor/config.hpp"
#include <string>

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

/**
 * @brief Panic on non-success vulkan result
 *
 * 'r' must not be '__ret__'
 */
#define OnPanic(r, f, ...)                                                                    \
    {                                                                                         \
        VkResult __ret__ = (r);                                                               \
        if (__ret__ != VK_SUCCESS) {                                                          \
            throw ErrorFormat("[VkResult = {}] " f, VkStr(VkResult, __ret__), ##__VA_ARGS__); \
        }                                                                                     \
    }

/**
 * @brief Return Er on non-success vulkan result
 *
 * 'r' must not be '__ret__'
 */
#define OnRet(r, f, ...)                                                              \
    {                                                                                 \
        VkResult __ret__ = (r);                                                       \
        if (__ret__ != VK_SUCCESS) {                                                  \
            return Er("[VkResult = {}] " f, VkStr(VkResult, __ret__), ##__VA_ARGS__); \
        }                                                                             \
    }

#define OnName(r) OnRet(r.setDebugName(), "Failed to set debug name: {}", r.__name)

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
    operator Type() const {        \
        return Var;                \
    }                              \
    operator const Type*() const { \
        return &Var;               \
    }

/** A lite string as name */
typedef std::string Name;

/**
 * @brief Base built type that builder to build
 */
struct BuilderBuilt : private NonCopyable {
    Name __name = ""; /**< Debug name */

    BuilderBuilt(const Name& name) : __name(name) {}
    BuilderBuilt(Name&& name) : __name(std::move(name)) {}
    // `BuilderBuilt& operator=(BuilderBuilt&&)` will be auto deleted because the move constructor is explicitly declared
    virtual ~BuilderBuilt() {}
};

/**
 * @brief Vulkan handle that builder to build
 */
template <typename T>
struct BuiltHandle : public BuilderBuilt {
    T handle = VK_NULL_HANDLE; /**< Vulkan handle */

    BuiltHandle(const Name& name) : BuilderBuilt(name) {}
    BuiltHandle(Name&& name) : BuilderBuilt(std::move(name)) {}
    virtual ~BuiltHandle() {}
    OnType(T, this->handle);
};

/**
 * @brief Vulkan resource that builder to build
 */
template <typename T, VkObjectType OBJECT_TYPE, typename D>
    requires std::derived_from<D, BuiltHandle<VkDevice>>
struct BuiltResource : public BuiltHandle<T> {
    const D& device;

    BuiltResource(const D& device, const Name& name) : BuiltHandle<T>(name), device(device) {}
    BuiltResource(const D& device, Name&& name) : BuiltHandle<T>(std::move(name)), device(device) {}
    virtual ~BuiltResource() {}
    /**
     * @brief Set resource name for debug conveniently
     */
    inline VkResult setDebugName(Name&& name) {
        this->__name = std::move(name);
        return core::setDebugName(device, OBJECT_TYPE, u64(reinterpret_cast<uint64_t>(this->handle)), this->__name.c_str());
    }
    inline VkResult setDebugName() const {
        return core::setDebugName(device, OBJECT_TYPE, u64(reinterpret_cast<uint64_t>(this->handle)), this->__name.c_str());
    }
};

/**
 * @brief Info for builder to build
 */
struct BuilderInfo {
    Name __name = ""; /**< Debug name for BuilderBuilt*/
    bool __verbose = VKT_CORE_VERBOSE;
    // bool __movable = true;
};

/**
 * @brief Base builder class
 *
 * Example code:
 * ```cpp
 *      struct Type : public BuilderBuilt<VkXXX> {}; // Define what to build
 *      struct TypeInfo : public BuilderInfo {}; // Define type info to build with
 *      class TypeBuilder : public Builder<TypeBuilder, Type, TypeInfo> {
 *      public:
 *          virtual Built build() override { return Built{}; } // Define how to build
 *          Self set() { ...; return *this; };
 *          Self add() { ...; return *this; };
 *      };
 *
 *      auto tyb = TypeBuilder();
 *      tyb.set().add();
 *      auto ty1 = tyb.build().unwrap();
 *      tyb.set().add(); // Should re-set/add again, but not re-use the builder
 *      auto ty2 = tyb.build().unwrap();
 * ```
 */
template <typename S, typename T, typename I>
    requires std::derived_from<T, BuilderBuilt> and std::derived_from<I, BuilderInfo>
class Builder : private NonCopyable {
public:
    using Self = S&;
    using Built = Res<T>;
    using Info = I;

    virtual Built build() = 0;
    Built operator()() {
        return this->build();
    }

    inline Self setDebugName(Name&& name) {
        info.__name = std::move(name);
        return static_cast<Self>(*this);
    }
    inline Self setVerbose(bool verbose = true) {
        info.__verbose = verbose;
        return static_cast<Self>(*this);
    }

protected:
    explicit Builder(Name&& name) {
        info.__name = std::move(name);
    }

    Info info{};
};

NAMESPACE_END(core)
NAMESPACE_END(vkt)
