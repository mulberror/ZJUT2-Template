#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2e7 + 5;

int n, m;
int nxt[maxn], ext[maxn];
char s[maxn], t[maxn];

void get_nxt() {  // 求t的nxt数组
    int j = 0, p = 1, q;
    nxt[0] = m;
    while (j + 1 < m && t[j] == t[j + 1])
        j++;
    nxt[1] = j;
    for (int i = 2; i < m; i++) {
        q = p + nxt[p] - 1;
        if (i + nxt[i - p] <= q)
            nxt[i] = nxt[i - p];
        else {
            j = max(q - i + 1, 0);
            while (i + j < m && t[i + j] == t[j])
                j++;
            nxt[i] = j, p = i;
        }
    }
}

void get_ext() {  // 求t与s每一个后缀的lcp
    int j = 0, p = 0, q;
    while (j < n && j < m && s[j] == t[j])
        j++;
    ext[0] = j;
    for (int i = 1; i < n; i++) {
        q = p + ext[p] - 1;
        if (i + nxt[i - p] <= q)
            ext[i] = nxt[i - p];
        else {
            j = max(q - i + 1, 0);
            while (i + j < n && j < m && s[i + j] == t[j])
                j++;
            ext[i] = j, p = i;
        }
    }
}

int main() {
    long long z, p;
    z = p = 0;
    scanf("%s", s);
    scanf("%s", t);
    n = strlen(s);
    m = strlen(t);
    get_nxt();
    get_ext();
    for (int i = 0; i < n; i++)
        p ^= (1LL * (i + 1) * (ext[i] + 1));
    for (int i = 0; i < m; i++)
        z ^= (1LL * (i + 1) * (nxt[i] + 1));
    printf("%lld\n%lld\n", z, p);
    return 0;
}
