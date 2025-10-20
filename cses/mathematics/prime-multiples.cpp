// https://cses.fi/problemset/task/2185

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

const int K = 25;

ll n;
int k;
ll a[K];

int main() {
    scanf("%lld %d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%lld", &a[i]);
    }
    double log_n = log(n) + 0.001;
    ll res = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        bool odd = (__builtin_popcount(mask) & 1);
        ll prod = 1;
        double log_prod = 0.0;
        for (int i = 0; i < k; i++) {
            if ((mask >> i) & 1) {
                prod *= a[i];
                log_prod += log(a[i]);
            }
        }
        if (log_prod < log_n) {
            res += (odd ? 1 : -1) * (n / prod);
        }
    }
    printf("%lld\n", res);
}