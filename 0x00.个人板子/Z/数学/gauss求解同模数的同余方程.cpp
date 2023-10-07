int gauss(std::vector<std::vector<int>> &a) { 
    // 高斯消元
    // 0 表示无解
    // 1 表示有唯一解
    // 2 表示有无限解
    int n = a.size(), m = a[0].size() - 1, r = 0;
    // n 是方程组数
    // m 是元个数
    // r 是秩
    for (int i = 0; i < m; i++) {
        int p = -1;
        for (int j = r; j < n; j++) {
            if (a[j][i] != 0) {
                p = j;
                break;
            }
        }
        if (p != -1) {
            if (p != r) std::swap(a[p], a[r]);
            for (int j = 0, x = invn[a[r][i]]; j <= m; j++) a[r][j] = a[r][j] * x % P; 
            for (int j = r + 1; j < n; j++) {
                for (int k = 0, x = a[j][i]; k <= m; k++) {
                    a[j][k] -= x * a[r][k] % P;
                    if (a[j][k] < 0) a[j][k] += P;
                }
            }
            r++;
        }
    }
    for (int i = r - 1; i >= 0; i--) {
        int p = 0;
        for (int j = 0; j <= m; j++) {
            if (a[i][j] == 1) {
                p = j;
                break;
            }
        }
        for (int j = n - 1; j >= 0; j--) {
            if (j == i) continue;
            for (int k = 0, x = a[j][p]; k <= m; k++) {
                a[j][k] -= x * a[i][k] % P;
                if (a[j][k] < 0) a[j][k] += P;
            }
        }
    }
    for (int i = r; i < n; i++) {
        if (a[i][m] != 0) return 0;
    }
    if (r < m) return 2;
    return 1;
}
