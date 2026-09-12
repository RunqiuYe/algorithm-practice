// https://cses.fi/problemset/task/3138/

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

const int N = 2e5 + 5;
string s;
int n;

const ll MOD = 1e9 + 7;
const int p = 37;
ll pw[N];
ll fh[N];
ll bh[N];

int d1[N];
int d2[N];
vector<int> cd[N][2];
int res[N];

void init() {
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = pw[i - 1] * p % MOD;
  }
}

ll fh_substr(int i, int j) {
  return (fh[j] + MOD - fh[i - 1] * pw[j - i + 1] % MOD) % MOD;
}

ll bh_substr(int i, int j) {
  return (bh[n + 1 - i] + MOD - bh[n - j] * pw[j - i + 1] % MOD) % MOD;
}

int main() {
  getline(cin, s);
  n = s.size();
  init();
  for (int i = 1; i <= n; i++) {
    int j = n + 1 - i;
    fh[i] = (fh[i - 1] * p % MOD + (s[i - 1] - 'a')) % MOD;
    bh[i] = (bh[i - 1] * p % MOD + (s[j - 1] - 'a')) % MOD;
  }

  for (int i = 1; i <= n; i++) {
    int lo = 0;
    int hi = min(n - i, i - 1) + 1;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      int start_idx = i - mid;
      int end_idx = i + mid;

      ll f = fh_substr(start_idx, end_idx);
      ll b = bh_substr(start_idx, end_idx);
      if (f == b) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    d1[i] = lo - 1;
  }
  for (int i = 2; i <= n; i++) {
    int lo = 1;
    int hi = min(n + 1 - i, i - 1) + 1;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      int start_idx = i - mid;
      int end_idx = i + mid - 1;
      ll f = fh_substr(start_idx, end_idx);
      ll b = bh_substr(start_idx, end_idx);
      if (f == b) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    d2[i] = lo - 1;
  }

  set<int> center[2];
  for (int i = 1; i <= n; i++) {
    res[i] = 1;
    center[0].insert(i);
    cd[i + d1[i] + 1][0].push_back(i);

    if (d2[i] != 0) {
      center[1].insert(i);
      cd[i + d2[i]][1].push_back(i);
    }

    for (auto j : cd[i][0]) {
      center[0].erase(j);
    }
    for (auto j : cd[i][1]) {
      center[1].erase(j);
    }

    if (!center[0].empty()) {
      int c = *center[0].begin();
      res[i] = max(res[i], 2 * (i - c) + 1);
    }
    if (!center[1].empty()) {
      int c = *center[1].begin();
      res[i] = max(res[i], 2 * (i - c + 1));
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", res[i], " \n"[i == n]);
  }
}
