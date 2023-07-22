#include <bits/stdc++.h>
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    char ch = 0;
    int f = 1;
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
    x *= f;
}
template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T>
void writeln(T x) {
    write(x), putchar('\n');
}

const int N = 1e5 + 5, M = 3000;

namespace fhq {
struct node {
    int sz;
    int val;  // 存储信息
    int rnd;  // 随机权值
    int ch[2];

    int tag, multag;  // 旋转懒标记，乘法懒标记
} tr[N];
int nodeCnt = 0;
int create(int val) {
    ++nodeCnt;
    tr[nodeCnt].ch[0] = tr[nodeCnt].ch[1] = 0;
    tr[nodeCnt].val = val;
    tr[nodeCnt].rnd = rand();
    tr[nodeCnt].sz = 1;
    return nodeCnt;
}
void pushup(int p) { tr[p].sz = tr[tr[p].ch[0]].sz + tr[tr[p].ch[1]].sz + 1; }
void pushdown(int p) {
    if (tr[p].tag) {
        swap(tr[p].ch[0], tr[p].ch[1]);
        tr[tr[p].ch[0]].tag ^= 1;
        tr[tr[p].ch[1]].tag ^= 1;
        tr[p].tag ^= 1;
    }
}
void split(int p, int x, int& l, int& r) {  // l为左树的val<=x, r为右树的val>x
    if (p == 0) {
        l = r = 0;
        return;
    }
    if (tr[p].val <= x) {
        l = p;
        split(tr[l].ch[1], x, tr[l].ch[1], r);
    } else {
        r = p;
        split(tr[r].ch[0], x, l, tr[r].ch[0]);
    }
    pushup(p);
}
int merge(int l, int r) {  // 把两棵树拼在一起，返回树根的编号
    if (!l || !r) return l | r;
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
void insert(int& root, int x) {  // 插入一个 val=x 的节点
    int ltree, rtree;
    split(root, x, ltree, rtree);
    root = merge(merge(ltree, create(x)), rtree);
}
void erase(int& root, int x) {  // 删除 root 树中一个 val=x 的节点
    int ltree, rtree, tmp;      // tmp 存的是 val 全为 x 的节点的树根
    split(root, x - 1, ltree, rtree);
    split(rtree, x, tmp, rtree);
    tmp = merge(tr[tmp].ch[0], tr[tmp].ch[1]);
    root = merge(ltree, merge(tmp, rtree));
}
int getRank(int& root, int x) {
    int ltree, rtree;
    split(root, x - 1, ltree, rtree);
    int ans = tr[ltree].sz + 1;
    root = merge(ltree, rtree);
    return ans;
}
int getNum(int& root, int num) {
    int u = tr[tr[root].ch[0]].sz + 1;
    if (u == num) return tr[root].val;
    if (num < u) return getNum(tr[root].ch[0], num);
    return getNum(tr[root].ch[1], num - u);
}
int getPre(int& root, int x) {  // 找到 x 的前驱(3个log的写法)
    int ltree, rtree;
    split(root, x - 1, ltree, rtree);
    int ans = getNum(ltree, tr[ltree].sz);
    root = merge(ltree, rtree);
    return ans;
}
int getSuc(int& root, int x) {  // 后继(3个log的做法)
    int ltree, rtree;
    split(root, x, ltree, rtree);
    int ans = getNum(rtree, 1);
    root = merge(ltree, rtree);
    return ans;
}

void dfs(int u) {
    if (!u) return;
    dfs(tr[u].ch[0]);
    cout << tr[u].val << " ";
    dfs(tr[u].ch[1]);
}
}  // namespace fhq
using namespace fhq;

int main() {
    srand(time(0));
    int root;
    int n;
    read(n);
    while (n--) {
        int opt, x;
        read(opt), read(x);
        if (opt == 1) {
            insert(root, x);
        } else if (opt == 2) {
            erase(root, x);
        } else if (opt == 3) {
            writeln(getRank(root, x));
        } else if (opt == 4) {
            writeln(getNum(root, x));
        } else if (opt == 5) {
            writeln(getPre(root, x));
        } else {
            writeln(getSuc(root, x));
        }
    }
    return 0;
}