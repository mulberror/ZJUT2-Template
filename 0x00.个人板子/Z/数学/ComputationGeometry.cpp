#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
namespace ComputationGeometry {
// ================================================================================
// 二维计算几何基础
const double eps = 1e-6;
const double PI = acos(-1);
const double INF = 1e20;

int sgn(long double x) {
    if (abs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

// ================================================================================
// 二维计算几何——点相关
template <typename T>
struct PT {
    T x, y;
    PT(T x = 0, T y = 0) : x(x), y(y) {}
    PT operator+(const PT& b) {
        return PT(x + b.x, y + b.y); 
    }
    PT operator-(const PT& b) { 
        return PT(x - b.x, y - b.y); 
    }
    PT operator*(T k) { 
        return PT(x * k, y * k); 
    }
    PT operator/(T k) {
        return PT(x / k, y / k);
    }
    PT rotleft() { // 逆时针旋转90度
        return PT(-y, x);
    }
    PT rotright() { // 顺时针旋转90度
        return PT(y, -x);
    }
    PT rot(double k) { // 逆时针旋转k度（弧度制）
        return PT(cos(k) * x - sin(k) * y, cos(k) * y + sin(k) * x);
    }
    PT trunc(T len) {
        double l = sqrt(x * x + y * y);
        if (!sgn(l)) return *this;
        len /= l;
        return PT(x * len, y * len);
    }
    T len2() const {
        return x * x + y * y;
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
    bool operator<(PT b) const { //极角排序
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    bool operator==(PT b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
};

// 两个点的点积（a*b)
template <typename T>
T dot(PT<T> a, PT<T> b) { 
    return a.x * b.x + a.y * b.y; 
}
// pa和pb的点积
template <typename T>
T dot(PT<T> p, PT<T> a, PT<T> b) { 
    return dot(a - p, b - p); 
}
// a和b的叉积
template <typename T>
T cross(PT<T> a, PT<T> b) { 
    return a.x * b.y - a.y * b.x; 
}
// 向量pa和pb的叉积
template <typename T>
T cross(PT<T> p, PT<T> a, PT<T> b) {
    return cross(a - p, b - p);
}

using Point = PT<double>;
using Vector = Point;

double dist(Point a, Point b) {
    return (a - b).len();
}

double rad(Point p, Point a, Point b) { // 线段pa和pb所成夹角，测试 LightOJ 1203，https://lightoj.com/problem/guarding-bananas
    return abs(atan2(fabs(cross(p, a, b)), dot(p, a, b)));
}

// ================================================================================
// 二维计算几何——线相关
// Line 如果是直线，那么s,e表示两个在直线上的点
//      如果是线段，那么就是线段的端点
struct Line { 
    Point s, e;
    Line() : s(0, 0), e(0, 0) {}
    Line(Point a, Point b) : s(a), e(b) {}
    // 给定
    Line(Point p, double ang) {
        s = p;
        if (sgn(ang - PI / 2) == 0) {
            e = s + Point(0, 1);
        } else {
            e = s + Point(1, tan(ang));
        }
    }
    // 给定一般式
    Line (double a, double b, double c) {
        if (sgn(a) == 0) {
            s = Point(0, -c / b);
            e = Point(1, -c / b);
        } else if (sgn(b) == 0) {
            s = Point(-c / a, 0);
            e = Point(-c / a, 1);
        } else {
            s = Point(0, -c / b);
            e = Point(1, (-c - a) / b);
        }
    }
    // 改为方向指向上方
    void fix() { 
        if (e < s) swap(s, e); 
    }
    double length() { 
        return (s - e).len();
    }
};
// 返回直线倾斜角 0 <= ang < PI
double angle(Line v) {
    double k = atan2(v.e.y - v.s.y, v.e.x - v.s.x);
    if (sgn(k) < 0) k += PI;
    if (!sgn(k - PI)) k -= PI;
    return k;
}
// =================== 点、线段、直线关系 =====================
// 点和直线的关系 1: 在左侧,  2: 在右侧, 3: 在直线上
int relation(Point p, Line v) {
    int c = sgn(cross(v.s, p, v.e));
    if (c < 0) return 1;
    else if (c > 0) return 2;
    else return 3;
}
// 点在线段上的判断
bool segrelation(Point p, Line v) {
    return sgn(cross(v.s, p, v.e)) == 0 && sgn(dot(p - v.s, p - v.e)) <= 0;
}
// 判断两向量平行  (对应直线平行或重合) 
bool parallel(Line a, Line b) { 
    return sgn(cross(a.e - a.s, b.e - b.s)) == 0;
}
// 两线段相交判断 (2: 规范相交, 1: 非规范相交, 0: 不相交) 
int seg_cross_seg(Line a, Line b) {
    int d1 = sgn(cross(a.s, a.e, b.s));
    int d2 = sgn(cross(a.s, a.e, b.e));
    int d3 = sgn(cross(b.s, b.e, a.s));
    int d4 = sgn(cross(b.s, b.e, a.e));
    if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
    return (d1 == 0 && sgn(dot(b.s - a.s, b.s - a.e)) <= 0) ||
        (d2 == 0 && sgn(dot(b.e - a.s, b.e - a.e)) <= 0) ||
        (d3 == 0 && sgn(dot(a.s - b.s, a.s - b.e)) <= 0) ||
        (d4 == 0 && sgn(dot(a.e - b.s, a.e - b.e)) <= 0);
}
// 直线和线段的相交判断 (2: 规范相交, 1: 非规范相交, 0: 不相交) , b 是线段
int line_cross_seg(Line a, Line b) {
    int d1 = sgn(cross(a.s, a.e, b.s));
    int d2 = sgn(cross(a.s, a.e, b.e));
    if ((d1 ^ d2) == -2) return 2;
    return (d1 == 0 || d2 == 0);
}

// =================== 交点 =====================
// 两条直线的交点
Point line_cross_line(Line a, Line b) {
    double k = cross(a.s, b.s, b.e) / cross(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * k;
}

// =================== 距离 =====================
// 点到直线的距离
double dist_point_to_line(Line v, Point p) {
    return fabs(cross(v.s, p, v.e)) / v.length();
}
// 点到线段的距离
double dist_point_to_seg(Line v, Point p) {
    if (sgn(dot(p - v.s, v.e - v.s)) < 0 || sgn(dot(p - v.e, v.s - v.e)) < 0) {
        return min(dist(p, v.s), dist(p, v.e));
    }
    return dist_point_to_line(v, p);           
}
// 线段到线段的距离, 前提是两条线段不相交
double dist_point_to_seg(Line a, Line b) {
    return min(dist_point_to_line(a, b.s), dist_point_to_line(a, b.e));
}

// =================== 点的投影和对称点 =====================
// 返回点在直线上的投影 P
Point propl(Point p, Line v) {
    Point t = v.e - v.s;
    return v.s + t * dot(t, p - v.s) / t.len2();
}
// 返回点 p 关于直线的对称点
Point symmetrypoint(Line v, Point p) {
    Point q = propl(p, v);
    return Point(2 * q.x - p.x, 2 * q.y - p.y);
}

// ================================================================================
// 二维计算几何——圆相关
struct Circle {
    Point p;
    double r;
    Circle(Point p = Point(0, 0), double r = 0) : p(p), r(r) {}
    // 三角形的外接圆, 利用两条边的中垂线得到圆心, 测试: UVA12304
    Circle(Point a, Point b, Point c) {
        Point x = (a + b) / 2, y = (b + c) / 2;
        Line u = Line(x, x + (b - a).rotleft());
        Line v = Line(y, y + (c - b).rotleft());
        p = line_cross_line(u, v);
        r = dist(p, a);
    }
    // 三角形的内切圆, bool t 没有作用, 只是为了和上面区别, 测试: UVA12304
    Circle(Point a, Point b, Point c, bool t) {
        Line u, v;
        double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
        u.s = a;
        u.e = u.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        m = atan2(a.y - b.y, a.x - b.x);
        n = atan2(c.y - b.y, c.x - b.x);
        v.s = b;
        v.e = v.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        p = line_cross_line(u, v);
        r = dist_point_to_line(Line(a, b), p);
    }
    bool operator==(Circle c) const { 
        return p == c.p && sgn(r - c.r) == 0; 
    } 
    double area() {
        return PI * r * r;
    }
    double perimeter() {
        return 2.0 * PI * r;
    }
    Point point(double rad) { // 圆的参数方程
        return Point(p.x + cos(rad) * r, p.y + sin(rad) * r);
    }
};
// 点和圆的关系 (0: 圆外, 1: 圆上, 2: 圆内) 
int circle_relation_point(Circle c, Point a) {
    double dst = dist(a, c.p);
    if (sgn(dst - c.r) < 0) return 2;
    else if (sgn(dst - c.r) == 0) return 1;
    return 0;
}
// 线段和圆的关系, 比较的是圆心到线段的距离和半径的关系
int circle_relation_seg(Circle c, Line v) {
    double dst = dist_point_to_seg(v, c.p);
    if (sgn(dst - c.r) < 0) return 2;
    else if (sgn(dst - c.r) == 0) return 1;
    return 0;
}
// 直线和圆的关系, 比较的是圆心到直线的距离和半径的关系
int circle_relation_line(Circle c, Line v) {
    double dst = dist_point_to_line(v, c.p);
    if (sgn(dst - c.r) < 0) return 2;
    else if (sgn(dst - c.r) == 0) return 1;
    return 0;
}
// 两圆的关系 (5: 相离, 4: 外切, 3: 相交, 2: 内切, 1: 内含, 0: 重合) 
int circle_relation_circle(Circle a, Circle b) {
    double d = dist(a.p, b.p);
    if (sgn(d - a.r - b.r) > 0) return 5;
    if (sgn(d - a.r - b.r) == 0) return 4;
    double l = fabs(a.r - b.r);
    if (sgn(d - a.r - b.r) < 0 && sgn(d - l) > 0) return 3;
    if (sgn(d - l) == 0) return 2;
    if (sgn(d - l) < 0) return 1;
    return 0;
}
// 直线与圆的交点: 利用圆中的直角三角形求解
// 返回int表示交点的个数
int circle_line_intersection(Circle a, Line b, Point &p1, Point &p2) {
    Point p = propl(a.p, b);                //中点
    double d = dist(p, a.p);
    if (sgn(d - a.r) > 0) return 0;         //相离
    if (sgn(d - a.r) == 0) {                //相切
        p1 = p2 = p;
        return 1;
    }
    Point dir = (b.s - b.e).trunc(1);       //相交
    double len = sqrt(a.r * a.r - d * d);
    p1 = p - dir * len, p2 = p + dir * len;
    return 2;
}
// 两圆相交的交点: 利用余弦定理
// 求两个圆的交点，返回 0 表示没有交点，返回 1 是一个交点，2 是两个交点
int circle_circle_intersection(Circle a, Circle b, Point &p1, Point &p2) {
    double d = dist(a.p, b.p);
    if (!sgn(d)) {
        if (!sgn(a.r - b.r)) return -1; // 两圆重合
        else return 0; // 无交点, 同心圆
    }
    if (sgn(a.r + b.r - d) < 0) return 0; // 外离
    if (sgn(fabs(a.r - b.r) - d) > 0) return 0;
    Vector dir = b.p - a.p;
    double ang = atan2(dir.y, dir.x);       //要得到一个 (-PI, PI] 内的角
    double rad = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
    p1 = a.point(ang - rad);
    p2 = a.point(ang + rad);
    return 1 + !(p1 == p2);
}

// =================== 圆的面积 =====================
// 求两圆相交的面积
double area_circle_circle(Circle a, Circle b) {
    int rel = circle_relation_circle(a, b);
    if (rel >= 4) return 0.0;
    if (rel <= 2) return min(a.area(), b.area());
    double d = dist(a.p, b.p);
    double hf = (a.r + b.r + d) / 2.0; 
    double ss = 2 * sqrt(hf * (hf - a.r) * (hf - b.r) * (hf - d)); // 海伦公式
    double a1 = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d)); // 余弦定理, 求的是角度的一般
    double a2 = acos((b.r * b.r + d * d - a.r * a.r) / (2 * b.r * d));
    a1 = a1 * a.r * a.r, a2 = a2 * b.r * b.r;   // 扇形面积, 这里不用乘以0.5
    return a1 + a2 - ss;
}
// 圆和三角形 pab的相交面积
//测试：POJ3675 HDU3982 HDU2892
double area_circle_triangle(Circle c, Point a, Point b) {
    Point p = c.p;
    double r = c.r;
    if (sgn(cross(p, a, b)) == 0) return 0;
    Point q[5];
    int len = 0;
    q[len++] = a;
    Line l(a, b);
    Point p1, p2;
    if (circle_line_intersection(c, l, q[1], q[2]) == 2) {
        if (sgn(dot(q[1], a, b)) < 0) q[len++] = q[1];
        if (sgn(dot(q[2], a, b)) < 0) q[len++] = q[2];
    }
    q[len++] = b;
    if (len == 4 && sgn(dot(q[1], q[0], q[2])) > 0) {
        swap(q[1], q[2]);
    }
    double res = 0;
    for (int i = 0; i < len - 1; i++) {
        if (circle_relation_point(c, q[i]) == 0 || circle_relation_point(c, q[i + 1]) == 0) {
            double arg = rad(p, q[i], q[i + 1]);
            res += r * r * arg / 2.0;
        } else {
            res += abs(cross(p, q[i], q[i + 1])) / 2.0;
        }
    }
    return res;
}

// =================== 圆的切线 =====================
// 过一点作圆的切线(不用保证一定是圆外的点), 测试: POJ1375
int tangentline_circle_point(Circle c, Point p, Line &u, Line &v){
    int t = circle_relation_point(c, p);
    Vector dir = p - c.p;
    if (t == 2) return 0;
    if (t == 1) {
        u = Line(p, p + dir.rotleft());
        v = u;
        return 1;
    }
    double d = dist(c.p, p);
    double l = c.r * c.r / d;
    double h = sqrt(c.r * c.r - l * l);
    u = Line(p, c.p + (dir.trunc(l) + dir.rotleft().trunc(h)));
    v = Line(p, c.p + (dir.trunc(l) + dir.rotright().trunc(h)));
    return 2;
}

// 求两圆的公切线, 测试: UVA10674
int ltangentcc(Circle a, Circle b, Point* p1, Point* p2) {
    if (a.r < b.r) {
        swap(a, b);
        swap(p1, p2);
    }
    double diff = a.r - b.r;
    double sum = a.r + b.r;
    double d2 = (a.p.x - b.p.x) * (a.p.x - b.p.x) + (a.p.y - b.p.y) * (a.p.y - b.p.y);
    // 情况一: 重合
    if (a.p == b.p && sgn(a.r - b.r) == 0)  return -1;
    // 情况二: 内含
    if (sgn(d2 - diff * diff) < 0) return 0;
    // 情况三: 内切
    int res = 0;
    double base = atan2(b.p.y - a.p.y, b.p.x - a.p.x);
    if (sgn(d2 - diff * diff) == 0) {
        p1[res] = a.point(base), p2[res] = b.point(base); res++;
        return 1;
    }
    // 情况四: 相交 (有外公切线) 
    double ang = acos((a.r - b.r) / sqrt(d2));
    p1[res] = a.point(base + ang), p2[res] = b.point(base + ang), res++;
    p1[res] = a.point(base - ang), p2[res] = b.point(base - ang), res++;
    // 情况五: 外切 (有一条内公切线) 
    if (sgn(sum * sum - d2) == 0) {
        p1[res] = p2[res] = a.point(base), res++;
    }
    // 情况六: 外离 (有两条内公切线) 
    else if (sgn(sum * sum - d2) < 0) {
        ang = acos ((a.r + b.r) / sqrt(d2));
        p1[res] = a.point(base + ang), p2[res] = b.point(PI + base + ang), res++;
        p1[res] = a.point(base - ang), p2[res] = b.point(PI + base - ang), res++;
    }
    return res;
}
// =================== 通过特殊条件生成圆 =====================
// 得到过 a, b 两点, 半径为 r0 的两个圆, 测试: UVA12304
int getcircle(Point a, Point b, double r0, Circle &c1, Circle &c2) {
    Circle x(a, r0), y(b, r0);
    int t = circle_circle_intersection(x, y, c1.p, c2.p);
    if (!t) return 0;
    c1.r = c2.r = r0;
    return t;
}
// 得到与直线 u 相切, 过点 q, 半径为 r0 的圆, 测试: UVA12304
int getcircle(Line u, Point p, double r0, Circle &c1, Circle &c2) {
    double dis = dist_point_to_line(u, p);
    if (sgn(dis - r0 * 2) > 0) return 0;
    Point down = (u.e - u.s).rotleft().trunc(r0);
    Point up = (u.e - u.s).rotright().trunc(r0);  //两个对应点
    if (!sgn(dis)) {
        c1.p = p + down;
        c2.p = p + up;
        c1.r = c2.r = r0;
        return 2;
    }
    Line u1(u.s + down, u.e + down), u2(u.s + up, u.e + up);    //两条线
    Circle cc(p, r0);
    Point p1, p2;
    if (!circle_line_intersection(cc, u1, p1, p2))    //只会与一条线交
        circle_line_intersection(cc, u2, p1, p2);
    c1 = Circle(p1, r0), c2 = Circle(p2, r0);
    if (p1 == p2) return 1;             //相切    == = [](){return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0;}
    return 2;                           //相交
}
// 得到与直线 u, v 相切, 半径为 r0 的圆, 测试: UVA12304
int getcircle(Line u, Line v, double r0, Circle &c1, Circle &c2, Circle &c3, Circle &c4) {
    if (parallel(u, v) == 1) return 0;              // parallel=[](u, v){return sgn(Cross(u.e - u.s, v.e - v.s)) == 0}
    Point down1 = (u.e - u.s).rotleft().trunc(r0);
    Point down2 = (v.e - v.s).rotleft().trunc(r0);
    Point up1 = (u.e - u.s).rotright().trunc(r0);
    Point up2 = (v.e - v.s).rotright().trunc(r0);     //得到四个点
    Line u1(u.s + down1, u.e + down1), u2(u.s + up1, u.e + up1);
    Line v1(v.s + down2, v.e + down2), v2(v.s + up2, v.e + up2);    //得到四条平行线
    c1.r = c2.r = c3.r = c4.r = r0;
    c1.p = line_cross_line(u1, v1);
    c2.p = line_cross_line(u1, v2);
    c3.p = line_cross_line(u2, v1);
    c4.p = line_cross_line(u2, v2);                                        //四个交点对应四个圆心
    return 4;
}
// 得到同时与不相交圆(要保证不相交) cx, cy 相切, 半径为 r0 的圆, 测试: UVA12304
int getcircle(Circle cx, Circle cy, double r0, Circle &c1, Circle &c2) {
    Circle x(cx.p, r0 + cx.r), y(cy.p, r0 + cy.r);  //两圆交点即为圆心
    int t = circle_circle_intersection(x, y, c1.p, c2.p);
    if (!t) return 0;      //无圆
    c1.r = c2.r = r0;
    return t;
}

// ================================================================================
// 二维计算几何——多边形凸包相关
const int N = ::N;

Point tmp[N];
struct Polygon {
    Point p[N];
    int n;
    // 进行极角排序
    Polygon() : n(0) {}
    void append(Point pt) {
        p[n++] = pt;
    }
    Point& operator[](int index) {
        return p[index];
    }
    void norm() {
        Point mi = p[0];
        for (int i = 1; i < n; i++) {
            mi = min(mi, p[i]);
        }
        sort(p, p + n, [&](Point a, Point b) {
            int d = sgn(cross(mi, a, b));
            if (d == 0) {
                return sgn(dist(a, mi) - dist(b, mi)) < 0;
            } else {
                return d > 0;
            }
        });
    }
    double perimeter() { // 多边形周长
        double ans = 0;
        for (int i = 0; i < n; i++) {
            ans += dist(p[i], p[(i + 1) % n]);
        }
        return ans;
    }
    double area() { // 多边形面积
        double ans = 0;
        for (int i = 0; i < n; i++) { 
            ans += cross(p[i], p[(i + 1) % n]);
        }
        return ans / 2;           // 面积有正负, 需根据题意来判断要不要取绝对值
    }
    Point bary_center() { // 多边形重心
        Point res(0, 0);
        double area = 0;
        for (int i = 1; i < n - 1; i++) {
            double tmp = cross(p[0], p[i], p[i + 1]);
            if (sgn(tmp) == 0) continue;
            area += tmp;
            res.x += (p[0].x + p[i].x + p[i + 1].x) / 3 * tmp;
            res.y += (p[0].y + p[i].y + p[i + 1].y) / 3 * tmp;
        }
        if (sgn(area)) res = res / area;
        return res;
    }
    //多边形和圆交的面积
    //测试：POJ3675 HDU3982 HDU2892
    double area_circle(Circle c) {
        double ans = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if (sgn(cross(c.p, p[i], p[j])) >= 0) {
                ans += area_circle_triangle(c, p[i], p[j]);
            } else {
                ans -= area_circle_triangle(c, p[i], p[j]);
            }
        }
        return abs(ans);
    }
    // ================== 凸包相关 ===================
    // 是否构成凸包
    // 顺逆时针都可以判断
    // 判断是否是凸包, 方向不一定是逆时针
    bool is_convex(){
        int dir = 0;
        p[n] = p[0], p[n + 1] = p[1];
        for (int i = 1; i <= n; i ++) {
            int u = sgn(cross(p[i] - p[i - 1], p[i + 1] - p[i]));
            if (!dir) dir = u;
            if (u * dir < 0) return false;
        }
        return true;
    }
    // 注意如果有影响，要特判下所有点共点，或者共线的特殊情况
    // O(nlogn) 求解凸包
    // 变成一个凸包
    void become_convex() {
        sort(p, p + n);
        n = unique(p, p + n) - p;
        int top = 0;
        for (int i = 0; i < n; i++) {
            while (top > 1 && sgn(cross(tmp[top - 2], tmp[top - 1], p[i])) <= 0) {
                --top;
            }
            tmp[top++] = p[i];
        }
        int bud = top;
        for (int i = n - 2; i >= 0; i--) {
            while (top > bud && sgn(cross(tmp[top - 2], tmp[top - 1], p[i])) <= 0) {
                --top;
            }
            tmp[top++] = p[i];
        }
        if (n > 1) top--;
        for (int i = 0; i < top; i++) {
            p[i] = tmp[i];
        }
        n = top;
    }
};

// =================== 点和凸包的关系 =====================
// 2: 里边, 1: 上边, 0: 外边
// 时间复杂度 O(logn),测试: UVALive - 7281
int relation(Polygon p, Point pt) {
    // l 取 1 的原因是要以p[0]作为基准点, r 取 n-2 的原因是下面要进行mid+1
    int n = p.n;
    int l = 1, r = n - 2; 
    while (l <= r) {
        int mid = (l + r) >> 1;
        int d1 = sgn(cross(p[0], p[mid], pt));
        int d2 = sgn(cross(p[0], p[mid + 1], pt));
        if (d1 >= 0 && d2 <= 0) { // 找到 pt 所在的三角区域
            // 如果在左侧或在边上, 说明在内部
            int c = sgn(cross(p[mid], p[mid + 1], pt));
            if (c > 0) return 2;
            else if (c == 0) return 1;
            else return 0; // 否则不在
        }
        else if (d1 < 0) {
            r = mid - 1; // 在右边
        }
        else {
            l = mid + 1; // 在左边
        }
    }
    return 0;
}

// =================== 过凸包外一点求凸包的切线 =====================
// 时间复杂度 O(log n) , 测试: Codeforces - gym - 101201E
int minslope(Polygon p, int l, int r, Point pt, int w) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (sgn(cross(pt, p[mid], p[mid + 1])) * w >= 0) r = mid;
        else l = mid + 1;
    }
    return l;
}
// w = 1:  二分查找第一个大于等于 x 对应的点
// w = -1: 二分查找第一个小于等于 x 对应的点
int border(Polygon p, int l, int r, double x, int w) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (sgn(x - p[mid].x) * w <= 0) r = mid;
        else l = mid + 1;
    }
    return l;
}

// 使用该函数之前要判断点是否在凸包外
pair<int, int> pptangentpcon(Polygon p, int n, Point pt, int Rx) {
    int L, R, Mid;
    if (sgn(pt.x - p[0].x) < 0) {  // 情况一: 点在凸包的左边
        L = minslope(p, 0, Rx, pt, 1), R = minslope(p, Rx, n, pt, -1);
    } else if (sgn(pt.x - p[Rx].x) > 0) {  // 情况二: 点在凸包的右边
        L = minslope(p, 0, Rx, pt, -1), R = minslope(p, Rx, n, pt, 1);
    } else if (cross(pt, p[0], p[Rx]) > 0) { // 情况三: 点在凸包的上方
        Mid = border(p, Rx, n, pt.x, -1);
        L = Mid > Rx ? minslope(p, Rx, Mid-1, pt, -1) : Mid;
        R = minslope(p, Mid, n, pt, 1);
    } else {                              // 情况四: 点在凸包的下方
        Mid = border(p, 0, Rx, pt.x, 1);
        L = Mid > 0 ? minslope(p, 0, Mid - 1, pt, -1) : 0;
        R = minslope(p, Mid, Rx, pt, 1);
    }
    return {L, R}; // 返回找到的两个切点
}
} // 参考自 kuangbin 和 https://www.cnblogs.com/TanJI-C/p/16092786.html

using namespace ComputationGeometry;

double x, y, vx, vy, h;
double r;
int n;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(2);
    Polygon p;
    while (cin >> x >> y >> h) {
        cin >> vx >> vy >> r;
        cin >> n;
        p.n = 0;
        for (int i = 0; i < n; i++) {
            double nx, ny;
            cin >> nx >> ny;
            p.append(Point(nx, ny));
        }
        double t = sqrt(2 * h / 10);
        x += vx * t, y += vy * t;
        Circle c(Point(x, y), r);
        cout << p.area_circle(c) << "\n";
    }
    return 0;
}
