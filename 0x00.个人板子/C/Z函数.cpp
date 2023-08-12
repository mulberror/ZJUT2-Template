#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e7 + 5;
int n, m;
int nxt[maxn], ext[maxn], eb[maxn], z[maxn];
char s[maxn], t[maxn];
void e_kmp(char *s, char *t, int *has, int *e_has) {
    int sp, p, mx, tn;
    for (sp = p = mx = 0; s[p] > 0; p++) {
        if (mx == p || p + e_has[p - sp] >= mx) {
            for (tn = mx - p; s[mx] == t[tn]; tn++) mx++;
            has[sp = p] = mx - p;
            if (mx == p)
                sp = ++mx;
        } else
            has[p] = e_has[p - sp];
    }
}
int main() {
    scanf("%s", s);
    scanf("%s", t);
    int n = strlen(t);
    eb[0] = strlen(t);            // 初始化
    t[n] = -1;                    // 初始化
    e_kmp(t + 1, t, eb + 1, eb);  // t先跟自己求一遍
    e_kmp(s, t, z, eb);           // t与s求一遍
    long long ans = 0;
    for (int i = 0; i < n; i++) ans ^= 1ll * (i + 1) * (eb[i] + 1);
    cout << ans << endl;
    ans = 0;
    for (int i = 0; i < strlen(s); i++) ans ^= 1ll * (i + 1) * (z[i] + 1);
    cout << ans << endl;
}
