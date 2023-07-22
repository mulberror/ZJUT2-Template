#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5, LG = 24;

int LOG2[N << 1];

int main() {
    LOG2[0] = -1;
    for (int i = 1; i < N * 2; i++) {
        LOG2[i] = LOG2[i >> 1] + 1;
    }
    return 0;
}

int n, m;
vector<int> adj[N];
int flca[N << 1][LG + 2];
int dep[N];
int dfn[N];
int par[N];
int dfc;

void dfs0(int u, int fa) {
    dep[u] = dep[fa] + 1;
    par[u] = fa;
    flca[dfn[u] = ++dfc][0] = u;
    for (int i = 0; i < int(adj[u].size()); i++) {
        int v = adj[u][i];
        if (v == fa) continue;
        dfs0(v, u);
        flca[++dfc][0] = u;
    }
}

int lca(int u, int v) {
    if (dfn[u] > dfn[v]) swap(u, v);
    int k = LOG2[dfn[v] - dfn[u] + 1];
    int p1 = flca[dfn[u]][k];
    int p2 = flca[dfn[v] - (1 << k) + 1][k];
    return dep[p1] < dep[p2] ? p1 : p2;
}

int dist(int u, int v) {  // 计算u,v之间的距离
    int LCA = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[LCA];
}

bool check(int u, int v, int x) {  // 判断 x 是否在 (u,v) 的简单路径上
    return dist(u, x) + dist(v, x) == dist(u, v);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs0(1, 0);
    for (int j = 1; j <= LG; j++) {
        for (int i = 1; i + (1 << j) <= dfc; i++) {
            if (dep[flca[i][j - 1]] < dep[flca[i + (1 << (j - 1))][j - 1]]) {
                flca[i][j] = flca[i][j - 1];
            } else {
                flca[i][j] = flca[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}