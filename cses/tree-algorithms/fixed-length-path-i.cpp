// https://cses.fi/problemset/task/2080

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
vector<int> G[N];
int path_cnt[N];
int subtree_size[N];
bool vis[N];        // mark nodes already used as centriod
int max_depth = 0;  // maximum depth in subtree
ll ans = 0;

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
    if (depth > k) return;
    max_depth = max(max_depth, depth);
    if (flag) {
        ans += path_cnt[k - depth];
    } else {
        path_cnt[depth]++;
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
    fill(path_cnt + 1, path_cnt + max_depth + 1, 0);
    for (int v : G[centroid]) {
        if (vis[v]) continue;
        solve(v);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    path_cnt[0] = 1;
    solve(1);
    printf("%lld\n", ans);
}