#include <bits/stdc++.h>

using i64 = long long;

namespace generator {
constexpr int mod = 1000000007;
int seed;
int rnd() {
    int ret = seed;
    seed = (i64(seed) * 7 + 13) % mod;
    return ret;
}
}

const int N = 1e5 + 5;

int n, m, vmax;
int a[N];

struct Node {
    int l, r;
    mutable i64 v;
    Node(int l, int r, i64 v) : l(l), r(r), v(v) {}
    bool operator<(const Node &rhs) const {
        return l < rhs.l;
    }
};

std::set<Node> s;

std::set<Node>::iterator split(int pos) {
    auto i = s.lower_bound(Node(pos, 0, 0));
    if (i == s.end() || i->l == pos) {
        return i;
    }
    i--;
    int l = i->l, r = i->r;
    i64 v = i->v;
    s.erase(i);
    s.insert(Node(l, pos - 1, v));
    return s.insert(Node(pos, r, v)).first; // c++ stl insert 传出一个 std::pair<iterator, bool> 
}

void modify(int l, int r, int v) {
    auto ir = split(r + 1), il = split(l); // ir 分裂出来的是 [r + 1, xxx] 区间
    for (auto i = il; i != ir; i++) {
        i->v += v;
    }
}

void assign(int l, int r, int v) {
    auto ir = split(r + 1), il = split(l); 
    s.erase(il, ir);
    s.insert(Node(l, r, v));
}

i64 kth(int l, int r, int k) {
    auto ir = split(r + 1), il = split(l); 
    std::vector<std::pair<i64, int>> v;

    for (auto i = il; i != ir; i++) {
        v.push_back({i->v, i->r - i->l + 1});
    }
    std::sort(v.begin(), v.end());
    for (auto [x, c] : v) {
        k -= c;
        if (k <= 0) {
            return x;
        }
    }
    return -1;
}

int power(i64 x, i64 y, int p) {
    int res = 1;
    for (; y; y >>= 1, x = i64(x) * x % p) {
        if (y & 1) {
            res = i64(res) * x % p;
        }
    }
    return res;
}

int query(int l, int r, int x, int P) {
    auto ir = split(r + 1), il = split(l);
    int ans = 0;
    for (auto i = il; i != ir; i++) {
        ans += i64(i->r - i->l + 1) * power(i->v, x, P) % P;
        if (ans >= P) {
            ans -= P;
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);

    std::cin >> n >> m >> generator::seed >> vmax;
    for (int i = 1; i <= n; i++) {
        a[i] = generator::rnd() % vmax + 1;
        s.insert(Node(i, i, a[i]));
    }

    while (m--) {
        int opt = generator::rnd() % 4 + 1;
        int l = generator::rnd() % n + 1;
        int r = generator::rnd() % n + 1;
        int x, y;
        if (l > r) {
            std::swap(l, r);
        }

        if (opt == 3) {
            x = (generator::rnd() % (r - l + 1)) + 1;
        } else {
            x = (generator::rnd() % vmax) + 1;
        }
        if (opt == 4) {
            y = (generator::rnd() % vmax) + 1;
        }

        if (opt == 1) {
            modify(l, r, x);
        } else if (opt == 2) {
            assign(l, r, x);
        } else if (opt == 3) {
            std::cout << kth(l, r, x) << "\n";
        } else {
            std::cout << query(l, r, x, y) << "\n";
        }
    }
}
