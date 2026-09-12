// https://cses.fi/problemset/task/2420/

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
int n, q;
char s[N];

const ll MOD = 1e9 + 7;
const int p = 37;
ll pw[N];
ll inv[N];
ll ft[4 * N];
ll bt[4 * N];

void pull(ll* t, int p) { t[p] = (t[2 * p] + t[2 * p + 1]) % MOD; }

void build(int p, int l, int r) {
  if (l == r) {
    ft[p] = (ll)(s[l] - 'a') * pw[l - 1] % MOD;
    bt[p] = (ll)(s[n + 1 - l] - 'a') * pw[l - 1] % MOD;
    return;
  }
  int mid = l + (r - l) / 2;
  build(2 * p, l, mid);
  build(2 * p + 1, mid + 1, r);
  pull(ft, p);
  pull(bt, p);
}

void update(ll* t, int p, int l, int r, int i, char x) {
  if (l == r) {
    t[p] = (ll)(x - 'a') * pw[i - 1] % MOD;
    return;
  }
  int mid = l + (r - l) / 2;
  if (i <= mid) {
    update(t, 2 * p, l, mid, i, x);
  } else {
    update(t, 2 * p + 1, mid + 1, r, i, x);
  }
  pull(t, p);
}

ll query(ll* t, int p, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    return t[p];
  }
  int mid = l + (r - l) / 2;
  ll ans = 0;
  if (L <= mid) {
    ans += query(t, 2 * p, l, mid, L, R);
    ans %= MOD;
  }
  if (R > mid) {
    ans += query(t, 2 * p + 1, mid + 1, r, L, R);
    ans %= MOD;
  }
  return ans;
}

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

void init() {
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = pw[i - 1] * p % MOD;
  }
  inv[N - 1] = exp(pw[N - 1], MOD - 2);
  for (int i = N - 2; i >= 0; i--) {
    inv[i] = inv[i + 1] * p % MOD;
  }
}

bool is_palindrome(int a, int b) {
  ll fh = query(ft, 1, 1, n, a, b);
  fh = fh * inv[a - 1] % MOD;
  ll bh = query(bt, 1, 1, n, n + 1 - b, n + 1 - a);
  bh = bh * inv[n - b] % MOD;
  return fh == bh;
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf(" %c", &s[i]);
  }
  init();
  build(1, 1, n);
  while (q--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int k;
      char x;
      scanf("%d %c", &k, &x);
      update(ft, 1, 1, n, k, x);
      update(bt, 1, 1, n, n + 1 - k, x);
    } else {
      int a, b;
      scanf("%d %d", &a, &b);
      if (is_palindrome(a, b)) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
  }
}
