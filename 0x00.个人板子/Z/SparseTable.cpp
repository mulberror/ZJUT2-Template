#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>
class sparseTable {
   private:
    vector<vector<T>> st;

    static T func(const T &lhs, const T &rhs) { return std::max(lhs, rhs); }

    std::function<T(const T &, const T &)> judge;

   public:
    sparseTable(const std::vector<T> &v, std::function<T(const T &, const T &)> _func = func) {
        judge = _func;
        int n = v.size(), k = ceil(log2(n)) + 1;
        st.assign(n, std::vector<T>(k, 0));
        for (int i = 0; i < n; i++) {
            st[i][0] = v[i];
        }
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[i][j] = judge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = log2(r - l + 1);
        return judge(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

template <typename T>
void read(T &x) {
    x = 0;
    char ch = 0;
    int f = 1;
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
    x *= f;
}

int main() {
    int n, m;
    read(n), read(m);
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }
    SparseTable<int> rmq(a, [](int lhs, int rhs) { return std::max(lhs, rhs); });
    while (m--) {
        int l, r;
        read(l), read(r);
        l--, r--;
        printf("%d\n", rmq.query(l, r));
    }
    return 0;
}