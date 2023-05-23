// 矩阵乘法快速幂
#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
struct matrix {
    long long x[5][5];
} ans, base;
matrix mul(matrix a, matrix b, int n) {
    matrix c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) c.x[i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j] % MOD + MOD) % MOD;
        }
    return c;
}
matrix ksm(long long k, matrix s, matrix x) {
    while (k) {
        if (k & 1)
            s = mul(s, x, 3);
        x = mul(x, x, 3);
        k >>= 1;
    }
    return s;
}
int main() {
    long long x, y, n;
    scanf("%lld%lld%lld", &x, &y, &n);
    ans.x[1][1] = ((y - x) % MOD + MOD) % MOD;
    ans.x[1][2] = (y + MOD) % MOD;
    ans.x[1][3] = (x + MOD) % MOD;
    base.x[1][1] = 1;
    base.x[1][2] = 1;
    base.x[1][3] = 0;
    base.x[2][1] = -1;
    base.x[2][2] = 0;
    base.x[2][3] = 1;
    if (n <= 3)
        printf("%lld\n", ans.x[1][3 - n + 1]);
    else {
        ans = ksm(n - 3, ans, base);
        printf("%lld\n", ans.x[1][1]);
    }
}