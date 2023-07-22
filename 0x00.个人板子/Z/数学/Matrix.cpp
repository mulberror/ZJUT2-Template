#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int P = 1e9 + 7;

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

struct M {  // -P < x < 2 * P
   private:
    int fix(int x) { return x < 0 ? x + P : (x < P ? x : x -= P); }
    int norm(int x) { return fix(x < -P || x > P ? x %= P : x); }

    int v;

   public:
    M() : v(0) {}
    M(int x) : v(norm(x)) {}
    M(i64 x) : v(norm(x)) {}

    int val() const { return v; }
    M operator-() const { return M(P - v); }

    M inv() const {
        assert(v != 0);
        return power(*this, P - 2);
    }

    M &operator=(const int &rhs) { return v = norm(rhs), *this; }
    M &operator=(const i64 &rhs) { return v = norm(rhs), *this; }
    M &operator+=(const M &rhs) { return v = fix(v + rhs.v), *this; }
    M &operator-=(const M &rhs) { return v = fix(v - rhs.v), *this; }
    M &operator*=(const M &rhs) { return v = i64(v) * rhs.v % P, *this; }
    M &operator/=(const M &rhs) { return *this *= rhs.inv(), *this; }
    M operator+(const M &rhs) { return M((*this).val()) += rhs; }
    M operator-(const M &rhs) { return M((*this).val()) -= rhs; }
    M operator*(const M &rhs) { return M((*this).val()) *= rhs; }
    M operator/(const M &rhs) { return M((*this).val()) /= rhs; }

    friend std::ostream &operator<<(std::ostream &os, const M &rhs) { return os << rhs.val(); }

    friend std::istream &operator>>(std::istream &is, M &rhs) {
        i64 x;
        ;
        is >> x;
        rhs = x;
        return is;
    }
};

struct Matrix {
   private:
    std::vector<std::vector<M> > a;

   public:
    Matrix() { a.resize(0); }
    Matrix(int n, int m) { a.resize(n, std::vector<M>(m, 0)); }

    int row() const { return int(a.size()); }

    int column() const { return int(a[0].size()); }

    std::vector<M> &operator[](int i) { return a[i]; }

    std::vector<M> operator[](int i) const { return a[i]; }

    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        assert(a.column() == b.row());
        Matrix c(a.row(), b.column());

        for (int i = 0; i < a.row(); i++) {
            for (int j = 0; j < b.column(); j++) {
                for (int k = 0; k < a.column(); k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
            std::cerr << "dbg:" << i << "\n";
        }
        return c;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs) {
        for (int i = 0; i < rhs.row(); i++) {
            for (int j = 0; j < rhs.column(); j++) {
                os << rhs[i][j] << " \n"[j == rhs.column() - 1];
            }
        }
        return os;
    }
};

M a[505][505], b[505][505], c[505][505];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, p, m;
    std::cin >> n >> p >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> b[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}