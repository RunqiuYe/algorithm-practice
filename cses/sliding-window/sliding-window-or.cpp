// https://cses.fi/problemset/task/3405/

#include <algorithm>
#include <array>
#include <cmath>
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

typedef long long ll;

using namespace std;

const int N = 1e7 + 5;

int n, k;
ll x, a, b, c;

int table[N];

int main() {
    scanf(" %d %d", &n, &k);
    scanf(" %lld %lld %lld %lld", &x, &a, &b, &c);
    int logk = log2(k);
    int maxw = 1 << logk;
    table[1] = x;
    for (int i = 2; i <= n; i++) {
        ll num = ((a * (ll)table[i - 1]) % c + b) % c;
        table[i] = num;
    }

    for (int j = 1; j <= logk; j++) {
        int w = 1 << j;
        for (int i = 1; i <= n - w + 1; i++) {
            table[i] = table[i] | table[i + (w >> 1)];
        }
    }
    int res = 0;
    for (int i = 1; i <= n - k + 1; i++) {
        res ^= (table[i] | table[i + k - maxw]);
    }
    printf("%d\n", res);
}
