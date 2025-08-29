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
int n, q;
int k = 1;
vector<int> G[N];
ll value[N];

ll traversal_value[N];
int traversal_index[N];
int subtree_size[N];

ll tree[4 * N];
ll dirty[4 * N];

void dfs(int x, int p) {
    traversal_index[x] = k;
    traversal_value[k] = traversal_value[traversal_index[p]] + value[x];
    subtree_size[k] += 1;
    k++;
    for (int v : G[x]) {
        if (v == p) continue;
        dfs(v, x);
        subtree_size[traversal_index[x]] += subtree_size[traversal_index[v]];
    }
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = traversal_value[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void update(int p, int l, int r, int L, int R, int x) {
    if (L <= l && r <= R) {
        tree[p] += x * (r - l + 1);
        dirty[p] += x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (dirty[p] != 0 && l != r) {
        tree[2 * p] += dirty[p] * (mid - l + 1);
        tree[2 * p + 1] += dirty[p] * (r - mid);
        dirty[2 * p] += dirty[p];
        dirty[2 * p + 1] += dirty[p];
        dirty[p] = 0;
    }
    if (L <= mid) {
        update(2 * p, l, mid, L, R, x);
    }
    if (R > mid) {
        update(2 * p + 1, mid + 1, r, L, R, x);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

ll query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = l + (r - l) / 2;
    if (dirty[p] != 0) {
        tree[2 * p] += dirty[p] * (mid - l + 1);
        tree[2 * p + 1] += dirty[p] * (r - mid);
        dirty[2 * p] += dirty[p];
        dirty[2 * p + 1] += dirty[p];
        dirty[p] = 0;
    }
    ll res = 0;
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
        scanf("%lld", &value[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            int j = traversal_index[s];
            ll diff = x - value[s];
            value[s] = x;
            update(1, 1, n, j, j + subtree_size[j] - 1, diff);
        } else {
            int s;
            scanf("%d", &s);
            int j = traversal_index[s];
            printf("%lld\n", query(1, 1, n, j, j));
        }
    }
}