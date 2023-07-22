#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct DSU {
    vector<int> fa, siz;

    DSU(int n) {
        fa.clear(), fa.resize(n + 1);
        siz.clear(), siz.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
        fill(siz.begin(), siz.end(), 1);
    }

    int get(int u) { return fa[u] == u ? fa[u] : fa[u] = get(fa[u]); }

    int size(int u) { return siz[get(u)]; }

    void merge(int x, int y) {
        x = get(x), y = get(y);
        if (x != y) {
            fa[x] = y;
            siz[y] += siz[x];
        }
    }
};

struct rDSU {};