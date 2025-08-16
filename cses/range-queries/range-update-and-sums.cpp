// https://cses.fi/problemset/task/1735

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

const int N = 2e5 + 5;

ll tree[4 * N];
ll setm[4 * N];
ll incm[4 * N];
ll nums[N];

int n, k;

void apply_set(int p, int l, int r, ll x) {
    tree[p] = x * (r - l + 1);
    setm[p] = x;
    incm[p] = 0;
}

void apply_inc(int p, int l, int r, ll x) {
    tree[p] += x * (r - l + 1);
    if (setm[p] != 0) {
        setm[p] += x;
    } else {
        incm[p] += x;
    }
}

void push_down(int p, int l, int r) {
    int mid = l + (r - l) / 2;
    if (setm[p] != 0) {
        apply_set(2 * p, l, mid, setm[p]);
        apply_set(2 * p + 1, mid + 1, r, setm[p]);
        setm[p] = 0;
        incm[p] = 0;
    }
    if (incm[p] != 0) {
        apply_inc(2 * p, l, mid, incm[p]);
        apply_inc(2 * p + 1, mid + 1, r, incm[p]);
        incm[p] = 0;
    }
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = nums[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void inc_update(int p, int l, int r, int L, int R, ll x) {
    if (L <= l && r <= R) {
        apply_inc(p, l, r, x);
        return;
    }
    int mid = l + (r - l) / 2;
    push_down(p, l, r);
    if (L <= mid) {
        inc_update(2 * p, l, mid, L, R, x);
    }
    if (R > mid) {
        inc_update(2 * p + 1, mid + 1, r, L, R, x);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void set_update(int p, int l, int r, int L, int R, ll x) {
    if (L <= l && r <= R) {
        apply_set(p, l, r, x);
        return;
    }
    int mid = l + (r - l) / 2;
    push_down(p, l, r);
    if (L <= mid) {
        set_update(2 * p, l, mid, L, R, x);
    }
    if (R > mid) {
        set_update(2 * p + 1, mid + 1, r, L, R, x);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

ll query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    ll res = 0;
    int mid = l + (r - l) / 2;
    push_down(p, l, r);
    if (L <= mid) {
        res += query(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        res += query(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nums[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= k; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int a, b;
            ll x;
            scanf("%d %d %lld", &a, &b, &x);
            inc_update(1, 1, n, a, b, x);
        } else if (op == 2) {
            int a, b;
            ll x;
            scanf("%d %d %lld", &a, &b, &x);
            set_update(1, 1, n, a, b, x);
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%lld\n", query(1, 1, n, a, b));
        }
    }
}