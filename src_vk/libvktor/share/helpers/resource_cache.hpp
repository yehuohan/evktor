#pragma once
#include "../printer.hpp"
#include "helpers.hpp"
#include "result.hpp"
#include "traits.hpp"
#include <functional>
#include <mutex>

template <typename T>
class ResourceCache : private NonCopyable {
private:
    HashMap<size_t, T> map{};
    std::mutex mtx{};

public:
    ResourceCache() {}
    // Just create a new mutex, no need to move mutex and mutex doesn't has move constructor.
    ResourceCache(ResourceCache&& rhs) : map(std::move(rhs.map)) {}
    ResourceCache& operator=(ResourceCache&& rhs) {
        map = std::move(rhs.map);
        return *this;
    }

    auto begin() {
        return map.begin();
    }

    auto end() {
        return map.end();
    }

    const auto begin() const {
        return map.begin();
    }

    const auto end() const {
        return map.end();
    }

    inline size_t size() const {
        return map.size();
    }

    inline void clear() {
        map.clear();
    }

    inline HashMap<size_t, T>::iterator find(size_t key) {
        return map.find(key);
    }

    inline bool found(const HashMap<size_t, T>::iterator& item) {
        return item != map.end();
    }

    /**
     * @brief Request resource that stored in `map`
     *
     * CRef<T>不应该长久持有，因为map中value的地址可能会变
     */
    inline Res<CRef<T>> request(size_t key, std::function<Res<T>()> fn) {
        std::lock_guard<std::mutex> guard(mtx);

        T* ptr;
        if (auto it = this->find(key); this->found(it)) {
            ptr = &it->second;
        } else {
            auto res = fn();
            OnErr(res);
            auto iter = this->add(key, res.unwrap());
            ptr = &iter->second;
        }

        return Ok(newCRef(*ptr));
    }

private:
    /**
     * @brief Add resource
     *
     * This returns the iterator returned from HashMap::insert() directly.
     * So you should make sure the insertion is going to success or fail.
     */
    inline HashMap<size_t, T>::iterator add(size_t key, T&& value) {
        return map.insert({key, std::move(value)}).first;
    }
};
