// https://cses.fi/problemset/task/1739/

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

struct Query {
  int diff;
  int y1;
  int x1;
  int y2;
  int x2;
};

const int N = 1005;
int grid[N][N];
int prefix[N][N];
int tree[4 * N];

const int Q = 2e5 + 5;
Query qs[Q];
int res[Q];

int n, q;

void update(int p, int l, int r, int i, int x) {
  if (l == r) {
    tree[p] += x;
    return;
  }
  int mid = l + (r - l) / 2;
  if (i <= mid) {
    update(2 * p, l, mid, i, x);
  } else {
    update(2 * p + 1, mid + 1, r, i, x);
  }
  tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int query(int p, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    return tree[p];
  }
  int mid = l + (r - l) / 2;
  int res = 0;
  if (L <= mid) {
    res += query(2 * p, l, mid, L, R);
  }
  if (R > mid) {
    res += query(2 * p + 1, mid + 1, r, L, R);
  }
  return res;
}

void solve(int lo, int hi) {
  if (lo == hi) {
    return;
  }
  int mid = lo + (hi - lo) / 2;
  solve(lo, mid);
  solve(mid + 1, hi);

  vector<int> updates;
  vector<pair<int, int>> qleft;  // (endpoint, query_idx)
  vector<pair<int, int>> qright; // (endpoint, query_idx)
  for (int i = lo; i <= mid; i++) {
    if (qs[i].diff != 0) {
      updates.push_back(i);
    }
  }
  for (int i = mid + 1; i <= hi; i++) {
    auto& q = qs[i];
    if (q.diff == 0) {
      if (q.x1 != 1) {
        qleft.push_back({q.x1 - 1, i});
      }
      qright.push_back({q.x2, i});
    }
  }
  sort(updates.begin(), updates.end(),
       [](int upd1, int upd2) { return qs[upd1].x1 < qs[upd2].x1; });
  sort(qleft.begin(), qleft.end());
  sort(qright.begin(), qright.end());

  if (updates.empty()) {
    return;
  }

  int ql_idx = 0;
  int qr_idx = 0;
  for (int upd_idx : updates) {
    auto& upd = qs[upd_idx];
    for (; ql_idx < qleft.size() && qleft[ql_idx].first < upd.x1; ql_idx++) {
      int q_idx = qleft[ql_idx].second;
      auto& q = qs[q_idx];
      int top = q.y1;
      int bot = q.y2;
      res[q_idx] -= query(1, 1, n, top, bot);
    }
    for (; qr_idx < qright.size() && qright[qr_idx].first < upd.x1; qr_idx++) {
      int q_idx = qright[qr_idx].second;
      auto& q = qs[q_idx];
      int top = q.y1;
      int bot = q.y2;
      res[q_idx] += query(1, 1, n, top, bot);
    }
    update(1, 1, n, upd.y1, upd.diff);
  }

  for (; ql_idx < qleft.size(); ql_idx++) {
    int q_idx = qleft[ql_idx].second;
    auto& q = qs[q_idx];
    int top = q.y1;
    int bot = q.y2;
    res[q_idx] -= query(1, 1, n, top, bot);
  }
  for (; qr_idx < qright.size(); qr_idx++) {
    int q_idx = qright[qr_idx].second;
    auto& q = qs[q_idx];
    int top = q.y1;
    int bot = q.y2;
    res[q_idx] += query(1, 1, n, top, bot);
  }
  for (int upd_idx : updates) {
    auto& upd = qs[upd_idx];
    update(1, 1, n, upd.y1, -upd.diff);
  }
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      scanf(" %c", &c);
      if (c == '*') {
        grid[i][j] = 1;
      } else {
        grid[i][j] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      prefix[i][j] = prefix[i][j - 1] + grid[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      prefix[i][j] += prefix[i - 1][j];
    }
  }
  for (int i = 1; i <= q; i++) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int y, x;
      scanf("%d %d", &y, &x);
      if (grid[y][x] == 0) {
        qs[i] = {1, y, x, 0, 0};
        grid[y][x] = 1;
      } else {
        qs[i] = {-1, y, x, 0, 0};
        grid[y][x] = 0;
      }
    } else {
      int y1, x1, y2, x2;
      scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
      qs[i] = {0, y1, x1, y2, x2};
    }
  }
  for (int i = 1; i <= q; i++) {
    auto& q = qs[i];
    if (q.diff == 0) {
      res[i] = prefix[q.y2][q.x2] - prefix[q.y2][q.x1 - 1]
               - prefix[q.y1 - 1][q.x2] + prefix[q.y1 - 1][q.x1 - 1];
    }
  }

  // CDQ divide and conquer
  solve(1, q);
  // output result
  for (int i = 1; i <= q; i++) {
    auto& q = qs[i];
    if (q.diff == 0) {
      printf("%d\n", res[i]);
    }
  }
}