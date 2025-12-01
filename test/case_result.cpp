#include "__helpers.hpp"
#include <share/result.hpp>

static uint32_t cnt = 0;
static uint32_t cnt_copy = 0;
static uint32_t cnt_move = 0;
static uint32_t cnt_copy_assign = 0;
static uint32_t cnt_move_assign = 0;

void resetCnt() {
    cnt = 0;
    cnt_copy = 0;
    cnt_move = 0;
    cnt_copy_assign = 0;
    cnt_move_assign = 0;
}

void assertCnt(uint32_t c, uint32_t cc, uint32_t cm, uint32_t cca, uint32_t cma) {
    assert(cnt == c);
    assert(cnt_copy == cc);
    assert(cnt_move == cm);
    assert(cnt_copy_assign == cca);
    assert(cnt_move_assign == cma);
}

void printCnt() {
    tstOut("{}, {}, {}, {}, {}", cnt, cnt_copy, cnt_move, cnt_copy_assign, cnt_move_assign);
}

class Vec {
public:
    int* num;

    Vec() {
        cnt++;
        num = new int[3];
        num[0] = 123;
    }
    Vec(const Vec& rhs) {
        cnt_copy++;
        num = new int[3];
        num[0] = rhs.num[0];
        tstOut("Vec.Copy");
    }
    Vec& operator=(const Vec& rhs) {
        cnt_copy_assign++;
        num = new int[3];
        num[0] = rhs.num[0];
        tstOut("Vec.CopyAssign");
        return *this;
    }

    Vec(Vec&& rhs) {
        cnt_move++;
        num = rhs.num;
        rhs.num = nullptr;
        tstOut("Vec.Move");
    }
    Vec& operator=(Vec&& rhs) {
        cnt_move_assign++;
        num = rhs.num;
        rhs.num = nullptr;
        tstOut("Vec.MoveAssign");
        return *this;
    }

    bool operator==(const Vec& rhs) const {
        return num[0] == rhs.num[0];
    }
};

using tstOk = Ok<Vec>;
using tstErr = Err<std::runtime_error>;
using tstRes = Result<Vec, std::runtime_error>;

tstRes createVec(uint32_t type) {
    switch (type) {
    case 1:
        {
            return tstOk(Vec{});
        }
        break;
    case 2:
        {
            Vec v;
            tstOk r = std::move(v);
            return r;
        }
        break;
    case 3:
        {

            Vec v;
            tstRes r = tstOk(std::move(v));
            return r;
        }
        break;
    case 22:
        {
            Vec v;
            tstOk r = v;
            return r;
        }
        break;
    case 33:
        {

            Vec v;
            tstRes r = tstOk(v);
            return r;
        }
        break;
    default:
        {
            return tstErr(std::runtime_error("Vec.Error"));
        }
        break;
    }
}

void case_result() {
    {
        resetCnt();
        tstRes r = createVec(1);
        assert(r.isOk());
        assertCnt(1, 0, 2, 0, 0);
    }
    {
        resetCnt();
        tstRes r = createVec(2);
        assert(r.isOk());
        assertCnt(1, 0, 2, 0, 0);
    }
    {
        resetCnt();
        tstRes r = createVec(3);
        assert(r.isOk());
        assertCnt(1, 0, 3, 0, 0);
    }

    {
        resetCnt();
        tstRes r = createVec(22);
        assert(r.isOk());
        assertCnt(1, 1, 1, 0, 0);
    }
    {
        resetCnt();
        tstRes r = createVec(33);
        assert(r.isOk());
        assertCnt(1, 1, 2, 0, 0);
    }

    {
        resetCnt();
        tstRes r = createVec(0);
        assert(r.isErr());
        assertCnt(0, 0, 0, 0, 0);

        tstOut("{}", r.unwrapErr().what());
        try {
            r.unwrap();
        } catch (const std::exception e) {
            tstOut("Catch {}", e.what());
        }
    }
}
