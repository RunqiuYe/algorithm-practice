// https://cses.fi/problemset/task/2417

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

const int X = 1e6 + 5;

int n;
ll res = 0;
bool is_prime[X];
vector<int> primes;
int dp[X];  // dp[x] is the number of previously seen numbers divisible by x

void sieve() {
    fill(is_prime + 2, is_prime + X, true);
    for (int i = 2; i * i < X; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < X; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i < X; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

// count the number of previously seen numbers that are comprime with x
void solve(int x) {
    vector<int> prime_factors;
    for (int p : primes) {
        if (x == 1) break;
        if (is_prime[x]) {
            prime_factors.push_back(x);
            break;
        }
        if (x % p == 0) {
            prime_factors.push_back(p);
            while (x % p == 0) {
                x /= p;
            }
        }
    }

    int k = prime_factors.size();
    for (int mask = 1; mask < (1 << k); mask++) {
        int factor = 1;
        for (int i = 0; i < k; i++) {
            if ((mask >> i) & 1) {
                factor *= prime_factors[i];
            }
        }
        bool odd = (__builtin_popcount(mask) & 1);
        res += (odd ? -dp[factor] : dp[factor]);
        dp[factor]++;
    }
}

int main() {
    sieve();
    scanf("%d", &n);
    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        res += i;
        solve(x);
    }
    printf("%lld\n", res);
}