// https://cses.fi/problemset/task/2064

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

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int n;
ll fact[N];
ll inv_fact[N];

ll power(ll b, ll e) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res *= b;
            res %= MOD;
        }
        b *= b;
        b %= MOD;
        e >>= 1;
    }
    return res;
}

void init() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[N - 1] = power(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

int main() {
    init();
    scanf("%d", &n);
    if (n % 2 != 0) {
        printf("0\n");
        return 0;
    }
    int m = n / 2;
    ll res = ((fact[2 * m] * inv_fact[m]) % MOD * inv_fact[m]) % MOD;
    res -= ((fact[2 * m] * inv_fact[m - 1] % MOD) * inv_fact[m + 1]) % MOD;
    res = (res + MOD) % MOD;
    printf("%lld\n", res);
}