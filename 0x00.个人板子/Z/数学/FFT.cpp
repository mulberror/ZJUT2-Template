#include <bits/stdc++.h>

using i64 = long long;
using namespace std;

const int P = 998244353, G = 3;
const int N = 1 << 18 | 1;

template <typename T>
void read(T& x) {
    x = 0; char ch = 0; int f = 1;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
    x *= f;
}

struct NumberTheory { // 数论基础
    static const int N = ::N;
    int fac[N], ifac[N], inv[N];

    int mpow(int x, int y, int p = P) {
        int res = 1;
        while (y) {
            if (y & 1) res = i64(res) * x % p;
            x = i64(x) * x % p;
            y >>= 1;
        }
        return res;
    }

    int gcd(int x, int y) {
        return !y ? x : gcd(y, x % y);
    }

    i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
        if (!b) { x = 1, y = 0; return a; }
        i64 d = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    }

    int Inv(int a, int p = P) {
        return mpow(a, p - 2, p);
        i64 x, y;
        exgcd(a, p, x, y);
        return (x % p + p) % p;
    }

    NumberTheory() {
        fac[0] = 1;
        for (int i = 1; i < N; i++) fac[i] = i64(fac[i - 1]) * i % P;
        ifac[N - 1] = Inv(fac[N - 1]);
        for (int i = N - 2; i >= 0; i--) ifac[i] = i64(ifac[i + 1]) * (i + 1) % P;
        inv[0] = inv[1] = 1;
        for (int i = 2; i < N; i++) inv[i] = i64(P - P / i) * inv[P % i] % P;
    }
} math;

namespace Polynomial {
#define add(x, y) ((x) + (y) >= P ? (x) + (y) - P : (x) + (y))
#define sub(x, y) ((x) - (y) < 0 ? (x) - (y) + P : (x) - (y))
using poly = vector<int>;
const int L = 18, LIM = 1 << L | 1;
struct fft {
    int lg2[LIM], rev[LIM], gn[LIM], ign[LIM];
    fft() {
        lg2[0] = -1;
        for (int i = 1; i < LIM; i++) lg2[i] = lg2[i >> 1] + 1;
        for (int i = 0; i < LIM; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << (L - 1);
        for (int i = 1; i < (1 << L); i <<= 1) {
            int gen = math.mpow(G, (P - 1) / i >> 1), igen = math.Inv(gen);
            gn[i] = ign[i] = 1;
            for (int j = 1; j < i; j++) {
                gn[i + j] = i64(gn[i + j - 1]) * gen % P;
                ign[i + j] = i64(ign[i + j - 1]) * igen % P;
            }
        }
    }
    void ntt(poly& a, int type) {
        int n = a.size(), k = lg2[n], p = 0;
        for (int i = 0; i < n; i++) {
            p = rev[i] >> (L - k);
            if (i < p) swap(a[i], a[p]);
        }
        for (int mid = 1; mid < n; mid <<= 1) {
            for (int i = 0; i < n; i += (mid << 1)) {
                for (int j = 0; j < mid; j++) {
                    int x = a[i + j], y = i64(a[i + j + mid]) * (type ? ign[mid | j] : gn[mid | j]) % P;
                    a[i + j] = add(x, y), a[i + j + mid] = sub(x, y);
                }
            }
        }
    }
    void dft(poly& a) {
        ntt(a, 0);
    }
    void idft(poly& a) {
        ntt(a, 1);
        for (int i = 0, n = a.size(), invn = math.inv[n]; i < n; i++) a[i] = i64(a[i]) * invn % P;
    }
    int extend(int x) {
        int k = 1 << lg2[x];
        return k == x ? k : (k << 1);
    }
} fft;

poly operator*(poly a, int v) {
    for (int i = 0, n = a.size(); i < n; i++) a[i] = i64(a[i]) * v % P;
    return a;
}
poly operator-(poly a) {
    for (int i = 0, n = a.size(); i < n; i++) a[i] = P - a[i];
    return a;
}
poly operator+(poly a, int v) { return a[0] = add(a[0], v), a; }
poly operator-(poly a, int v) { return a[0] = sub(a[0], v), a; }
poly operator-(int v, poly a) { return -a + v; }
poly operator-(const poly& a, const poly& b) {
    poly c(a.size() > b.size() ? a.size() : b.size());
    for (int i = 0; i < a.size() && i < b.size(); i++) c[i] = sub(a[i], b[i]);
    return c;
}

poly operator*(poly a, poly b) {
    int n = a.size(), m = b.size(), k = fft.extend(n + m - 1);
    a.resize(k), b.resize(k);
    fft.dft(a), fft.dft(b);
    for (int i = 0; i < k; i++) a[i] = i64(a[i]) * b[i] % P;
    fft.idft(a);
    a.resize(n + m - 1);
    return a;
} 

poly inv(poly a, int n) { // 多项式求逆
    a.resize(n);
    if (n == 1) return poly(1, math.Inv(a[0]));
    poly b = inv(a, n + 1 >> 1);
    int k = fft.extend(n * 2);
    a.resize(k), b.resize(k);
    fft.dft(a), fft.dft(b);
    for (int i = 0; i < k; i++) b[i] = i64(b[i]) * (P + 2 - i64(a[i]) * b[i] % P) % P;
    fft.idft(b), b.resize(n);
    return b;
}

poly inv(poly a) { return inv(a, a.size()); }

poly dev(poly f) { // 求导
    int n = f.size();
    for (int i = 1; i < n; ++i) f[i - 1] = i64(f[i]) * i % P;
    f.resize(n - 1);
    return f;
}

poly idev(poly f) { // 积分
    int n = f.size();
    for (int i = n - 1; i; --i) f[i] = i64(f[i - 1]) * math.inv[i] % P;
    f[0] = 0;
    return f;
}

poly ln(poly a) { // 多项式求对数
    int n = a.size();
    poly b = dev(a) * inv(a);
    b.resize(n);
    return idev(b);
}

// poly exp(poly a) {

// }

poly ppow(poly a, int y) {
    int n = a.size();
    poly res{1};
    while (y) {
        if (y & 1) res = res * a, res.resize(n);
        a = a * a, a.resize(n);
        y >>= 1;
    }
    return res;
}

void debug(poly a) {
    if (a.size() == 0) {
        cerr << "[]\n";
        return;
    }
    cerr << "[";
    for (int i = 0; i < a.size() - 1; i++) cerr << a[i] << ", ";
    cerr << a[a.size() - 1] << "]\n";
}
}

using namespace Polynomial;
