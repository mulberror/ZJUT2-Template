#include <bits/stdc++.h>
using namespace std;
namespace ComputationGeometry {
const double EPS = 1e-6;

int sgn(double x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Point {
    double x, y;
    Point(double X = 0, double Y = 0) : x(X), y(Y) {}

    Point operator+(const Point &b) { return Point(x + b.x, y + b.y); }
    Point operator-(const Point &b) { return Point(x - b.x, y - b.y); }
    double operator*(const Point &b) { return x * b.x + y * b.y; }  // 点积
    double operator^(const Point &b) { return x * b.y - y * b.x; }  // 叉积

    Point turn(double k) {  // 点绕原点逆时针旋转k
        return Point(cos(k) * x - sin(k) * y, cos(k) * y + sin(k) * x);
    }

    Point operator*(const double &k) { return Point(x * k, y * k); }
    Point operator/(const double &k) { return Point(x / k, y / k); }
    double dis() { return sqrt(x * x + y * y); }          // 点到原点的距离
    Point unit() { return Point(x / dis(), y / dis()); }  // 该方向上的单位向量

    friend bool operator<(const Point &lhs, const Point &rhs) {  // 极角排序
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
};

using Vector = Point;

double triArea(Point a, Point b, Point c) {  // 三角形面积
    Vector v1 = b - a;
    Vector v2 = c - a;
    return abs(v1 ^ v2) / 2.0;
}

double dist(Point a, Point b) { return (a - b).dis(); }  // 两点的距离

struct Line {     // 直线
    Point s, fx;  // s:起点 fx:方向向量
    Line() {}
    Line(Point a, Vector v) : s(a), fx(v) {}
    Line(Point a, double k) {
        s = a;
        fx = Point(1.0, k);
    }
};

Point interPoint(Line a, Line b) {  // 直线a与直线b的交点
    double t = ((b.s - a.s) ^ b.fx) / (a.fx ^ b.fx);
    return a.s + a.fx * t;
}

double disToLine(Point p, Point a, Point b) {  // 点p到直线(a,b) 的距离
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    return fabs(v1 ^ v2) / v1.dis();
}

double disToSegment(Point p, Point a, Point b) {  // 点p到线段(a,b)的距离
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (sgn(v1 * v2) <= 0) {
        return v2.dis();
    } else if (sgn(v1 * v3) >= 0) {
        return v3.dis();
    } else {
        return fabs(v1 ^ v2) / v1.dis();
    }
}

using Polygon = vector<Point>;

double area(Polygon v) {
    double ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ans += fabs(v[i] ^ v[(i + 1) % v.size()]);
    }
    return ans / 2.0;
}

Point tmp[100005];
Polygon convexHull(Polygon a) {  // O(nlogn) 求解凸包
    sort(a.begin(), a.end());
    int m = 0, n = a.size();
    for (int i = 0; i < n; i++) {
        while (m > 1 && sgn((tmp[m] - tmp[m - 1]) ^ (a[i] - tmp[m - 1])) <= 0) m--;
        tmp[++m] = a[i];
    }
    int k = m;
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && sgn((tmp[m] - tmp[m - 1]) ^ (a[i] - tmp[m - 1])) <= 0) m--;
        tmp[++m] = a[i];
    }
    if (n > 1) m--;
    Polygon ans;
    for (int i = 1; i <= m; i++) ans.push_back(tmp[i]);
    return ans;
}
}  // namespace ComputationGeometry
using namespace ComputationGeometry;

int n;
Polygon a;
int main() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    Polygon v = convexHull(a);
    double ans = 0;
    int m = v.size();
    for (int i = 0; i < m; i++) ans += (v[i] - v[(i - 1 + m) % m]).dis();
    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}
