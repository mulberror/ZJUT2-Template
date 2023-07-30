/*
- 给定一个 $n$ 个点，$n$ 条边的环，有 $n$ 种颜色，给每个顶点染色，问有多少种**本质不同**的染色方案，答案对 $10^9+7$ 取模
- 注意本题的本质不同，定义为：**只需要不能通过旋转与别的染色方案相同**。
*/
#include <bits/stdc++.h>
#define Mod 1000000007
#define ll long long 
using namespace std;
ll power(ll n, ll m) {
	ll res = 1;
	for (; m; m>>= 1) {
		if (m & 1) res = res * n % Mod;
		n = n * n % Mod; 
	}
	return res;
}
ll euler_phi(ll n) {
	ll res = 1;
	for (ll i = 2; i * i <= n; i ++) {
		if (n % i == 0) {
			n /= i;
			res = res * (i - 1);
			while (n % i == 0) n /= i, res = res * i;
		}
	}
	if (n > 1) res = res * (n - 1);
	return res % Mod;
}
ll polya(ll m, ll n) {
	ll res = 0;
	for (ll i = 1; i * i <= n; i ++) {
		if (n % i) continue;
		res = (res + euler_phi(i) * power(m, n / i - 1)) % Mod;
		if (i * i != n) res = (res + euler_phi(n / i) * power(m, i - 1)) % Mod;
	}
	return res % Mod;
}
int main() {
	int t;
	scanf("%d", &t);
	while (t --) {
		ll x; 
		scanf("%lld", &x);
		printf("%lld\n", polya(x, x));
	}
	return 0;
}
