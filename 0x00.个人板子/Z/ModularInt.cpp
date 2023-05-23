#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>
T power(T x, i64 y) {
    T res = 1;
    for (; y; y >>= 1, x *= x) {
        if (y & 1) {
            res *= x;
        }
    }
    return res;
}

template <int MOD = 998244353>
struct ModularInt {
    static constexpr int P = MOD;

    static int norm(int x) {
        x %= P;
        if (x < 0) {
            x += P;
        }
        return x;
    }

    int x;

    ModularInt() : x(0) {}
    ModularInt(int x) : x(norm(x)) {}

    int val() const { return v; }
    ModularInt operator-() const { return ModularInt(P - x); }

    ModularInt inv() const {
        assert(v != 0);
        return power(*this, P - 2);
    }

    ModularInt &operator=(const int &rhs) { return v = norm(rhs), *this; }

    ModularInt &operator+=(const ModularInt &rhs) { return v = fix(v + rhs.v), *this; }
    ModularInt &operator-=(const ModularInt &rhs) { return v = fix(v - rhs.v), *this; }
    ModularInt &operator*=(const ModularInt &rhs) { return v = i64(v) * rhs.v % P, *this; }
    ModularInt &operator/=(const ModularInt &rhs) { return *this *= rhs.inv(), *this; }

    ModularInt operator+(const ModularInt &rhs) { return ModularInt((*this).val()) += rhs; }
    ModularInt operator-(const ModularInt &rhs) { return ModularInt((*this).val()) -= rhs; }
    ModularInt operator*(const ModularInt &rhs) { return ModularInt((*this).val()) *= rhs; }
    ModularInt operator/(const ModularInt &rhs) { return ModularInt((*this).val()) /= rhs; }

    friend std::ostream &operator<<(std::ostream &os, const ModularInt &rhs) {
        return os << rhs.val();
    }

    friend std::istream &operator>>(std::istream &is, ModularInt &rhs) {
        i64 x;
        is >> x;
        rhs = x;
        return is;
    }
};

using mint = ModularInt<998244353>;
