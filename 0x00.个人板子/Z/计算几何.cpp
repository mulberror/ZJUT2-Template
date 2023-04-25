#include <bits/stdc++.h>

namespace CG {

using db = double;

const db EPS = 1e-6;

int sgn(db x) {
    if (fabs(x) < EPS) {
        return 0;
    } else if (x > 0) {
        return 1;
    } else {
        return -1;
    }
}

struct Point {
    db x, y;
    Point(db X = 0, db Y = 0) : x(X), y(Y) {}

    Point operator+(const Point &b) { return Point(x + b.x, y + b.y); }
    Point operator-(const Point &b) { return Point(x - b.x, y - b.y); }
    db operator*(const Point &b) { return x * b.x + y * b.y; } // 点积
    db operator^(const Point &b) { return x * b.y - y * b.x; } // 叉积

    Point operator*(const db &k) { return Point(x * k, y * k); }
    Point operator/(const db &k) { return Point(x / k, y / k); }

    db dis() { return sqrt(x * x + y * y); } // 点到原点的距离

    Point unit() { return Point(x / dis(), y / dis()); } // 该方向上的单位向量
};

using Vector = Point;

db dist(Point a, Point b) { return (a - b).dis(); } // 两点的距离

struct Line {    // 直线
    Point s, fx; // s:起点 fx:方向向量

    Line() {}
    Line(Point a, Vector v) : s(a), fx(v) {}
    Line(Point a, db k) {
        s = a;
        fx = Point(1.0, k);
    }
};

Point interPoint(Line a, Line b) { // 直线a与直线b的交点
    db t = ((b.s - a.s) ^ b.fx) / (a.fx ^ b.fx);
    return a.s + a.fx * t;
}

db disToSegment(Point p, Point a, Point b) { // 点p到线段(a,b)的距离
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (sgn(v1 * v2) <= 0) {
        return v2.dis();
    } else if (sgn(v1 * v3) >= 0) {
        return v3.dis();
    } else {
        return fabs(v1 ^ v2) / v1.dis();
    }
}

struct Polygon { // 多边形
    std::vector<Point> v;

    Polygon(int x = 0) { v.resize(x); }

    db area() {
        db ans = 0;
        for (int i = 0; i < v.size(); i++) {
            ans += fabs(v[i] ^ v[(i + 1) % v.size()]);
        }
        return ans / 2.0;
    }

    Point &operator[](int k) { return v[k]; }
};
} // namespace CG