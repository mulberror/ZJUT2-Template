#include <bits/stdc++.h>

using namespace std;

struct LCT {
    static const int N = 1E5 + 7;

    int ch[N][2], fa[N], rev[N], sz[N], mx[N];
    int sk[N];

    bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    void reverse(int x) { rev[x] ^= 1, swap(ch[x][0], ch[x][1]); }

    void update(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1; }

    void pushDown(int x) {
        if (!rev[x]) return;
        if (ch[x][0]) reverse(ch[x][0]);
        if (ch[x][1]) reverse(ch[x][1]);
        rev[x] = 0;
    }

    void rotate(int x) {
        int f = fa[x], gf = fa[f];
        int t1 = (x != ch[f][0]), t2 = (f != ch[gf][0]), tmp = ch[x][1 ^ t1];
        if (!isroot(f)) ch[gf][0 ^ t2] = x;
        fa[tmp] = f, fa[x] = gf, ch[x][1 ^ t1] = f, fa[f] = x, ch[f][0 ^ t1] = tmp;
        update(f);
    }

    void splay(int x) {
        int top = 0;
        sk[++top] = x;
        for (int i = x; !isroot(i); i = fa[i]) sk[++top] = fa[i];
        while (top) pushDown(sk[top--]);
        for (int f = fa[x], gf = fa[f]; !isroot(x); rotate(x), f = fa[x], gf = fa[f])
            if (!isroot(f)) rotate((x == ch[f][0]) ^ (f == ch[gf][0]) ? x : f);
        update(x);
    }

    void access(int x) {
        for (int p = 0; x; p = x, x = fa[x]) {
            splay(x);
            ch[x][1] = p;
            update(x);
        }
    }

    void makeRoot(int x) { access(x), splay(x), reverse(x); }

    int findRoot(int x) {
        access(x), splay(x);
        while (ch[x][0]) {
            pushDown(x);
            x = ch[x][0];
        }
        return x;
    }

    void link(int x, int y) {
        makeRoot(x);
        if (findRoot(y) != x) {
            fa[x] = y;
        }
    }

    void cut(int x, int y) {
        makeRoot(x), access(y), splay(y);
        if (ch[y][0] == x) ch[y][0] = fa[x] = 0;
        update(y);
    }
} lct;