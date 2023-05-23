#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 500005
using namespace std;
int To[N << 1], x, y, dep[N], Head[N], tot, Next[N << 1], f[N][21], root, n, m;
void add(int x, int y) {
    tot++;
    Next[tot] = Head[x];
    To[tot] = y;
    Head[x] = tot;
}
void dfs(int x, int fa) {
    for (int i = 1; i <= 20; i++)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = Head[x]; i; i = Next[i]) {
        int y = To[i];
        if (y != fa) {
            f[y][0] = x;
            dep[y] = dep[x] + 1;
            dfs(y, x);
        }
    }
}
int LCA(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    return f[x][0];
}
int main() {
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dep[root] = 1;
    dfs(root, 0);
    while (m--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", LCA(x, y));
    }
}