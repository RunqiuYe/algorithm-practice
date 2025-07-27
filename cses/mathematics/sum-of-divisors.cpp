// https://cses.fi/problemset/task/1082

#include <algorithm>
#include <array>
#include <bit>
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

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

ll f(ll x) { return ((x % MOD) * ((x + 1) % MOD) / 2) % MOD; }

int main() {
    ll n;
    scanf("%lld", &n);

    ll res = 0;
    for (ll l = 1; l <= n; l++) {
        ll k = n / l;
        ll r = n / k;
        res += (k % MOD) * ((f(r) - f(l - 1) + MOD) % MOD) % MOD;
        res %= MOD;
        l = r;
    }
    printf("%lld\n", res);
}