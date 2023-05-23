#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 100005
using namespace std;
int x, y, z, Son[N << 1], tot, Next[N << 1], Head[N << 1], dep[N], f[N], a[N], b[N], Tree[N << 2], top[N], size[N], son[N], cnt, id[N], MOD, lazy[N << 2], ans, n, m, root, A;
void add(int x, int y) {
    tot++;
    Son[tot] = y;
    Next[tot] = Head[x];
    Head[x] = tot;
}
void dfs1(int x, int deep, int fa) {
    dep[x] = deep;
    f[x] = fa;
    size[x] = 1;
    int maxson = 0;
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Son[i];
        if (y == fa)
            continue;
        dfs1(y, deep + 1, x);
        size[x] = size[x] + size[y];
        if (size[y] > maxson)
            son[x] = y, maxson = size[y];
    }
}
void dfs2(int x, int Top) {
    cnt++;
    id[x] = cnt;
    b[cnt] = a[x];
    top[x] = Top;
    if (!son[x])
        return;
    dfs2(son[x], Top);
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Son[i];
        if (y == f[x] || y == son[x])
            continue;
        dfs2(y, y);
    }
}
void Build(int p, int l, int r) {
    if (l == r) {
        Tree[p] = b[l] % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    Build(p << 1, l, mid);
    Build(p << 1 | 1, mid + 1, r);
    Tree[p] = Tree[p << 1] + Tree[p << 1 | 1];
}
void Pushdown(int p, int Len) {
    lazy[p << 1] += lazy[p];
    lazy[p << 1 | 1] += lazy[p];
    Tree[p << 1] = (Tree[p << 1] + lazy[p] * (Len - (Len >> 1))) % MOD;
    Tree[p << 1 | 1] = (Tree[p << 1 | 1] + lazy[p] * (Len >> 1)) % MOD;
    lazy[p] = 0;
}
void Query(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        ans = (ans + Tree[p]) % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    if (lazy[p])
        Pushdown(p, r - l + 1);
    if (x <= mid)
        Query(p << 1, l, mid, x, y);
    if (y > mid)
        Query(p << 1 | 1, mid + 1, r, x, y);
}
void Change(int p, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) {
        lazy[p] = lazy[p] + z;
        Tree[p] = (Tree[p] + z * (r - l + 1)) % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    if (lazy[p])
        Pushdown(p, r - l + 1);
    if (x <= mid)
        Change(p << 1, l, mid, x, y, z);
    if (y > mid)
        Change(p << 1 | 1, mid + 1, r, x, y, z);
    Tree[p] = (Tree[p << 1] + Tree[p << 1 | 1]) % MOD;
}
void Query_Tree(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        Query(1, 1, n, id[top[x]], id[x]);
        x = f[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    Query(1, 1, n, id[x], id[y]);
}
void Change_Tree(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        Change(1, 1, n, id[top[x]], id[x], z);
        x = f[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    Change(1, 1, n, id[x], id[y], z);
}
void Query_Tree_Son(int x) {
    Query(1, 1, n, id[x], id[x] + size[x] - 1);
}
void Change_Tree_Son(int x, int y) {
    Change(1, 1, n, id[x], id[x] + size[x] - 1, y);
}
int main() {
    scanf("%d%d%d%d", &n, &m, &root, &MOD);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs1(root, 1, 0);
    dfs2(root, root);
    Build(1, 1, n);
    while (m--) {
        scanf("%d", &A);
        ans = 0;
        if (A == 1) {
            scanf("%d%d%d", &x, &y, &z);
            Change_Tree(x, y, z);
        }
        if (A == 2) {
            scanf("%d%d", &x, &y);
            Query_Tree(x, y);
            printf("%d\n", ans);
        }
        if (A == 3) {
            scanf("%d%d", &x, &z);
            Change_Tree_Son(x, z);
        }
        if (A == 4) {
            scanf("%d", &x);
            Query_Tree_Son(x);
            printf("%d\n", ans);
        }
    }
}