#include <bits/stdc++.h>

#define FI first
#define SE second

using namespace std;

template <class T> void chkmax(T& x, T y) { x = max(x, y); }
template <class T> void chkmin(T& x, T y) { x = min(x, y); }

template <class T> void re(T& x) {
    x = 0;
    char ch = 0;
    int f = 1;
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    x *= f;
}

const int N = 1e5 + 5;
const int MG = 17;

int n, m;

int fx[19][N];
int a[N], lg2[N];

void initST() {
    lg2[0] = -1;
    for (int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; i++) fx[0][i] = a[i];
    for (int i = 1; i <= MG; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            fx[i][j] = max(fx[i - 1][j], fx[i - 1][j + (1 << (i - 1))]);
}

int queryMax(int l, int r) {
    int k = lg2[r - l + 1];
    return max(fx[k][l], fx[k][r - (1 << k) + 1]);
}

int main() {
    re(n), re(m);
    for (int i = 1; i <= n; i++) re(a[i]);
    initST();
    while (m--) {
        int l, r;
        re(l), re(r);
        printf("%d\n", queryMax(l, r));
    }
    return 0;
}