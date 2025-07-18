// https://cses.fi/problemset/task/1753

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

const int N = 1e6 + 5;
const ll MOD = 1e9 + 7;
const int P = 3;
const vector<int> primes = {31, 37, 43};
ll s_hash[P];
ll t_hash[P];
ll power[P][N];

bool hash_equal() {
    for (int p = 0; p < P; p++) {
        if (s_hash[p] != t_hash[p]) {
            return false;
        }
    }
    return true;
}

int main() {
    string s, t;
    getline(cin, s);
    getline(cin, t);
    int n = s.length();
    int m = t.length();
    int res = 0;

    if (m > n) {
        printf("0\n");
        return 0;
    }

    for (int p = 0; p < P; p++) {
        power[p][0] = 1;
        for (int i = 1; i <= m; i++) {
            power[p][i] = power[p][i - 1] * primes[p];
            power[p][i] %= MOD;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int p = 0; p < P; p++) {
            s_hash[p] += (s[i] - 'a' + 1) * power[p][m - i - 1] % MOD;
            s_hash[p] %= MOD;
            t_hash[p] += (t[i] - 'a' + 1) * power[p][m - i - 1] % MOD;
            t_hash[p] %= MOD;
        }
    }

    if (hash_equal()) res++;
    for (int i = m; i < n; i++) {
        for (int p = 0; p < P; p++) {
            s_hash[p] *= primes[p];
            s_hash[p] %= MOD;
            s_hash[p] -= (s[i - m] - 'a' + 1) * power[p][m] % MOD;
            s_hash[p] += MOD;
            s_hash[p] %= MOD;
            s_hash[p] += s[i] - 'a' + 1;
            s_hash[p] %= MOD;
        }
        if (hash_equal()) res++;
    }
    printf("%d\n", res);
}