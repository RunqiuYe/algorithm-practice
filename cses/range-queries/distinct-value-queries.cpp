// https://cses.fi/problemset/task/1734

#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int Q = 2e5 + 5;
int nums[N];
int tree[4 * N];
int next_index[N];
array<int, 3> queries[Q];
int ans[N];

int n, q;

void update(int p, int l, int r, int i, int x) {
    if (l == r) {
        tree[p] = x;
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
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
    }

    map<int, int> dict;
    for (int i = n; i >= 1; i--) {
        if (dict.find(nums[i]) != dict.end()) {
            next_index[i] = dict[nums[i]];
        }
        dict[nums[i]] = i;
    }
    for (auto iter = dict.begin(); iter != dict.end(); iter++) {
        int j = iter->second;
        update(1, 1, n, j, 1);
    }

    for (int i = 1; i <= q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        queries[i] = {a, b, i};
    }
    sort(queries + 1, queries + q + 1);

    int lo = 1;  // current left index
    for (int i = 1; i <= q; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        int j = queries[i][2];
        while (lo < a) {
            if (next_index[lo] != 0) {
                update(1, 1, n, lo, 0);
                update(1, 1, n, next_index[lo], 1);
            }
            lo++;
        }
        ans[j] = query(1, 1, n, a, b);
    }
    for (int i = 1; i <= q; i++) {
        printf("%d\n", ans[i]);
    }
}