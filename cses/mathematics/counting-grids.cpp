// https://cses.fi/problemset/task/2210

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

int n;

ll exp(ll b, ll e) {
  e %= MOD - 1;
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
int main() {
  scanf("%d", &n);
  ll s;
  if (n % 2 == 0) {
    s = (ll)(n / 2) * (n / 2);
  } else {
    s = (ll)(n / 2) * (n / 2 + 1);
  }
  ll res = 2 * exp(2, s + (n % 2)) % MOD;
  res += exp(2, 2 * s + (n % 2));
  res %= MOD;
  res += exp(2, (ll)n * n);
  res %= MOD;
  res *= exp(4, MOD - 2);
  res %= MOD;
  printf("%lld\n", res);
}