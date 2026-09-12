// https://cses.fi/problemset/task/1112/

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

const int N = 1005;
const int M = 105;
const int K = 30;
const int MOD = 1e9 + 7;

int n;
int m;
string pattern;

int pi[M];
int aut[M][K];
int dp[N][M];

ll exp(ll b, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) {
      res = res * b % MOD;
    }
    b = b * b % MOD;
    e >>= 1;
  }
  return res;
}

int main() {
  cin >> n;
  getline(cin >> ws, pattern);
  m = pattern.size();

  for (int i = 1; i < m; i++) {
    int j = pi[i - 1];
    while (j > 0 && pattern[i] != pattern[j]) {
      j = pi[j - 1];
    }
    pi[i] = (pattern[i] == pattern[j]) ? j + 1 : 0;
  }
  for (int i = 0; i <= m; i++) {
    for (char c = 'A'; c <= 'Z'; c++) {
      int k = c - 'A';
      if (i < m && pattern[i] == c) {
        aut[i][k] = i + 1;
      } else if (i == 0) {
        aut[i][k] = 0;
      } else {
        aut[i][k] = aut[pi[i - 1]][k];
      }
    }
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k < 26; k++) {
      for (int j = 0; j < m; j++) {
        dp[i][aut[j][k]] += dp[i - 1][j];
        dp[i][aut[j][k]] %= MOD;
      }
    }
  }
  int res = 0;
  for (int j = 0; j < m; j++) {
    res = (res + dp[n][j]) % MOD;
  }
  printf("%lld\n", (exp(26, n) + MOD - res) % MOD);
}