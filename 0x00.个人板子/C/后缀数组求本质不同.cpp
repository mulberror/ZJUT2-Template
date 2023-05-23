// 后缀数组求本质不同字串数
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 1000005
using namespace std;
int n, m;
char s[N];
int x[N], c[N], sa[N], y[N], hei[N], Rank[N], h[N];
void get_sa() {
    for (int i = 1; i <= n; i++) sa[i] = y[i] = x[i] = 0;
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) {
        x[i] = s[i];
        c[x[i]]++;
    }
    for (int i = 2; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) {
        sa[c[x[i]]] = i;
        c[x[i]]--;
    }
    for (int k = 1; k <= n; k <<= 1) {
        int tot = 0;
        for (int i = n - k + 1; i <= n; i++) y[++tot] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > k)
                y[++tot] = sa[i] - k;
        for (int i = 1; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 2; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) {
            sa[c[x[y[i]]]] = y[i];
            c[x[y[i]]]--;
            y[i] = 0;
        }
        for (int i = 1; i <= n; i++) y[i] = x[i];
        x[sa[1]] = 1;
        tot = 1;
        for (int i = 2; i <= n; i++)
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = tot;
            else
                x[sa[i]] = ++tot;
        if (tot == n)
            break;
        m = tot;
    }
}
void get_height() {
    for (int i = 1; i <= n; i++) hei[i] = Rank[i] = 0;
    int k = 0;
    for (int i = 1; i <= n; i++) Rank[sa[i]] = i;
    for (int i = 1; i <= n; i++) {
        if (k)
            k--;
        int j = sa[Rank[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        hei[Rank[i]] = k;
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        m = 122;
        get_sa();
        get_height();
        long long ans = 0;
        for (int i = 1; i <= n; i++) ans += n - sa[i] + 1 - hei[i];
        printf("%lld\n", ans);
    }
}