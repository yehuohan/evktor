#pragma once
#include <volk.h>

#include "generated/vk_initializer.hpp"
#include "generated/vk_string.hpp"
#include "share/helpers.hpp"
#include "share/result.hpp"
#include "share/share.hpp"
#include "share/traits.hpp"
#include <string>

#define VKT_CORE_VERBOSE        true
#define VKT_CORE_QUEUE_PRIORITY 1.0f
#define VKT_CORE_MAX_SETS       16

NAMESPACE_BEGIN(vkt)
NAMESPACE_BEGIN(core)

/**
 * @brief Enumerate template for Vulkan
 *
 * Function 'F' return VkResult
 */
template <typename T, typename F, typename... Ts>
auto enumerate(Vector<T>& out, F&& f, Ts&&... ts) -> VkResult {
    uint32_t count = 0;
    VkResult ret;
    do {
        ret = f(ts..., &count, nullptr);
        if (ret != VK_SUCCESS) {
            return ret;
        }
        out.resize(count);
        ret = f(ts..., &count, out.data());
        out.resize(count);
    } while (ret == VK_INCOMPLETE);
    return ret;
}

/**
 * @brief Enumerate template for Vulkan
 *
 * Function 'F' return void
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

template <typename T>
auto vec2str(const Vector<T>& vec) -> std::string {
    std::string str("[");
    for (uint32_t k = 0; k < vec.size(); k++) {
        str += " ";
        str += std::to_string(k);
        str += ",";
    }
    str += " ]";

    return std::move(str);
}

NAMESPACE_END(core)
NAMESPACE_END(vkt)
