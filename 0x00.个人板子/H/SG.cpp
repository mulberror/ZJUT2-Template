// 博弈论
void Solve() {
  memset(SG, 0, sizeof(SG));
  for (int i = 1; i <= 10000; i++) {
    memset(S, 0, sizeof(S));
    for (int j = 1; j <= n; j++) {
      if (f[j] > i) break;
      S[SG[i - f[j]]] = 1;
    }
    for (int j = 0;; j++) {
      if (!S[j]) {
        SG[i] = j;
        break;
      }
    }
  }
}
// Nim博弈 取走最后一个人胜利
// 将所有SG[i]异或在一起,Ans>0就先手胜利,反之后手胜利

// 反Nim博弈  最后没得取的人胜利
// 满足下列任何一种
// 1、若SG[i]的数量都为1， 并且1的数量为偶数先手赢
// 2、若不都为1， 那么Nim相反判断Ans即可
