// https://cses.fi/problemset/task/2105

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

int sa[N];
int rk[2 * N];
int old_rk[2 * N];

int lcp[N];

char s[N];
int n;

int main() {
    scanf("%s", s + 1);  // 1-index for string
    n = strlen(s + 1);

    // calculate suffix array
    for (int i = 1; i <= n; i++) {
        sa[i] = i;
        rk[i] = s[i];
    }
    for (int w = 1; w < n; w *= 2) {
        sort(sa + 1, sa + n + 1, [w](int x, int y) {
            return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        });
        memcpy(old_rk, rk, sizeof(rk));
        // remove duplicate in rank
        int p = 1;
        rk[sa[1]] = 1;
        for (int i = 2; i <= n; i++) {
            if (old_rk[sa[i]] == old_rk[sa[i - 1]] &&
                old_rk[sa[i] + w] == old_rk[sa[i - 1] + w]) {
                rk[sa[i]] = p;
            } else {
                p++;
                rk[sa[i]] = p;
            }
        }
    }
    // calculate LCP array
    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (rk[i] == n) continue;
        if (k != 0) {
            k--;
        }
        while (s[i + k] == s[sa[rk[i] + 1] + k]) {
            k++;
        }
        lcp[rk[i]] = k;
    }
    // calculate answer
    ll res = (ll)n * (n + 1) / 2;
    for (int i = 1; i < n; i++) {
        res -= lcp[i];
    }
    printf("%lld\n", res);
}