#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, m;
int e[N][N];
int ans[N];

void gauss() {
    int c = 0, r = 0;
    for (c = 0, r = 0; c < n; c++) {
        int t = r;
        for (int i = r; i < n; i++) {
            if (e[i][c]) {
                t = i;
                break;
            }
        }
        if (!e[t][c]) continue;
        for (int i = c; i <= n; i++) swap(e[t][i], e[r][i]);
        for (int i = r + 1; i < n; i++) {
            if (e[i][c]) {
                for (int j = c; j <= n; j++) {
                    e[i][j] ^= e[r][j];
                }
            }
        }
        r++;
    }
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++) e[i][n] ^= e[i][j] * e[j][n];
    for (int i = 0; i < n; i++) ans[i] = e[i][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        e[x][y] ^= 1, e[y][x] ^= 1;
    }
    return 0;
}
