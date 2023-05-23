//矩阵乘法快速幂
#include<bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
struct matrix{
    long long x[5][5];
}ans,base;
matrix mul(matrix a,matrix b,int n){
    matrix c;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++) c.x[i][j]=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            for (int k=1;k<=n;k++) c.x[i][j]=(c.x[i][j]+a.x[i][k]*b.x[k][j]%MOD+MOD)%MOD;
        }
    return c;
}
matrix ksm(long long k,matrix s,matrix x){
    while (k){
        if (k&1) s=mul(s,x,3);
        x=mul(x,x,3);
        k>>=1;
    }
    return s;
}
int main(){
    long long x,y,n;
    scanf("%lld%lld%lld",&x,&y,&n);
    ans.x[1][1]=((y-x)%MOD+MOD)%MOD; ans.x[1][2]=(y+MOD)%MOD; ans.x[1][3]=(x+MOD)%MOD;
    base.x[1][1]=1; base.x[1][2]=1; base.x[1][3]=0;
    base.x[2][1]=-1; base.x[2][2]=0; base.x[2][3]=1;
    if (n<=3) printf("%lld\n",ans.x[1][3-n+1]);
    else{
        ans=ksm(n-3,ans,base);
        printf("%lld\n",ans.x[1][1]);
    }
}
/*****************************************************************************************************/
//快速读入
int read(){
    int s=0;
    char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9'){
        s=s*10+ch-48;
        ch=getchar();
    }
    return s;
}
/*****************************************************************************************************/
//hash 回文
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define Seed 131
#define MOD 998244353
using namespace std;
char s[100005];
long long a[100005],b[100005],c[100005];
int n;
int check(int l,int r){
	if ((a[r]-a[l-1]*b[r-l+1]%MOD+MOD)%MOD==(c[n-l+1]-c[n-r]*b[r-l+1]%MOD+MOD)%MOD) return 1; 
	else return 0;
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	b[1]=Seed;
	for (int i=2;i<=n;i++) b[i]=b[i-1]*Seed%MOD;
	for (int i=1;i<=n;i++) a[i]=(a[i-1]*Seed+s[i])%MOD; //正着哈希
	for (int i=1;i<=n;i++) c[i]=(c[i-1]*Seed+s[n-i+1])%MOD;   //daozhe
	int T;
	cin>>T;
	while (T--){
		int l,r;
		cin>>l>>r;
		if (check(l,r)) printf("YES\n"); else printf("NO\n");
	} 
}
/*****************************************************************************************************/
//快速幂
int ksm(int x,int k){
    int s=1;
    while (k){
        if (k&1) s=(long long)s*x%MOD;
        x=(long long)x*x%MOD;
        k>>=1;
    }
    return s;
}
/*****************************************************************************************************/