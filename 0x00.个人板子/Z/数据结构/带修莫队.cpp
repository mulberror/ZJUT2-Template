#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e5 + 5;

int n, q, bklen;
int a[N];
int dsc[N * 3], dscc;

struct Query {
    int l, r, id, t;
} qr[N];

struct Modi {
    int p, x;
} md[N];

int qrc, mdc;
int ans[N];
int cnt[N * 2]; // 每个颜色出现的次数
int ccnt[N * 2]; // 出现的出现次数的次数

void add(int c) {
    ccnt[cnt[c]]--;
    cnt[c]++;
    ccnt[cnt[c]]++;
}

void sub(int c) {
    ccnt[cnt[c]]--;
    cnt[c]--;
    ccnt[cnt[c]]++;
}

void mdf(int x, int y) { // 第x个询问，第y个修改
    if (md[y].p >= qr[x].l && md[y].p <= qr[x].r) {
        sub(a[md[y].p]);
        add(md[y].x);
    }
    swap(a[md[y].p], md[y].x);
}

int main() {
    cin >> n >> q;
    dscc = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dsc[++dscc] = a[i];
    }
    for (int i = 1; i <= q; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r; 
            cin >> l >> r;
            ++qrc, qr[qrc] = {l, r, qrc, mdc};
        } else {
            int p, x;
            cin >> p >> x;
            dsc[++dscc] = x;
            ++mdc, md[mdc] = {p, x};
        }
    }
    sort(dsc + 1, dsc + 1 + dscc);
    dscc = unique(dsc + 1, dsc + 1 + dscc) - dsc - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(dsc + 1, dsc + 1 + dscc, a[i]) - dsc;
    }
    for (int i = 1; i <= mdc; i++) {
        md[i].x = lower_bound(dsc + 1, dsc + 1 + dscc, md[i].x) - dsc;
    }
    
    bklen = pow(n, 2.0 / 3);
    sort(qr + 1, qr + 1 + qrc, [&](Query a, Query b) {
        return (a.l / bklen != b.l / bklen) ? (a.l < b.l) : (a.r / bklen != b.r / bklen ? a.r < b.r : a.t < b.t);
    });

    int l = 1, r = 0, mt = 0;
    ccnt[0] = N + 1;
    for (int i = 1; i <= qrc; i++) {
        while (l > qr[i].l) add(a[--l]);
        while (r < qr[i].r) add(a[++r]);
        while (l < qr[i].l) sub(a[l++]);
        
        while (r > qr[i].r) sub(a[r--]);
        while (mt < qr[i].t) mdf(i, ++mt);
        while (mt > qr[i].t) mdf(i, mt--);

        for (int pt = 0; ccnt[pt] > 0; pt++) {
            ans[qr[i].id] = pt + 1;
        }
    }
    
    for (int i = 1; i <= qrc; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
