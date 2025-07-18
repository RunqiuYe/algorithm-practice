// https://cses.fi/problemset/task/1733

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
const int MOD = 1e9 + 7;
const int P = 2;
vector<int> primes = {31, 37};
ll hash_value[P][N];
ll power[P][N];
ll v[P];

string s;
int n;

int main() {
    getline(cin, s);
    n = s.length();

    for (int p = 0; p < P; p++) {
        power[p][0] = 1;
        for (int i = 1; i < n; i++) {
            power[p][i] = power[p][i - 1] * primes[p];
            power[p][i] %= MOD;
        }
    }
    for (int p = 0; p < P; p++) {
        hash_value[p][0] = s[0] - 'a' + 1;
    }
    for (int i = 1; i < n; i++) {
        for (int p = 0; p < P; p++) {
            hash_value[p][i] = hash_value[p][i - 1] * primes[p];
            hash_value[p][i] %= MOD;
            hash_value[p][i] += s[i] - 'a' + 1;
            hash_value[p][i] %= MOD;
        }
    }

    vector<int> res;
    for (int len = 1; len <= n; len++) {
        for (int p = 0; p < P; p++) {
            v[p] = 0;
        }
        for (int i = 1; i < n / len + 1; i++) {
            for (int p = 0; p < P; p++) {
                v[p] *= power[p][len];
                v[p] %= MOD;
                v[p] += hash_value[p][len - 1];
                v[p] %= MOD;
            }
        }

        if (n % len != 0) {
            for (int p = 0; p < P; p++) {
                v[p] *= power[p][n % len];
                v[p] %= MOD;
                v[p] += hash_value[p][n % len - 1];
                v[p] %= MOD;
            }
        }
        bool flag = true;
        for (int p = 0; p < P; p++) {
            if (v[p] != hash_value[p][n - 1]) {
                flag = false;
                break;
            }
        }
        if (flag) res.push_back(len);
    }
    for (int len : res) {
        printf("%d ", len);
    }
    printf("\n");
}