// // https://cses.fi/problemset/task/3223

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

int n, k;
int nums[N];
int disc[N];
ll ans[N];
int tree[4 * N];

int indexOf(int x) {
    int lo = 1;
    int hi = n + 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (disc[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

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

int main() {
    scanf("%d %d", &n, &k);
    set<int> S;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &nums[i]);
        disc[i] = nums[i];
    }
    sort(disc + 1, disc + n + 1);
    ll inv = 0;
    for (int i = 1; i < k; ++i) {
        int j = indexOf(nums[i]);
        inv += query(1, 1, n, j + 1, n);
        update(1, 1, n, j, 1);
    }
    for (int i = k; i <= n; ++i) {
        int j = indexOf(nums[i]);
        inv += query(1, 1, n, j + 1, n);
        update(1, 1, n, j, 1);

        ans[i] = inv;
        j = indexOf(nums[i - k + 1]);
        inv -= query(1, 1, n, 1, j - 1);
        update(1, 1, n, j, -1);
    }
    for (int i = k; i <= n; ++i) {
        printf("%lld%c", ans[i], " \n"[i == n]);
    }
}