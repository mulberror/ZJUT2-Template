#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 2e5 + 5;

template <typename T> void read(T& x) {
    x = 0;
    char ch = 0;
    int f = 1;
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
    x *= f;
}

int n, t;
int blockLength;
int a[N], disc[N], b[N];

struct Query {
    int l, r, id, blockId;

    bool operator<(const Query& rhs) const {
        if (blockId == rhs.blockId) {
            return r < rhs.r;
        } else {
            return blockId < rhs.blockId;
        }
    }
} q[N];

int cnt[N];
i64 ans;
i64 qans[N];

void add(int id) {
    int x = a[id];
    ans += (2 * cnt[x] + 1) * b[x];
    cnt[x]++;
}

void del(int id) {
    int x = a[id];
    ans -= (2 * cnt[x] - 1) * b[x];
    cnt[x]--;
}

int main() {
    read(n), read(t);
    blockLength = sqrt(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        disc[i] = a[i];
    }
    sort(disc + 1, disc + 1 + n);
    int eleCnt = unique(disc + 1, disc + 1 + n) - disc - 1;
    for (int i = 1; i <= n; i++) {
        int x = lower_bound(disc + 1, disc + 1 + eleCnt, a[i]) - disc;
        b[x] = a[i];
        a[i] = x;
    }
    for (int i = 1; i <= t; i++) {
        read(q[i].l), read(q[i].r);
        q[i].blockId = (q[i].l - 1) / blockLength + 1;
        q[i].id = i;
    }
    sort(q + 1, q + 1 + t);
    int l = 0, r = 1;
    ans = 0;
    for (int i = 1; i <= t; i++) {
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        qans[q[i].id] = ans;
    }
    for (int i = 1; i <= t; i++) {
        printf("%lld\n", qans[i]);
    }
    return 0;
}