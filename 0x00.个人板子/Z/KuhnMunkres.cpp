#include <bits/stdc++.h>

using i64 = long long;

namespace KM {

#define inf 0x3f3f3f3f3f3f3f3f

constexpr int N = 805;

int n, m;
int matchx[N], matchy[N];
int pre[N];
bool visx[N], visy[N];
i64 slack[N];
i64 lx[N], ly[N];
std::queue<int> q; 
i64 g[N][N];

bool check(int u) {
  visy[u] = 1; 
  if (matchy[u] != -1) {
    q.push(matchy[u]); 
    visx[matchy[u]] = 1; 
    return 0; 
  }
  while (u != -1) {
    matchy[u] = pre[u]; 
    std::swap(u, matchx[pre[u]]);
  }
  return 1; 
}

void add(int u, int v, i64 w) {
  g[u][v] = std::max(0ll, w); 
}

void bfs(int i) {
  while (!q.empty()) {
    q.pop();
  }
  q.push(i);
  visx[i] = true;
  while (true) {
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v = 1; v <= n; v++) {
        if (!visy[v]) {
          i64 delta = lx[u] + ly[v] - g[u][v];
          if (slack[v] >= delta) {
            pre[v] = u;
            if (delta) {
              slack[v] = delta;
            } else if (check(v)) {  // delta=0 代表有机会加入相等子图 找增广路
                                    // 找到就return 重建交错树
              return;
            }
          }
        }
      }
    }
    // 没有增广路 修改顶标
    i64 a = inf;
    for (int j = 1; j <= n; j++) {
      if (!visy[j]) {
        a = std::min(a, slack[j]);
      }
    }
    for (int j = 1; j <= n; j++) {
      if (visx[j]) {  // S
        lx[j] -= a;
      }
      if (visy[j]) {  // T
        ly[j] += a;
      } else {  // T'
        slack[j] -= a;
      }
    }
    for (int j = 1; j <= n; j++) {
      if (!visy[j] && slack[j] == 0 && check(j)) {
        return;
      }
    }
  }
}

i64 res;

void solve() {
  n = std::max(n, m); 
  for (int i = 1; i <= n; i++) {
    matchx[i] = matchy[i] = -1; 
    lx[i] = -inf;
    ly[i] = slack[i] = 0; 
    pre[i] = 0; 
    visx[i] = visy[i] = 0; 
  }
  res = 0; 
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      lx[i] = std::max(lx[i], g[i][j]); 
    }
  }
  for (int i = 1; i <= n; i++) {
    std::fill(slack + 1, slack + 1 + n, inf);
    std::fill(visx + 1, visx + 1 + n, false);
    std::fill(visy + 1, visy + 1 + n, false);  
    bfs(i);   
  }
  for (int i = 1; i <= n; i++) {
    if (g[i][matchx[i]] > 0) {
      res += g[i][matchx[i]];
    }  
  }
}
}

using KM::add;
using KM::solve;
using KM::res;

template<typename T> 
void read(T& x) {
    x = 0; char ch = 0; int f = 1; 
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1; 
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15); 
    x *= f; 
}

int n, m;

int main() {
    read(n), read(m);
    KM::n = n, KM::m = m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        i64 w; 
        read(u), read(v), read(w); 
        add(u, v, w); 
    }    
    return 0; 
}