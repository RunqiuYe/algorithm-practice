// https://cses.fi/problemset/task/2182

#include <algorithm>
#include <array>
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

const int N = 1e5 + 5;
int n;
ll x, k;

ll primes[N];
ll exps[N];
ll prefix[N];
ll suffix[N];

const ll MOD = 1e9 + 7;

ll pow(ll x, ll k) {
    k %= MOD - 1;
    x %= MOD;

    ll res = 1;
    while (k > 0) {
        if (k & 1) {
            res *= x;
            res %= MOD;
        }
        k >>= 1;
        x *= x;
        x %= MOD;
    }
    return res;
}

ll f(ll x) { return x * (x + 1) / 2; }

int main() {
    scanf("%d", &n);

    ll cnt = 1;
    ll sum = 1;
    ll prod = 1;

    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &primes[i], &exps[i]);
    }
    prefix[0] = prefix[n + 1] = 1;
    suffix[n + 1] = suffix[0] = 1;
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] * (exps[i] + 1) % (MOD - 1);
        suffix[n + 1 - i] =
            suffix[n + 2 - i] * (exps[n + 1 - i] + 1) % (MOD - 1);
    }

    for (int i = 1; i <= n; i++) {
        ll x = primes[i];
        ll k = exps[i];

        cnt *= k + 1;
        cnt %= MOD;

        sum *= (pow(x, k + 1) - 1) * pow(x - 1, MOD - 2) % MOD;
        sum %= MOD;

        prod *= pow(pow(x, f(k)), prefix[i - 1] * suffix[i + 1] % (MOD - 1));
        prod %= MOD;
    }
    printf("%lld %lld %lld\n", cnt, sum, prod);
}
