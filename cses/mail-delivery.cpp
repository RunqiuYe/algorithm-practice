// https://cses.fi/problemset/task/1691/

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

const int N = 1e5 + 5;

int n, m;
set<int> G[N];
int deg[N];
vector<int> path;
bool cycle[N];

// Hierholzer algorithm for Euler's ring
void dfs(int u) {
    while (G[u].size() != 0) {
        auto iter = G[u].begin();
        int v = *iter;
        G[u].erase(iter);
        G[v].erase(u);
        dfs(v);
    }
    path.push_back(u);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].emplace(v);
        G[v].emplace(u);
        deg[u]++;
        deg[v]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 != 0) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }
    dfs(1);
    int k = path.size();

    // graph is not connected
    if (k != m + 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    // output path
    for (int i = k - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    return 0;
}