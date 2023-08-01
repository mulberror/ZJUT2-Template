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
