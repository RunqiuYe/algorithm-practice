// https://cses.fi/problemset/task/2422/

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

ll n;

bool check(ll mid, ll target) {
  ll cnt = 0;
  for (int i = 1; i <= n; i++) {
    cnt += min(n, mid / i);
    if (cnt >= target) {
      return true;
    }
  }
  return false;
}

int main() {
  scanf("%lld", &n);
  ll target = (n * n + 1) / 2;

  ll lo = 1;
  ll hi = n * n;
  while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    if (check(mid, target)) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  printf("%lld\n", lo);
}