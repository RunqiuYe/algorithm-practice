// https://cses.fi/problemset/task/1095

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

const int MOD = 1e9 + 7;
int n;

ll solve(ll a, ll b) {
    ll res = 1;
    ll cur = a;
    while (b > 0) {
        if (b & 1) {
            res *= cur;
            res %= MOD;
        }
        cur *= cur;
        cur %= MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", solve(a, b));
    }
}