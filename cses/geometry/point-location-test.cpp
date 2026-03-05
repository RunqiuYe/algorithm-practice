// https://cses.fi/problemset/task/2189

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

int n;
int x, y, x2, y2, x3, y3;

ll cross(pair<ll, ll> p1, pair<ll, ll> p2) {
    return p1.first * p2.second - p1.second * p2.first;
}

int main() {
    scanf(" %d", &n);
    for (int i = 1; i <= n; i++) {
        scanf(" %d %d %d %d %d %d", &x, &y, &x2, &y2, &x3, &y3);
        pair<int, int> v1 = {x2 - x, y2 - y};
        pair<int, int> v2 = {x3 - x, y3 - y};
        ll c = cross(v1, v2);
        if (c < 0) {
            printf("RIGHT\n");
        } else if (c == 0) {
            printf("TOUCH\n");
        } else {
            printf("LEFT\n");
        }
    }
}