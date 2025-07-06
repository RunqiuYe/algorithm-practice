// https://cses.fi/problemset/task/1651

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
ll tree[4 * N];
ll dirty[4 * N];

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

ll query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    ll res = 0;
    int mid = l + (r - l) / 2;
    if (dirty[p] != 0) {
        dirty[2 * p] += dirty[p];
        dirty[2 * p + 1] += dirty[p];
        tree[2 * p] += dirty[p] * (mid - l + 1);
        tree[2 * p + 1] += dirty[p] * (r - mid);
        dirty[p] = 0;
    }
    if (L <= mid) {
        res += query(2 * p, l, mid, L, R);
    }
    if (R >= mid + 1) {
        res += query(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

void update(int p, ll x, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        tree[p] += (r - l + 1) * x;
        dirty[p] += x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (dirty[p] != 0 && l != r) {
        dirty[2 * p] += dirty[p];
        dirty[2 * p + 1] += dirty[p];
        tree[2 * p] += dirty[p] * (mid - l + 1);
        tree[2 * p + 1] += dirty[p] * (r - mid);
        dirty[p] = 0;
    }
    if (L <= mid) {
        update(2 * p, x, l, mid, L, R);
    }
    if (R >= mid + 1) {
        update(2 * p + 1, x, mid + 1, r, L, R);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        nums[i] = x;
    }
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int a, b, u;
            scanf("%d %d %d", &a, &b, &u);
            update(1, u, 1, n, a, b);
        } else {
            int k;
            scanf("%d", &k);
            printf("%lld\n", query(1, 1, n, k, k));
        }
    }
    return 0;
}