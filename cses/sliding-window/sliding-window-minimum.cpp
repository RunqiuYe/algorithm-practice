// https://cses.fi/problemset/task/3221

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>

typedef long long ll;

using namespace std;

int n, k;
ll x, a, b, c;

int main() {
    scanf("%d %d", &n, &k);
    scanf("%lld %lld %lld %lld", &x, &a, &b, &c);
    deque<pair<ll, int>> window = {};

    for (int i = 1; i < k; i++) {
        while (window.size() != 0 && window[window.size() - 1].first >= x) {
            window.pop_back();
        }
        window.push_back({x, i});
        x = (a * x + b) % c;
    }
    ll res = 0LL;
    for (int i = k; i <= n; i++) {
        while (window.size() != 0 && window[window.size() - 1].first >= x) {
            window.pop_back();
        }
        window.push_back({x, i});

        res ^= window[0].first;
        if (window[0].second <= i - k + 1) {
            window.pop_front();
        }
        x = (a * x + b) % c;
    }
    printf("%lld\n", res);
}