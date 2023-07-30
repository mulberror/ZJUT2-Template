#include <bits/stdc++.h>
#define inf 2147483647
#define lc (nod << 1)
#define rc (nod << 1 | 1)
#define N 500004
using namespace std;
template <typename T>
inline void read(T &x) {
	x = 0; T fl = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		if (ch == '-') fl = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	x *= fl;
}
struct node {
	int val, cnt, ch[2], sz, rd;
	void init(int x) {val = x; cnt = sz = 1; ch[1] = ch[0] = 0; rd = rand() % 100;}
}tr[N * 20];
int tot;
struct Treap {
	#define ls tr[nod].ch[0]
	#define rs tr[nod].ch[1]
	void pushup(int nod) {
		tr[nod].sz = tr[ls].sz + tr[rs].sz + tr[nod].cnt;
	}
	void rotate(int &nod, int d) {
		int k = tr[nod].ch[d];
		tr[nod].ch[d] = tr[k].ch[d ^ 1];
		tr[k].ch[d ^ 1] = nod;
		pushup(nod); 
		pushup(k);
		nod = k;
	}
	void ins(int &nod, int val) {
		if (!nod) {
			tr[nod = ++ tot].init(val);
			return;
		}
		tr[nod].sz ++;
		if (tr[nod].val == val) {
			tr[nod].cnt ++;
			return;
		}
		int d = val > tr[nod].val;
		ins(tr[nod].ch[d], val);
		if (tr[nod].rd > tr[tr[nod].ch[d]].rd) rotate(nod, d);
	}
	void del(int &nod, int val) {
		if (!nod) return;
		if (tr[nod].val == val) {
			if (tr[nod].cnt > 1) {
				tr[nod].cnt --;
				tr[nod].sz --;
				return;
			}
			int d = tr[ls].rd > tr[rs].rd;
			if (ls == 0 || rs == 0) nod = ls + rs;
			else rotate(nod, d), del(nod, val);
		}
		else tr[nod].sz --, del(tr[nod].ch[tr[nod].val < val], val);
	}
	int rk(int nod, int val) {
		if (!nod) return 0;
		if (tr[nod].val == val) return tr[ls].sz;
		if (tr[nod].val > val) return rk(ls, val);
		else return tr[ls].sz + tr[nod].cnt + rk(rs, val);
	}
	int kth(int nod, int k)  {
		while (233) {
			if (k <= tr[ls].sz) nod = ls;
			else if (k > tr[ls].sz + tr[nod].cnt) k -= tr[ls].sz + tr[nod].cnt, nod = rs;
			else return tr[nod].val;
		}
	}
	int pre(int nod, int val) {
		if (!nod) return -inf;
		if (tr[nod].val >= val) return pre(ls, val);
		else return max(tr[nod].val, pre(rs, val));
	}
	int suc(int nod, int val) {
		if (!nod) return inf;
		if (tr[nod].val <= val) return suc(rs, val);
		else return min(tr[nod].val, suc(ls, val));
	}
}tp[N << 2];
int n, m;
int a[N], rt[N];
void build(int nod, int l, int r) {
    for (int i = l; i <= r; i ++) tp[nod].ins(rt[nod], a[i]);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
int query_rk(int nod, int l, int r, int ql, int qr, int k) {
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return tp[nod].rk(rt[nod], k);
    int mid = (l + r) >> 1, res = 0;
    res += query_rk(lc, l, mid, ql, qr, k);
    res += query_rk(rc, mid + 1, r, ql, qr, k);
    return res;
}
void update_point(int nod, int l, int r, int k, int val) {
    if (k < l || k > r) return;
    tp[nod].del(rt[nod], a[k]);
    tp[nod].ins(rt[nod], val);
    if (l == r) return;
    int mid = (l + r) >> 1;
    update_point(lc, l, mid, k, val);
    update_point(rc, mid + 1, r, k, val);
}
int query_pre(int nod, int l, int r, int ql, int qr, int k) {
    if (l > qr || r < ql) return -inf;
    if (ql <= l && r <= qr) return tp[nod].pre(rt[nod], k);
    int mid = (l + r) >> 1, res = query_pre(lc, l, mid, ql, qr, k);
    res = max(res, query_pre(rc, mid + 1, r, ql, qr, k));
    return res;
}
int query_suc(int nod, int l, int r, int ql, int qr, int k) {
    if (l > qr || r < ql) return inf;
    if (ql <= l && r <= qr) return tp[nod].suc(rt[nod], k);
    int mid = (l + r) >> 1, res = query_suc(lc, l, mid, ql, qr, k);
    res = min(res, query_suc(rc, mid + 1, r, ql, qr, k));
    return res;
}
int query_fd(int ql, int qr, int k) {
    int l = 0, r = 1e8, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (query_rk(1, 1, n, ql, qr, mid) + 1 <= k) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}
int main() {
	srand(time(NULL));
    tot = 0;
    read(n); read(m);
    for (int i = 1; i <= n; i ++) read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; i ++) {
        int opt, x, y, z;
        read(opt);
        if (opt == 1) {
            read(x); read(y); read(z);
            printf("%d\n", query_rk(1, 1, n, x, y, z) + 1); 
        }
        if (opt == 2) {
            read(x); read(y); read(z);
            printf("%d\n", query_fd(x, y, z));
        }
        if (opt == 3) {
            read(x); read(y);
            update_point(1, 1, n, x, y);
            a[x] = y;
        }
        if (opt == 4) {
            read(x); read(y); read(z);
            int res = query_pre(1, 1, n, x, y, z);
            printf("%d\n", res);
        }
        if (opt == 5) {
            read(x); read(y); read(z);
            int res = query_suc(1, 1, n, x, y, z);
            printf("%d\n", res);
        }
    }
    return 0;
}
