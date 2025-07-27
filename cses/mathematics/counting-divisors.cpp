// https://cses.fi/problemset/task/1713

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

void init() {
    for (int i = 1; i < K; i++) {
        for (int j = i; j < K; j += i) {
            divisor[j]++;
        }
    }
}

int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        printf("%d\n", divisor[x]);
    }
}