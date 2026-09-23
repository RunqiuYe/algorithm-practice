// https://cses.fi/problemset/task/1096

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

const ll MOD = 1e9 + 7;
const int N = 6;

struct Mat {
  ll data[N][N];

  Mat() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        data[i][j] = 0;
      }
    }
  }
};

Mat matmul(Mat a, Mat b) {
  Mat res;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        res.data[i][j] += a.data[i][k] * b.data[k][j] % MOD;
        res.data[i][j] %= MOD;
      }
    }
  }
  return res;
}

Mat matexp(Mat m, ll e) {
  Mat res;
  for (int i = 0; i < N; i++) {
    res.data[i][i] = 1;
  }
  while (e > 0) {
    if (e & 1) {
      res = matmul(res, m);
    }
    m = matmul(m, m);
    e >>= 1;
  }
  return res;
}

ll n;

int main() {
  scanf("%lld", &n);
  Mat a;
  for (int i = 0; i < N - 1; i++) {
    a.data[i][i + 1] = 1;
  }
  for (int i = 0; i < N; i++) {
    a.data[N - 1][i] = 1;
  }
  a = matexp(a, n);
  printf("%lld\n", a.data[N - 1][N - 1]);
}