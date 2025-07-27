// https://cses.fi/problemset/task/1081

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

const int K = 1e6 + 1;
int divisor[K];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        divisor[x]++;
    }
    for (int j = K - 1; j >= 1; j--) {
        int cnt = 0;
        for (int i = j; i < K; i += j) {
            cnt += divisor[i];
        }
        if (cnt > 1) {
            printf("%d\n", j);
            return 0;
        }
    }
}