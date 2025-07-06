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
int price[N];
int tree[4 * N][2];
int ans[N];

void build(int p, int l, int r) {
    if (l == r) {
        tree[p][0] = price[l] + l;
        tree[p][1] = price[l] + n - l + 1;
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p][0] = min(tree[2 * p][0], tree[2 * p + 1][0]);
    tree[p][1] = min(tree[2 * p][1], tree[2 * p + 1][1]);
}

void update(int x, int k, int p, int l, int r) {
    if (l == r) {
        tree[p][0] = x + k;
        tree[p][1] = x + n - k + 1;
        return;
    }
    int mid = (r - l) / 2 + l;
    if (k <= mid) {
        update(x, k, 2 * p, l, mid);
    } else {
        update(x, k, 2 * p + 1, mid + 1, r);
    }
    tree[p][0] = min(tree[2 * p][0], tree[2 * p + 1][0]);
    tree[p][1] = min(tree[2 * p][1], tree[2 * p + 1][1]);
}

int query(int p, int l, int r, int L, int R, int left_side) {
    if (L <= l && r <= R) {
        return tree[p][left_side];
    }
    int mid = (r - l) / 2 + l;
    int res = INT_INF;
    if (L <= mid) {
        res = min(res, query(2 * p, l, mid, L, R, left_side));
    }
    if (R >= mid + 1) {
        res = min(res, query(2 * p + 1, mid + 1, r, L, R, left_side));
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int k, x;
            scanf("%d %d", &k, &x);
            update(x, k, 1, 1, n);
        } else {
            int k;
            scanf("%d", &k);
            int lp = query(1, 1, n, 1, k, 1);
            int rp = query(1, 1, n, k, n, 0);
            printf("%d\n", min(rp - k, lp - (n - k + 1)));
        }
    }
    return 0;
}