// 快速幂
int ksm(int x, int k) {
    int s = 1;
    while (k) {
        if (k & 1)
            s = (long long)s * x % MOD;
        x = (long long)x * x % MOD;
        k >>= 1;
    }
    return s;
}