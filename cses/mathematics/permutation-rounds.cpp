// https://cses.fi/problemset/task/3398/

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
const ll MOD = 1e9 + 7;

int perm[N];
bool vis[N];

vector<int> cyc_len;
set<int> cyc;
vector<map<int, int>> factors;

int n;

ll exp(ll b, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) {
      res = res * b % MOD;
    }
    e >>= 1;
    b = b * b % MOD;
  }
  return res;
}

void dfs(int x) {
  if (cyc.find(x) != cyc.end()) {
    cyc_len.push_back(cyc.size());
    cyc = {};
    return;
  }
  vis[x] = true;
  cyc.insert(x);
  dfs(perm[x]);
}

void factorize() {
  for (auto x : cyc_len) {
    map<int, int> f;
    int p = 2;
    while (p < x) {
      while (x % p == 0) {
        f[p]++;
        x /= p;
      }
      p++;
    }
    if (x > 1) {
      f[x]++;
    }
    factors.push_back(f);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &perm[i]);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }
  factorize();
  map<int, int> mp = factors[0];
  map<int, int> mp2;
  for (int j = 1; j < factors.size(); j++) {
    for (auto& [f, cnt] : mp) {
      mp2[f] = max(cnt, factors[j][f]);
    }
    for (auto& [f, cnt] : factors[j]) {
      mp2[f] = max(cnt, mp2[f]);
    }
    swap(mp, mp2);
  }
  ll res = 1;
  for (auto& [f, cnt] : mp) {
    res *= exp(f, cnt);
    res %= MOD;
  }
  printf("%lld\n", res);
}