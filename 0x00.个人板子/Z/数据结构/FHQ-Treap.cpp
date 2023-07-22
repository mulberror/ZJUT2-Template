#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T& x) {
    x = 0;
    char ch = 0;
    int f = 1;
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
    x *= f;
}
template <typename T> void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) { write(x), putchar('\n'); }

const int N = 1e5 + 5;

namespace fhq {
struct node {
    int sz;
    int val;  // 关键字
    int rnd;  // 随机权值
    int ch[2];

    int rtag;  // 旋转懒标记，乘法懒标记
} tr[N];
int nodeCnt = 0;
int create(int val) {
    ++nodeCnt;
    tr[nodeCnt].ch[0] = tr[nodeCnt].ch[1] = 0;
    tr[nodeCnt].rtag = 0;
    tr[nodeCnt].val = val;
    tr[nodeCnt].rnd = rand();
    tr[nodeCnt].sz = 1;
    return nodeCnt;
}
void pushup(int p) { tr[p].sz = tr[tr[p].ch[0]].sz + tr[tr[p].ch[1]].sz + 1; }
void pushdown(int p) {
    if (tr[p].rtag) {
        swap(tr[p].ch[0], tr[p].ch[1]);
        tr[tr[p].ch[0]].rtag ^= 1;
        tr[tr[p].ch[1]].rtag ^= 1;
        tr[p].rtag = 0;
    }
}
void split(int p, int x, int& l, int& r) {  // 现在需要找出中序遍历的[l,r]
    if (p == 0) {
        l = r = 0;
        return;
    }
    pushdown(p);
    int u = tr[tr[p].ch[0]].sz + 1;
    if (u <= x) {
        l = p;
        split(tr[l].ch[1], x - u, tr[l].ch[1], r);
    } else {
        r = p;
        split(tr[r].ch[0], x, l, tr[r].ch[0]);
    }
    pushup(p);
}
int merge(int l, int r) {  // 把两棵树拼在一起，返回树根的编号
    if (!l || !r) return l | r;
    pushdown(l), pushdown(r);
    if (tr[l].rnd <= tr[r].rnd) {
        tr[l].ch[1] = merge(tr[l].ch[1], r);
        pushup(l);
        return l;
    } else {
        tr[r].ch[0] = merge(l, tr[r].ch[0]);
        pushup(r);
        return r;
    }
}
void rev(int& root, int l, int r) {
    int sec1, sec2, sec3;  // sec1:[1,l-1], sec2:[l,r], sec3:[r+1,n]
    split(root, l - 1, sec1, sec2);
    split(sec2, r - l + 1, sec2, sec3);
    tr[sec2].rtag ^= 1;
    root = merge(sec1, merge(sec2, sec3));
}
void build(int& root, int l, int r) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    root = create(mid);
    build(tr[root].ch[0], l, mid - 1);
    build(tr[root].ch[1], mid + 1, r);
    pushup(root);
}
void dfs(int p) {
    if (!p) return;
    pushdown(p);
    dfs(tr[p].ch[0]);
    write(tr[p].val), putchar(' ');
    dfs(tr[p].ch[1]);
}
}  // namespace fhq

using namespace fhq;

int n, m;
int root;

int main() {
    read(n), read(m);
    build(root, 1, n);
    while (m--) {
        int l, r;
        read(l), read(r);
        rev(root, l, r);
    }
    dfs(root);
    return 0;
}
