#include <bits/stdc++.h>

using i64 = long long;

const int N = 1e5 + 5;

int tmp[N], rec[N];

i64 solve(int l, int r) {
    if (l == r) {
        return 0; 
    }
    int mid = l + r >> 1; 
    int ls = l, rs = mid + 1, p = 0;
    i64 res = solve(l, mid) + solve(mid + 1, r);  
    while (ls <= mid && rs <= r) {
        if (rec[ls] > rec[rs]) {
            res += mid - ls + 1; 
            tmp[p++] = rec[rs++];
        } else {
            tmp[p++] = rec[ls++];
        }
    } 
    while (ls <= mid) {
        tmp[p++] = rec[ls++]; 
    }
    while (rs <= r) {
        tmp[p++] = rec[rs++];
    }
    for (int i = l; i <= r; i++) {
        rec[i] = tmp[i - l];
    }
    return res; 
}

int main() {
    return 0; 
}