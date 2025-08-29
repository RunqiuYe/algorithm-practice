// https://cses.fi/problemset/task/3163

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

int nums[N];
int disc[N];

pair<int, int> ql[N];  // (endpoint, query index)
pair<int, int> qr[N];
pair<int, int> ranges[N];
int ans[N];

int tree[4 * N];

void update(int p, int l, int r, int i, int x) {
    if (l == r) {
        tree[p] += x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (i <= mid) {
        update(2 * p, l, mid, i, x);
    } else {
        update(2 * p + 1, mid + 1, r, i, x);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int query(int p, int l, int r, int L, int R) {
    if (L > R) {
        return 0;
    }
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = l + (r - l) / 2;
    int res = 0;
    if (L <= mid) {
        res += query(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        res += query(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

// first index >= x
int indexOf(int x) {
    int lo = 1;
    int hi = n + 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (disc[mid] >= x) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        disc[i] = nums[i];
    }
    sort(disc + 1, disc + 1 + n);

    for (int i = 1; i <= q; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        ql[i] = {a - 1, i};
        qr[i] = {b, i};
        ranges[i] = {c, d};
    }
    sort(ql + 1, ql + q + 1);
    sort(qr + 1, qr + q + 1);

    int lidx = 1;
    int ridx = 1;
    for (int idx = 1; idx <= n; idx++) {
        int k = indexOf(nums[idx]);
        update(1, 1, n, k, 1);

        int i, c, d, l, r;
        for (; ql[lidx].first <= idx && lidx <= q; lidx++) {
            if (ql[lidx].first == 0) {
                continue;
            }
            i = ql[lidx].second;
            c = ranges[i].first;
            d = ranges[i].second;
            l = indexOf(c);
            r = indexOf(d);
            if (disc[r] > d) {
                r--;
            }
            ans[i] -= query(1, 1, n, l, r);
        }

        for (; qr[ridx].first <= idx && ridx <= q; ridx++) {
            i = qr[ridx].second;
            c = ranges[i].first;
            d = ranges[i].second;
            l = indexOf(c);
            r = indexOf(d);
            if (disc[r] > d) {
                r--;
            }
            ans[i] += query(1, 1, n, l, r);
        }
    }
    for (int i = 1; i <= q; i++) {
        printf("%d\n", ans[i]);
    }
}