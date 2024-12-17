#pragma once
#include "entry.hpp"
#include "generated/vk_ldt.hpp"
#include "share/traits.hpp"
#include <share/helpers.hpp>
#include <share/share.hpp>

#define vktlyrOut(f, ...)  vkt::print(vktFmt("[vktlyr] " f "\n", ##__VA_ARGS__))
#define vktlyrLogW(f, ...) vkt::print(vktFmt("[vktlyr][W] " f "\n", ##__VA_ARGS__))
#define vktlyrLogE(f, ...) vkt::print(vktFmt("[vktlyr][E({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__))

/**
 * @brief Reference layer implementation
 *
 * - Must not invoke at any namespace
 * - Must invoke once and only once
 */
#define vktlyrSetImpl(impl) vktlyr::VktorLayerImpl& vktlyr::__impl = impl;
/** De-reference layer implementation as VktorLayerImpl */
#define vktlyrGetImpl(impl) dynamic_cast<vktlyr::VktorLayerImpl*>(&impl)
/** Define hook pair */
#define vktlyrHook(ns, name) {"vk" #name, (PFN_vkVoidFunction)ns::name}
// clang-format off
/** Default layer hooks */
#define vktlyrDefaultHooks()                                      \
        vktlyrHook(vktlyr, GetInstanceProcAddr),                  \
        vktlyrHook(vktlyr, GetPhysicalDeviceProcAddr),            \
        vktlyrHook(vktlyr, GetDeviceProcAddr),                    \
        vktlyrHook(vktlyr, CreateInstance),                       \
        vktlyrHook(vktlyr, DestroyInstance),                      \
        vktlyrHook(vktlyr, CreateDevice),                         \
        vktlyrHook(vktlyr, DestroyDevice),                        \
        vktlyrHook(vktlyr, EnumerateInstanceLayerProperties),     \
        vktlyrHook(vktlyr, EnumerateInstanceExtensionProperties), \
        vktlyrHook(vktlyr, EnumerateDeviceLayerProperties),       \
        vktlyrHook(vktlyr, EnumerateDeviceExtensionProperties)
// clang-format on

NAMESPACE_BEGIN(vktlyr)

typedef struct LayerDispatchKey_T* LayerDispatchKey;
typedef vkt::HashMap<std::string, PFN_vkVoidFunction> LayerHookMap;

/**
 * @brief Layer dispatch table
 */
template <typename T>
class LayerDispatchTable : private vkt::NonCopyable, protected vkt::HashMap<LayerDispatchKey, T> {
public:
    template <typename K>
    inline LayerDispatchKey key(const K k) const {
        return *(LayerDispatchKey*)k;
    }

    template <typename K>
    inline void set(const K k, const T& t) {
        // ldt[key(k)] = t; Require T has default constructor
        this->insert_or_assign(key(k), t);
    }

    template <typename K>
    inline const T* get(const K k) const {
        auto res = this->find(key(k));
        if (res != this->end()) {
            return &res->second;
        }
        return nullptr;
    }

    template <typename K>
    inline const T* operator[](const K k) {
        return &vkt::HashMap<LayerDispatchKey, T>::operator[](key(k));
    }

    template <typename K>
    inline void del(const K k) {
        this->erase(key(k));
    }
};

/**
 * @brief Base Vulkan layer implementation
 */
class VktorLayerImpl : private vkt::NonCopyable {
protected:
    /**
     * @brief Layer hooks
     *
     * By default, VktorLayerImpl prepares few functions `hooks` (see entry.hpp).
     * Also we can override VktorLayerImpl::hooks at subclass constructor.
     */
    const LayerHookMap hooks{vktlyrDefaultHooks()};

public:
    LayerDispatchTable<VkLayerInstanceDispatchTable> ldt_inst{};
    LayerDispatchTable<VkLayerDeviceDispatchTable> ldt_dev{};

public:
    // Functions
    VktorLayerImpl() = default;
    VktorLayerImpl(const LayerHookMap&& _hooks) : hooks(std::move(_hooks)) {}
    ~VktorLayerImpl() = default;

    /**
     * @brief Get device dispatch table quickly
     *
     * Must make sure the table to get is existed
     */
    template <typename K>
    const VkLayerDeviceDispatchTable* operator[](const K k) {
        return ldt_dev[k];
    }

public:
    // Interfaces
    virtual const PFN_vkVoidFunction tryHook(VkInstance instance, const char* fname) const;
    virtual const PFN_vkVoidFunction tryHook(VkDevice device, const char* fname) const;
    virtual const VkLayerProperties& getLayerProps() const;
    virtual const vkt::Vector<VkExtensionProperties>& getInstanceExtensions() const;
    virtual const vkt::Vector<VkExtensionProperties>& getDeviceExtensions() const;

public:
    // Helpers
    static VkLayerInstanceCreateInfo* getChainInfo(const VkInstanceCreateInfo* create_info, VkLayerFunction func);
    static VkLayerDeviceCreateInfo* getChainInfo(const VkDeviceCreateInfo* create_info, VkLayerFunction func);
    static VkResult copyLayerProperties(const uint32_t src_count,
                                        const VkLayerProperties* src_properties,
                                        uint32_t* dst_count,
                                        VkLayerProperties* dst_properties);
    static VkResult copyExtensionProperties(const uint32_t src_count,
                                            const VkExtensionProperties* src_properties,
                                            uint32_t* dst_count,
                                            VkExtensionProperties* dst_properties);
};

extern VktorLayerImpl& __impl;

NAMESPACE_END(vktlyr)
