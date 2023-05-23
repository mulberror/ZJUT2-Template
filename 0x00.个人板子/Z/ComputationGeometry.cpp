#include <bits/stdc++.h>

using i64 = long long;

struct point {
    double x, y;
    point(double a, double b) : x(a), y(b) {}

    point turn(double k) { // 点绕原点逆时针旋转k 
        return point(std::cos(k) * x - std::sin(k) * y, std::cos(k) * y + std::sin(k) * x); 
    }
};
point operator+(point a, point b) {
    return point(a.x + b.x, a.y + b.y); 
}
point operator-(point a, point b) {
    return point(a.x - b.x, a.y - b.y); 
}
point operator/(point a, double k) { 
    return point(a.x / k, a.y / k); 
}

double dot(point a, point b) {  //点积
    return a.x * b.x + a.y * b.y; 
}
double cross(point a, point b) { //叉积
    return a.x * b.y - a.y * b.x; 
} 

int main() {
    return 0; 
}