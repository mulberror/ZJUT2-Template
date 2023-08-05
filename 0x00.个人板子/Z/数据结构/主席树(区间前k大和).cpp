#define ls (tr[p].ch[0])
#define rs (tr[p].ch[1])
  
struct Info {
    i64 sum;
    int cnt;
    int ch[2];
} tr[N * 80];
  
int nodeCnt;
int root[N];
vector<int> disc;
  
void pushup(int p) {
    tr[p].cnt = 0;
    tr[p].sum = 0;
    if (ls) {
        tr[p].cnt += tr[ls].cnt;
        tr[p].sum += tr[ls].sum;
    }
    if (rs) {
        tr[p].cnt += tr[rs].cnt;
        tr[p].sum += tr[rs].sum;
    }
}
  
void modify(int& p, int pre, int l, int r, int pos, int v) {
    p = ++nodeCnt;
    tr[p] = tr[pre];
    if (l == r) {
        tr[p].cnt += v;
        tr[p].sum += v * disc[l];
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        modify(tr[p].ch[0], tr[pre].ch[0], l, mid, pos, v);
    } else {
        modify(tr[p].ch[1], tr[pre].ch[1], mid + 1, r, pos, v);
    }
    pushup(p);
}
  
i64 calc(int A, int B, int l, int r, int k) { // [A, B]
    if (l == r) {
        return k * disc[l];
    }
    int mid = (l + r) / 2;
    if (tr[tr[B].ch[1]].cnt - tr[tr[A].ch[1]].cnt >= k) {
        return calc(tr[A].ch[1], tr[B].ch[1], mid + 1, r, k);
    } else {
        return tr[tr[B].ch[1]].sum - tr[tr[A].ch[1]].sum + calc(tr[A].ch[0], tr[B].ch[0], l, mid, k - (tr[tr[B].ch[1]].cnt - tr[tr[A].ch[1]].cnt));
    }
}
 
int m;

i64 getSectionKth(int l, int r, int k) { // [l,r] 区间前k大的和
    return calc(root[l - 1], root[r], 0, m - 1, x);
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(w[i]), disc.push_back(w[i]);
    sort(disc.begin(), disc.end());
    disc.erase(unique(disc.begin(), disc.end()), disc.end());
    m = disc.size();
    for (int i = 1; i <= n; i++) {
        w[i] = lower_bound(disc.begin(), disc.end(), w[i]) - disc.begin();
        modify(root[i], root[i - 1], 0, m - 1, w[i], 1);
    }
}

///================================================

struct ZXtree {
    #define ls(p) (tr[(p)].ch[0])
    #define rs(p) (tr[(p)].ch[1])
    struct Node {
        int sum, cnt;
        int ch[2];
    } tr[N * 32 * 32];
    int cnt;
    ZXtree() : cnt(0) {}
 
    void pushup(int p) {
        tr[p].sum = tr[p].cnt = 0;
        if (ls(p)) tr[p].sum += tr[ls(p)].sum, tr[p].cnt += tr[ls(p)].cnt;
        if (rs(p)) tr[p].sum += tr[rs(p)].sum, tr[p].cnt += tr[rs(p)].cnt;
    }
 
    void modify(int& p, int fr, int l, int r, int pos, int v) {
        p = ++cnt, tr[p] = tr[fr];
        if (l == r) {
            tr[p].sum += v;
            tr[p].cnt++;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) modify(ls(p), ls(fr), l, mid, pos, v);
        else modify(rs(p), rs(fr), mid + 1, r, pos, v);
        pushup(p);
    }
 
    int find(int p1, int p2, int l, int r, int k) { // sum<=k的和
        if (l == r) {
            if (tr[p2].sum - tr[p1].sum <= k) return tr[p2].sum - tr[p1].sum;
            return 0;
        }
        int mid = (l + r) >> 1, sum = tr[rs(p2)].sum - tr[rs(p1)].sum;
        if (sum <= k) {
            return find(ls(p1), ls(p2), l, mid, k - sum) + tr[rs(p2)].sum - tr[rs(p1)].sum;
        }
        return find(rs(p1), rs(p2), mid + 1, r, k);
    }
 
    int kth(int p1, int p2, int l, int r, int k) { // 第k大的数
        if (tr[p2].sum - tr[p1].sum < k) return 0;
        if (l == r) return l;
        int mid = (l + r) >> 1, sum = tr[rs(p2)].sum - tr[rs(p1)].sum;
        if (sum >= k) return kth(rs(p1), rs(p2), mid + 1, r, k);
        return kth(ls(p1), ls(p2), l, mid, k - sum);
    }
} tr[2];
