#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5, bit = 24;

int n;
string s;
int fa[N][bit + 1];
int dep[N];

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = bit; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    } else {
        for (int i = bit; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
}

int nxt[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s;
    n = s.length();
    s = "$" + s;

    nxt[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) {
            j = nxt[j];
        }
        if (s[i] == s[j + 1]) {
            j++;
        }
        nxt[i] = j;
    }

    for (int i = 1; i <= n; i++) {
        fa[i][0] = nxt[i];
        dep[i] = dep[nxt[i]] + 1;

        for (int j = 1; j <= bit; j++) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }

    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) - 1 << "\n";
    }
    return 0;
}