// https://cses.fi/problemset/task/3311

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

const int N = 505;

int grid[N][N];
int res[N][N];
int m, n;

int main() {
  scanf("%d %d", &m, &n);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      scanf(" %c", &c);
      grid[i][j] = c - 'A';
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      bool vis[4];
      fill(vis, vis + 4, false);
      vis[res[i - 1][j]] = true;
      vis[res[i][j - 1]] = true;
      vis[grid[i][j]] = true;
      for (int p = 0; p < 4; p++) {
        if (!vis[p]) {
          res[i][j] = p;
          break;
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      printf("%c", res[i][j] + 'A');
    }
    printf("\n");
  }
}