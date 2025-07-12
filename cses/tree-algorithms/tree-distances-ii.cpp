// https://cses.fi/problemset/task/1133

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
vector<int> G[N];
vector<ll> branch_dist[N];
int size[N];
ll dist[N];
ll ans[N];

void dfs(int x, int p) {
    ll res = 0LL;
    int children = 0;
    for (int v : G[x]) {
        if (v == p) continue;
        dfs(v, x);
        res += dist[v] + size[v];
        children += size[v];
    }
    size[x] = children + 1;
    dist[x] = res;
}

void dfs_ans(int x, int p, ll dist_above, int size_above) {
    ans[x] = dist[x] + dist_above + size_above;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == p) continue;
        ll d = dist[x] - dist[v] - size[v] + dist_above + size_above;
        ll s = size[x] - size[v] + size_above;
        dfs_ans(v, x, d, s);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf(" %d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    dfs_ans(1, -1, 0, 0);
    for (int i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
}