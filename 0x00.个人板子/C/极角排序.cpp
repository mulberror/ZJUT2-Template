// 极角排序
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n;
long long ans;
struct node {
    long long x, y;
    double angle;
} a[100005];
bool cmp(node a, node b) {
    return a.angle < b.angle;
}
bool check(int i, int j) {
    return a[i].x * a[j].y - a[i].y * a[j].x >= 0;  // y在x的逆时针方向
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &a[i].x, &a[i].y);
        a[i].angle = atan2(a[i].y, a[i].x);
    }
    sort(a + 1, a + 1 + n, cmp);
    ans = (long long)n * (n - 1) * (n - 2) / 6;
    long long nxt = 2;
    long long tot = 0;
    for (int i = 1; i <= n; i++) {
        while (nxt != i && check(i, nxt)) {
            tot++;
            nxt = nxt % n + 1;
        }
        ans -= tot * (tot - 1) / 2;
        tot--;
    }
    printf("%lld\n", ans);
}