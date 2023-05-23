#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, x, y, f[100005][21];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &f[i][0]);
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    while (m--) {
        scanf("%d%d", &x, &y);
        int k = log2(y - x + 1);
        printf("%d\n", max(f[x][k], f[y - (1 << k) + 1][k]));
    }
}