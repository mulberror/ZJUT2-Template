#include <bits/stdc++.h>
using namespace std;
const long long MOD[2] = {998244353, 1000000007};
const long long Seed = 131;
long long b[N][2];
char s[N];
struct Hash {
    long long a[N][2];
    pair<long long, long long> get_hash(int l, int r) {
        pair<long long, long long> pr;
        pr.first = (a[r][0] - a[l - 1][0] * b[r - l + 1][0] % MOD[0] + MOD[0]) % MOD[0];
        pr.second = (a[r][1] - a[l - 1][1] * b[r - l + 1][1] % MOD[1] + MOD[1]) % MOD[1];
        return pr;
    }
} a, c;
int check(int l1, int r1, int l2, int r2) {
    return (a.get_hash(l1, r1) == c.get_hash(l2, r2));
}
int main() {
    b[0][0] = 1;
    b[0][1] = 1;
    for (int j = 0; j < 2; j++)
        for (int i = 1; i <= n; i++) b[i][j] = b[i - 1][j] * Seed % MOD[j];
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i <= n; i++) a.a[i][j] = (a.a[i - 1][j] * Seed + s[i]) % MOD[j];
    }
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i <= n; i++) c.a[i][j] = (c.a[i - 1][j] * Seed + s[n - i + 1]) % MOD[j];
    }
}
