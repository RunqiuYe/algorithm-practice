// https://cses.fi/problemset/task/2416

#include <algorithm>
#include <array>
#include <bit>
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

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

int n, q;
ll nums[N];
ll prefix[N];
ll ans[N];
ll sum_tree[4 * N];
ll max_tree[4 * N];
ll dirty[4 * N];
vector<pair<int, int>> queries[N];

void push(int p, int l, int r) {
    int mid = l + (r - l) / 2;
    if (dirty[p] != 0) {
        sum_tree[2 * p] = dirty[p] * (mid - l + 1);
        sum_tree[2 * p + 1] = dirty[p] * (r - mid);
        max_tree[2 * p] = dirty[p];
        max_tree[2 * p + 1] = dirty[p];
        dirty[2 * p] = dirty[p];
        dirty[2 * p + 1] = dirty[p];
    }
}

void pull(int p) {
    sum_tree[p] = sum_tree[2 * p] + sum_tree[2 * p + 1];
    max_tree[p] = max(max_tree[2 * p], max_tree[2 * p + 1]);
}

int query_greater(int p, int l, int r, int L, int R, ll x) {
    if (l == r) {
        return l;
    }
    push(p, l, r);
    int mid = l + (r - l) / 2;
    if (L <= mid && max_tree[2 * p] >= x) {
        return query_greater(2 * p, l, mid, L, R, x);
    } else {
        return query_greater(2 * p + 1, mid + 1, r, L, R, x);
    }
}

void update(int p, int l, int r, int L, int R, ll x) {
    if (L > R) return;
    if (L <= l && r <= R) {
        sum_tree[p] = x * (r - l + 1);
        max_tree[p] = x;
        dirty[p] = x;
        return;
    }
    push(p, l, r);
    int mid = l + (r - l) / 2;
    if (L <= mid) {
        update(2 * p, l, mid, L, R, x);
    }
    if (R > mid) {
        update(2 * p + 1, mid + 1, r, L, R, x);
    }
    pull(p);
}

ll query_sum(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum_tree[p];
    }
    push(p, l, r);
    int mid = l + (r - l) / 2;
    ll res = 0;
    if (L <= mid) {
        res += query_sum(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        res += query_sum(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nums[i]);
    }
    // calculate prefix sum for queries
    for (int i = 1; i <= n; i++) {
        prefix[i] = nums[i] + prefix[i - 1];
    }

    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        queries[l].push_back({r, i});
    }
    // process queries from right to left, update segment tree
    for (auto q : queries[n]) {
        ans[q.second] = 0;
    }
    update(1, 1, n, n, n, nums[n]);

    for (int l = n - 1; l >= 1; l--) {
        ll x = nums[l];

        // find first index greater than or equal to x
        int bound =
            max_tree[1] < x ? (n + 1) : query_greater(1, 1, n, l + 1, n, x);
        update(1, 1, n, l, l, x);
        update(1, 1, n, l + 1, bound - 1, x);
        for (auto q : queries[l]) {
            int r = q.first;
            int j = q.second;
            ans[j] = query_sum(1, 1, n, l, r) - (prefix[r] - prefix[l - 1]);
        }
    }
    for (int i = 1; i <= q; i++) {
        printf("%lld\n", ans[i]);
    }
}