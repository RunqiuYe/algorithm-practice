// https://cses.fi/problemset/task/2209/

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

const int N = 1e6 + 5;
const ll MOD = 1e9 + 7;

int n, m;
ll pw[N];

ll exp(ll b, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) {
      res *= b;
      res %= MOD;
    }
    b = b * b % MOD;
    e >>= 1;
  }
  return res;
}

int gcd(int x, int y) {
  if (y == 0) {
    return x;
  }
  return gcd(y, x % y);
}

int main() {
  scanf("%d %d", &n, &m);
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = pw[i - 1] * m % MOD;
  }
  ll res = 0;
  for (int i = 1; i <= n; i++) {
    int g = gcd(i, n);
    res = (res + pw[g]) % MOD;
  }
  res *= exp(n, MOD - 2);
  res %= MOD;
  printf("%lld\n", res);
}