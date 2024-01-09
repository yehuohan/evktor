#pragma once
#include <iostream>
#include <optional>
#include <variant>

namespace vkt {

/** By pass Result<Err> */
#define OnErr(r)                     \
    if ((r).isErr()) {               \
        return Err((r).unwrapErr()); \
    }

template <typename T>
struct Ok {
    T value;
    Ok(const T& val) : value(val) {}
    Ok(T&& val) : value(std::move(val)) {}
    Ok(const Ok<T>&) = delete; // value should have one owner of Ok
    Ok(Ok<T>&&) = default;
};

template <typename E>
struct Err {
    E value;
    Err(const E& val) : value(val) {}
    Err(E&& val) : value(std::move(val)) {}
    Err(const Err<E>&) = delete; // value should have one owner of Err
    Err(Err<E>&&) = default;
};

/**
 * @brief A simplified `Result` like rust's `std::Result`
 *
 * Code is studied from https://github.com/p-ranav/result
 */
template <typename T, typename E>
class Result {
public:
    std::variant<Ok<T>, Err<E>> value;

    Result(const Ok<T>& val) : value(val) {}
    Result(const Err<E>& val) : value(val) {}
    Result(Ok<T>&& val) : value(std::move(val)) {}
    Result(Err<E>&& val) : value(std::move(val)) {}
    Result(const Result<T, E>&) = delete; // value should have one owner of Result
    Result(Result<T, E>&&) = default;

    bool isOk() const {
        return std::holds_alternative<Ok<T>>(value);
    }

    bool isErr() const {
        return std::holds_alternative<Err<E>>(value);
    }

    /**
     * @brief Convert from Result<T, E> to std::optional<const T*>
     */
    std::optional<const T*> ok() const {
        if (isOk()) {
            return &std::get<Ok<T>>(value).value;
        }
        return {};
    }

    /**
     * @brief Convert from Result<T, E> to std::optional<const E*>
     */
    std::optional<const E*> err() const {
        if (isErr()) {
            return &std::get<Err<E>>(value).value;
        }
        return {};
    }

    /**
     * @brief Unwrap a result, then yield the content of an Ok, or throw if the value is an Err
     *
     * `unwrap` will move out the value, so DO NOT unwrap a result more than once.
     * And unwrap CAN NOT mark as a const function to perform `std::move`.
     */
    auto unwrap() {
        if (isOk()) {
            return std::get<Ok<T>>(std::move(value)).value;
        } else {
            throw std::get<Err<E>>(std::move(value)).value;
        }
    }

    /**
     * @brief Unwrap a result, then yield the content of an Err, or throw if the value is an Ok
     *
     * `unwrapErr` will move out the value, so DO NOT unwrap a result more than once.
     * And unwrap CAN NOT mark as a const function to perform `std::move`.
     */
    auto unwrapErr() {
        if (isErr()) {
            return std::get<Err<E>>(std::move(value)).value;
        } else {
            throw std::get<Ok<T>>(std::move(value)).value;
        }
    }

    // All `operator` requires T and E has corresponding implementation
    bool operator==(const Ok<T>& val) const {
        return isOk() && std::get<Ok<T>>(value).value == val.value;
    }

    bool operator==(const Err<E>& val) const {
        return isErr() && std::get<Err<E>>(value).value == val.value;
    }

    bool operator==(const Result<T, E>& rhs) const {
        return ((isOk() && rhs.isOk() && *this == std::get<Ok<T>>(rhs.value)) ||
                (isErr() && rhs.isErr() && *this == std::get<Err<E>>(rhs.value)));
    }

    bool operator!=(const Result<T, E>& rhs) const {
        return !(*this == rhs);
    }
};

template <typename T>
using Res = Result<T, std::runtime_error>;

} // namespace vkt
