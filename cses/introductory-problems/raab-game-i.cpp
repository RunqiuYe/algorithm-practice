// https://cses.fi/problemset/task/3399

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

int n;
int score_a, score_b;

const int N = 105;
int a[N];
int b[N];

void solve() {
  scanf("%d %d %d", &n, &score_a, &score_b);
  if (score_a + score_b > n) {
    printf("NO\n");
    return;
  }
  if ((score_a == 0) != (score_b == 0)) {
    printf("NO\n");
    return;
  }
  int draw = n - score_a - score_b;
  int cnt = 1;
  for (; cnt <= draw; cnt++) {
    a[cnt] = cnt;
    b[cnt] = cnt;
  }
  int j = n + 1 - score_a;
  for (int i = 0; i < score_a; i++) {
    a[cnt] = j + i;
    b[cnt] = draw + 1 + i;
    cnt++;
  }
  j = n + 1 - score_b;
  for (int i = 0; i < score_b; i++) {
    a[cnt] = draw + 1 + i;
    b[cnt] = j + i;
    cnt++;
  }
  printf("YES\n");
  for (int i = 1; i <= n; i++) {
    printf("%d%c", a[i], " \n"[i == n]);
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", b[i], " \n"[i == n]);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
