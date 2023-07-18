#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 2e5 + 5;

struct segment2 {  // 构造一个区间加和区间乘区间查询的线段树
    int cnt[N << 2], mul[N << 2], add[N << 2];
    i64 sum[N << 2];

    void pushup(int p) {
        cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }
    void build(int p, int l, int r) {
        cnt[p] = add[p] = sum[p] = 0;
        mul[p] = 1;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void apply0(int p, int v) {  // 处理乘法懒标记
        sum[p] *= v;
        add[p] *= v;
        mul[p] *= v;
    }
    void apply1(int p, int v) {  // 处理加法懒标记
        sum[p] += i64(cnt[p]) * v;
        add[p] += v;
    }
    void pushdown(int p) {
        if (mul[p] != 1) {
            apply0(p << 1, mul[p]);
            apply0(p << 1 | 1, mul[p]);
            mul[p] = 1;
        }
        if (add[p] != 0) {
            apply1(p << 1, add[p]);
            apply1(p << 1 | 1, add[p]);
            add[p] = 0;
        }
    }
    void secmul(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            apply0(p, v);
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) secmul(p << 1, l, mid, ql, qr, v);
        if (qr > mid) secmul(p << 1 | 1, mid + 1, r, ql, qr, v);
        pushup(p);
    }
    void secadd(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            apply1(p, v);
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) secadd(p << 1, l, mid, ql, qr, v);
        if (qr > mid) secadd(p << 1 | 1, mid + 1, r, ql, qr, v);
        pushup(p);
    }
    void insert(int p, int l, int r, int pos, int v) {
        if (l == r) {
            cnt[p] = 1;
            sum[p] = v;
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            insert(p << 1, l, mid, pos, v);
        } else {
            insert(p << 1 | 1, mid + 1, r, pos, v);
        }
        pushup(p);
    }
    i64 query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[p];
        pushdown(p);
        i64 sum = 0;
        int mid = (l + r) >> 1;
        if (ql <= mid) sum += query(p << 1, l, mid, ql, qr);
        if (qr > mid) sum += query(p << 1 | 1, mid + 1, r, ql, qr);
        return sum;
    }
} sgt2;

int main() { return 0; }