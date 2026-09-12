// https://cses.fi/problemset/task/1149/

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

const int N = 5e5 + 5;
const int MOD = 1e9 + 7;

string s;
int n;
int dp[N];
int prev_idx[N];

int main() {
  getline(cin, s);
  n = s.size();
  fill(prev_idx, prev_idx + n, -1);

  map<char, int> mp;
  for (int i = 0; i < n; i++) {
    char c = s[i];
    if (mp.find(c) != mp.end()) {
      prev_idx[i] = mp[c];
    }
    mp[c] = i;
  }

  dp[1] = 1;
  for (int i = 1; i < n; i++) {
    dp[i + 1] = dp[i];
    if (prev_idx[i] == -1) {
      dp[i + 1] += dp[i] + 1;
      dp[i + 1] %= MOD;
    } else {
      int j = prev_idx[i];
      dp[i + 1] += (dp[i] + MOD - dp[j]) % MOD;
      dp[i + 1] %= MOD;
    }
  }
  printf("%d\n", dp[n]);
}