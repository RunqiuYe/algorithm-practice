// https://cses.fi/problemset/task/3396

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

const int sqrtN = 1e6 + 5;

int t;
ll n;
bool is_prime[sqrtN];
vector<int> primes;

void sieve() {
    fill(is_prime + 2, is_prime + sqrtN, true);
    for (int i = 2; i * i < sqrtN; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < sqrtN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i < sqrtN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

bool test_prime(ll n) {
    if (n < sqrtN) {
        return is_prime[n];
    }
    int k = primes.size();
    for (int i = 0; i < k && (ll)primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    sieve();
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        n++;
        while (!test_prime(n)) {
            n++;
        }
        printf("%lld\n", n);
    }
}