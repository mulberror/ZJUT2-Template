#include <bits/stdc++.h>

using i64 = long long;

using i64 = long long;

const int P = 998244353;

template<typename T> 
T power(T x, i64 y) {
  T res = 1;
  for (; y; y >>= 1, x *= x) {
    if (y & 1) { res *= x; }
  }
  return res;
}

struct M { // -P < x < 2 * P
private: 
  int fix(int x) {
    return x < 0 ? x + P : (x < P ? x : x -= P);
  }
  int norm(int x) {
    return fix(x < -P || x > P ? x %= P : x);
  }
  
  int v;

public:
  M() : v(0) {}
  M(int x) : v(norm(x)) {}

  int val() const { return v; }
  M operator-() const {
    return M(P - v); 
  }

  M inv() const { 
    assert(v != 0);
    return power(*this, P - 2); 
  }

  M &operator=(const int &rhs) {
    return v = norm(rhs), *this; 
  }
  M &operator+=(const M &rhs) {
    return v = fix(v + rhs.v), *this;
  }
  M &operator-=(const M &rhs) {
    return v = fix(v - rhs.v), *this;
  }
  M &operator*=(const M &rhs) {
    return v = i64(v) * rhs.v % P, *this;
  }
  M operator+(const M &rhs) {
    return M((*this).val()) += rhs;
  }
  M operator-(const M &rhs) {
    return M((*this).val()) -= rhs;
  }
  M operator*(const M &rhs) {
    return M((*this).val()) *= rhs;
  }
  M operator/(const M &rhs) {
    return M((*this).val()) /= rhs;
  }

  M &operator/=(const M &rhs) {
    return *this *= rhs.inv(), *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const M &rhs) {
    return os << rhs.val();
  }

  friend std::istream &operator>>(std::istream &is, M &rhs) {
    i64 x;;
    is >> x; 
    rhs = x; 
    return is; 
  }
};

struct Poly {
private:
    std::vector<M> a; 
    int n;

public:
};

int main() {
    return 0;
}