#pragma once
#include <cstring>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace vkt {

#define newBox  std::make_unique
#define newPtr  std::make_shared
#define newRef  std::ref
#define newCRef std::cref

template <typename T>
using Box = std::unique_ptr<T>;

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;

template <typename T>
using Ref = std::reference_wrapper<T>;

template <typename T>
using CRef = std::reference_wrapper<const T>;

template <typename T>
using Opt = std::optional<T>;

template <typename T>
using Vector = std::vector<T>;

template <typename K, typename T, typename P = std::less<K>>
using Map = std::map<K, T, P>;

template <typename K, typename T, typename H = std::hash<K>>
using HashMap = std::unordered_map<K, T, H>;

template <typename T>
inline uint8_t u8(T value) {
    return static_cast<uint8_t>(value);
}

template <typename T>
inline uint16_t u16(T value) {
    return static_cast<uint16_t>(value);
}

template <typename T>
inline uint32_t u32(T value) {
    return static_cast<uint32_t>(value);
}

template <typename T>
inline uint64_t u64(T value) {
    return static_cast<uint64_t>(value);
}

inline static bool strLess(const char* a, const char* b) {
    return std::strcmp(a, b) < 0;
}

/**
 * @brief Hash combination function from boost
 *
 * @param seed The base hash value
 * @param v The value to hash then combine with seed
 */
template <class T>
inline void hashCombine(size_t& seed, const T& v) {
    size_t hash = std::hash<T>{}(v);
    hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash;
}

template <typename T, typename... Args>
inline void hashCombine(size_t& seed, const T& first, const Args&... args) {
    hashCombine(seed, first);
    hashCombine(seed, args...);
}

/**
 * @brief Hash function for libvktor
 *
 * Just implement std::hash via hashCombine for what need to hash
 */
template <typename... Args>
inline size_t hash(const Args&... args) {
    size_t seed = 0;
    hashCombine(seed, args...);
    return seed;
}

/**
 * @brief Print vector to string
 */
template <typename T>
auto vec2str(const Vector<T>& vec) -> std::string {
    std::string str("[");
    for (const auto& v : vec) {
        str += " ";
        str += std::to_string(v);
        str += ",";
    }
    str += " ]";

    return std::move(str);
}

} // namespace vkt
