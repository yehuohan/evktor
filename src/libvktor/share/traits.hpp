#pragma once

namespace vkt {

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

} // namespace vkt
