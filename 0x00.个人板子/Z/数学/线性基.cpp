#include <bits/stdc++.h>
using namespace std;
const int BIT = 63;
const int N = 52;
typedef long long ll;
ll a[N], p[BIT + 2];
int n; 
void ins(ll x) {
	for (int i = BIT; ~i; i --) {
		if ((x >> i) == 0) continue; 
		if (!p[i]) { p[i] = x; break; }
		x ^= p[i];
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= n; i ++) ins(a[i]);
	ll ans = 0;
	for (int i = BIT; ~i; i --) 
		if ((ans ^ p[i]) > ans) ans ^= p[i];
	cout << ans << endl;
	return 0;
}
