#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 100005
using namespace std;
int x, y, n, m, MOD, a[N], T[N << 2], tag1[N << 2], tag2[N << 2], z;
void Build(int p, int l, int r) {
    if (l == r) {
        T[p] = a[l] % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    Build(p << 1, l, mid);
    Build(p << 1 | 1, mid + 1, r);
    T[p] = ((long long)T[p << 1] + T[p << 1 | 1]) % MOD;
}
void pushdown(int p, int l, int r) {
    int mid = (l + r) >> 1;
    T[p << 1] = ((long long)T[p << 1] * tag1[p] % MOD + (long long)tag2[p] * (mid - l + 1) % MOD) % MOD;
    T[p << 1 | 1] = ((long long)T[p << 1 | 1] * tag1[p] % MOD + (long long)tag2[p] * (r - mid) % MOD) % MOD;
    tag1[p << 1] = (long long)tag1[p << 1] * tag1[p] % MOD;
    tag1[p << 1 | 1] = (long long)tag1[p << 1 | 1] * tag1[p] % MOD;
    tag2[p << 1] = ((long long)tag2[p << 1] * tag1[p] % MOD + tag2[p]) % MOD;
    tag2[p << 1 | 1] = ((long long)tag2[p << 1 | 1] * tag1[p] % MOD + tag2[p]) % MOD;
    tag1[p] = 1;
    tag2[p] = 0;
}
void Change1(int p, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) {
        T[p] = (long long)T[p] * z % MOD;
        tag1[p] = (long long)tag1[p] * z % MOD;
        tag2[p] = (long long)tag2[p] * z % MOD;
        return;
    }
    if (tag1[p] != 1 || tag2[p])
        pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid)
        Change1(p << 1, l, mid, x, y, z);
    if (y > mid)
        Change1(p << 1 | 1, mid + 1, r, x, y, z);
    T[p] = ((long long)T[p << 1] + T[p << 1 | 1]) % MOD;
}
void Change2(int p, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) {
        T[p] = ((long long)T[p] + (long long)z * (r - l + 1)) % MOD;
        tag2[p] = ((long long)tag2[p] + z) % MOD;
        return;
    }
    if (tag1[p] != 1 || tag2[p])
        pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid)
        Change2(p << 1, l, mid, x, y, z);
    if (y > mid)
        Change2(p << 1 | 1, mid + 1, r, x, y, z);
    T[p] = ((long long)T[p << 1] + T[p << 1 | 1]) % MOD;
}
int Query(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y)
        return T[p];
    if (tag1[p] != 1 || tag2[p])
        pushdown(p, l, r);
    int mid = (l + r) >> 1;
    int t = 0;
    if (x <= mid)
        t = ((long long)t + Query(p << 1, l, mid, x, y)) % MOD;
    if (y > mid)
        t = ((long long)t + Query(p << 1 | 1, mid + 1, r, x, y)) % MOD;
    return t;
}
int main() {
    scanf("%d%d%d", &n, &m, &MOD);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    Build(1, 1, n);
    for (int i = 1; i <= (n << 2); i++) tag1[i] = 1;
    while (m--) {
        scanf("%d", &x);
        if (x == 1) {
            scanf("%d%d%d", &x, &y, &z);
            Change1(1, 1, n, x, y, z);
            continue;
        }
        if (x == 2) {
            scanf("%d%d%d", &x, &y, &z);
            Change2(1, 1, n, x, y, z);
            continue;
        }
        if (x == 3) {
            scanf("%d%d", &x, &y);
            printf("%d\n", Query(1, 1, n, x, y));
        }
    }
}