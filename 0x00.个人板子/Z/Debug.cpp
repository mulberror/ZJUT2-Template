#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

string debugToString(const int& v) { return to_string(v); }
string debugToString(const long long& v) { return to_string(v); }
string debugTostring(char ch) { return to_string(ch); }
string debugToString(const unsigned long long& v) { return to_string(v); }
string debugToString(const double& v) { return to_string(v); }
string debugToString(const long double& v) { return to_string(v); }
string debugToString(const string& s) { return s; }

string debugToString(char* s) {
  int n = strlen(s);
  string t;

  for (int i = 0; i < n; i++) {
    t += s[i];
  }
  return t;
}

template <typename T, typename U>
string debugToString(const pair<T, U>& s);

template <typename T>
string debugToString(vector<T> v) {
  string t = "[";

  for (int i = 0; i < int(v.size()); i++) {
    t += debugToString(v[i]) + ",]"[i == int(v.size()) - 1];
  }
  return t;
}

template <typename T, typename U>
string debugToString(const pair<T, U>& s) {
  return "{" + debugToString(s.first) + "," + debugToString(s.second) + "}";
}

// output
template <typename T>
string debugToStrings(const T& s) {
  return debugToString(s);
}

template <typename T, typename... U>
string debugToStrings(const T& s, const U&... t) {
  return debugToString(s) + "," + debugToStrings(t...);
}

template <typename T, typename... U>
void debug(T s, U... t) {
  cerr << "debug:" << debugToStrings(s, t...) << "\n";
}

template <typename T>
void debug(T s) {
  cerr << "debug:" << debugToString(s) << "\n";
}

int main() {
  int b = 6;
  double c = 6.7;
  pair<vector<int>, vector<double>> a;
  a.first.resize(5), a.second.resize(3);
  iota(a.first.begin(), a.first.end(), 3);
  for (auto& it : a.second) {
    it = 3.1415926;
  }
  return 0;
}