// https://cses.fi/problemset/task/1722/

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

const ll MOD = 1e9 + 7;

struct Mat2 {
  ll a, b, c, d;

  Mat2 matmul(const Mat2& other) {
    ll a1 = (a * other.a % MOD + b * other.c % MOD) % MOD;
    ll b1 = (a * other.b % MOD + b * other.d % MOD) % MOD;
    ll c1 = (c * other.a % MOD + d * other.c % MOD) % MOD;
    ll d1 = (c * other.b % MOD + d * other.d % MOD) % MOD;

    return {a1, b1, c1, d1};
  }
};

Mat2 matexp(Mat2 m, ll e) {
  Mat2 res = {1, 0, 0, 1};
  while (e > 0) {
    if (e & 1) {
      res = res.matmul(m);
    }
    m = m.matmul(m);
    e >>= 1;
  }
  return res;
}

ll n;

int main() {
  scanf("%lld", &n);
  Mat2 a = {0, 1, 1, 1};
  a = matexp(a, n);
  printf("%lld\n", a.b);
}