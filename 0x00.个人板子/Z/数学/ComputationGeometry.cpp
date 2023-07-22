#include <bits/stdc++.h>

namespace CG {

const double EPS = 1e-6;

int sgn(double x) {
    if (fabs(x) < EPS) {
        return 0;
    } else if (x > 0) {
        return 1;
    } else {
        return -1;
    }
}

struct Point {
    double x, y;
    Point(double X = 0, double Y = 0) : x(X), y(Y) {}

    Point operator+(const Point &b) { return Point(x + b.x, y + b.y); }
    Point operator-(const Point &b) { return Point(x - b.x, y - b.y); }
    double operator*(const Point &b) { return x * b.x + y * b.y; }  // 点积
    double operator^(const Point &b) { return x * b.y - y * b.x; }  // 叉积

    Point turn(double k) {  // 点绕原点逆时针旋转k
        return Point(std::cos(k) * x - std::sin(k) * y, std::cos(k) * y + std::sin(k) * x);
    }

    Point operator*(const double &k) { return Point(x * k, y * k); }
    Point operator/(const double &k) { return Point(x / k, y / k); }

    double dis() { return sqrt(x * x + y * y); }  // 点到原点的距离

    Point unit() { return Point(x / dis(), y / dis()); }  // 该方向上的单位向量
};

using Vector = Point;

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

struct Polygon {  // 多边形
    std::vector<Point> v;

    Polygon(int x = 0) { v.resize(x); }

    double area() {
        double ans = 0;
        for (int i = 0; i < v.size(); i++) {
            ans += fabs(v[i] ^ v[(i + 1) % v.size()]);
        }
        return ans / 2.0;
    }

    Point &operator[](int k) { return v[k]; }
};
}  // namespace CG