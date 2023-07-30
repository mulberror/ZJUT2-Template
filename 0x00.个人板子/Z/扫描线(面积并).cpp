/*
 * Author: chhokmah
 * Date: 2020-08-17 21:42:52
 */

#include <bits/stdc++.h>

#define y2 LZMAKIOI

using namespace std;

template <typename T>
void read(T& x) {
    x = 0;
    int c = 0, f = 0;
    for (; !isdigit(c); c = getchar()) f |= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c & 15);
    x = f ? -x : x;
}

const int N = 2e5 + 5;

struct Line {
    int x, y1, y2, type;

    bool operator<(const Line& rhs) const {
        return x < rhs.x;
    }
} s[N << 1];

int n, dcnt, m;
int disc[N << 1];
long long ans = 0;

struct Node {
    int sum;
    int cnt;  //cover precisely
} seg[N << 4];

void pushup(int p, int l, int r) {
    if (seg[p].cnt > 0)
        seg[p].sum = disc[r + 1] - disc[l];
    else if (seg[p << 1].cnt > 0 && seg[p << 1 | 1].cnt > 0)
        seg[p].sum = disc[r + 1] - disc[l];
    else
        seg[p].sum = seg[p << 1].sum + seg[p << 1 | 1].sum;
}

void modify(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        seg[p].cnt += v;
        pushup(p, l, r);
        return;
    }
    int mid = l + r >> 1;
    if (ql <= mid) modify(p << 1, l, mid, ql, qr, v);
    if (qr > mid) modify(p << 1 | 1, mid + 1, r, ql, qr, v);
    pushup(p, l, r);
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        int x1, x2, y1, y2;
        read(x1), read(y1), read(x2), read(y2);
        s[++m] = (Line){x1, y1, y2, 1};
        s[++m] = (Line){x2, y1, y2, -1};
        disc[++dcnt] = y1;
        disc[++dcnt] = y2;
    }
    sort(s + 1, s + 1 + m);
    sort(disc + 1, disc + 1 + dcnt);
    dcnt = unique(disc + 1, disc + 1 + dcnt) - disc - 1;
    s[m + 1].x = s[m].x;
    for (int i = 1; i <= m; i++) {
        s[i].y1 = lower_bound(disc + 1, disc + 1 + dcnt, s[i].y1) - disc;
        s[i].y2 = lower_bound(disc + 1, disc + 1 + dcnt, s[i].y2) - disc;
        modify(1, 1, dcnt, s[i].y1, s[i].y2 - 1, s[i].type);
        if (s[i].x != s[i + 1].x) ans += 1ll * seg[1].sum * (s[i + 1].x - s[i].x);
    }
    printf("%lld\n", ans);
    return 0;
}
