// kmp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 1000005
using namespace std;
char s1[N], s2[N];
int nxt[N], n1, n2;
void kmp() {
    int i = 1;
    nxt[i] = 0;
    int j = 0;
    while (i <= n2) {
        if (j == 0 || s2[i] == s2[j])
            nxt[++i] = ++j;
        else
            j = nxt[j];
    }
}
int main() {
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    n1 = strlen(s1 + 1);
    n2 = strlen(s2 + 1);
    kmp();
    int j = 1;
    int i = 1;
    while (i <= n1) {
        if (j == 0 || s2[j] == s1[i]) {
            j++;
            i++;
        } else
            j = nxt[j];
        if (j > n2) {
            printf("%d\n", i - n2);
            j = nxt[j];
        }
    }
    for (int i = 2; i <= n2 + 1; i++) printf("%d ", nxt[i] - 1);
}
