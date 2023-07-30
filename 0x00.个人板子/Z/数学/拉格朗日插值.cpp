#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, w = 0; char ch = 0;
	while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return w ? -x : x;
}
const ll P = 998244353;
const int N = 2000 + 5;
int n;
ll k;
ll x[N], y[N];
ll qpow(ll x, ll y) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % P;
		y >>= 1; x = x * x % P;
	}
	return res;
}
ll lagrange(ll* x, ll* y, int n, ll k) {
	ll ans = 0;
	for (int i = 0; i <= n; i ++) {
		ll s1 = 1, s2 = 1; 
		for (int j = 0; j <= n; j ++) {
			if (i == j) continue; 
			s1 = s1 * (k - x[j]) % P; s2 = s2 * (x[i] - x[j]) % P;
		}
		ans = (ans + y[i] * s1 % P * qpow(s2, P - 2) % P) % P;
	}
	return (ans % P + P) % P;
}
int main() {
	n = read(), k = read(); n --; 
	for (int i = 0; i <= n; i ++) x[i] = read(), y[i] = read();
	cout << lagrange(x, y, n, k) << '\n';
	return 0;
}
