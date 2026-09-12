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

const int N = 1e5 + 5;

string s;
int n;

int sa[N];
int rk[2 * N];
int old_rk[2 * N];
int lca[N];

int main() {
  getline(cin, s);
  n = s.size();

  for (int i = 0; i < n; i++) {
    rk[i + 1] = s[i] - 'a' + 1;
    sa[i + 1] = i + 1;
  }
  for (int w = 1; w < n; w *= 2) {
    sort(sa + 1, sa + 1 + n, [w](int i, int j) {
      return rk[i] == rk[j] ? rk[i + w] < rk[j + w] : rk[i] < rk[j];
    });
    memcpy(old_rk, rk, sizeof(rk));
    int p = 1;
    rk[sa[1]] = 1;
    for (int i = 2; i <= n; i++) {
      if (old_rk[sa[i]] == old_rk[sa[i - 1]]
          && old_rk[sa[i] + w] == old_rk[sa[i - 1] + w]) {
        rk[sa[i]] = p;
      } else {
        p++;
        rk[sa[i]] = p;
      }
    }
  }
  int k = 0;
  for (int i = 1; i <= n; i++) {
    if (rk[i] == n) {
      continue;
    }
    if (k != 0) {
      k--;
    }
    while (s[i + k - 1] == s[sa[rk[i] + 1] + k - 1]) {
      k++;
    }
    lca[rk[i]] = k;
  }
  int max_lca = 0;
  int p = 0;
  for (int i = 1; i < n; i++) {
    if (lca[i] > max_lca) {
      max_lca = lca[i];
      p = i;
    }
  }
  if (max_lca == 0) {
    cout << -1 << endl;
    return 0;
  }
  cout << s.substr(sa[p] - 1, max_lca) << endl;
}