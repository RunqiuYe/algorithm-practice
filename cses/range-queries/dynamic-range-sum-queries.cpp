// https://cses.fi/problemset/task/1648

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
ll tree[4 * N];
int ans[N];

void update(ll x, int i, int index, int l, int r) {
    if (l == r) {
        tree[index] = x;
        return;
    }
    int mid = (r - l) / 2 + l;
    if (i <= mid) {
        update(x, i, 2 * index, l, mid);
    } else {
        update(x, i, 2 * index + 1, mid + 1, r);
    }
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

ll query(int index, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[index];
    }
    int mid = (r - l) / 2 + l;
    ll res = 0;
    if (L <= mid) {
        res += query(2 * index, l, mid, L, R);
    }
    if (R >= mid + 1) {
        res += query(2 * index + 1, mid + 1, r, L, R);
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        ll x;
        scanf("%lld", &x);
        update(x, i, 1, 1, n);
    }
    for (int i = 0; i < q; i++) {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);
        if (op == 1) {
            update(b, a, 1, 1, n);
        } else {
            printf("%lld\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}