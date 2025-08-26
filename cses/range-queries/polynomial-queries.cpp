// https://cses.fi/problemset/task/1736

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

const static int N = 2e5 + 5;
int n, q;
int a[N];
int d[N];

// segment tree for d[i]
ll tree1[4 * N];
ll mark1[4 * N];

// segment tree for d[i] * i
ll tree2[4 * N];
ll mark2[4 * N];

// gives l + (l + 1) + ... + r
ll f(int l, int r) { return ((ll)l + r) * ((ll)r - l + 1) / 2; }

void pull(int p) {
    tree1[p] = tree1[2 * p] + tree1[2 * p + 1];
    tree2[p] = tree2[2 * p] + tree2[2 * p + 1];
}

void push(int p, int l, int r) {
    int mid = l + (r - l) / 2;
    if (mark1[p] != 0) {
        tree1[2 * p] += (mid - l + 1) * mark1[p];
        tree1[2 * p + 1] += (r - mid) * mark1[p];
        mark1[2 * p] += mark1[p];
        mark1[2 * p + 1] += mark1[p];
        mark1[p] = 0;
    }
    if (mark2[p] != 0) {
        tree2[2 * p] += f(l, mid) * mark2[p];
        tree2[2 * p + 1] += f(mid + 1, r) * mark2[p];
        mark2[2 * p] += mark2[p];
        mark2[2 * p + 1] += mark2[p];
        mark2[p] = 0;
    }
}

void build(int p, int l, int r) {
    if (l == r) {
        tree1[p] = d[l];
        tree2[p] = (ll)d[l] * l;
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    pull(p);
}

void update(int p, int l, int r, int L, int R, ll x) {
    if (L <= l && r <= R) {
        tree1[p] += (r - l + 1) * x;
        mark1[p]++;
        tree2[p] += f(l, r) * x;
        mark2[p]++;
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

pair<ll, ll> query(int p, int l, int r, int L, int R) {
    if (R < L) {
        return {0, 0};
    }
    if (L <= l && r <= R) {
        return {tree1[p], tree2[p]};
    }
    push(p, l, r);
    pair<ll, ll> res = {0, 0};
    int mid = l + (r - l) / 2;
    if (L <= mid) {
        pair<ll, ll> ansl = query(2 * p, l, mid, L, R);
        res.first += ansl.first;
        res.second += ansl.second;
    }
    if (R > mid) {
        pair<ll, ll> ansr = query(2 * p + 1, mid + 1, r, L, R);
        res.first += ansr.first;
        res.second += ansr.second;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        d[i] = a[i] - a[i - 1];
    }
    build(1, 1, n);

    for (int i = 1; i <= q; i++) {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);
        if (op == 1) {
            update(1, 1, n, a, b, 1);
            if (b != n) {
                update(1, 1, n, b + 1, b + 1, -(b - a + 1));
            }
        } else {
            pair<ll, ll> ansr = query(1, 1, n, 1, b);
            pair<ll, ll> ansl = query(1, 1, n, 1, a - 1);
            printf("%lld\n", ansr.first * (b + 1) - ansl.first * a -
                                 ansr.second + ansl.second);
        }
    }
}