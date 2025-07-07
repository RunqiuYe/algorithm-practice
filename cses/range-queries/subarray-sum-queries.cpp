// https://cses.fi/problemset/task/1190

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
const int INT_INF = 0x7f7f7f7f;
int n, q;
ll nums[N];
vector<ll> tree[4 * N];

vector<ll> f(vector<ll> lc, vector<ll> rc) {
    ll s = lc[3] + rc[3];
    ll pre = max(lc[1], lc[3] + rc[1]);
    ll suf = max(rc[2], lc[2] + rc[3]);
    ll ans = max(lc[0], max(rc[0], lc[2] + rc[1]));
    return {ans, pre, suf, s};
}

vector<ll> singelton(ll x) {
    ll u = max(0LL, x);
    return {u, u, u, x};
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = singelton(nums[l]);
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p] = f(tree[2 * p], tree[2 * p + 1]);
}

void update(int x, int k, int p, int l, int r) {
    if (l == r) {
        tree[p] = singelton(x);
        return;
    }
    int mid = (r - l) / 2 + l;
    if (k <= mid) {
        update(x, k, 2 * p, l, mid);
    } else {
        update(x, k, 2 * p + 1, mid + 1, r);
    }
    tree[p] = f(tree[2 * p], tree[2 * p + 1]);
}

vector<ll> query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = (r - l) / 2 + l;
    vector<ll> lc = {0, 0, 0, 0};
    vector<ll> rc = {0, 0, 0, 0};
    if (L <= mid) {
        lc = query(2 * p, l, mid, L, R);
    }
    if (R >= mid + 1) {
        rc = query(2 * p + 1, mid + 1, r, L, R);
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
        int k;
        ll x;
        scanf("%d %lld", &k, &x);
        update(x, k, 1, 1, n);
        printf("%lld\n", tree[1][0]);
    }
    return 0;
}