#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
char s[N];
int m;
long long su[10][N];
struct Palindromic_Tree {
    int next[N][26];  // next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[N];      // fail指针，失配后跳转到fail指针指向的节点     最长回文后缀
    int len[N];       // len[i]表示节点i表示的回文串的长度
    int S[N];         // 存放添加的字符
    ll cnt[N];        // 结点表示的本质不同的回文串的个数(调用count()后)
    int num[N];       // 结点表示的最长回文串的最右端点为回文串结尾的回文串个数
    int last;         // 指向上一个字符所在的节点，方便下一次add
    int n;            // 字符数组指针
    int p;            // 节点指针

    int newnode(int x) {  // 新建节点
        memset(next[p], 0, sizeof(next[p]));
        cnt[p] = 0;
        num[p] = 0;
        len[p] = x;
        return p++;
    }
    void init() {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        S[0] = -1;  // 开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }
    int get_fail(int x) {  // 和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }
    void add(int c, int k) {
        c -= 'a';
        S[++n] = c;
        int cur = get_fail(last);                      // 通过上一个回文串找这个回文串的匹配位置
        if (!next[cur][c]) {                           // 如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);           // 新建节点
            fail[now] = next[get_fail(fail[cur])][c];  // 和AC自动机一样建立fail指针，以便失配后跳转
            num[now] = num[fail[now]] + 1;
            next[cur][c] = now;
            su[k][now] = su[k - 1][now] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
        su[k][last] = su[k - 1][last] + 1;
    }
    void count() {
        for (int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
        // 父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
} pam;
int main() {
    scanf("%d", &m);
    pam.init();
    for (int _ = 1; _ <= m; _++) {
        scanf("%s", s);
        int len = strlen(s);
        for (int i = 0; i < len; i++) {
            pam.add(s[i], _);
            // printf("%d%c",pam.p-2," \n"[i==len-1]);
        }
        if (_ != m) {
            pam.add('*', _);
            pam.add('#', _);
        }
        // long long y=pam.solve(_);
    }
    long long ans = 0;
    for (int i = 2; i <= pam.p - 1; i++)
        if (su[m][i] >= m)
            ans++;
    printf("%lld\n", ans);
}