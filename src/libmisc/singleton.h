#pragma once
#include <iostream>

// over c++11 is required
template<typename T>
class TSingleton {
public:
    static T& GetInstance() {
        // C++ 11之后，被static修饰的变量可以保证是线程安全
        static T instance;
        return instance;
    }

    TSingleton(T&&) = delete;
    TSingleton(const T&) = delete;
    T& operator=(const T&) = delete;

protected:
    TSingleton() = default;
    virtual ~TSingleton() = default;
};
