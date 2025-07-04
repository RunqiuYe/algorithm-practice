// https://cses.fi/problemset/task/1751/

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <cstring>
#include <queue>

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;

int n;
int G[N];
bool vis[N];
bool cycle[N];
int ans[N];
bool scc_vis[N];
vector<int> inc_finish;

void dfs(int u) {
    vis[u] = true;
    int v = G[u];
    if (!vis[v]) {
        dfs(v);
    }
    inc_finish.push_back(u);
}

void dfs_transpose(int u, vector<int>& scc, vector<vector<int>>& transpose) {
    vis[u] = true;
    cycle[u] = true;
    for (int v : transpose[u]) {
        if (cycle[v] || vis[v]) continue;
        dfs_transpose(v, scc, transpose);
    }
    scc.push_back(u);
    cycle[u] = false;
}

void dfs_scc(int i) {
    if (scc_vis[i]) return;
    scc_vis[i] = true;
    dfs_scc(G[i]);
    ans[i] = ans[G[i]] + 1;
}

int main() {
    scanf("%d", &n); 
    vector<vector<int>> transpose(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &G[i]);
        transpose[G[i]].push_back(i);
    }
    // first dfs
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    // second dfs for SCC
    memset(vis, 0, sizeof(vis));
    for (int i = n - 1; i >= 0; i--) {
        int u = inc_finish[i];
        vector<int> scc;
        if (!vis[u]) {
            dfs_transpose(u, scc, transpose);
            if (scc.size() != 1) {
                for (int x : scc) {
                    ans[x] = scc.size();
                    scc_vis[x] = true;
                }
            }
        }
    }
    // final dfs for answer
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0) {
            dfs_scc(i);
        }
    }
    // print answer
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}