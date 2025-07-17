// https://cses.fi/problemset/task/2081

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
int n, k1, k2;
vector<int> G[N];

ll seg_tree[4 * N];
ll path_cnt[N];
int subtree_size[N];
bool vis[N];        // mark nodes already used as centriod
int max_depth = 0;  // maximum depth in subtree
ll ans = 0;

void update(int p, int l, int r, int i, int x) {
    if (l == r) {
        seg_tree[p] += x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (i <= mid) {
        update(2 * p, l, mid, i, x);
    } else {
        update(2 * p + 1, mid + 1, r, i, x);
    }
    seg_tree[p] = seg_tree[2 * p] + seg_tree[2 * p + 1];
}

ll query(int p, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (L <= l && r <= R) {
        return seg_tree[p];
    }
    int mid = l + (r - l) / 2;
    ll res = 0;
    if (L <= mid) {
        res += query(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        res += query(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

// get size of subtree and update `subtree_size` array
int get_size(int u, int p) {
    subtree_size[u] = 1;
    for (int v : G[u]) {
        if (v == p || vis[v]) continue;
        get_size(v, u);
        subtree_size[u] += subtree_size[v];
    }
    return subtree_size[u];
}

// find a centroid in the subtree, `m` is size of subtree
int find_centroid(int u, int p, int m) {
    for (int v : G[u]) {
        if (v == p || vis[v] || subtree_size[v] <= m / 2) continue;
        return find_centroid(v, u, m);
    }
    return u;
}

// dfs in the subtree
// if flag, update answer, otherwise update path_cnt.
void dfs(int u, int p, int depth, bool flag) {
    if (depth > k2) return;
    max_depth = max(max_depth, depth);
    if (flag) {
        ans += query(1, 1, n, max(1, k1 - depth), k2 - depth);
        if (depth >= k1) ans++;
    } else {
        path_cnt[depth]++;
        update(1, 1, n, depth, 1);
    }
    for (int v : G[u]) {
        if (v == p || vis[v]) continue;
        dfs(v, u, depth + 1, flag);
    }
}

// get the number of path with length k through centroid
void solve(int u) {
    int m = get_size(u, -1);
    int centroid = find_centroid(u, -1, m);
    vis[centroid] = true;
    max_depth = 0;
    for (int v : G[centroid]) {
        if (vis[v]) continue;
        dfs(v, centroid, 1, true);
        dfs(v, centroid, 1, false);
    }
    for (int i = 1; i <= max_depth; i++) {
        update(1, 1, n, i, -path_cnt[i]);
        path_cnt[i] = 0;
    }
    for (int v : G[centroid]) {
        if (vis[v]) continue;
        solve(v);
    }
}

int main() {
    scanf("%d %d %d", &n, &k1, &k2);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    solve(1);
    printf("%lld\n", ans);
}