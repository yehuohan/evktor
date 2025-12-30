#include "__helpers.hpp"

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

using TstOk = Ok<Vec>;
using TstErr = Err<std::runtime_error>;
using TstRes = Result<Vec, std::runtime_error>;

TstRes createVec(uint32_t type) {
    switch (type) {
    case 1:
        {
            return TstOk(Vec{}); // Construct, move construct
        }
        break;
    case 2:
        {
            Vec v;                  // Construct
            TstOk r = std::move(v); // Move construct
            return r;
        }
        break;
    case 22:
        {
            Vec v;       // Construct
            TstOk r = v; // Copy construct
            return r;
        }
        break;
    case 3:
        {

            Vec v;                          // Construct
            TstRes r = TstOk(std::move(v)); // Move construct, move construct
            return r;
        }
        break;
    case 33:
        {

            Vec v;               // Construct
            TstRes r = TstOk(v); // Copy construct
            return r;
        }
        break;
    default:
        {
            return TstErr(std::runtime_error("Vec.Error"));
        }
        break;
    }
}

void case_share_result() {
    {
        resetCnt();
        TstRes r = createVec(1); // Move construct
        assert(r.isOk());
        auto v = r.unwrap(); // Move construct
        assertCnt(1, 0, 3, 0, 0);
    }

    {
        resetCnt();
        TstRes r = createVec(2); // Move construct
        assert(r.isOk());
        auto v = std::move(r.unwrap()); // Move construct, move construct
        assertCnt(1, 0, 4, 0, 0);
    }
    {
        resetCnt();
        TstRes r = createVec(22); // Move construct
        assert(r.isOk());
        Vec v;          // Construct
        v = r.unwrap(); // Move assign
        assertCnt(2, 1, 2, 0, 1);
    }

    {
        resetCnt();
        TstRes r = createVec(3); // Move construct
        assert(r.isOk());
        auto v = r.unwrap(); // Move construct
        assertCnt(1, 0, 4, 0, 0);
    }
    {
        resetCnt();
        TstRes r = createVec(33); // Move construct
        assert(r.isOk());
        auto v = r.unwrap(); // Move construct
        Vec u;               // Construct
        u = v;               // Copy assign
        assertCnt(2, 1, 3, 1, 0);
    }

    {
        resetCnt();
        TstRes r = createVec(0);
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
