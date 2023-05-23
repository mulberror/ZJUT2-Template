#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

struct Segment {
    int length;

    int ls, rs;
    int maxVal, minVal;

    i64 sum;
    int lazyTag;

    friend Segment operator+(const Segment &lhs, const Segment &rhs) const {
        Segment ret;

        ret.length = lhs.length + rhs.length;
        ret.maxVal = max(lhs.maxVal, rhs.maxVal);
        ret.minVal = min(lhs.minVal, rhs.minVal);
    }
};

void pushDown() struct SegmentTree {
    vector<Segment> v;
    int n;

    SegmentTree(int N) : n(N) { v.clear(), v.resize(n << 1); }

    void modify(int nod, int l, int r, int ql, int qr, int v) {}
};

int main() { return 0; }