#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
const int N = 2005, P = 1e9 + 7;

int a[N][N];
int n, m;

char s[N];
// 第一个哈希的数组
int base1[N];
int base2[N];
int h[2][N][N];

// 第二个哈希的数组
u64 b1[N], b2[N];
u64 h2[2][N][N];

int get(int x1, int y1, int x2, int y2, int opt) {  // opt = (0/1)
    int ans = (i64(h[opt][x2][y2]) - i64(h[opt][x2][y1 - 1]) * base1[y2 - y1 + 1] % P -
               i64(h[opt][x1 - 1][y2]) * base2[x2 - x1 + 1] % P +
               (i64)h[opt][x1 - 1][y1 - 1] * base1[y2 - y1 + 1] % P * base2[x2 - x1 + 1] % P) %
              P;
    return ans < 0 ? ans += P : ans;
}

u64 get2(int x1, int y1, int x2, int y2, int opt) {
    u64 ans = (h2[opt][x2][y2] - h2[opt][x2][y1 - 1] * b1[y2 - y1 + 1] -
               h2[opt][x1 - 1][y2] * b2[x2 - x1 + 1] +
               h2[opt][x1 - 1][y1 - 1] * b1[y2 - y1 + 1] * b2[x2 - x1 + 1]);
    return ans;
}

bool check(int x1, int y1, int x2, int y2) {
    return get(x1, y1, x2, y2, 0) == get(n - x2 + 1, m - y2 + 1, n - x1 + 1, m - y1 + 1, 1) &&
           get2(x1, y1, x2, y2, 0) == get2(n - x2 + 1, m - y2 + 1, n - x1 + 1, m - y1 + 1, 1);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; j++) {
            a[i][j] = s[j];
        }
    }

    base1[0] = base2[0] = 1;
    b1[0] = b2[0] = 1;
    for (int i = 1; i <= max(n, m); i++) {
        base1[i] = i64(base1[i - 1]) * 131 % P, base2[i] = i64(base2[i - 1]) * 233 % P;
        b1[i] = b1[i - 1] * 131ull, b2[i] = b2[i - 1] * 233ull;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; j++) {
            h[0][i][j] = (i64(h[0][i][j - 1]) * 131 + a[i][j]) % P;
            h[1][i][j] = (i64(h[1][i][j - 1]) * 131 + a[n - i + 1][m - j + 1]) % P;
            h2[0][i][j] = h2[0][i][j - 1] * 131ull + a[i][j];
            h2[1][i][j] = h2[1][i][j - 1] * 131ull + a[n - i + 1][m - j + 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            h[0][i][j] = (i64(h[0][i][j]) + i64(h[0][i - 1][j]) * 233 % P) % P;
            h[1][i][j] = (i64(h[1][i][j]) + i64(h[1][i - 1][j]) * 233 % P) % P;
            h2[0][i][j] = h2[0][i][j] + h2[0][i - 1][j] * 233ull;
            h2[1][i][j] = h2[1][i][j] + h2[1][i - 1][j] * 233ull;
        }
    }
}