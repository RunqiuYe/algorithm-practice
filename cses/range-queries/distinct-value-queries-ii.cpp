// https://cses.fi/problemset/task/3356/

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

struct Segtree {
  int tree[4 * N];

  void clear(int p, int l, int r) {
    if (l == r) {
      tree[p] = 0;
      return;
    }
    int mid = l + (r - l) / 2;
    clear(2 * p, l, mid);
    clear(2 * p + 1, mid + 1, r);
    tree[p] = 0;
  }

  void update(int p, int l, int r, int i, int dx) {
    if (l == r) {
      tree[p] += dx;
      return;
    }
    int mid = l + (r - l) / 2;
    if (i <= mid) {
      update(2 * p, l, mid, i, dx);
    } else {
      update(2 * p + 1, mid + 1, r, i, dx);
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
};

Segtree tree;

int n, q;
int t = 0;
int positions[N];
int color[N];
int mod_color[N];
int pre[N];
int mod_pre[N];
map<int, set<int>> color_idx;

struct Update {
  int t;
  int diff;
  int pos;
  int pre;

  bool operator<(const Update& other) const { return pre < other.pre; }
};

struct Query {
  int t;
  int l;
  int r;
  int ans;

  bool operator<(const Query& other) const { return l < other.l; }
};

vector<Update> updates;
vector<Query> queries;

void change_pre(int pos, int new_pre) {
  if (mod_pre[pos] == new_pre) {
    return;
  }
  updates.push_back({t++, -1, pos, mod_pre[pos]});
  updates.push_back({t++, 1, pos, new_pre});
  mod_pre[pos] = new_pre;
}

void cdq(int upd_l, int upd_r, int qry_l, int qry_r, int time_l, int time_r) {
  if (upd_l == upd_r || qry_l == qry_r) {
    return;
  }
  int time_mid = time_l + (time_r - time_l) / 2;

  // find corresponding midpoint for updates and queries
  int upd_mid = upd_l;
  while (upd_mid < upd_r && updates[upd_mid].t < time_mid) {
    upd_mid++;
  }
  int qry_mid = qry_l;
  while (qry_mid < qry_r && queries[qry_mid].t < time_mid) {
    qry_mid++;
  }
  cdq(upd_l, upd_mid, qry_l, qry_mid, time_l, time_mid);
  cdq(upd_mid, upd_r, qry_mid, qry_r, time_mid, time_r);

  sort(updates.begin() + upd_l, updates.begin() + upd_mid);
  sort(queries.begin() + qry_mid, queries.begin() + qry_r);

  int updi = upd_l;
  for (int qi = qry_mid; qi < qry_r; qi++) {
    auto& q = queries[qi];
    for (; updi < upd_mid && updates[updi].pre < q.l; updi++) {
      auto& upd = updates[updi];
      tree.update(1, 1, n, upd.pos, upd.diff);
    }
    q.ans += tree.query(1, 1, n, q.l, q.r);
  }
  for (int j = upd_l; j < updi; j++) {
    auto& upd = updates[j];
    tree.update(1, 1, n, upd.pos, -upd.diff);
  }
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++) {
    positions[i] = i;
    scanf("%d", &color[i]);
    mod_color[i] = color[i];
    if (color_idx.find(color[i]) == color_idx.end()) {
      color_idx[color[i]] = {0};
    }
    auto& cidx = color_idx[color[i]];
    pre[i] = *(--cidx.end());
    mod_pre[i] = pre[i];
    cidx.insert(i);
  }
  for (int i = 1; i <= q; i++) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int k, u;
      scanf("%d %d", &k, &u);
      int old_color = mod_color[k];
      if (old_color == u) {
        continue;
      }

      // delete point correspond to old_color
      {
        auto& cidx = color_idx[old_color];
        auto iter = cidx.find(k);
        int pre_i = *prev(iter);
        auto next_iter = next(iter);
        if (next_iter != cidx.end()) {
          change_pre(*next_iter, pre_i);
        }
        cidx.erase(iter);
      }

      // add point correspond to new_color
      {
        auto& cidx = color_idx[u];
        if (cidx.empty()) {
          cidx.insert(0);
        }
        auto next_iter = cidx.lower_bound(k);
        int pre_i = *prev(next_iter);
        if (next_iter != cidx.end()) {
          change_pre(*next_iter, k);
        }
        change_pre(k, pre_i);
        cidx.insert(k);
        mod_color[k] = u;
      }
    } else {
      int a, b;
      scanf("%d %d", &a, &b);
      queries.push_back({t++, a, b, 0});
    }
  }

  // Answer queries with initial colors
  sort(positions + 1, positions + 1 + n,
       [](int i, int j) { return pre[i] < pre[j]; });
  sort(queries.begin(), queries.end());

  int pi = 1;
  for (auto& q : queries) {
    for (; pi <= n && pre[positions[pi]] < q.l; pi++) {
      tree.update(1, 1, n, positions[pi], 1);
    }
    q.ans = tree.query(1, 1, n, q.l, q.r);
  }

  // CDQ divide and conquer to calculate impact of updates
  tree.clear(1, 1, n);
  sort(queries.begin(), queries.end(),
       [](const Query& q1, const Query& q2) { return q1.t < q2.t; });
  cdq(0, updates.size(), 0, queries.size(), 0, t);
  sort(queries.begin(), queries.end(),
       [](const Query& q1, const Query& q2) { return q1.t < q2.t; });

  for (auto& q : queries) {
    if (q.ans == q.r - q.l + 1) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
