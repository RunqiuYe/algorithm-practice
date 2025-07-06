// https://cses.fi/problemset/task/2166

#include <cstring>
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

const int N = 2e5 + 5;
int n, q;
ll nums[N];
pair<ll, ll> tree[4 * N];

pair<ll, ll> f(pair<ll, ll> lc, pair<ll, ll> rc) {
    ll sum = lc.first + rc.first;
    ll max_prefix = max(lc.second, lc.first + rc.second);
    return {sum, max_prefix};
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = {nums[l], max(0LL, nums[l])};
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p] = f(tree[2 * p], tree[2 * p + 1]);
}

void update(int p, int l, int r, int k, ll u) {
    if (l == r) {
        tree[p] = {u, max(0LL, u)};
        return;
    }
    int mid = l + (r - l) / 2;
    if (k <= mid) {
        update(2 * p, l, mid, k, u);
    } else {
        update(2 * p + 1, mid + 1, r, k, u);
    }
    tree[p] = f(tree[2 * p], tree[2 * p + 1]);
}

pair<ll, ll> query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[p];
    int mid = l + (r - l) / 2;
    pair<ll, ll> lc = {0, 0};
    pair<ll, ll> rc = {0, 0};
    if (L <= mid) {
        lc = query(p * 2, l, mid, L, R);
    }
    if (R >= mid + 1) {
        rc = query(p * 2 + 1, mid + 1, r, L, R);
    }
    return f(lc, rc);
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nums[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int k;
            ll u;
            scanf("%d %lld", &k, &u);
            update(1, 1, n, k, u);
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%lld\n", query(1, 1, n, a, b).second);
        }
    }
    return 0;
}