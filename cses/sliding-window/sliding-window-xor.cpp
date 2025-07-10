// https://cses.fi/problemset/task/3426

#include <cstring>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

int n, k;
ll x, a, b, c;

int main() {
    scanf("%d %d", &n, &k);
    scanf("%lld %lld %lld %lld", &x, &a, &b, &c);
    int hi = 1;
    ll s = 0;
    ll y = x;

    for (; hi < k; hi++) {
        s ^= x;
        x = (a * x + b) % c;
    }
    ll res = 0LL;
    for (; hi <= n; hi++) {
        s ^= x;
        res ^= s;
        s ^= y;
        x = (a * x + b) % c;
        y = (a * y + b) % c;
    }
    printf("%lld\n", res);
}
