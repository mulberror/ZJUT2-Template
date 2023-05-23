#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int M = 1e6 + 3;
struct node {
    int x, opt, id;
} a[M];
long long ans[M];
struct SAM {
    int maxlen[M * 2], trans[M * 2][26], link[M * 2], size, last;
    SAM() { size = last = 1; }
    inline void extend(int id) {
        int cur = (++size), p;
        maxlen[cur] = maxlen[last] + 1;
        for (p = last; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
        if (!p)
            link[cur] = 1;
        else {
            int q = trans[p][id];
            if (maxlen[q] == maxlen[p] + 1)
                link[cur] = q;
            else {
                int clone = (++size);
                maxlen[clone] = maxlen[p] + 1;
                for (int i = 0; i < 26; i++) trans[clone][i] = trans[q][i];
                link[clone] = link[q];
                for (; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
                link[cur] = link[q] = clone;
            }
        }
        last = cur;
    }
    inline long long gao() {  // 本质不同字符字串个数
        ll ans = 0;
        for (int i = 2; i <= last; ++i) ans += maxlen[i] - maxlen[link[i]];
        return ans;
    }
} sam;
char s[M];
int n, q;
long long f[M];
bool cmp(node a, node b) {
    return a.x < b.x;
}
int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    // int tot=0;
    // for (int i=1;i<=q;i++){
    //     int l; int r;
    //     scanf("%d%d",&l,&r);
    //     tot++;
    //     a[tot].x=l-1;
    //     a[tot].opt=-1;
    //     a[tot].id=i;
    //     tot++;
    //     a[tot].x=r;
    //     a[tot].opt=1;
    //     a[tot].id=i;
    // }
    // int k=1;
    // sort(a+1,a+1+tot,cmp);
    // for (int i=1;i<=tot;i++) cout<<a[i].x<<' '<<a[i].opt<<' '<<a[i].id<<endl;
    // while (a[k].x==0) k++;
    // long long last=0;
    for (int i = 1; i <= n; i++) {
        sam.extend(s[i] - 'a');
        f[i] = f[i - 1] + sam.gao();
        // b[i]=sam.gao()-last;
        // last=sam.gao();
        // cout<<sam.gao()<<' ';
        // while (k<=tot&&a[k].x==i){
        //     ans[a[k].id]+=sam.gao()*a[k].opt;
        //     k++;
        // }
    }
    // cout<<endl;
    // for (int i=1;i<=n;i++) cout<<b[i]<<' ';
    // cout<<endl;
    // for (int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", f[r] - f[l - 1]);
    }
    return 0;
}