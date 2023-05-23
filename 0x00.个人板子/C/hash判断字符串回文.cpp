// hash 回文
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define Seed 131
#define MOD 998244353
using namespace std;
char s[100005];
long long a[100005], b[100005], c[100005];
int n;
int check(int l, int r) {
    if ((a[r] - a[l - 1] * b[r - l + 1] % MOD + MOD) % MOD == (c[n - l + 1] - c[n - r] * b[r - l + 1] % MOD + MOD) % MOD)
        return 1;
    else
        return 0;
}
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    b[1] = Seed;
    for (int i = 2; i <= n; i++) b[i] = b[i - 1] * Seed % MOD;
    for (int i = 1; i <= n; i++) a[i] = (a[i - 1] * Seed + s[i]) % MOD;          // 正着哈希
    for (int i = 1; i <= n; i++) c[i] = (c[i - 1] * Seed + s[n - i + 1]) % MOD;  // daozhe
    int T;
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        if (check(l, r))
            printf("YES\n");
        else
            printf("NO\n");
    }
}