#include <bits/stdc++.h>
using namespace std;
char buf[1 << 21], *p1 = buf, *p2 = buf, ch;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
template <typename T>
void read(T& x) {
    x = ch = 0;
    for (; ch < '0' || ch > '9'; ch = getchar())
        ;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch & 15);
}
template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T>
void writeln(T x) {
    write(x), putchar('\n');
}

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}
i64 inv(i64 a, i64 b) {  // 求解 ax=1(mod b)
    i64 x, y;
    i64 g = exgcd(a, b, x, y);
    return g == 1 ? (x % b + b) % b : -1;
}
i64 calc(i64 A, i64 B, i64 C) {  // -Ax + By = C (x>=0)
    i64 x, y, g, gd = gcd(A, B);
    g = exgcd(-A, B, x, y);
    A /= gd, B /= gd;
    if (C % g != 0) return -1;
    x *= C / g;
    return (x % B + B) % B;
}
i64 gcd(i64 x, i64 y) { return !y ? x : gcd(y, x % y); }
i64 lcm(i64 x, i64 y) { return x / gcd(x, y) * y; }
i64 exCRT(vector<i64> a, vector<i64> b) {  // x = a (mod b)
    int n = a.size();
    i64 M = b[0];
    i64 ans = a[0] % M;
    for (int i = 1; i < n; i++) {
        i64 tmp = calc(M, b[i], ans - a[i]);
        if (tmp == -1) return -1;
        ans += M * tmp;
        M = lcm(M, b[i]);
    }
    return ans;
}

int n;
vector<i64> a, b;

int main() {
    read(n);
    for (int i = 0; i < n; i++) {
        i64 x, y;
        read(x), read(y);
        a.push_back(x), b.push_back(y);
    }
    i64 ans = exCRT(b, a);
    writeln(ans);
    return 0;
}