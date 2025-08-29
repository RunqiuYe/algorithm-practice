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
vector<int> G[N];
int subtree_size[N];
int value[N];
int id[N];
int depth[N];
int par[N];
int heavy_top[N];
int tree[4 * N];
int k = 1;

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
    tree[p] = max(tree[2 * p], tree[2 * p + 1]);
}

int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = l + (r - l) / 2;
    int res = 0;
    if (L <= mid) {
        res = max(res, query(2 * p, l, mid, L, R));
    }
    if (R > mid) {
        res = max(res, query(2 * p + 1, mid + 1, r, L, R));
    }
    return res;
}

// process `subtree_size`, `depth`, `parent` for light-heavy decomposition
void dfs(int x, int p, int dep) {
    subtree_size[x] = 1;
    depth[x] = dep;
    par[x] = p;
    for (int v : G[x]) {
        if (v == p) continue;
        dfs(v, x, dep + 1);
        subtree_size[x] += subtree_size[v];
    }
}

// light-heavy decomposition, process `id` and `heavy-top`
// this ensures that heavy path are consecutive
void dfs_lhd(int x, int p, int top) {
    heavy_top[x] = top;
    id[x] = k;
    update(1, 1, n, k, value[x]);
    k++;

    // find heavy child
    int heavy_size = -1;
    int heavy_child = -1;
    for (int v : G[x]) {
        if (v == p) continue;
        if (subtree_size[v] > heavy_size) {
            heavy_size = subtree_size[v];
            heavy_child = v;
        }
    }
    if (heavy_child == -1) return;

    dfs_lhd(heavy_child, x, top);
    for (int v : G[x]) {
        if (v == p || v == heavy_child) continue;
        dfs_lhd(v, x, v);
    }
}

int solve(int x, int y) {
    int res = 0;
    while (heavy_top[x] != heavy_top[y]) {
        if (depth[heavy_top[x]] < depth[heavy_top[y]]) {
            swap(x, y);
        }
        res = max(res, query(1, 1, n, id[heavy_top[x]], id[x]));
        x = par[heavy_top[x]];
    }
    if (depth[x] > depth[y]) {
        swap(x, y);
    }
    res = max(res, query(1, 1, n, id[x], id[y]));
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 1, 1);
    dfs_lhd(1, 1, 1);

    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            update(1, 1, n, id[s], x);
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", solve(a, b));
        }
    }
}