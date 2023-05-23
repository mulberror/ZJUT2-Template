#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e7, MAXM = 7e5;

int primeCnt;
bool notPrime[MAXN + 1];
int prime[MAXM + 1];
int primeFrom[MAXN + 1];

void Sieve() {
  for (int i = 2; i <= MAXN; i++) {
    if (!notPrime[i])
      prime[++primeCnt] = i, primeFrom[i] = i;

    for (int j = 1; j <= primeCnt && prime[j] * i <= MAXN; j++) {
      primeFrom[prime[j] * i] = prime[j];
      notPrime[prime[j] * i] = 1;
      if (i % prime[j] == 0)
        break;
    }
  }
}

vector<pair<int, int>> Divide(int x) {
  vector<pair<int, int>> ret;

  while (x > 1) {
    int t = primeFrom[x], cnt = 0;
    for (; t == primeFrom[x]; x /= primeFrom[x])
      cnt++;
    ret.push_back({t, cnt});
  }
  return ret;
}

int main() {
  Sieve();
  return 0;
}