#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int N = 1e5 + 5;

struct edge {
    int to, nxt;
} ed[N << 1];
int edgeCnt;
int head[N];

void addEdge(int u, int v) {
    ed[++edgeCnt] = (edge){v, head[u]};
    head[u] = edgeCnt;
}

int BIT[N][21];
int dep[N];

void dfs(int u, int fa) {
    BIT[u][0] = fa, dep[u] = dep[fa] + 1;
    for (int i = 1; i <= 20; i++) {
        BIT[u][i] = BIT[BIT[u][i - 1]][i - 1];
    }
    for (int e = head[u]; e; e = ed[e].nxt) {
        int v = ed[e].to;
        if (v != fa) {
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    for (int i = 20; i >= 0; i--) {
        if (dep[BIT[u][i]] >= dep[v]) {
            u = BIT[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; i--) {
        if (BIT[u][i] != BIT[v][i]) {
            u = BIT[u][i];
            v = BIT[v][i];
        }
    }
    return BIT[u][0];
}
