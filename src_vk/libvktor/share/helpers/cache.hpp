#pragma once
#include "../printer.hpp"
#include "helpers.hpp"
#include "result.hpp"
#include "traits.hpp"
#include <functional>
#include <mutex>

template <typename T>
class Cache : private NonCopyable {
private:
    HashMap<size_t, T> map{};
    std::mutex mtx{};

public:
    Cache() {}
    // Just create a new mutex, no need to move mutex and mutex doesn't has move constructor.
    Cache(Cache&& rhs) : map(std::move(rhs.map)) {}
    Cache& operator=(Cache&& rhs) {
        map = std::move(rhs.map);
        return *this;
    }

    inline size_t size() const {
        return map.size();
    }

    inline void clear() {
        std::lock_guard<std::mutex> guard(mtx);
        map.clear();
    }

    /**
     * @brief Request resource that stored in `map`
     *
     * CRef<T>不应该长久持有，因为map中value的地址可能会变
     */
    inline Res<CRef<T>> request(size_t key, std::function<Res<T>()> fn) {
        std::lock_guard<std::mutex> guard(mtx);

        T* ptr;
        if (auto it = map.find(key); it != map.end()) {
            ptr = &it->second;
        } else {
            OnErr(res, fn());
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
