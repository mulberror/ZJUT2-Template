namespace PollardRho {
using i64 = long long;
using u64 = unsigned long long;

u64 modmul(u64 a, u64 b, u64 M) {
    i64 ret = a * b - M * u64(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (i64)M);
}

u64 modpow(u64 b, u64 e, u64 mod) {
    u64 ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1)
            ans = modmul(ans, b, mod);
    return ans;
}

template <typename T>
T modinv(T a) {
    T b = ((a << 1) + a) * ((a << 1) + a);
    b *= 2 - a * b;
    b *= 2 - a * b;
    b *= 2 - a * b;
    b *= 2 - a * b;
    return b;
}

u64 montgomery(u64 a, u64 M) {
    u64 ninv = -modinv(M) & 0x7fffffff;
    const u64 b = (a + ((a * ninv) & 0x7fffffff) * M) >> 31;
    return (b >= M) ? (b - M) : b;
}

/*Montgomery Multiplt Template*/

bool isPrime(u64 n) {
    if (n < 2 || n % 6 % 4 != 1)
        return (n | 1) == 3;
    std::vector<u64> A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    u64 s = __builtin_ctzll(n - 1), d = n >> s;
    for (u64 a : A) {  // ^ count trailing zeroes
        u64 p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}
u64 pollard(u64 n) {
    auto f = [n](u64 x, u64 k) { return modmul(x, x, n) + k; };
    u64 x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || std::__gcd(prd, n) == 1) {
        if (x == y)
            x = ++i, y = f(x, i);
        if ((q = modmul(prd, std::max(x, y) - std::min(x, y), n)))
            prd = q;
        x = f(x, i), y = f(f(y, i), i);
    }
    return std::__gcd(prd, n);
}
u64 factor(u64 n) {
    if (n == 1)
        return 1;
    if (isPrime(n))
        return n;
    u64 x = pollard(n);
    return max(factor(x), factor(n / x));
}
}  // namespace Factor
