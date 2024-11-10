#include <iostream>
#include <share/result.hpp>

class Vec {
public:
    int* num;

    Vec() {
        num = new int[3];
        num[0] = 121;
    }
    Vec(const Vec& vec) {
        *this = vec;
    }
    Vec(Vec&& vec) {
        *this = std::move(vec);
    }
    Vec& operator=(const Vec& vec) {
        num = new int[3];
        num[0] = vec.num[0];
        std::printf("Copy vec\n");
        return *this;
    }
    Vec& operator=(Vec&& vec) {
        num = vec.num;
        vec.num = nullptr;
        std::printf("Move vec\n");
        return *this;
    }
    bool operator==(const Vec& vec) const {
        return num[0] == vec.num[0];
    }
    void print() const {
        if (num) {
            std::printf("num[0]: %d\n", num[0]);
        } else {
            std::printf("num[0]: nullptr\n");
        }
    }
};

using vktOk = vkt::Ok<Vec>;
using vktErr = vkt::Err<std::runtime_error>;
using vktRes = vkt::Result<Vec, std::runtime_error>;

vktRes get() {
    Vec v;
    // return vktErr(std::runtime_error("Vec error"));
    return vktOk(std::move(v));
    // vktOk r = std::move(v); return r;
    // vktRes r = vktOk(std::move(v)); return r;
}

void case_result() {
    get();
    vktRes r = get();

    std::printf("c1: %d\n", r == vktOk(Vec{}));

    if (r.ok().has_value()) {
        r.ok().value()->print();
    }
    if (r.isOk()) {
        r.ok().value()->print();
    }
    if (r.isErr()) {
        std::printf("%s\n", r.err().value()->what());
    }
    if (r.err().has_value()) {
        std::printf("%s\n", r.err().value()->what());
    }
    try {
        r.unwrap().print();
        // std::printf("%s\n", r.unwrapErr().what());
    } catch (const std::exception& e) {
        std::printf("Catch %s\n", e.what());
    }
}
