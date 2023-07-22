#include <bits/stdc++.h>

using i64 = long long;

namespace MinCostMaxFlow {

#define inf 0x3f3f3f3f3f3f3f3f

constexpr int N = 805, M = 320005;

struct Edge {
  int v;
  i64 w, c; 
  int nxt;

  Edge() {}
  Edge(int a, i64 ws, i64 cs, int b) : v(a), w(ws), c(cs), nxt(b) {}
} edge[M];

int edgeCnt = 1; 
int head[N], arc[N];
bool vis[N];

int S, T;

i64 dis[N];
i64 ans, ret; 

void addEdge(int u, int v, i64 w, i64 c) {
  edge[++edgeCnt] = Edge(v, w, c, head[u]);
  head[u] = edgeCnt; 
}

void add(int u, int v, i64 w, i64 c) {
  addEdge(u, v, w, c);
  addEdge(v, u, 0, -c);
}

bool spfa() {
  for (int i = S; i <= T; i++) {
    dis[i] = inf; 
    arc[i] = head[i]; 
  }
  std::queue<int> q;
  dis[S] = 0; 
  vis[S] = 1; 
  q.push(S); 
  while (!q.empty()) {
    int u = q.front();
    q.pop(); 
    vis[u] = 0; 
    for (int e = head[u]; e; e = edge[e].nxt) {
      int v = edge[e].v;
      if (edge[e].w && dis[v] > dis[u] + edge[e].c) {
        dis[v] = dis[u] + edge[e].c;
        if (!vis[v]) {
          q.push(v); 
          vis[v] = 1; 
        }
      }
    }
  }
  return dis[T] != inf;
}

i64 dfs(int u, i64 flow) {
  if (u == T) {
    return flow;
  }
  vis[u] = 1; 
  i64 res = 0; 
  for (int &e = arc[u]; e && res < flow; e = edge[e].nxt) {
    int v = edge[e].v;
    if (!vis[v] && edge[e].w && dis[v] == dis[u] + edge[e].c) {
      i64 x = dfs(v, std::min(edge[e].w, flow - res));
      if (x) {
        edge[e].w -= x; 
        edge[e ^ 1].w += x; 
        res += x; 
        ret += x * edge[e].c;
      }
    }
  }
  vis[u] = 0; 
  return res; 
}

void solve() { // 注意要事先设定好源点和汇点，源点为第一个点，汇点为最后一个点
  memset(vis, 0, sizeof vis); 
  ans = 0; 
  ret = 0; 
  while (spfa()) {
    i64 x; 
    while ((x = dfs(S, inf))) {
      ans += x; 
    }
  }
}
}

using MinCostMaxFlow::S;
using MinCostMaxFlow::T;
using MinCostMaxFlow::solve;
using MinCostMaxFlow::add; 
using MinCostMaxFlow::ans;
using MinCostMaxFlow::ret;

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
    for (int i = 1; i <= m; i++) {
        int u, v; 
        i64 w, c; 
        read(u), read(v), read(w), read(c); 
        add(u, v, w, c); 
    }
    S = 1, T = n;
    solve(); 
    std::cout << ans << " " << ret << "\n";
    return 0; 
}