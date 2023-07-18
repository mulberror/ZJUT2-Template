bool Hungry(int u) {
  for (int i = 0; i < Edge[u].size(); i++) {
    int v = Edge[u][i];
    if (!Mark[v]) {
      Mark[v] = 1;
      if (Fa[v] == -1 || Hungry(Fa[v])) {
        Fa[v] = u;
        return true;
      }
    }
  }
  return false;
}
int main() {
  memset(Fa, -1, sizeof(Fa));
  for (int i = 1; i <= n; i++) {
    memset(Mark, 0, sizeof(Mark));
    if (Hungry(i)) Ans++;
  }
}
// 双向建边 最大匹配=Ans/2
// 双向建边 如果染色 if(Col[i]&&Hungry(i)) 最大匹配=Ans
// 最小点覆盖 = 最大匹配
// 最小独立集 = n - 最大匹配
// 最小不可相交路径覆盖 = n - 最大匹配
// 最小可相交路径覆盖 =
//		用floyd求出原图的传递，若a到b有路径，那么a->b。然后就转化成最小不相交路径覆盖问题
