#pragma once

/**
 * @brief Non-copyable
 *
 * Though there's an explict move constructor, something like `T t(rhs)` still
 * can NOT compile successful.
 */
class NonCopyable {
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

/**
 * @brief Non-moveable
 *
 * If there's an explict copy constructor, something like `T t(std::move(rhs))`
 * can compile successful and invoke copy constructor instead.
 */
class NonMoveable {
protected:
    NonMoveable() = default;
    ~NonMoveable() = default;

    NonMoveable(NonMoveable&&) = delete;
    NonMoveable& operator=(NonMoveable&&) = delete;
};

/**
 * @brief Singleton base class
 *
 * Example code:
 * ```cpp
 *  class Object : public Singleton<Object> {
 *      friend class Singleton<Object>;
 *
 *      private:
 *          Object();
 *          ~Object();
 *  };
 * ```
 */
template <typename T>
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

public:
    static T& get() {
        static T instance{};
        return instance;
    }
};
