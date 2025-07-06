// https://cses.fi/problemset/task/1749

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
int n;
int nums[N];
int cnt[N];
int tree[4 * N];
int ans[N];

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = cnt[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int query(int x, int p, int l, int r) {
    if (l == r) {
        tree[p] = 0;
        return nums[l];
    }
    int mid = l + (r - l) / 2;
    int res;
    if (tree[2 * p] >= x) {
        res = query(x, 2 * p, l, mid);
    } else {
        res = query(x - tree[2 * p], 2 * p + 1, mid + 1, r);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        cnt[i]++;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        ans[i] = query(x, 1, 1, n);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}